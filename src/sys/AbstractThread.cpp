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

#include "sys/AbstractThread.h"
#include <iostream>

#if defined (__linux__ ) || ( defined (__unix__) ) || (defined (__APPLE__))
    #define THREAD_API_POSIX
    #include <pthread.h>
#elif defined ( _WIN32 )
    #define THREAD_API_WIN32
    #include <windows.h>
#endif

typedef ::std::lock_guard<std::mutex> TLockMutex;
typedef ::std::unique_lock<std::mutex> TLockUnique;

namespace
{
    void setThreadName( ::std::thread& object, const ::std::string& name )
    {
        auto handle = object.native_handle();
        #if defined (THREAD_API_POSIX)        
        pthread_setname_np( handle, name.c_str() );           
        #elif defined (THREAD_API_WIN32)
        // Sorry, no windows implementation available
        #else
            #error Not supported API
        #endif        
    }
    
    
    void setThreadPriority( ::std::thread& object, const int32_t priority )
    {
        auto handle = object.native_handle();
        #if defined (THREAD_API_POSIX)        
        pthread_setschedprio( handle, priority );
        #elif defined (THREAD_API_WIN32)
        SetThreadPriority( handle, priority );
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
        
        setThreadName( m_thread, m_name );
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
