#ifndef __XBasicAmpTmpl_H__
#define __XBasicAmpTmpl_H__

//#include "PerformanceCounterScope.h"
#ifndef CEXCOMPILE
#include "XBasicAmp.h"
#endif

// Assumed headers:
// TIOAdapter type
// XDSP: ProcessGlobals, Node, Node::Voice

template <class TIOAdapter> class XBasicAmp::Worker : public TIOAdapter
{
public:

	// Import the typedefs and usings from mathops base class    
    DEFINE_MATHOPS_IMPORTS;
    

    static void ProcessBuffer (const XDSP::ProcessGlobals& process_globals, TIOAdapter& voices, const Node::ProcessAttributes& pa)
	{
	//	PerformanceCounterScope perfScope(__FUNCTION__);

		//static
		const int32 block_length = process_globals.block_length;
		vec_float next_linear_gain  = voices.controlport_gather(C_GAIN_LINEAR);
        vec_float next_cubic_gain  = voices.controlport_gather(C_GAIN_CUBIC);
        vec_float next_pan  = voices.controlport_gather(C_PAN);
        
        next_cubic_gain *= next_cubic_gain * next_cubic_gain;

		vec_float last_linear_gain = voices.member_gather(my_offsetof(m_linear_gain));
        vec_float last_cubic_gain = voices.member_gather(my_offsetof(m_cubic_gain));
        vec_float last_pan = voices.member_gather(my_offsetof(m_pan));
        
        vec_float linear_gain_diff = (next_linear_gain - last_linear_gain) * process_globals.block_length_norm_inv;
        vec_float cubic_gain_diff = (next_cubic_gain - last_cubic_gain) * process_globals.block_length_norm_inv;
        vec_float pan_diff = (next_pan - last_pan) * process_globals.block_length_norm_inv;
        
        SampleInputStream instream = voices.getInputStream(0);
        SampleOutputStream outstream0 = voices.getOutputStream(0);
        SampleOutputStream outstream1 = voices.getOutputStream(1);
        
		for (int32 t=0; t<block_length; t++)
		{
/*            vec_float in_sample;
            instream >> in_sample; // Read a group of samples
            next_linear_gain += linear_gain_diff;
            next_cubic_gain += cubic_gain_diff;
            next_pan += pan_diff;

			outstream0 << in_sample * next_linear_gain * next_cubic_gain * next_pan;
			outstream1 << in_sample * next_linear_gain * next_cubic_gain * (set1ps(1.f) - next_pan);
 */
            vec_float in_sample;
             instream >> in_sample; // Read a group of samples
             outstream0 << in_sample * next_linear_gain * next_cubic_gain * next_pan;
            
        }
		voices.member_scatter(next_linear_gain,my_offsetof(m_linear_gain));
        voices.member_scatter(next_cubic_gain,my_offsetof(m_cubic_gain));
        voices.member_scatter(next_pan,my_offsetof(m_pan));
    };

};	// end of class Worker


#endif
