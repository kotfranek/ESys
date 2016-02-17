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

#ifndef THREAD_H
#define THREAD_H

#include <thread>
#include <mutex>
#include <condition_variable>

#include "esys/AutoString.h"

/**
 * Thread Abstraction Class
 * Object Oriented apporach to multithreading in C++11
 * Implement the void run() method
 * 
 * Newly created object does not start Execution.
 * Calling start will 
 */

namespace sys
{

class AbstractThread
{
public:
    virtual ~AbstractThread();
    
    /**
     * Start the thread.
     * Success only when state is New
     */
    bool start();
    
    /* Request Thread stop. Possible only in state Running */
    void requestStop();
    
    
    /**
     * Wait for the thread to finish with given timeout.
     * @arg timeout in ms
     */
    bool join( const uint32_t timeout = 0U );
    
    /**
     * Expose the Thread name
     */
    const ::esys::TString31& getName() const
    {
        return m_name;
    }
    
    
    /**
     * Set the thread's priority value
     */
    void setPriority( const int32_t priority );
    
    /**
     * Make the current thread sleep for short time
     * Milliseconds version.
     * @arg time in ms
     */
    static void sleep( const uint32_t time );
    
    
    /**
     * Make the current thread sleep for short time.
     * Microseconds version.
     * @arg time in us
     */
    static void sleepUs( const uint32_t time );    
    
protected:
    explicit AbstractThread( const ::esys::TString31& name ); 
    /* Thread body 
     * Thread will not stop until this method exits.
     */
    virtual void run() = 0;
    
    /* Poll this while running to be able to exit nicely */
    bool isStopRequested();
        
private:
    
    /* Possible thread states */
    enum ThreadState
    {
        ThreadState_New,
        ThreadState_Running,
        ThreadState_StopRequested,
        ThreadState_Stopped,
    };
    
    /**
     * Check if current state equals the given one
     * This has to be called with the Mutex locked!
     */
    bool isState( const ThreadState state ) const
    {
        return state == m_state;
    }
    
    
    /**
     * Set the new state
     * @arg state
     */
    void setState( const ThreadState state )
    {
        m_state = state;
    }
    
    
    /** 
     * Internal thread body implementation. 
     * Executes the run() method 
     */
    void threadBody();
    
    
    /**
     * Thread trampoline.
     * This is actually executed by the multithreading framework
     */
    static void trampoline( AbstractThread* object );

    
    AbstractThread& operator=(const AbstractThread& other);
    AbstractThread(const AbstractThread& other);

    /* Data access protection */
    ::std::mutex m_mutex;
        
    /* Thread name */
    const ::esys::TString31 m_name;
    
    /* Thread state */
    ThreadState m_state;
    
    /* Condition */
    ::std::condition_variable m_condition;
    
    /* Actual Thread object */
    ::std::thread m_thread;
};

}; // namespace sys

#endif // THREAD_H
