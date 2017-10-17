#ifndef __XFilterLadder_H__
#define __XFilterLadder_H__

class XFilterLadder
{
public:
    
    // Some control I/O ports
    enum eControlIn
    {
        C_POWER     = 0,
        C_DRIVE        ,
        C_MODE         ,
        C_PITCH        ,
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
    
    // Type specific Node class: implements ProcessBuffer() to provide entry point for the node's processing.
    class Node : public XDSP::NodeTmpl<XFilterLadder>
    {
    public:
        virtual void ProcessBuffer (const XDSP::ProcessGlobals& process_globals)
        {
            // Call the templated base class to dispatch
            ProcessBuffer_Dispatch(process_globals);
        }
        
        // Extended processing attributes
        class ProcessAttributes
        {
        };
        
        ProcessAttributes m_pa;
        
        const ProcessAttributes& GetProcessAttributes()
        {
            return m_pa;
        };
        
    };
    
    // Voice member data
    class Voice : public XDSP::VoiceTmpl <XFilterLadder>
    {
    public:
        virtual void Reset ()
        {
            Voice defaultState;
            *this = defaultState;
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
        float m_g1 = 0.f;
        float m_g1_inv = 0.f;
    };
    
    
};

#endif // __XFilterLadder_H__
