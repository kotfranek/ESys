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

#include "app/AppContext.h"
#include <csignal>
#include <chrono> 

namespace
{
    ::app::AppContext g_appContext;
}

typedef ::std::lock_guard<std::mutex> TLockMutex;
typedef ::std::unique_lock<std::mutex> TLockUnique;

namespace app
{

AppContext& AppContext::instance()
{
    return g_appContext;
}


AppContext::AppContext()
    : m_mutex()
    , m_condExit()
    , m_flagExit( false )
    , m_instance( NULL )
{
    ::std::signal( SIGTERM, &AppContext::signalHandler );
    ::std::signal( SIGINT, &AppContext::signalHandler );
}


bool AppContext::registerApp( SimpleApp* app )
{        
    bool result = false;
    TLockMutex l( m_mutex );   
    
    if ( NULL == m_instance )
    {            
        m_instance = app;            
        result = true;
    }
    
    return result;
}


bool AppContext::waitForExit( const uint32_t timeout )
{
    bool result = false;
    
    TLockUnique l( m_mutex );
    
    if ( 0U == timeout )
    {
        m_condExit.wait( l );
        result = true;
    }
    else
    {
        result = std::cv_status::no_timeout == m_condExit.wait_for( l, ::std::chrono::milliseconds( timeout ) );
    }
    
    return result;
}



void AppContext::signalHandler( const int32_t signal )
{
    g_appContext.onSignal( signal );
}


void AppContext::onSignal( const int32_t signal )
{
    TLockMutex l( m_mutex );
    if ( NULL != m_instance )
    {
        switch( signal )
        {
            case SIGINT:
            case SIGTERM:
                m_flagExit = true;
                m_condExit.notify_all();
                break;
                
            default:
                break;
        }
    }
}

}; // namespace app
