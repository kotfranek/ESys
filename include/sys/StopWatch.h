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

#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <stdint.h>

namespace sys
{

    class StopWatch
    {
    public:
        /**
        * Create the StopWatch
        * @arg start Start immediatelly
        */
        StopWatch( const bool startNow = false );
        
        /* Start the time measurement */
        void start();
        
        /**
        * Stop the counter and get the value
        */
        int64_t stop();
        
        
        /**
        * Retrieve the elapsed time. 
        * Do not stop.
        */
        int64_t elapsed() const;
        
    private:
        StopWatch& operator=(const StopWatch& other);
        StopWatch(const StopWatch& other);
        
        
        inline bool isRunning() const
        {
            return 0 != m_timeStart;
        };
            
        
        /* Start Time in us */
        int64_t m_timeStart;
    };

}; // namespace sys

#endif // STOPWATCH_H
