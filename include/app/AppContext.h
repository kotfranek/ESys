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

#ifndef APPCONTEXT_H
#define APPCONTEXT_H

#include <mutex>
#include <condition_variable>

namespace app
{
    class SimpleApp;

    class AppContext
    {
    public:
        static AppContext& instance();
        
        
        AppContext();
        
        
        /**
         * Register only one APP instance
         * @param app
         * @return 
         */
        bool registerApp( SimpleApp* app );
        
        
        /**
        * Wait for exit signal with the given timeout
        * @arg timeout Time in ms
        * @return true on signal, false on timeout
        */
        bool waitForExit( const uint32_t timeout = 0U );
        
        
        /**
         * Register the signal handler for the given Signal-Id
         * @param signal
         */
        void handleSignal( const int32_t signal );
        
        
    private:
        /**
         * Signal handler function. Forwards the call to the AppContext object.
         * @param signal
         */
        static void signalHandler( const int32_t signal );        
        
        
        /**
         * AppContext signal handler. Notifies the Application instance.
         * @param signal
         */
        void onSignal( const int32_t signal );
        
        /* Access protection */
        ::std::mutex m_mutex;
        
        
        /* Application Exit condition */
        ::std::condition_variable m_condExit;
        
        /* Set when exit requested via a SIGTERM */
        bool m_exitSignalRaised;
        
        /* Instance - Can be only single App in process */
        SimpleApp* m_instance;
    };

}; // namespace app
#endif // APPCONTEXT_H
