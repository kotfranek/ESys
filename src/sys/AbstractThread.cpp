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

#include "sys/ESysDefs.h"
#include "sys/AbstractThread.h"
#include <iostream>

#if defined ESYS_API_POSIX
    #include <pthread.h>
#elif defined ESYS_API_WIN32
    #include <windows.h>
#endif

namespace
{
    void setThreadName( ::std::thread& object, const ::std::string& name )
    {
        auto handle = object.native_handle();
        #if defined (ESYS_API_POSIX)        
        ::pthread_setname_np( handle, name.c_str() );           
        #elif defined (ESYS_API_WIN32)
        // Sorry, no windows implementation available
        #else
            #error Not supported API
        #endif        
    }
    
    
    void setThreadPriority( ::std::thread& object, const int32_t priority )
    {
        auto handle = object.native_handle();
        #if defined (ESYS_API_POSIX)        
        ::pthread_setschedprio( handle, priority );
        #elif defined (ESYS_API_WIN32)
        ::SetThreadPriority( handle, priority );
        #else
            #error Not supported OS
        #endif         
    }
};

namespace sys 
{

void AbstractThread::trampoline( AbstractThread* object )
{
    object->threadBody();
}

    

AbstractThread::AbstractThread( const std::string& name )
    : m_mutex()
    , m_name( name )
    , m_state( AbstractThread::ThreadState_New )
    , m_condition()
    , m_thread()
{

}


bool AbstractThread::start()
{
    bool result = false;
    
    TLockMutex l( m_mutex );
    
    if ( isState( ThreadState_New ) )
    {
        setState( ThreadState_Running );
        m_thread = std::thread( &AbstractThread::trampoline, this );
        result = m_thread.joinable();
        
        ::setThreadName( m_thread, m_name );
    }                     
    
    return result;
}


void AbstractThread::requestStop()
{
    TLockMutex l( m_mutex );    

    if ( isState( ThreadState_Running ) )
    {
        setState( ThreadState_StopRequested );
    }
}


void AbstractThread::threadBody()
{    
    {
        TLockMutex l( m_mutex );
        
        if ( isState( ThreadState_Running ) )
        {     
            m_mutex.unlock();
            run();        
            m_mutex.lock();
        }
    }
    
    TLockUnique lo( m_mutex );
    setState( ThreadState_Stopped );
    m_condition.notify_all();
}



bool AbstractThread::join( const uint32_t timeout )
{
    bool result = false;
    
    TLockUnique l( m_mutex );
    
    if ( !isState( ThreadState_New ) )
    {             
        while( !isState( ThreadState_Stopped ) )
        {           
            m_condition.wait( l );
        }                
        
        if( m_thread.joinable() )
        {
            m_thread.join();
            result = true;
        }
    }
        
    return result;
}


void AbstractThread::sleep( const uint32_t time )
{
    ::std::this_thread::sleep_for ( std::chrono::milliseconds( time ) );
}


void AbstractThread::setPriority( const int32_t priority )
{
    TLockMutex l( m_mutex );
    
    if ( isState( ThreadState_Running ) )
    {
        setThreadPriority( m_thread, priority );
    }
}




bool AbstractThread::isStopRequested()
{
    TLockMutex l( m_mutex );
    
    return isState( ThreadState_StopRequested );
}




AbstractThread::~AbstractThread()
{
    requestStop();
    join();
}

}; // namespace sys
