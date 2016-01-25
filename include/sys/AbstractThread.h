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

#ifndef THREAD_H
#define THREAD_H

#include <thread>
#include <mutex>
#include <condition_variable>

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
    const ::std::string& getName() const
    {
        return m_name;
    }
    
    
    /**
     * Set the thread's priority value
     */
    void setPriority( const int32_t priority );
    
    /**
     * Make the current thread sleep for short time
     * @arg time in ms
     */
    static void sleep( const uint32_t time );
    
    
protected:
    explicit AbstractThread( const ::std::string& name ); 
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
    const ::std::string m_name;
    
    /* Thread state */
    ThreadState m_state;
    
    /* Condition */
    ::std::condition_variable m_condition;
    
    /* Actual Thread object */
    ::std::thread m_thread;
};

}; // namespace sys

#endif // THREAD_H
