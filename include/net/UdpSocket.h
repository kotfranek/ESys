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

#ifndef UDPSOCKET_H
#define UDPSOCKET_H

#include "sys/SysTypes.h"
#include "net/NetTypes.h"
#include "net/Address.h"

#if defined ESYS_API_WIN32
#include <winsock2.h>
#include <windows.h>
#endif

namespace net
{
    class Datagram;
	
#if defined ESYS_API_POSIX	
	typedef int32_t TSocket;
#elif defined ESYS_API_WIN32
	typedef SOCKET TSocket;
#endif	
    
    class UdpSocket
    {
    public:
        UdpSocket();        
        ~UdpSocket();
        
        /**
         * Open the Socket for listening on given port
         * @arg port Port Number
         * @result true on success
         */
        bool open( const TPort port );
        
        
        /**
         * Set the SEND/RECEIVE timeout
         * @arg sndTimeout
         * @arg recvTimeout
         */
        void setTimeouts( const uint32_t sndTimeout, const uint32_t recvTimeout );
        
        
        /**
         * Bind to the given address
         * @arg Address
         */
        bool bind( const Address& addr );
        

        /**
         * Conenct to the given address
         * @arg Address
         */        
        bool connect( const Address& addr );
        
        /**
         * Send a datagram
         * @arg datagram
         * @result true on success
         */
        bool send( const Datagram& datagram );
        
        
        /**
         * Get a datagram
         * @arg datagram
         * @result true on success
         */
        bool receive( Datagram& datagram );
        
        
        /**
         * Close the Socket if was opened
         */
        void close();
        
        
        /**
         * Get the connected state
         * @return 
         */
        bool isConnected() const
        {
            return m_connected;
        }
        
    private:
        UdpSocket(const UdpSocket& other);        
        UdpSocket& operator=(const UdpSocket& other); 
        
        /* Socket Descriptor */
        TSocket m_socket;
        
        /* Socket connected flag */
        bool m_connected;
    };

}; // namespace net

#endif // UDPSOCKET_H
