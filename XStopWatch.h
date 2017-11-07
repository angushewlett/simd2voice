#ifndef XSTOPWATCH_H
#define XSTOPWATCH_H

////////////////////////////////
// File: XStopWatch.h
// Simple high-res runtime stopwatch.
// Author: Angus F. Hewlett
// Copyright FXpansion Audio UK Ltd. 2014-2017
////////////////////////////////

#include <stdlib.h>
#include <stdint.h>
#if MACOSX
#include <mach/mach_time.h>
#endif
#if LINUX
#include <time.h>
#endif

////////////////////////////////
// High resolution stopwatch timer wrapper class
class StopWatch
{
public:
    StopWatch ()
    {
        if (!s_bDidInit) StaticInit();
        Reset();
    };
    
    void Reset()
    {
#if WIN32
        QueryPerformanceCounter ((LARGE_INTEGER*)&m_count1);
#endif
#ifdef MACOSX
        m_count1 = mach_absolute_time ();
#endif
#if LINUX
        struct timespec spec;
        clock_gettime(CLOCK_REALTIME, &spec);
        m_count1 = ((spec.tv_sec % 1000) *1e9) + spec.tv_nsec;
#endif
    };

	////////////////////////////////
	// Get elapsed time since instantiation / last reset in seconds
    double GetElapsedTime () const
    {
#if WIN32
        uint64_t count2;
        QueryPerformanceCounter ((LARGE_INTEGER*)&count2);
        uint64_t count_diff = 0;
        if (m_count1 > count2)
        {
            count_diff = ~(m_count1 - count2);
        }
        else
        {
            count_diff = count2 - m_count1;
        }
        const double t = (double)(count_diff) * s_freq_inv;
        return t;
#endif
        
#if MACOSX
        uint64_t count2 = mach_absolute_time ();
        uint64_t count_diff = count2 - m_count1;
        uint64_t elapsedNano = count_diff * sTimebaseInfo.numer / sTimebaseInfo.denom;
        return (double)((double) (elapsedNano) * (double) 1e-9);
#endif
#if LINUX
        struct timespec spec;
        clock_gettime(CLOCK_REALTIME, &spec);
        uint64_t count2 = ((spec.tv_sec % 1000) * 1e9) + spec.tv_nsec;
        uint64_t count_diff = count2 - m_count1;
        return (double)((double)(count_diff) / (double) 1e9);
#endif
        
    };
    
	////////////////////////////////
	// Static initialization
    static void StaticInit()
    {
#if WIN32
        LARGE_INTEGER freq;
        
        // we need the accuracy
        if(!QueryPerformanceFrequency (&freq))
        {
            printf ("QueryPerformanceFrequency () failed\n");
            return; // win errors
        }
        // usually the rate will be 1193180
        if(freq.QuadPart == 0)
        {
            printf ("QueryPerformanceFrequency () failed\n");
            return;
        }
        s_freq_inv = 1.0/(double)(freq.QuadPart);
#endif
#if MACOSX
        mach_timebase_info(&sTimebaseInfo);
#endif
        s_bDidInit = true;
    };
    
private:
    uint64_t       m_count1;			/**< Timer count */
#if MACOSX
    static mach_timebase_info_data_t sTimebaseInfo;
#endif
#if WIN32
    static double s_freq_inv;		/**< Sampling frequency */
#endif
    static bool s_bDidInit;
};

#if WIN32
double StopWatch::s_freq_inv = 1.0;		/**< Sampling frequency */
#endif

#if MACOSX
mach_timebase_info_data_t    StopWatch::sTimebaseInfo;
#endif
bool StopWatch::s_bDidInit = false;


#endif
