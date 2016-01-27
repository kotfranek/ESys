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

#ifndef NET_ADDRESS_H
#define NET_ADDRESS_H

#include <string>

struct sockaddr_in;

namespace net 
{

    class Address
    {
    public:
        /**
         * Constructor
         * @arg addr
         * @arg port
         */
        explicit Address( const uint16_t port = 0U, const ::std::string& addr = "" );
        
        /**
         * Set the address based on the given sockaddr struct
         * @arg addr
         */
        void fromSockAddr( const struct sockaddr_in& addr );
        
        /**
         * Fill the sockaddr
         * @arg addr
         */
        void toSockAddr( struct sockaddr_in& addr ) const;
        
        /**
         * @result Address
         */
        const ::std::string& getIp() const
        {
            return m_address;
        }
        
        /*
         * @result Port
         */
        uint16_t getPort() const
        {
            return m_port;
        }
        
    private:
        
        /* Port Number */
        uint16_t m_port;
        
        /* Address */
        ::std::string m_address;
    };

}; // namespace net

#endif // NET_ADDRESS_H
