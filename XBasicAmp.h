#ifndef __XBasicAmp_H__
#define __XBasicAmp_H__

////////////////
// A basic linear gain amp
class XBasicAmp
{
public:
    static const char* GetDescription() { return "XBasicAmp"; };
    
    // Some control I/O ports
    enum eControlIn
    {
        C_GAIN_LINEAR     = 0,
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
    class Voice : public XDSP::VoiceTmpl <XBasicAmp>
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
        template <class T> friend class Worker;
        float m_linear_gain = 1.f;
    };
    
    ////////
    // Type specific Node class, implementation via CRTP
    class Node : public XDSP::NodeTmpl<XBasicAmp>
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
            //	PerformanceCounterScope perfScope(__FUNCTION__);
            //  printf("Interleave = %d, sizeof(vf) = %d\n", TIOAdapter::interleave, (int)sizeof(vec_float));
            //  printf("Fn %s\n", __PRETTY_FUNCTION__);
            const int32 block_length = process_globals.block_length;
            vec_float next_linear_gain  = voices.controlport_gather(C_GAIN_LINEAR);
            SampleInputStream instream = voices.getInputStream(0);
            SampleOutputStream outstream = voices.getOutputStream(0);            
            //#pragma unroll(1)
            for (int32 t=0; t<block_length; t++)
            {
                *outstream++ = *instream++ * next_linear_gain;
            }
        }; // ProcessBuffer()
    };	// class Worker
};
#endif // __XBasicAmp_H__












