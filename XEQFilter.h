#ifndef __XEQFilter_H__
#define __XEQFilter_H__

////////////////
// A basic amp with linear & cubic gain controls and panning.
template <int32 numBands> class XEQFilter
{
public:
    static const char* GetDescription() { return "XEQFilter"; };
    
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
        float m_freq = 0.5f;
        float m_gain = 1.f;
        float m_q = 0.5f;
        
        float a[5] = {0.5f, 0.5f, 0.5f, 0.5f, 0.5f};   // Coefficients
        float x[2] = {0.f, 0.f};   // Input memory
        float y[2] = {0.f, 0.f};   // Output memory
    };
    

    
    ////////
    // Node implementation via CRTP
    class Node : public XDSP::NodeTmpl<XEQFilter>
    {
    public:
        typedef XDSP::Node::ProcessAttributes ProcessAttributes;         // Pass default implementation back to the template.
    };
    
    /*
     vinline void process12_mono (float& x0)
     {
     const double y0 = m_a[0]*x0 + m_a[1]*m_x0[0] + m_a[2]*m_x0[1] - m_a[3]*m_y0[0] - m_a[4]*m_y0[1];
     m_x0[1] = m_x0[0];
     m_y0[1] = m_y0[0];
     m_x0[0] = x0 + m_noise();
     m_y0[0] = y0;
     x0 = (float)(y0);
     }
     */
    

    
    ////////
    // Worker does the processing   
    template <class TIOAdapter> class Worker : public TIOAdapter
    {
    public:
        DEFINE_MATHOPS_IMPORTS;      // Import the typedefs and usings from mathops base class
        
        class VecBandState
        {
        public:
            vec_float m_freq, m_gain, m_q;
            vec_float a[5], x[2], y[2];
        };
        
        static void ProcessBuffer (const XDSP::ProcessGlobals& process_globals, TIOAdapter& voices, const typename Node::ProcessAttributes& pa)
        {
            const int32 block_length = process_globals.block_length;

            SampleInputStream instream = voices.getInputStream(0);
            SampleOutputStream outstream = voices.getOutputStream(0);
            VecBandState bands[numBands];
            
            // Gather - assume precomputed coefficients
            // nb: this is the outer loop, can forgive sloppy performance from compilers that don't unroll
            for (int32 i = 0; i < numBands; i++)
            {
                bands[i].x[0] = voices.member_gather(my_offsetof(m_bandState[i].x[0]));
                bands[i].x[1] = voices.member_gather(my_offsetof(m_bandState[i].x[1]));
                bands[i].y[0] = voices.member_gather(my_offsetof(m_bandState[i].y[0]));
                bands[i].y[1] = voices.member_gather(my_offsetof(m_bandState[i].y[1]));
                for (int32 j = 0; j < 5; j++)
                {
                    bands[i].a[j] = voices.member_gather(my_offsetof(m_bandState[i].a[j]));
                }
            }

            
            for (int32 t=0; t<block_length; t++)
            {
                 vec_float io_sample;
                 instream >> io_sample;
                
                // Would be nice to write as a compile time loop, but... MS compiler.
                 if (numBands > 0)
                 {
                     const vec_float y0 = bands[0].a[0] * io_sample + bands[0].a[1] * bands[0].x[0] + bands[0].a[2] * bands[0].x[1] - bands[0].a[3] * bands[0].y[0] - bands[0].a[4] * bands[0].y[1];
                     bands[0].x[1] = bands[0].x[0];
                     bands[0].x[0] = io_sample;
                     bands[0].y[1] = bands[0].y[0];
                     bands[0].y[0] = y0;
                     io_sample = y0;
                 }
                if (numBands > 1)
                {
                    VecBandState& bs = bands[1];
                    const vec_float y0 = bs.a[0] * io_sample + bs.a[1] * bs.x[0] + bs.a[2] * bs.x[1] - bs.a[3] * bs.y[0] - bs.a[4] * bs.y[1];
                    bs.x[1] = bs.x[0];
                    bs.x[0] = io_sample;
                    bs.y[1] = bs.y[0];
                    bs.y[0] = y0;
                    io_sample = y0;
                }
                if (numBands > 2)
                {
                    VecBandState& bs = bands[2];
                    const vec_float y0 = bs.a[0] * io_sample + bs.a[1] * bs.x[0] + bs.a[2] * bs.x[1] - bs.a[3] * bs.y[0] - bs.a[4] * bs.y[1];
                    bs.x[1] = bs.x[0];
                    bs.x[0] = io_sample;
                    bs.y[1] = bs.y[0];
                    bs.y[0] = y0;
                    io_sample = y0;
                }
                if (numBands > 3)
                {
                    VecBandState& bs = bands[3];
                    const vec_float y0 = bs.a[0] * io_sample + bs.a[1] * bs.x[0] + bs.a[2] * bs.x[1] - bs.a[3] * bs.y[0] - bs.a[4] * bs.y[1];
                    bs.x[1] = bs.x[0];
                    bs.x[0] = io_sample;
                    bs.y[1] = bs.y[0];
                    bs.y[0] = y0;
                    io_sample = y0;
                }
                if (numBands > 4)
                {
                    VecBandState& bs = bands[4];
                    const vec_float y0 = bs.a[0] * io_sample + bs.a[1] * bs.x[0] + bs.a[2] * bs.x[1] - bs.a[3] * bs.y[0] - bs.a[4] * bs.y[1];
                    bs.x[1] = bs.x[0];
                    bs.x[0] = io_sample;
                    bs.y[1] = bs.y[0];
                    bs.y[0] = y0;
                    io_sample = y0;
                }
                if (numBands > 5)
                {
                    VecBandState& bs = bands[5];
                    const vec_float y0 = bs.a[0] * io_sample + bs.a[1] * bs.x[0] + bs.a[2] * bs.x[1] - bs.a[3] * bs.y[0] - bs.a[4] * bs.y[1];
                    bs.x[1] = bs.x[0];
                    bs.x[0] = io_sample;
                    bs.y[1] = bs.y[0];
                    bs.y[0] = y0;
                    io_sample = y0;
                }
                if (numBands > 6)
                {
                    VecBandState& bs = bands[6];
                    const vec_float y0 = bs.a[0] * io_sample + bs.a[1] * bs.x[0] + bs.a[2] * bs.x[1] - bs.a[3] * bs.y[0] - bs.a[4] * bs.y[1];
                    bs.x[1] = bs.x[0];
                    bs.x[0] = io_sample;
                    bs.y[1] = bs.y[0];
                    bs.y[0] = y0;
                    io_sample = y0;
                }
                if (numBands > 7)
                {
                    VecBandState& bs = bands[7];
                    const vec_float y0 = bs.a[0] * io_sample + bs.a[1] * bs.x[0] + bs.a[2] * bs.x[1] - bs.a[3] * bs.y[0] - bs.a[4] * bs.y[1];
                    bs.x[1] = bs.x[0];
                    bs.x[0] = io_sample;
                    bs.y[1] = bs.y[0];
                    bs.y[0] = y0;
                    io_sample = y0;
                }
                
                 outstream << io_sample;
            }
            // Scatter
            for (int32 i = 0; i < numBands; i++)
            {
                voices.member_scatter(bands[i].x[0], my_offsetof(m_bandState[i].x[0]));
                voices.member_scatter(bands[i].x[1], my_offsetof(m_bandState[i].x[1]));
                voices.member_scatter(bands[i].y[0], my_offsetof(m_bandState[i].y[0]));
                voices.member_scatter(bands[i].y[1], my_offsetof(m_bandState[i].y[1]));
                for (int32 j = 0; j < 5; j++)
                {
                    voices.member_scatter(bands[i].a[j], my_offsetof(m_bandState[i].a[j]));
                }
            }
        }; // ProcessBuffer()
    };	// class Worker
    
    ////////
    // Voice member data
    class Voice : public XDSP::VoiceTmpl <XEQFilter>
    {
    public:
        Voice() {};
        virtual ~Voice() {};
        virtual void Reset ()
        {
            Voice defaultState;
            *this = defaultState;
        };
        // Dummy method for anything not parallelisable
        vforceinline void PreProcessBuffer(const XDSP::ProcessGlobals& process_globals) {};
        
    protected:
        template <class TIOAdapter> friend class Worker;
        BandState m_bandState[numBands];
    };
};
#endif // __XEQFilter_H__












