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
#include "esys/utils.h"

#if defined ESYS_API_POSIX
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> 
#elif defined ESYS_API_WIN32
#include <winsock2.h>
#include <windows.h>
#endif

#include <iostream>

namespace
{
#if defined ESYS_API_POSIX	
    /* Invalid Socket Id */
    const ::net::TSocket INVALID_SOCKET = -1; 
  
    /* Socket error return code */
    const int32_t SOCKET_ERROR = -1;
#elif defined ESYS_API_WIN32
	typedef size_t socklen_t;
#endif   
    /* Socket Reusability */
    const int32_t OPT_REUSE_VALUE = 1;
    
    
    /* Test the socket validity */
    inline bool isSocketValid( const ::net::TSocket socket )
    {
        return socket != INVALID_SOCKET;
    }
    
        
    /**
     * Set the Socket option
     * @arg socketId
     * @arg optionName
     * @arg option
     * @result true on success
     */
    template<typename T> bool setSocketOption( const int32_t socketId, const int32_t optionName, const T& option )
    {
        return SOCKET_ERROR != ::setsockopt( socketId, SOL_SOCKET, optionName, &option, sizeof( T ) );
    }
        
}

namespace net
{

UdpSocket::UdpSocket()
    : m_socket()
    , m_connected( false )
{

}


bool UdpSocket::open( const TPort port )
{
    bool result = false;
    const int32_t socketId = socket( AF_INET, SOCK_DGRAM, IPPROTO_UDP );
    
    if ( ::isSocketValid( socketId ) )
    {
        m_socket = socketId;
                
        struct sockaddr_in addrOwn;
        Address( port ).toSockAddr( addrOwn );
        
        if ( SOCKET_ERROR != ::bind( m_socket, ( struct sockaddr * ) &addrOwn, sizeof( addrOwn ) ) )
        {
            result = ::setSocketOption( m_socket, SO_REUSEADDR, OPT_REUSE_VALUE );
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
    
    if ( ::isSocketValid( m_socket ) )
    {    
        const TDataGramBuffer& db = datagram.getData();
        
        struct sockaddr* socketAddress = NULL;
        size_t socketAddressSize = 0U;
        
        struct sockaddr_in addrTo;
        
        if ( !m_connected )
        {
            datagram.getAddress().toSockAddr( addrTo );
            socketAddress = (sockaddr*) &addrTo;
            socketAddressSize = sizeof( addrTo );          
        }
        
        if ( SOCKET_ERROR != ::sendto( m_socket, db.begin(), db.size(), 0, socketAddress, socketAddressSize ) )
        {
            result = true;
        }
        else
        {
            m_connected = false;
            ::std::cout << strerror(errno) << ::std::endl;
        }         
    }
    
    return result;
}


void UdpSocket::setTimeouts( const uint32_t sndTimeout, const uint32_t recvTimeout )
{
    if ( ::isSocketValid( m_socket ) )
    {
        struct timeval timeout;
        timeout.tv_sec = recvTimeout / 1000U;
        timeout.tv_usec = ( recvTimeout % 1000U ) * 1000;        
        ::setSocketOption( m_socket, SO_RCVTIMEO, timeout );
        
        timeout.tv_sec = sndTimeout / 1000U;
        timeout.tv_usec = ( sndTimeout % 1000U ) * 1000;
        ::setSocketOption( m_socket, SO_SNDTIMEO, timeout );     
    }
}


bool UdpSocket::connect( const Address& addr )
{
    if ( ::isSocketValid( m_socket ) )
    {
        struct sockaddr_in addrTo;
        
        addr.toSockAddr( addrTo );
        
        if ( SOCKET_ERROR != ::connect( m_socket, ( struct sockaddr * ) &addrTo, sizeof( addrTo ) ) )
        {
            m_connected = true;            
        }
    }
    
    return m_connected;
}




bool UdpSocket::receive( Datagram& datagram )
{
    bool result = false;    
    
    if ( ::isSocketValid( m_socket ) )
    {           
        struct sockaddr_in addrFrom;
        socklen_t slen = sizeof( addrFrom );
        ::esys::zeroMem( addrFrom );
        
        uint8_t buffer[ ::net::TDataGramBuffer::CAPACITY ];
               
        const ssize_t count = recvfrom( m_socket, buffer, sizeof( buffer ), 
                                        0 , (struct sockaddr*) &addrFrom, &slen );     
        
        if( SOCKET_ERROR != count )
        {
            Address incomingAddr;
            incomingAddr.fromSockAddr( addrFrom );
            
            datagram.setContent( buffer, count );
            datagram.setAddress( incomingAddr ); 
            
            result = true;
        }        
    }
    
    return result;
}


void UdpSocket::close()
{
#if defined ESYS_API_POSIX
    ::close( m_socket );
#elif defined ESYS_API_WIN32
	::closesocket( m_socket );
	::WSACleanup();
#endif	
}



UdpSocket::~UdpSocket()
{
    close();
}

}; // namespace net
