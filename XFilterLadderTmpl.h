
#ifndef __XFilterLadderTmpl_H__
#define __XFilterLadderTmpl_H__

//#include "PerformanceCounterScope.h"
#include "XFilterLadder.h"

// Assumed headers:
// SIMD_IO type
// XDSP: ProcessGlobals, Node, Node::Voice

template <class SIMD_IO> class XFilterLadder::Worker : public SIMD_IO
{
public:

	// Import the typedefs and usings from mathops base class
    typedef typename SIMD_IO::vec_float vec_float;
    typedef typename SIMD_IO::SampleInputStream SampleInputStream;
    typedef typename SIMD_IO::SampleOutputStream SampleOutputStream;
    typedef SIMD_IO SimdAdapter;
    
    using SIMD_IO::mulps;
    using SIMD_IO::addps;
    using SIMD_IO::subps;
    using SIMD_IO::maxps;
    using SIMD_IO::minps;
    using SIMD_IO::fma;
    using SIMD_IO::clipps;
    using SIMD_IO::absps;
    using SIMD_IO::set1ps;
    using SIMD_IO::zerops;
    using SIMD_IO::divps;
    using SIMD_IO::rcpps;
    using SIMD_IO::fpow2ps_poly4;
    using SIMD_IO::fpow2ps_poly2;
    
    class VECPRE_NATIVE VFastRand
    {
    public:
        vforceinline VFastRand()
        {
            m_seed[0] = (int32)(((size_t)(void*)(this)));
            // use our mem address as a crude seed. no system calls needed. will truncate on x64 systems, doesnt matter.
        };
        
        vforceinline vec_float DISPATCH_ATTRIBUTE_TAG white1()
        {
            uint32 l_seed = m_seed[0];
            l_seed *= 196314163;
            l_seed += 907633515;
            uint32 _white = (l_seed >> 9) | 0x40000000;
            float fwhite = (*(float*)&_white);
            m_seed[0] = l_seed;
            return set1ps(fwhite - 3.f);
        };
        
        uint32 m_seed[8];
    };
    
    static void ProcessBuffer (const XDSP::ProcessGlobals& process_globals, SIMD_IO& voices, const XFilterLadder::Node::ProcessAttributes& pa)
	{
	//	PerformanceCounterScope perfScope(__FUNCTION__);

		//static
		const int32 block_length = process_globals.block_length;
        static VECPRE_NATIVE VFastRand randwhite VECPOST_NATIVE;

        // vec_float;
        //test1; // = set1ps(2.f);
        //const float drv       = 0.5f*VConvertAmpLog::ConvertToUnits (*ControlIn (C_DRIVE));
		//        return max0f (fastpow2f (c_clipf (10.0f, value)) - db_min);     //         static const float db_min = 0.01636775478443233f;
		vec_float drv = mulps(set1ps(0.5f), maxps(zerops(), subps(fpow2ps_poly2(minps(voices.controlport_gather(C_DRIVE), set1ps(10.f))), set1ps(0.01636775478443233f))));
		vec_float inv_drv = divps(set1ps(1.f), drv);
		inv_drv = minps(inv_drv, set1ps(8.f)); // limit compensator to +18dB
		//const float ppp       = *ControlIn (C_PITCH);
		//const float freq      = c_clipf (-12.0f, 12.0f, ppp);
		vec_float freq = minps( maxps(voices.controlport_gather(C_PITCH), set1ps(-12.f)), set1ps(12.f));

		vec_float res  = voices.controlport_gather(C_RES);
		vec_float uncorrh = mulps(set1ps(process_globals.uncorr), set1ps(0.03f));

		vec_float bleed = voices.controlport_gather(C_BLEED);
		const float bleed_a = 0.f; // bleed.horizontal_add();
		bleed = mulps(bleed, mulps(bleed, bleed));
		
		//const float analog_noise_lev = process_globals.analog_noise[m_id];
		vec_float analog_noise_lev = set1ps(process_globals.analog_noise[0] ) * 0.25f ;	// assume same for all voices.
        vec_float analog_noise_lev_2 = set1ps(process_globals.analog_noise[0] ) * 0.01f ;	// assume same for all voices.

		const float *hum_in = process_globals.hum;

		// Horrible. Should use branchless LUT here.
		//const int32   mode0     = VConvert::round (clip0f (kNumModes1, *ControlIn (C_MODE)));
		const int32 mixtaps = 5;

		vec_float xmix_t[5]; // Target values (from vector values)
		vec_float xmix_m[5]; // Member values (from current state)
		vec_float xmix_d[5]; // difference value


        
        xmix_t[0] = set1ps(1.f);
        xmix_t[1] = set1ps(0.f);
        xmix_t[2] = set1ps(0.f);
        xmix_t[3] = set1ps(0.f);
        xmix_t[4] = set1ps(0.f);

		//	const float tap_gain = 0.5f; //2.f;
		for (int32 m = 0; m < 5; m++)
		{
			xmix_m[m] = voices.member_gather(my_offsetof(m_xmix) + (m * sizeof(float)));
			xmix_d[m] = (xmix_t[m] - xmix_m[m]) * set1ps(process_globals.block_length_norm_inv * 0.1f);
		}

		vec_float tsr = mulps(set1ps(process_globals.tune), set1ps(process_globals.sample_rate_inv));

		//const float nf1 = c_clipf (0.0f, 1.0f, process_globals.tune * process_globals.sample_rate_inv * fastpow2f (freq));
		vec_float nf1 = maxps(zerops(), minps(set1ps(1.f), mulps(tsr, fpow2ps_poly4(freq))));
		// const float nq = c_clipf (0.0f, 32.0f, 4.03f*res);
		vec_float nq = maxps(zerops(), minps(set1ps(32.f), mulps(res, set1ps(4.03f))));

		//const float f1_inc = (nf1-m_f1)*process_globals.block_length_inv;
		//const float qinc = (nq - m_q)*process_globals.block_length_inv;
		vec_float f1 = voices.member_gather(my_offsetof(m_f1));
		vec_float q =  voices.member_gather(my_offsetof(m_q));
		vec_float g1p = voices.member_gather(my_offsetof(m_g1));
		vec_float g1_inv = voices.member_gather(my_offsetof(m_g1_inv));

		vec_float  blinv  = set1ps (process_globals.block_length_norm_inv);
		vec_float f1_inc =  mulps  (subps (nf1, f1), blinv);
		vec_float  q_inc  =  mulps  (subps (nq, q), blinv);
		vec_float g1_inc = mulps(subps(drv, g1p), blinv);
		vec_float g1_inv_inc = mulps(subps(inv_drv, g1_inv), blinv);

		vec_float g0 = set1ps (0.74f);
		vec_float g1 = set1ps (0.26f);

		// vec_float  n = mulps(rand[0].white1(),set1ps (1e-10f));
		vec_float n = set1ps(0.f); // was 1e-10f, but SSE shouldnt need antidenorm.

		//const float dc_f = process_globals.filtg_2_5;
		vec_float  dc_f = set1ps (process_globals.filtg_2_5);
		vec_float dcv = voices.member_gather(my_offsetof(m_dc_f));

		vec_float  y0 =  addps(n, voices.member_gather(my_offsetof(m_y[0])));
		vec_float  y1 =  addps(n, voices.member_gather(my_offsetof(m_y[1])));
		vec_float  y2 =  addps(n, voices.member_gather(my_offsetof(m_y[2])));
		vec_float  y3 =  addps(n, voices.member_gather(my_offsetof(m_y[3])));
		vec_float  y4 =  addps(n, voices.member_gather(my_offsetof(m_y[4])));
		vec_float  in_lp =  addps(n, voices.member_gather(my_offsetof(m_in_lp)));
		vec_float  out_lp = addps(n, voices.member_gather(my_offsetof(m_out_lp)));
		vec_float  limit_f =addps(n, voices.member_gather(my_offsetof(m_limit)));

		//const float humfm = 0.025f*srscale;
		const vec_float  humfm = mulps(set1ps (0.025f), set1ps(process_globals.srscale));
		const vec_float  ptpxb = set1ps (12.00000000000000f);
		const vec_float  ptnxb = set1ps (-12.00000000000000f);
		const float ptxs = 0.08333333333333333f;
		const vec_float  ptx3 = set1ps (-0.006944444444444444f);
		const vec_float  ptx4 = set1ps (0.0002893518518518519f);

		const vec_float pk0 = set1ps(0.991549f);
		const vec_float pk1 = set1ps(0.111105f);
		const vec_float pk2 = set1ps(-0.131474f);
		const vec_float pk3 = set1ps(0.393442f);
        
        SampleInputStream instream = voices.getInputStream(0);
        SampleOutputStream outstream = voices.getOutputStream(0);

		for (int32 t=0; t<block_length; t++)
		{
			f1 = addps (f1, f1_inc);        //f1 += f1_inc;       
			q = addps (q, q_inc);		        //q += q_inc;
			g1p = addps(g1p, g1_inc);
			g1_inv = addps(g1_inv, g1_inv_inc);

			//        vec_float  rg0 = { set1ps (rand[0].gauss4 (uncorrh)) };
			//        vec_float  rg1 = { set1ps (rand[1].gauss4 (uncorrh)) };
			vec_float rg0 = mulps(randwhite.white1(), uncorrh);
			vec_float rg1 = mulps(randwhite.white1(), uncorrh);
			vec_float humhpin = mulps(set1ps (hum_in[t]), 2.f);
			//const float hm1 = clipf (analog_noise_lev * (hum_in[t] + m_randh1.gauss4 (uncorrh)));
			vec_float hm1 = mulps (analog_noise_lev, addps (humhpin, rg0));       
			//const float hm2 = clipf (analog_noise_lev * (hum_in[t] + m_randh2.gauss4 (uncorrh)));
			vec_float hm2 = mulps (analog_noise_lev, addps (humhpin, rg1));        
			//const float moogf = 1.0f - fastexpf (-pi2f()*clip0f (0.2f, f1 + humfm*hm2));
			vec_float mf = addps (f1, mulps (humfm, hm2));

//			vec_float rg2 =  mulps(rand[2].white1(), set1ps (0.0001f));
//			mf = addps(mf, rg2);
			mf = fma(mf, randwhite.white1(), analog_noise_lev_2 + set1ps(0.000001f));
			// mf = subps(mf, set1ps(0.00005f));

			//	const vec128m npi2expm = (-2.0f*3.14159265358979323846264338328f*1.4426950408889634073599246810019f) 
			vec_float  expmfin = mulps (set1ps (-2.0f*3.14159265358979323846264338328f*1.4426950408889634073599246810019f)  ,  maxps (set1ps(0.f), minps (set1ps(0.2f), mf)));        
			//vec_float  expmfout = { _mm_exp_ps (expmfin.m) };
			vec_float  expmfout = fpow2ps_poly4 (expmfin) ;
			vec_float  moogf = subps (set1ps (1.0f), expmfout);

			// Filter FMA: FMA(constant, a*b)

			//const float g = moogf*(pf[0] + moogf*(pf[1] + moogf*(pf[2] + moogf*(pf[3]))));
			//const float g = moogf*(FMA(pf[0], moogf, FMA(pf[1], moogf, FMA (pf[2],  moogf, pf[3]))));
//			vec_float  g = mulps(moogf, addps(pk0, mulps(moogf, addps(pk1, mulps(moogf, addps(pk2, mulps(moogf, pk3)))))));
			const vec_float  g = mulps(moogf, fma(pk0, moogf, fma(pk1, moogf, fma(pk2, moogf, pk3))));
//const float k =     q*(pk[0] + moogf*(pk[1] + moogf*(pk[2] + moogf*(pk[3]))));
			//const float k =  q * (FMA(pk[0], moogf, FMA(pk[1], moogf, FMA (pk[2],  moogf, pk[3]))));
			vec_float  k = mulps(q, fma(set1ps(1.00175f), moogf, fma(set1ps(-0.0635353f), moogf, fma(set1ps(-0.0408209f), moogf, set1ps(-0.22f)))));

			//const float i = drv* (in[t] + hm2);
            vec_float it;
            instream >> it; // Read a group of samples

			vec_float  inpt = mulps (g1p, addps (it, hm2));


			// feedback section -- custom clipper algorithm, tanh approximation with bias and a discontinuity around zero
			vec_float clipsignal = mulps (k, y4);


			const float SH101FILTER_GAIN = 0.4f; // 0.25f;
			const float SH101FILTER_GAIN_INV = 2.5f; // 4.f;
			const float SH101FILTER_BIAS = 0.01f; //was 0.17f; // 0..1.6
			// changing these sets the amount of shredder discontinuity (hard waveshape discontinuity in dy/dx) around the zerocrossing point. Set both to 0 for no shredding.
//			const float SHREDDER_MIN = -0.0001f; // 0..1.6
//			const float SHREDDER_MAX = 0.0001f; // 0..1.6

			// changing these sets the clip limit point. Our tanh approximator blows up above/below 1.6/-1.6, so keep in range 0.5..1.6
			const float CLIPPER_MIN = -2.f; // 0.95f; // 0..1.6
			const float CLIPPER_MAX = 2.f; // 0.95f; // 0..1.6

			// FMA here
			// Gain - 0.5
			clipsignal = mulps(SH101FILTER_GAIN, clipsignal);
			// Bias voltage = 0..1.67
			clipsignal = addps(SH101FILTER_BIAS, clipsignal);
			// hardclip at +1.6, -1.6 so tanh approximator doesnt blow up
			clipsignal = maxps(CLIPPER_MIN, minps(clipsignal, CLIPPER_MAX));

			// y = x - (2x^2)/4, abs compensated
			vec_float clipsignal_out = clipsignal - (clipsignal * absps(clipsignal) * 0.25f);

			// tanh approximator -- x - (x ^ 3) / 3
//			clipsignal = subps(clipsignal, mulps(mulps(mulps(clipsignal, clipsignal), clipsignal), set1ps(0.3333333f)));

			// Gain - 2.0
			clipsignal_out = mulps(set1ps(SH101FILTER_GAIN_INV), clipsignal_out);

			// Now for vicious twist
			// x +  abs(x) -  abs(x+.1)
		//	clipsignal = addps(clipsignal, subps(absps(addps(clipsignal,set1ps(SHREDDER_MIN))), absps(addps(clipsignal, set1ps(SHREDDER_MAX)))));


			// ------------------------------------------------------------
			vec_float  feedback = clipsignal_out;

			vec_float  tmp0 = y0;
			//tmp1 = i - in_lp;
			vec_float  tmp1 = subps (inpt, in_lp);

			//y0 = tmp1 - feedback;
			y0 = subps (tmp1, feedback);
			vec_float y0m = xmix_m[0] * y0;

			//in_lp += dc_f * tmp1;
			in_lp = fma(in_lp, dc_f, tmp1);

			// tmp1 = y1;
			vec_float t1 = (y1 * g1) - y2;

			vec_float xx;
				// ------------------------------------------------------------
				// y1 += g * tanh1 (g0*y0 + g1*tmp0 - y1 + hm1,  -0.5f);
				xx = (g0* y0) +  (g1* tmp0) - y1 + hm1;
				xx = clipps(xx, -12.f, 12.f);
				xx += xx * xx *xx * (ptx3 + (absps(xx) * ptx4));
				xx += xx * xx * -0.5f * ptxs;
				y1 += g * xx;
			vec_float y1m = xmix_m[1] * y1;


			// tmp0 = y2;
			vec_float t2 = (y2 * g1) - y3;

/*			if (bleed_a > 0.05f)
			{
				tmp0 = y2;
				y2 += g * (g0*y1 + g1*tmp1 - y2 + hm2);
			}
			else*/
			{
				// ------------------------------------------------------------
				// y2 += g * tanh1 (g0*y1 + g1*tmp1 - y2 + hm2,  -0.47f);
				xx = addps(addps(mulps(g0, y1), t1), hm2);
				xx = maxps(ptnxb, minps(ptpxb, xx));
				xx = addps(xx, mulps(mulps(xx, xx), mulps(xx, addps(ptx3, mulps(absps(xx), ptx4)))));
				xx = addps(xx, mulps(set1ps(-0.47f * ptxs), mulps(xx, xx)));
				y2 = addps(y2, mulps(g, xx));
				//			cleandiff2 += absps(y2 - y2_linear);
			}
			vec_float y2m = xmix_m[2] * y2;

			vec_float t3 = (y3 * g1) - y4;

/*			if (bleed_a > 0.05f)
			{
				tmp1 = y3;
				y3 += g * (g0*y2 + g1*tmp0 - y3 + hm1);
			}
			else*/
			{
				// ------------------------------------------------------------
				// y3 += g * tanh1 (g0*y2 + g1*tmp0 - y3 + hm1,  -0.5f);
				xx = addps(addps(mulps(g0, y2), t2), hm1);
				xx = maxps(ptnxb, minps(ptpxb, xx));
				xx = addps(xx, mulps(mulps(xx, xx), mulps(xx, addps(ptx3, mulps(absps(xx), ptx4)))));
				xx = addps(xx, mulps(set1ps(-0.5f * ptxs), mulps(xx, xx)));
				y3 = addps(y3, mulps(g, xx)); // FMA
				//			cleandiff3 += absps(y3 - y3_linear);
			}			
			
			vec_float y3m = xmix_m[3] * y3;

			if (bleed_a > 0.05f)
			{
				y4 += g * (g0*y3 + g1*tmp1 - y4 + hm1);
			}
			else
			{
				// ------------------------------------------------------------
				// y4 += g * tanh1 (g0*y3 + g1*tmp1 - y4 + hm2,  -0.49f);
				xx = addps(addps(mulps(g0, y3), t3), hm2);
				xx = maxps(ptnxb, minps(ptpxb, xx));
				xx = addps(xx, mulps(mulps(xx, xx), mulps(xx, addps(ptx3, mulps(absps(xx), ptx4)))));
				xx = addps(xx, mulps(set1ps(-0.49f * ptxs), mulps(xx, xx)));
				y4 = addps(y4, mulps(g, xx)); // FMA
				//			cleandiff4 += absps(y4 - y4_linear);
			}
			vec_float y4m = xmix_m[4] * y4;

//			sp++;

			//const float out_hp = mix0[0]*y0 + mix0[1]*y1 + mix0[2]*y2 + mix0[3]*y3 + mix0[4]*y4 - out_lp;
			vec_float  out_hp = (y0m + y1m) + (y2m + y3m)  + (y4m - out_lp);

			//out_lp += dc_f * out_hp;
			out_lp = addps (out_lp, mulps (dc_f, out_hp));
			out_hp =  mulps(g1_inv,out_hp);

			xmix_m[0] += xmix_d[0];
			xmix_m[1] += xmix_d[1];
			xmix_m[2] += xmix_d[2];
			xmix_m[3] += xmix_d[3];
			xmix_m[4] += xmix_d[4];
			
			limit_f = mulps(limit_f, set1ps(0.999f));
			limit_f = addps(limit_f, mulps(0.001f, subps(maxps(absps(mulps(out_hp, set1ps(1.1f))), limit_f), limit_f)));
			out_hp = mulps(out_hp, rcpps(maxps(set1ps(1.f), limit_f)));

			out_hp *= 0.125f;
			// y = x - (x^2 / 4)
			out_hp = out_hp - (out_hp * absps(out_hp) * 0.25f);
			out_hp *= 8.f;

			out_hp -= dcv;
			dcv += (dc_f * out_hp);

			outstream << addps(mulps(it, bleed),out_hp);
		}
		voices.member_scatter(f1,my_offsetof(m_f1));
		voices.member_scatter(q,my_offsetof(m_q));
		voices.member_scatter(g1p, my_offsetof(m_g1));
		voices.member_scatter(g1_inv, my_offsetof(m_g1_inv));
		voices.member_scatter(y0,my_offsetof(m_y[0]));
		voices.member_scatter(y1,my_offsetof(m_y[1]));
		voices.member_scatter(y2,my_offsetof(m_y[2]));
		voices.member_scatter(y3,my_offsetof(m_y[3]));
		voices.member_scatter(y4,my_offsetof(m_y[4]));
		voices.member_scatter(in_lp,my_offsetof(m_in_lp));
		voices.member_scatter(out_lp,my_offsetof(m_out_lp));
		voices.member_scatter(limit_f,my_offsetof(m_limit));
		voices.member_scatter(dcv,my_offsetof(m_dc_f));
		for (int32 m = 0; m < 5; m++)
		{
			voices.member_scatter(xmix_m[m], my_offsetof(m_xmix) + (m * sizeof(float)));
		}
	};




};	// end of class Worker


#endif
