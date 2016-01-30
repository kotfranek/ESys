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

#include "app/SimpleApp.h"
#include "app/AppContext.h"
#include <iostream>


namespace app
{

SimpleApp::SimpleApp( const ::std::string& name )
    : m_name( name )
{   
    if ( AppContext::instance().registerApp( this ) )
    {
        log( "App registered" );
    }
}


int32_t SimpleApp::run( const int32_t argc, const char * const * argv  )
{
    TStringVector args;
    args.reserve( argc );
    
    for ( int32_t i = 0; i < argc; i++ )
    {
        args.push_back( ::std::string( *( argv + i ) ) );
    }

    const int32_t status = onRun( args );
            
    return status;
}


void SimpleApp::waitForSignal( const uint32_t time )
{
    if ( AppContext::instance().waitForExit( time ) )
    {
        log( "Exit due to signal" );
    }
    else
    {
        log( "Timeout" );
    }
}


void SimpleApp::log( const char* message )
{
    ::std::cout << getName() << "::" << message << ::std::endl;
}


SimpleApp::~SimpleApp()
{

}
    
}; // namespace app
