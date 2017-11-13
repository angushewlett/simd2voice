#ifndef __YPannerAmp_H__
#define __YPannerAmp_H__

////////////////
// A basic amp with linear & cubic gain controls and panning.
class YPannerAmp
{
public:
    static const char* GetDescription() { return "YPannerAmp"; };
    
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
    class Voice : public XDSP::VoiceTmpl <YPannerAmp>
    {
    public:
        Voice() {};
        virtual ~Voice() {};
		virtual void Reset() {};
        // Dummy method for anything not parallelisable
        vforceinline void PreProcessBuffer(const XDSP::ProcessGlobals& process_globals) {};
        
    protected:
        template <class T> friend class Worker;
        float m_linear_gain = 1.f;
        float m_cubic_gain = 1.f;
        float m_pan = 0.5f;
    };
    
    ////////
    // Node implementation via CRTP
    class Node : public XDSP::NodeTmpl<YPannerAmp>
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
        
        static void ProcessBuffer (const XDSP::ProcessGlobals& process_globals, TIOAdapter& voices, const Node::ProcessAttributes& pa)
        {
            const int32 block_length = process_globals.block_length;
            vf next_linear_gain  = voices.controlport_gather(C_GAIN_LINEAR);
            vf next_cubic_gain  = voices.controlport_gather(C_GAIN_CUBIC);
            vf next_pan  = voices.controlport_gather(C_PAN);
            
            next_cubic_gain *= next_cubic_gain * next_cubic_gain;
            
            vf last_linear_gain = voices.member_gather(my_offsetof(m_linear_gain));
            vf last_cubic_gain = voices.member_gather(my_offsetof(m_cubic_gain));
            vf last_pan = voices.member_gather(my_offsetof(m_pan));
            
            vf linear_gain_diff = (next_linear_gain - last_linear_gain) * process_globals.block_length_norm_inv;
            vf cubic_gain_diff = (next_cubic_gain - last_cubic_gain) * process_globals.block_length_norm_inv;
            vf pan_diff = (next_pan - last_pan) * process_globals.block_length_norm_inv;
            
            SampleInputStream instream = voices.getInputStream(0);
            SampleOutputStream outstream0 = voices.getOutputStream(0);
            SampleOutputStream outstream1 = voices.getOutputStream(1);
            
            vf out_sample1 = 0.f;
            
            for (int32 t=0; t<block_length; t++)
            {
                 vf in_sample;
                 instream >> in_sample;
                 in_sample = (in_sample * 0.9f) + (out_sample1 * 0.1f);
                 next_linear_gain += linear_gain_diff;
                 next_cubic_gain += cubic_gain_diff;
                 next_pan += pan_diff;
                 
                 out_sample1 = in_sample * next_linear_gain * next_cubic_gain;
                 outstream0 << out_sample1 * next_pan;
                 outstream1 << out_sample1 * (1.f - next_pan);
            }
            voices.member_scatter(next_linear_gain,my_offsetof(m_linear_gain));
            voices.member_scatter(next_cubic_gain,my_offsetof(m_cubic_gain));
            voices.member_scatter(next_pan,my_offsetof(m_pan));
        }; // ProcessBuffer()
    };	// class Worker
};
#endif // __YPannerAmp_H__












