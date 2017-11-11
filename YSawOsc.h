#ifndef __YSawOsc_H__
#define __YSawOsc_H__

////////////////
// A basic PolyBLEP sawtooth oscillator
class YSawOsc
{
public:
    static const char* GetDescription() { return "YSawOsc"; };
    
    // Some control I/O ports
    enum eControlIn
    {
        C_FREQUENCY     = 0,
    };
    
    enum
    {
        kNumAudioInputs = 1,
        kNumAudioOutputs = 1,
    };
    
    // Forward declaration of templated Worker class
    template <class T> class Worker;
    
    ////////
    // Voice member data
    class Voice : public XDSP::VoiceTmpl <YSawOsc>
    {
    public:
        Voice() {};
        virtual ~Voice() {};
        virtual void Reset ()
        {
            m_phase = 0.f;
        };
        
    protected:
        template <class T> friend class Worker;
        float m_phase = 0.f;  // -1..+1 phase clock
    };
    
    ////////
    // Type specific Node class, implementation via CRTP
    class Node : public XDSP::NodeTmpl<YBasicAmp>
    {
    public:
        typedef XDSP::Node::ProcessAttributes ProcessAttributes;         // Pass default implementation back to the template.
    };
    
    ////////
    // Worker does the actual processing
    template <class TIOAdapter> class Worker : public TIOAdapter
    {
    public:
        // Import the typedefs and usings from mathops base class
        DEFINE_MATHOPS_IMPORTS;
        
        static void ProcessBuffer (const XDSP::ProcessGlobals& process_globals, TIOAdapter& voices, const Node::ProcessAttributes& pa)
        {
            const int32 block_length = process_globals.block_length;
            
            // Assume precomputed (0.. 0.5*SR) frequency
            vec_float freq01  = voices.controlport_gather(C_FREQUENCY);
            vec_float phase = voices.member_gather(my_offsetof(m_phase));
            SampleOutputStream outstream = voices.getOutputStream(0);
            
            for (int32 t=0; t<block_length; t++)
            {
                phase += freq01;
                phase -= ((phase > 1.f) & 2.f);
                
                vec_float out_sample = phase;
                outstream << out_sample;
            }
        }; // ProcessBuffer()
    };	// class Worker
};
#endif // __SawOsc_H__












