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

#ifndef SIMPLEAPP_H
#define SIMPLEAPP_H

#include <stdint.h>
#include <string>
#include <vector>

namespace app
{

    class SimpleApp
    {
    public:
        /* String Vector */
        typedef ::std::vector<std::string> TStringVector;
        
        explicit SimpleApp( const ::std::string& name );
        virtual ~SimpleApp();
        
        /**
        * Called from the main. Holds the main App loop
        * @param argc
        * @param argv
        */
        int32_t run( const int32_t argc, const char * const * argv  );
        
        
        /**
         * Invoked as a signal handler.
         * Implement this method if you need to handle any of the registered signals.
         * @param signal
         */
        virtual void onSignal( const int32_t signal )
        {            
        }        

    protected:    
        /**
        * Application loop
        * Called by the @run method implementation
        * @param args Command Line Arguments
        */
        virtual int32_t onRun( const TStringVector& args ) = 0;
               
        
        /**
        * Log method. By default to console.
        * @param message Log entry
        */
        virtual void log( const char* message );
        
        /* Expose the Application name */
        const ::std::string& getName() const
        {
            return m_name;
        }
            
        /**
        * Waits until the Application is closed by system Signal
        * @arg time Timeout in ms. 0 for no timeout.
        * @return true, if signal rised, false on timeout
        */
        bool waitForExit( const uint32_t timeout = 0U );
        
    private:
        /* Prohibit assignment */
        SimpleApp& operator = (const SimpleApp& other);
        
        /* Prohibit copying */
        SimpleApp (const SimpleApp & other);

        /* Application Name */
        const ::std::string m_name;
    };

}; // namespace app

#endif // SIMPLEAPP_H
