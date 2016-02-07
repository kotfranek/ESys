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

#ifndef ESYS_STOPWATCH_H
#define ESYS_STOPWATCH_H

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
        
        
        /* Restart the timer */
        void reStart();
        
        /**
        * Stop the counter and get the value
        */
        int64_t stop();
        
        
        /**
        * Retrieve the elapsed time. 
        * Do not stop.
        */
        int64_t elapsed() const;
        
        /**
         * Check if given time already elapsed
         * @param duration
         * @return 
         */
        inline bool elapsed( const int64_t& duration ) const
        {
            return duration < elapsed();            
        }
        
        
        /**
         * Stop the timer if given time period elapsed
         * @param duration Time Period
         * @return true, if timer was stopped
         */
        bool stopIfElapsed( const int64_t& duration );
        
    private:
        /* Forbid copy */
        StopWatch& operator=(const StopWatch& other);
        StopWatch(const StopWatch& other);
        
        
        /**
         * Test if the timer is enabled
         * @return 
         */
        inline bool isRunning() const
        {
            return 0 != m_timeStart;
        };
        
        
        /**
         * Stop implementation
         */
        inline void stopImpl()
        {
            m_timeStart = 0;
        }
            
        
        /* Start Time in us */
        int64_t m_timeStart;
    };

}; // namespace sys

#endif // ESYS_STOPWATCH_H
