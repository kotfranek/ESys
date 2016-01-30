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

#include "app/AppContext.h"
#include "sys/ESysDefs.h"
#include <csignal>
#include <chrono> 

namespace
{
    ::app::AppContext g_appContext;
}


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
    ::sys::TLockMutex l( m_mutex );   
    
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
    
    ::sys::TLockUnique l( m_mutex );
    
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
    ::sys::TLockMutex l( m_mutex );
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
