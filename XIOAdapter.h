#ifndef __XIOADAPTER_H__
#define __XIOADAPTER_H__

////////////////////////////////
// File: XIOAdapter.h
// I/O Adapter for XDSP <=> MathOps SIMD
// Author: Angus F. Hewlett
// Copyright FXpansion Audio UK Ltd. 2014-2017
////////////////////////////////

////////////////////////////////
// Scatter/gather class for XDSP process nodes with interleaved audio buffers
// Inherits from a math-ops class which provides the following:-
// * simd_t an opaque vector of (one or more) floats, with a fixed size of (num_elem) elements
// * static const int32 num_elem	-- an int declaring the total number of elements in the vector
// * static const int32 interleave -- an int declaring the vector's interleave factor
////////////////////////////////

// Macro for implementing dispatcher methods @ cpp compilation units
#define IMPLEMENT_DISPATCHMETHOD(AClass, AMethod) \
typedef XDSP::NodeTmpl<IMPL_Class> NodeImpl_##AClass;\
typedef IOAdapter<IMPL_MathNamespace::MathOps<1> , AClass> IOAdapterImpl_##AClass;\
template<> int32 NodeImpl_##AClass::AMethod(const XDSP::ProcessGlobals& process_globals, AClass::Node* caller)\
{\
    NodeImpl_##AClass::ProcessAllVoices<IOAdapterImpl_##AClass::Worker>(process_globals, caller);\
    return 0;\
};

// Hack for getting offset of members: 'offsetof' keyword isn't allowed for non POD types. Ugly but the compiler will resolve...
#define my_offsetof(MEMBER_VAR) (size_t)((char*)&(((Voice*)1)->MEMBER_VAR)-1)

////////////////////////////////
template <class simd_t, class dspnode_t> class IOAdapter : public simd_t
{
public:
    // Import types from the base mathops implementation
	typedef typename simd_t::vec_float vec_float;    
	static constexpr int32 num_elem = simd_t::num_elem;
	static constexpr int32 interleave = simd_t::interleave;
    
    // Import voice type from the DSP node
    typedef typename dspnode_t::Voice Voice;
    typedef typename dspnode_t::template Worker<IOAdapter> Worker;
    typedef Voice* VoiceBlock[simd_t::num_elem];
    
    /////////////////////////////////
    // Input stream (for reading from interleaved AudioDSPGraph I/O buffers)
    class SampleInputStream
    {
    public:

		// Init
        void Init(const vec_float* buff_start)
        {
            m_buff_read = m_buff_start = buff_start;
        };

		// Reset
        void ResetIterator() 
		{ 
			m_buff_read = m_buff_start; 
		};
        
		// Read & increment
        vforceinline SampleInputStream & operator >> (vec_float& f)
        {
            f= *m_buff_read;
            m_buff_read += XDSP::kMaxVoices / num_elem;
            return *this;
        };
        
		// Post-increment
        vforceinline SampleInputStream operator++(int n)
        {
            SampleInputStream tmp(*this);
            m_buff_read += XDSP::kMaxVoices / num_elem;
            return tmp;
        };
        
		// Read
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

		// Init
        void Init(vec_float* buff_start)
        {
            m_buff_write = m_buff_start = buff_start;
        };

		// Reset
        void ResetIterator() 
		{ 
			m_buff_write = m_buff_start; 
		};

		// Write & increment
        vforceinline SampleOutputStream & operator << (vec_float f)
        {
            *m_buff_write = f;
            m_buff_write += XDSP::kMaxVoices / num_elem;
            return *this;
        };
        
		// Increment
        vforceinline SampleOutputStream operator++(int n)
        {
            SampleOutputStream tmp(*this);
            m_buff_write += XDSP::kMaxVoices / num_elem;
            return tmp;
        };
        
		// Write
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
    SampleInputStream m_inStreams[dspnode_t::kNumAudioInputs];
    SampleOutputStream m_outStreams[dspnode_t::kNumAudioOutputs];
   	 
public:
    //////////////////////////////
    // ctor
    vforceinline IOAdapter (VoiceBlock& voices) : m_voices(voices)
	{
        for (int32 i = 0; i < dspnode_t::kNumAudioInputs; i++) m_inStreams[i].Init(reinterpret_cast<const vec_float*>(m_voices[0]->AudioIn(i)));
        for (int32 i = 0; i < dspnode_t::kNumAudioOutputs; i++) m_outStreams[i].Init(reinterpret_cast<vec_float*>(m_voices[0]->AudioOut(i)));
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
        const float* base = reinterpret_cast<const float*>(m_voices[0]);
        return simd_t::template gather<dspnode_t::Node::s_voice_size_padded> (base + (offset / sizeof(float)));
	};

    //////////////////////////////
    // Scatter for voice member variables
	vforceinline void member_scatter(const vec_float& data, size_t offset)
	{
        float* base = reinterpret_cast<float*>(m_voices[0]);
        simd_t::template scatter<dspnode_t::Node::s_voice_size_padded> (data, base + (offset / sizeof(float)));
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
