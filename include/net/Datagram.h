/*
 * Copyright (c) 2016, <copyright holder> <email>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *     * Neither the name of the <organization> nor the
 *     names of its contributors may be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY <copyright holder> <email> ''AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL <copyright holder> <email> BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef DATAGRAM_H
#define DATAGRAM_H

#include <cstddef>
#include <stdint.h>

#include "net/Address.h"
#include "sys/AutoArray.h"

namespace net
{
    /* Maximum Datagram length in bytes */
    static const size_t MAX_LENGTH = 1024U;    
    
    typedef ::sys::AutoArray<uint8_t, MAX_LENGTH> TDataGramBuffer;
    
    class Datagram
    {
    public:
        /* Maximum Datagram length in bytes */
        static const size_t MAX_LENGTH = 1470U;
            
        Datagram( const Address& addr = Address() );
        
        void setData( const void* from, const size_t bytes );
        
        
        void setAddress( const Address& addr );
        
        
        const Address& getAddress() const
        {
            return m_address;
        }
        
        
        const TDataGramBuffer& getData() const
        {
            return m_data;
        }
        
        
    private:    
        
        /* INET Address */
        Address m_address;
        
        /* Datagram content */
        TDataGramBuffer m_data;
    };

}; // namespace net

#endif // DATAGRAM_H
