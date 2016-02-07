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

#ifndef DATAGRAM_H
#define DATAGRAM_H

#include <cstddef>
#include <stdint.h>

#include "net/Address.h"
#include "sys/AutoArray.h"

namespace net
{
    /* Maximum Datagram length in bytes */
    static const size_t MAX_UDP_DATAGRAM_LENGTH = 1408U;    
    
    /* Datagram payload type */
    typedef ::sys::AutoArray<uint8_t, MAX_UDP_DATAGRAM_LENGTH> TDataGramBuffer;
    
    class Datagram
    {
    public:            
        Datagram( const Address& addr = Address() );
        
        
        /**
         * Fill the Datagram with given raw data
         * @arg from
         * @arg bytes
         */
        void setContent( const void* from, const size_t bytes );
        
        
        /**
         * Fill the Datagram with text
         * @arg text
         */
        void setContent( const ::std::string& text );
        
        
        /**
         * Set the Datagram's recipent
         * @arg addr
         */
        void setAddress( const Address& addr );
        
        
        /**
         * Convert the payload into string
         */
        void toString( std::string& text ) const;
        
        
        const Address& getAddress() const
        {
            return m_address;
        }
        
        
        const TDataGramBuffer& getData() const
        {
            return m_payload;
        }
        
        
    private:    
        
        /* INET Address */
        Address m_address;
        
        /* Datagram content */
        TDataGramBuffer m_payload;
    };

}; // namespace net

#endif // DATAGRAM_H
