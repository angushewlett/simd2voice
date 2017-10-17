#ifndef __XBasicAmp_H__
#define __XBasicAmp_H__

////////////////
// A basic amp with linear & cubic gain controls and panning.
class XBasicAmp
{
public:
    
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
        kNumAudioOutputs = 2,
    };
    
    ////////
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
        float m_cubic_gain = 1.f;
        float m_pan = 0.5f;
    };
    
    ////////
    // Type specific Node class: implements ProcessBuffer() to provide entry point for the node's processing.
    class Node : public XDSP::NodeTmpl<XBasicAmp>
    {
    public:
        virtual void ProcessBuffer (const XDSP::ProcessGlobals& process_globals)
        {
            // Call the templated base class to dispatch
            ProcessBuffer_Dispatch(process_globals);
        }
        
        // Extended processing attributes (We don't have any)
        class ProcessAttributes {};
        ProcessAttributes m_pa;
        const ProcessAttributes& GetProcessAttributes() {   return m_pa;  };
        
    };
    
};

#endif // __XBasicAmp_H__












