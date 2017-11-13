#ifndef __YBasicAmp_H__
#define __YBasicAmp_H__

////////////////
// A basic linear gain amp
class YBasicAmp
{
public:
    static const char* GetDescription() { return "YBasicAmp"; };
    
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
    class Voice : public XDSP::VoiceTmpl <YBasicAmp>
    {
    public:
        Voice() {};
        virtual ~Voice() {};
        virtual void Reset ()
        {
        };
        
    protected:
        template <class T> friend class Worker;
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
            vf next_linear_gain  = voices.controlport_gather(C_GAIN_LINEAR);
            SampleInputStream instream = voices.getInputStream(0);
            SampleOutputStream outstream = voices.getOutputStream(0);            
            
            for (int32 t=0; t<block_length; t++)
            {
                vf sample;
                instream >> sample;
                outstream << (sample * next_linear_gain);
                // Or: *outstream++ = *instream++ * next_linear_gain;
            }
        }; // ProcessBuffer()
    };	// class Worker
};
#endif // __YBasicAmp_H__












