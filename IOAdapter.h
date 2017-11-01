#ifndef __IOADAPTER_H__
#define __IOADAPTER_H__

//////////////////////////////////////////////
// Scatter/gather class for interleaved VDSP (voice member variables, control inputs & buffers fully interleaved)
// Inherits from a math-ops class which provides the following:-
//	typename MO::vec_float vec_float -- an opaque vector of (one or more) floats, with a fixed size of (vec_elem) elements
//	typename MO::vec_union_f vec_union_f -- a union type allowing scalar float data to be loaded
//	static const int32 vec_elem	-- an int declaring the total number of elements in the vector
//	static const int32 interleave -- an int declaring the vector's interleave factor
//  MO <-- Mathops_***<interleave>
//////////////////////////////////////////////

#include <algorithm>


#define IMPLEMENT_DISPATCHMETHOD(AClass, AMethod) \
typedef XDSP::NodeTmpl<IMPL_Class> NodeImpl_##AClass;\
typedef IOAdapter<IMPL_MathNamespace::MathOps<1> , AClass> IOAdapterImpl_##AClass;\
template<> int32 NodeImpl_##AClass::AMethod(const XDSP::ProcessGlobals& process_globals, AClass::Node* caller)\
{\
    NodeImpl_##AClass::ProcessAllVoices<IOAdapterImpl_##AClass::Worker>(process_globals, caller);\
    return 0;\
};

/*
// This macro allows you to declare a worker object type for a specific DSP class, I/O adapter and math operations set.
// (Invoking it will instantiate a template for this filter class & maths operation)
#define IMPL_WorkerType(nodeType, interleave) Worker<IOAdapter<IMPL_MathNamespace::MathOps<interleave> , nodeType> >

// This macro allows you to declare an implementation matching the method signatures called from NodeTmpl::ProcessBuffer_Dispatch.
// The method calls an instance of the worker type defined above.
#define IMPL_DispatchMethod(AClass, AMethod, AWorker) template<> void DISPATCH_ATTRIBUTE_TAG XDSP::NodeTmpl<AClass>::AMethod(const ProcessGlobals& process_globals, XDSP::Node* caller)\
{\
AClass::AWorker::ProcessAllVoices(process_globals, caller);\
}

*/
// Hack for getting offset of members: 'offsetof' keyword isn't allowed for non POD types
#define my_offsetof(_MEMBER) (size_t)((char*)&(((Voice*)1)->_MEMBER)-1)


template <class Mathops_t, class DSPNode_t> class IOAdapter : public Mathops_t
{
public:
    // Import types from the base mathops implementation
	typedef typename Mathops_t::vec_float vec_float;
//	typedef typename Mathops_t::vec_int vec_int;
	typedef typename Mathops_t::vec_union_f vec_union_f;
//	typedef typename Mathops_t::vec_union_i32 vec_union_i32;
    
	static constexpr int32 vec_elem = Mathops_t::vec_elem;
	static constexpr int32 interleave = Mathops_t::interleave;
    
    // Import voice type from the DSP node
    typedef typename DSPNode_t::Voice Voice;
    typedef typename DSPNode_t::template Worker<IOAdapter> Worker;
    typedef Voice* VoiceBlock[Mathops_t::vec_elem];
    
    /////////////////////////////////
    // Input stream (for reading from interleaved AudioDSPGraph I/O buffers)
    class SampleInputStream
    {
    public:
        void Init(const vec_float* buff_start)
        {
            m_buff_read = m_buff_start = buff_start;
        };
        void ResetIterator() { m_buff_read = m_buff_start; };
        //friend SampleInputStream & operator >> (SampleInputStream &instr,  vec_float& f);
        
        vforceinline SampleInputStream & operator >> (vec_float& f)
        {
            f= *m_buff_read;
            m_buff_read += XDSP::kMaxVoices / vec_elem;
            return *this;
        };
        
        vforceinline SampleInputStream operator++(int n)
        {
            SampleInputStream tmp(*this);
            m_buff_read += XDSP::kMaxVoices / vec_elem;
            return tmp;
        };
        
        vforceinline const vec_float & operator*()
        {
            return *m_buff_read;
        };
        
    protected:
        const vec_float* m_buff_read = 0;
        const vec_float* m_buff_start = 0;
    };

    /////////////////////////////////
    // Output stream (for writing to interleaved AudioDSPGraph I/O buffers)
    class SampleOutputStream
    {
    public:
        void Init(vec_float* buff_start)
        {
            m_buff_write = m_buff_start = buff_start;
        };
        void ResetIterator() { m_buff_write = m_buff_start; };

        vforceinline SampleOutputStream & operator << (vec_float f)
        {
            *m_buff_write = f;
            m_buff_write += XDSP::kMaxVoices / vec_elem;
            return *this;
        };
        
        vforceinline SampleOutputStream operator++(int n)
        {
            SampleOutputStream tmp(*this);
            m_buff_write += XDSP::kMaxVoices / vec_elem;
            return tmp;
        };
        
        vforceinline vec_float & operator*()
        {
            return *m_buff_write;
        };
        
    protected:
        vec_float* m_buff_write = 0;
        vec_float* m_buff_start = 0;
    };
    
protected:
    // Store all the voices
    VoiceBlock& m_voices;
    // I/O sample streaming objects
    SampleInputStream m_inStreams[DSPNode_t::kNumAudioInputs];
    SampleOutputStream m_outStreams[DSPNode_t::kNumAudioOutputs];
    
protected:
    // Helper for getting direct access pointers to member variables, given an offset. hacky.
    // this assumes 2^6 = 64-byte object alignment
    // Get a float ref from a voice object, where all voice objects are contiguous.
    static vforceinline float& member_access(const char* base, int32 voice_index, size_t offset)
    {
        const int32 voice_shift = (((sizeof(typename DSPNode_t::Voice) >> 6) + 1) << 6);
        return *(float*)(base + (voice_index * voice_shift) + offset);
    };
    
public:
    //////////////////////////////
    // ctor
    vforceinline IOAdapter (VoiceBlock& voices) : m_voices(voices)
	{
        for (int32 i = 0; i < DSPNode_t::kNumAudioInputs; i++) m_inStreams[i].Init(reinterpret_cast<const vec_float*>(m_voices[0]->AudioIn(i)));
        for (int32 i = 0; i < DSPNode_t::kNumAudioOutputs; i++) m_outStreams[i].Init(reinterpret_cast<vec_float*>(m_voices[0]->AudioOut(i)));
	};

    //////////////////////////////
    // Get the intput stream
    vforceinline SampleInputStream& getInputStream(int32 input)
    {
        return m_inStreams[input];
    }
    
    //////////////////////////////
    // Get the output stream
    vforceinline SampleOutputStream& getOutputStream(int32 output)
    {
        return m_outStreams[output];
    }
    
    //////////////////////////////
    // Gather for voice member variables
	vforceinline vec_float member_gather(size_t offset)
	{
// printf("%d\n", offset);
        vec_float result;
        vec_union_f loader;
        const char* base = reinterpret_cast<const char*>(m_voices[0]);
        
        #pragma unroll (vec_elem)
        for (int32 i = 0; i < vec_elem; i++)
        {
            loader.f[i] = member_access(base, i, offset);
// printf("%f\n", loader.f[i]);
        }
        
        #pragma unroll (interleave)
        for (int32 i = 0; i < interleave; i++)
        {
            result.m[i] = loader.m[i];
        }
        return result;
/*        
        
        vec_float res0;         
        constexpr int32 voice_shift = (((sizeof(typename DSPNode_t::Voice) >> 6) + 1) << 6);
        const char* base = reinterpret_cast<const char*>(m_voices[0]);
        char* wx = reinterpret_cast<char*>(&res0);
#pragma unroll (vec_elem)        
        for (int32 i = 0; i < vec_elem; i++)
        {
            *(((float*)wx)+i) = *(float*)(base + offset + (i * voice_shift));
        }
        vec_float result = res0;
        return result;
  */       
	};
    /*
    //////////////////////////////
    // Gather for voice member variables
    vforceinline void member_gather(vec_float& result, size_t offset)
    {
     
        vec_union_f loader;
        const char* base = reinterpret_cast<const char*>(m_voices[0]);
        
#pragma unroll (vec_elem)
        for (int32 i = 0; i < vec_elem; i++)
        {
            loader.f[i] = member_access(base, i, offset);
        }
        
#pragma unroll (interleave)
        for (int32 i = 0; i < interleave; i++)
        {
            result.m[i] = loader.m[i];
        }
        
         vec_float res0;
         constexpr int32 voice_shift = (((sizeof(typename DSPNode_t::Voice) >> 6) + 1) << 6);
         const char* base = reinterpret_cast<const char*>(m_voices[0]);
         char* wx = reinterpret_cast<char*>(&res0);
         #pragma unroll (vec_elem)
         for (int32 i = 0; i < vec_elem; i++)
         {
         *(((float*)wx)+i) = *(float*)(base + offset + (i * voice_shift));
         }
         result = res0;
         //return result;
        
    };*/
    

    //////////////////////////////
    // Scatter for voice member variables
	vforceinline void member_scatter(const vec_float& data, size_t offset)
	{
        vec_union_f loader;
        const char* base = reinterpret_cast<const char*>(m_voices[0]);
        
        #pragma unroll (interleave)
        for (int32 i = 0; i < interleave; i++)
        {
            loader.m[i] = data.m[i];
            
        }
        
        #pragma unroll (vec_elem)
        for (int32 i = 0; i < vec_elem; i++)
        {
            member_access(base, i, offset) = loader.f[i];
        }
        
    };

    ///////////////////////////////
    // Gather for controlport variables (assume interleaved)
	vforceinline vec_float controlport_gather(int32 portindex)
	{
		return *(vec_float*)(m_voices[0]->ControlIn(portindex));
	};
    
    ///////////////////////////////
    // Gather for controlport variables (assume interleaved)
    vforceinline void controlport_scatter(int32 portindex, const vec_float& data)
    {
        *m_voices[0]->ControlOut(portindex) = data;
    };
};


#endif	// __IOAdapter_H__
