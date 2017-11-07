#ifndef __YEQFilter_H__
#define __YEQFilter_H__

////////////////
// A basic amp with linear & cubic gain controls and panning.
template <int32 numBands> class YEQFilter
{
public:
    static const char* GetDescription() { return "YEQFilter"; };
    
    // Some control I/O ports
    enum eControlIn
    {
        C_GAIN_LINEAR     = 0,
        C_GAIN_CUBIC        ,
        C_PAN               ,
    };
    
    enum
    {
        kNumAudioInputs = 1,
        kNumAudioOutputs = 1,
    };
    
    ////////
    // Forward declaration of templated Worker class
    // template <class TIOAdapter> class Worker;
    
    class BandState
    {
    public:
	BandState()
        {
		// printf("A4 %f\n", a[4]);
	};
        float m_freq = 0.5f;
        float m_gain = 1.f;
        float m_q = 0.5f;
        
        float a[5] = {0.2f, 0.1f, 0.2f, 0.1f, 0.2f};   // Coefficients
        float x[2] = {0.f, 0.f};   // Input memory
        float y[2] = {0.f, 0.f};   // Output memory
    };
    

    
    ////////
    // Node implementation via CRTP
    class Node : public XDSP::NodeTmpl<YEQFilter>
    {
    public:
        typedef XDSP::Node::ProcessAttributes ProcessAttributes;         // Pass default implementation back to the template.
    };
    
    ////////
    // Worker does the processing   
    template <class TIOAdapter> class Worker : public TIOAdapter
    {
    public:
        DEFINE_MATHOPS_IMPORTS;      // Import the typedefs and usings from mathops base class
		//using TIOAdapter::vec_float;

		class VecBandState
        {
		public:
			typedef typename TIOAdapter::vec_float vec_float;
			vec_float m_freq;
			vec_float m_gain, m_q;
            vec_float a[numBands][5], x[numBands][2], y[numBands][2];
        } ALIGN_POST(TIOAdapter::alignment);
        
        static void ProcessBuffer (const XDSP::ProcessGlobals& process_globals, TIOAdapter& voices, const typename Node::ProcessAttributes& pa)
        {
            const int32 block_length = process_globals.block_length;

            SampleInputStream instream = voices.getInputStream(0);
            SampleOutputStream outstream = voices.getOutputStream(0);
            VecBandState bands, bands_out;

	// __asm__("int $3");
            
//#pragma unroll(numBands)
            for (int32 i = 0; i < numBands; i++)
            {
                bands.x[i][0] = voices.member_gather(my_offsetof(m_bandState[i].x[0]));
                bands.x[i][1] = voices.member_gather(my_offsetof(m_bandState[i].x[1]));
                bands.y[i][0] = voices.member_gather(my_offsetof(m_bandState[i].y[0]));
                bands.y[i][1] = voices.member_gather(my_offsetof(m_bandState[i].y[1]));
//#pragma unroll(5)                
                for (int32 j = 0; j < 5; j++)
                {
                    bands.a[i][j] = voices.member_gather(my_offsetof(m_bandState[i].a[j]));
                }
            }
            
#if 1 // EXTRA_TEMP_COPY
VecBandState bs = bands;
#else
#define bs bands
#endif

            for (int32 t=0; t<block_length; t++)
            {
                 vec_float io_sample;
                
                 instream >> io_sample;
                
                if (numBands > 0)
                {
                    static constexpr int bd = 0;
                    const vec_float y0 = bs.a[bd][0] * io_sample + bs.a[bd][1] * bs.x[bd][0] + bs.a[bd][2] * bs.x[bd][1] - bs.a[bd][3] * bs.y[bd][0] - bs.a[bd][4] * bs.y[bd][1];
                    bs.x[bd][1] = bs.x[bd][0];
                    bs.x[bd][0] = io_sample;
                    bs.y[bd][1] = bs.y[bd][0];
                    bs.y[bd][0] = y0;
                    io_sample = y0;
                }
                if (numBands > 1)
                {
                    static constexpr int bd = 1;
                    const vec_float y0 = bs.a[bd][0] * io_sample + bs.a[bd][1] * bs.x[bd][0] + bs.a[bd][2] * bs.x[bd][1] - bs.a[bd][3] * bs.y[bd][0] - bs.a[bd][4] * bs.y[bd][1];
                    bs.x[bd][1] = bs.x[bd][0];
                    bs.x[bd][0] = io_sample;
                    bs.y[bd][1] = bs.y[bd][0];
                    bs.y[bd][0] = y0;
                    io_sample = y0;
                }
                if (numBands > 2)
                {
                    static constexpr int bd = 2;
                    const vec_float y0 = bs.a[bd][0] * io_sample + bs.a[bd][1] * bs.x[bd][0] + bs.a[bd][2] * bs.x[bd][1] - bs.a[bd][3] * bs.y[bd][0] - bs.a[bd][4] * bs.y[bd][1];
                    bs.x[bd][1] = bs.x[bd][0];
                    bs.x[bd][0] = io_sample;
                    bs.y[bd][1] = bs.y[bd][0];
                    bs.y[bd][0] = y0;
                    io_sample = y0;
                }
                if (numBands > 3)
                {
                    static constexpr int bd = 3;
                    const vec_float y0 = bs.a[bd][0] * io_sample + bs.a[bd][1] * bs.x[bd][0] + bs.a[bd][2] * bs.x[bd][1] - bs.a[bd][3] * bs.y[bd][0] - bs.a[bd][4] * bs.y[bd][1];
                    bs.x[bd][1] = bs.x[bd][0];
                    bs.x[bd][0] = io_sample;
                    bs.y[bd][1] = bs.y[bd][0];
                    bs.y[bd][0] = y0;
                    io_sample = y0;
                }

                outstream << io_sample;
                
                // Fix for aggressive stores (post-checked loop): keep local scope for temporary.
                if (t == block_length - 1)
                {
                    bands_out = bs;
                }
            }
        
             for (int32 i = 0; i < numBands; i++)
             {
             voices.member_scatter(bands_out.x[i][0], my_offsetof(m_bandState[i].x[0]));
             voices.member_scatter(bands_out.x[i][1], my_offsetof(m_bandState[i].x[1]));
             voices.member_scatter(bands_out.y[i][0], my_offsetof(m_bandState[i].y[0]));
             voices.member_scatter(bands_out.y[i][1], my_offsetof(m_bandState[i].y[1]));
             // for (int32 j = 0; j < 5; j++)             voices.member_scatter(bands_out.a[i][j], my_offsetof(m_bandState[i].a[j]));
             }
    
            
        }; // ProcessBuffer()
    };	// class Worker
    
    ////////
    // Voice member data
    class Voice : public XDSP::VoiceTmpl <YEQFilter>
    {
    public:
        Voice() {};
        virtual ~Voice() {};
        virtual void Reset ()
        {
        };
        // Dummy method for anything not parallelisable
        vforceinline void PreProcessBuffer(const XDSP::ProcessGlobals& process_globals) {};
        template <class TIOAdapter> friend class Worker;
        BandState m_bandState[numBands];
        
    protected:
    };
};
#endif // __YEQFilter_H__












