#ifndef __YFilterLadder_H__
#define __YFilterLadder_H__

class YFilterLadder
{
public:
    static const char* GetDescription() { return "YFilterLadder"; };
    
    // Some control I/O ports
    enum eControlIn
    {
        C_POWER     = 0,
        C_DRIVE        ,
        C_MODE         ,
        C_FREQ        ,
        C_RES          ,
        C_FM_DEPTH     ,
        C_BLEED
    };
    
    // Some filter modes
    enum eModes
    {
        L2 = 0,
        L4,
        B2,
        B4,
        kNumModes,
        kNumModes1 = kNumModes-1,
    };
    
    enum
    {
        kNumAudioInputs = 1,
        kNumAudioOutputs = 1,
    };
    
    // Forward declaration of Worker class
    template <class SIMD_IO> class Worker;
    
    // Voice member data
    class Voice : public XDSP::VoiceTmpl <YFilterLadder>
    {
    public:
        virtual void Reset ()
        {
        };
        
        vforceinline void PreProcessBuffer(const XDSP::ProcessGlobals& process_globals)
        {
        };
        
        float m_q = 0.f;
        float m_in_lp = 0.f;
        float m_out_lp = 0.f;
        float m_dc_f = 0.f;
        float m_limit = 0.f;
        float m_y[5] = {0.f, 0.f, 0.f, 0.f, 0.f};
        float m_t[5] = {0.f, 0.f, 0.f, 0.f, 0.f};
        float m_xmix[5] = {0.f, 0.f, 0.f, 0.f, 0.f};
        float m_f1 = 0.f;
        float m_d = 0.f;
        float m_d_inv = 0.f;
    };
    
    // Type specific Node class: implements ProcessBuffer() to provide entry point for the node's processing.
    class Node : public XDSP::NodeTmpl<YFilterLadder>
    {
    public:
        typedef XDSP::Node::ProcessAttributes ProcessAttributes;         // Pass default implementation back to the template.
    };
    
    template <class TIOAdapter> class Worker : public TIOAdapter
    {
    public:
        DEFINE_MATHOPS_IMPORTS;      // Import the typedefs and usings from mathops base class

		static void ProcessBuffer (const XDSP::ProcessGlobals& process_globals, TIOAdapter& voices, const Node::ProcessAttributes& pa)
        {

            const int32 block_length = process_globals.block_length;
            vf drv = 0.5f * clipps( voices.controlport_gather(C_DRIVE), 0.f, 10.f);
            vf inv_drv = divps(1.f, drv);
            inv_drv = minps(inv_drv, 8.f); // limit compensator to +18dB

            vf freq = voices.controlport_gather(C_FREQ);
            vf res  = voices.controlport_gather(C_RES);
            vf bleed = voices.controlport_gather(C_BLEED);
            bleed = bleed * bleed * bleed;
            
//            const int32 mixtaps = 5;
            const float  ptpxb = 12.0f;
            const float  ptnxb = -12.f;
            const float ptxs = 1.f / ptpxb;
            const float  ptx3 = -0.006944444444444444f;
            const float  ptx4 = 0.0002893518518518519f;
            const float pk[] = {0.991549f, 0.111105f, -0.131474f, 0.393442f};
            const float pf[] = {1.00175f, -0.0635353f, -0.0408209f, -0.22f};
            const float scale_gain = 0.4f; // 0.25f;
            const float scale_gaininv = 2.5f; // 4.f;
            const float dc_bias = 0.01f; //was 0.17f; // 0..1.6
            // changing these sets the clip limit point. Our tanh approximator blows up above/below 1.6/-1.6, so keep in range 0.5..1.6
            const float clipper_min = -2.f; // 0.95f; // 0..1.6
            const float clipper_max = 2.f; // 0.95f; // 0..1.6
            const float g0 = 0.74f;
            const float g1 = 0.26f;
            
            vf xmix_t[5]; // Target values (from vector values)
            vf xmix_m[5]; // Member values (from current state)
            vf xmix_d[5]; // difference value
            vf y[5];     // local storage for filter memory
            
            //	const float tap_gain = 0.5f; //2.f;
            for (int32 m = 0; m < 5; m++)
            {
                xmix_t[m] = (m == 0) ? 1.f : 0.f;
                xmix_m[m] = voices.member_gather(my_offsetof(m_xmix) + (m * sizeof(float)));
                xmix_d[m] = (xmix_t[m] - xmix_m[m]) * (process_globals.block_length_norm_inv * 0.1f);
                y[m] = voices.member_gather(my_offsetof(m_y) + (m * sizeof(float)));
            }
            
            // Calculate updated (end-of-block) values for f1 and q
            vf nf1 = clipps (process_globals.tune * process_globals.sample_rate_inv * freq, 0.f, 1.f);
            vf nq = clipps(res * 4.03, 0.f, 32.f);

            // Get old values for f1, q, g1, g & then calculate per-sample delta
            vf f1 = voices.member_gather(my_offsetof(m_f1));
            vf q =  voices.member_gather(my_offsetof(m_q));
            vf d = voices.member_gather(my_offsetof(m_d));
            vf d_inv = voices.member_gather(my_offsetof(m_d_inv));
            
            float  blinv  = process_globals.block_length_norm_inv;
            vf f1_inc =  (nf1 - f1) * blinv;
            vf  q_inc  = (nq - q) * blinv;
            vf d_inc = (drv - g1) * blinv;
            vf d_inv_inc = (inv_drv - d_inv) * blinv;
            
            vf  dc_f = process_globals.filtg_2_5;
            vf dcv = voices.member_gather(my_offsetof(m_dc_f));
            
            vf  in_lp =  voices.member_gather(my_offsetof(m_in_lp));
            vf  out_lp = voices.member_gather(my_offsetof(m_out_lp));
            vf  limit_f = voices.member_gather(my_offsetof(m_limit));
            
            SampleInputStream instream = voices.getInputStream(0);
            SampleOutputStream outstream = voices.getOutputStream(0);
            
            for (int32 t=0; t<block_length; t++)
            {
//IACA_START;
                // ------------------------------------------------------------
                // interpolations, basic coeffs, input
                f1 += f1_inc;
                q += q_inc;
                d += d_inc;
                d_inv += d_inv_inc;
                
                const vf g =  f1 *(pf[0] + f1*(pf[1] + f1*(pf[2] + f1*pf[3])));
                const vf k =  q*(pk[0] + f1*(pk[1] + f1*(pk[2] + f1*pk[3])));

                vf input;
                instream >> input; // Read a group of samples
                vf  gain_input = g1 * input;
                
                // ------------------------------------------------------------
                // feedback section -- custom clipper algorithm, tanh approximation with bias and a discontinuity around zero
                vf clipsignal = k * y[4];
                // Gain and bias
                clipsignal =  (scale_gain * clipsignal) + dc_bias;
                // hardlimit to prevent approximator blow ups
                clipsignal = clipps(clipsignal, clipper_min,  clipper_max);
                // y = x - (2x^2)/4, abs compensated
                vf clipsignal_out = clipsignal - (clipsignal * absps(clipsignal) * 0.25f);
                // scale back
                clipsignal_out *= scale_gaininv;
                
                // ------------------------------------------------------------
                vf  feedback = clipsignal_out;
                
                vf  tmp0 = y[0];
                vf  tmp1 = gain_input - in_lp;
                
                y[0] = tmp1 - feedback;
                vf y0m = xmix_m[0] * y[0];
                
                //in_lp += dc_f * tmp1;
                in_lp += dc_f * tmp1;
                
                vf t1 = (y[1] * g1) - y[2];
                vf xx;
                // ------------------------------------------------------------
                // y1 += g * tanh1 (g0*y0 + g1*tmp0 - y1 + hm1,  -0.5f);
                xx = (g0* y[0]) +  (g1* tmp0) - y[1];
                xx = clipps(xx, -12.f, 12.f);
                xx += xx * xx * xx * (ptx3 + (absps(xx) * ptx4));
                xx += xx * xx * -0.5f * ptxs;
                y[1] += g * xx;
                vf y1m = xmix_m[1] * y[1];
                
                
                // tmp0 = y2;
                vf t2 = (y[2] * g1) - y[3];
                
                    // ------------------------------------------------------------
                    // y2 += g * tanh1 (g0*y1 + g1*tmp1 - y2 + hm2,  -0.47f);
                    xx = (g0 * y[1]) + t1;
                    xx = maxps(ptnxb, minps(ptpxb, xx));
                    xx = addps(xx, mulps(mulps(xx, xx), mulps(xx, addps(ptx3, mulps(absps(xx), ptx4)))));
                    xx = addps(xx, mulps((-0.47f * ptxs), mulps(xx, xx)));
                    y[2] = addps(y[2], mulps(g, xx));
                    //			cleandiff2 += absps(y2 - y2_linear);
                
                vf y2m = xmix_m[2] * y[2];
                
                vf t3 = (y[3] * g1) - y[4];
                
                    // ------------------------------------------------------------
                    // y3 += g * tanh1 (g0*y2 + g1*tmp0 - y3 + hm1,  -0.5f);
                    xx = addps(mulps(g0, y[2]), t2);
                    xx = maxps(ptnxb, minps(ptpxb, xx));
                    xx = addps(xx, mulps(mulps(xx, xx), mulps(xx, addps(ptx3, mulps(absps(xx), ptx4)))));
                    xx = addps(xx, mulps((-0.5f * ptxs), mulps(xx, xx)));
                    y[3] = addps(y[3], mulps(g, xx)); // FMA
                    //			cleandiff3 += absps(y3 - y3_linear);
                
                vf y3m = xmix_m[3] * y[3];
                
                    // ------------------------------------------------------------
                    // y4 += g * tanh1 (g0*y3 + g1*tmp1 - y4 + hm2,  -0.49f);
                    xx = addps(mulps(g0, y[3]), t3);
                    xx = maxps(ptnxb, minps(ptpxb, xx));
                    xx = addps(xx, mulps(mulps(xx, xx), mulps(xx, addps(ptx3, mulps(absps(xx), ptx4)))));
                    xx = addps(xx, mulps((-0.49f * ptxs), mulps(xx, xx)));
                    y[4] = addps(y[4], mulps(g, xx)); // FMA
                    //			cleandiff4 += absps(y4 - y4_linear);
                vf y4m = xmix_m[4] * y[4];
                
                //const float out_hp = mix0[0]*y0 + mix0[1]*y1 + mix0[2]*y2 + mix0[3]*y3 + mix0[4]*y4 - out_lp;
                vf  out_hp = (y0m + y1m) + (y2m + y3m)  + (y4m - out_lp);
                
                //out_lp += dc_f * out_hp;
                out_lp = addps (out_lp, mulps (dc_f, out_hp));
                out_hp =  mulps(d_inv,out_hp);
                
                xmix_m[0] += xmix_d[0];
                xmix_m[1] += xmix_d[1];
                xmix_m[2] += xmix_d[2];
                xmix_m[3] += xmix_d[3];
                xmix_m[4] += xmix_d[4];
                
                limit_f = limit_f * 0.999f;
                limit_f = addps(limit_f, mulps(0.001f, subps(maxps(absps(mulps(out_hp, 1.1f)), limit_f), limit_f)));
                out_hp = mulps(out_hp, rcpps(maxps(1.f, limit_f)));
                
                out_hp *= 0.125f;
                // y = x - (x^2 / 4)
                out_hp = out_hp - (out_hp * absps(out_hp) * 0.25f);
                out_hp *= 8.f;
                
                out_hp -= dcv;
                dcv += (dc_f * out_hp);
                
                outstream << out_hp + (input * bleed);
       //         IACA_END;
            }
            
            // Store members
            voices.member_scatter(f1,my_offsetof(m_f1));
            voices.member_scatter(q,my_offsetof(m_q));
            voices.member_scatter(d, my_offsetof(m_d));
            voices.member_scatter(d_inv, my_offsetof(m_d_inv));
            voices.member_scatter(in_lp,my_offsetof(m_in_lp));
            voices.member_scatter(out_lp,my_offsetof(m_out_lp));
            voices.member_scatter(limit_f,my_offsetof(m_limit));
            voices.member_scatter(dcv,my_offsetof(m_dc_f));
            for (int32 m = 0; m < 5; m++)
            {
                voices.member_scatter(xmix_m[m], my_offsetof(m_xmix) + (m * sizeof(float)));
                voices.member_scatter(y[m], my_offsetof(m_y) + (m * sizeof(float)));
            }
        };
    };	// end of class Worker
};

#endif // __YFilterLadder_H__
