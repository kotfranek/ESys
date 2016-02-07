/*
 * Copyright (c) 2016, Przemysław Podwapiński <p.podwapinski@gmail.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY Przemysław Podwapiński ''AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL Przemysław Podwapiński BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
 
#include "sys/StopWatch.h"
#include <chrono>

namespace
{
    inline void getMicroSecTime( int64_t& dest )
    {
        const auto now = ::std::chrono::high_resolution_clock::now();
        dest =  ::std::chrono::duration_cast<std::chrono::microseconds>( now.time_since_epoch() ).count();
    }
}
    
namespace sys
{

StopWatch::StopWatch( const bool startNow )
    : m_timeStart( 0 )
{
    if ( startNow )
    {
        start();
    }
}


void StopWatch::start()
{    
    if ( !isRunning() )
    {
        getMicroSecTime( m_timeStart );
    }   
}


void StopWatch::reStart()
{
    stopImpl();
    start();
}


int64_t StopWatch::elapsed() const
{
    int64_t result  = 0;
    
    if ( isRunning() )
    {
        int64_t timeNow = 0;
        getMicroSecTime( timeNow );
        
        result = timeNow - m_timeStart;
    }
    
    return result;
}


bool StopWatch::elapsed( const int64_t& duration ) const
{
    return duration < elapsed();
}


int64_t StopWatch::stop()
{
    int64_t result  = elapsed();
    
    stopImpl();

    return result;
}


bool StopWatch::stopIfElapsed( const int64_t& duration )
{
    bool result = false;
    
    if ( duration < elapsed() )
    {
        stopImpl();
    }
    
    return result;
}

}; // namespace sys
