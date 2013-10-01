/*
    Implementation of a timer SO independent
    Copyright (C) 2012  Matteo De Carlo <<matteo.dek@gmail.com>>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/


#ifndef TIMER_H
#define TIMER_H

#include "types.h"

#ifdef WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif

/**
 * @brief Implementation of a timer that is SO independent
 */
class Timer 
{
Q_OBJECT

public:
    explicit Timer()
    {
        #ifdef WIN32
        QueryPerformanceFrequency(&m_CounterFrequency);
        #endif
        this->reset();
    }

    /**
    * @brief Get the current count
    * 
    * @return smRealD times passed from the last reset
    */
    smRealD getElapsedSeconds()
    {
        #ifdef WIN32
        LARGE_INTEGER lCurrent;
        QueryPerformanceCounter(&lCurrent);

        return float((lCurrent.QuadPart - m_LastCount.QuadPart) /
                double(m_CounterFrequency.QuadPart));

        #else
        timeval lcurrent;
        gettimeofday(&lcurrent, 0);
        smRealD fSeconds = (smRealD)(lcurrent.tv_sec - m_LastCount.tv_sec);
        smRealD fFraction = (smRealD)(lcurrent.tv_usec - m_LastCount.tv_usec) * 0.000001f;
        return fSeconds + fFraction;
        #endif
    }
    
    /**
     * @brief Reset the reference for the time 0
     */
    void reset()
    {
        #ifdef WIN32
        QueryPerformanceCounter(&m_LastCount);
        #else
        gettimeofday(&m_LastCount, 0);
        #endif
    }
    
    /**
    * @brief get the time and reset
    * 
    * @return smRealD the time passed before reset
    */
    smRealD getElapsedSecondsAndReset()
    {
        smRealD time = this->getElapsedSeconds();
        this->reset();
        return time;
    }

protected:
    #ifdef WIN32
    LARGE_INTEGER m_CounterFrequency;
    LARGE_INTEGER m_LastCount;
    #else
    timeval m_LastCount;
    #endif
};
#endif // TIMER_H
