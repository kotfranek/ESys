/*
 * Copyright 2016 Przemyslaw Podwapinski <p.podwapinski@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
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


int64_t StopWatch::stop()
{
    int64_t result  = elapsed();
    
    m_timeStart = 0;

    return result;
}

}; // namespace sys
