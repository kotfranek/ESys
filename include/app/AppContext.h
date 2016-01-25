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
        
        
        bool registerApp( SimpleApp* app );
        
        
        /**
        * Wait for exit signal with the given timeout
        * @arg timeout Time in ms
        * @return true on signal, false on timeout
        */
        bool waitForExit( const uint32_t timeout = 0U );
        
        
    private:
        static void signalHandler( const int32_t signal );        
        
        
        void onSignal( const int32_t signal );
        
        /* Access protection */
        ::std::mutex m_mutex;
        
        
        /* Application Exit condition */
        ::std::condition_variable m_condExit;
        
        /* Set when exit requested via a SIGTERM */
        bool m_flagExit;
        
        /* Instance - Can be only single App in process */
        SimpleApp* m_instance;
    };

}; // namespace app
#endif // APPCONTEXT_H
