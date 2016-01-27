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

#include "net/UdpSocket.h"
#include "net/Datagram.h"

#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> 

#include <iostream>
#include <cstring>

namespace
{
    /* Invalid Socket Id */
    const int32_t SOCKET_INVALID = -1; 
    
    
    template<typename T> void zeroMem( T& object )
    {
        ::memset( &object, 0, sizeof( T ) );
    }
        
}

namespace net
{

UdpSocket::UdpSocket()
    : m_socket()
{

}


bool UdpSocket::open( const uint16_t port )
{
    bool result = false;
    const int32_t socketId = socket( AF_INET, SOCK_DGRAM, IPPROTO_UDP );
    
    if ( ::SOCKET_INVALID != socketId )
    {
        m_socket = socketId;
                
        struct sockaddr_in addrOwn;
        Address( port ).toSockAddr( addrOwn );
        
        if ( -1 != ::bind( m_socket, ( struct sockaddr * ) &addrOwn, sizeof( addrOwn ) ) )
        {
            ::std::cout << "BIND" << ::std::endl;
            result = true;
            int optval = 1;
            setsockopt(m_socket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof optval);
        }
        else
        {
            ::std::cout << strerror(errno) << ::std::endl;
        }

    }
        
    return result;
}


bool UdpSocket::send( const Datagram& datagram )
{
    bool result = false;
    
    if ( ::SOCKET_INVALID != m_socket )
    {    
        struct sockaddr_in addrTo;
        
        datagram.getAddress().toSockAddr( addrTo );
        
        if ( -1 != sendto( m_socket, "BA", 2, 0, ( struct sockaddr * )&addrTo, sizeof( addrTo )) )
        {
            ::std::cout << "SENT" << ::std::endl;
            result = true;
        }
        else
        {
            ::std::cout << strerror(errno) << ::std::endl;
        }    
    }
    
    return result;
}


void UdpSocket::setTimeouts( const uint32_t sndTimeout, const uint32_t recvTimeout )
{
    if ( ::SOCKET_INVALID != m_socket )
    {
        struct timeval timeout;
        timeout.tv_sec = recvTimeout / 1000U;
        timeout.tv_usec = ( recvTimeout % 1000U ) * 1000;
        if ( -1 == ::setsockopt( m_socket, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof( timeout ) ) )
        {
            ::std::cout << strerror(errno) << ::std::endl;            
        }
        timeout.tv_sec = sndTimeout / 1000U;
        timeout.tv_usec = ( sndTimeout % 1000U ) * 1000;
        if ( -1 == ::setsockopt( m_socket, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof( timeout ) ) )
        {
            ::std::cout << strerror(errno) << ::std::endl;            
        }        
    }
}



bool UdpSocket::receive( Datagram& datagram )
{
    bool result = false;    
    
    if ( ::SOCKET_INVALID != m_socket )
    {           
        struct sockaddr_in addrFrom;
        socklen_t slen = sizeof( addrFrom );
        ::zeroMem( addrFrom );
        
        uint8_t buffer[ ::net::TDataGramBuffer::CAPACITY ];
        
        ::std::cout << "waiting..." << ::std::endl;
               
        const ssize_t count = recvfrom( m_socket, buffer, sizeof( buffer ), 
                                        0 , (struct sockaddr*) &addrFrom, &slen );     
        
        if( -1 != count )
        {
            Address incomingAddr;
            incomingAddr.fromSockAddr( addrFrom );
            
            datagram.setData( buffer, count );
            datagram.setAddress( incomingAddr ); 
            
            result = true;
        }
        else
        {             
            ::std::cout <<"RECV: " << strerror(errno) << ::std::endl;       
        }
        
    }
    
    return result;
}


void UdpSocket::close()
{
    ::close( m_socket );
}



UdpSocket::~UdpSocket()
{
    close();
}

}; // namespace net
