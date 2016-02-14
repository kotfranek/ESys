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

#include "net/Address.h"
#include "esys/utils.h"

#include <netinet/in.h>
#include <arpa/inet.h>

namespace net
{

Address::Address( const uint16_t port, const TStringIp& addr )
    : m_port( port )
    , m_address( addr )
{

}


void Address::toSockAddr( sockaddr_in& addr ) const
{
    ::esys::zeroMem( addr );
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons( m_port );
    addr.sin_addr.s_addr = htonl( INADDR_ANY );
    
    if ( !m_address.empty() )
    {
        ::inet_aton( m_address.c_str(), &addr.sin_addr );    
    }
}


void Address::fromSockAddr( const sockaddr_in& addr )
{    
    m_port = ntohs( addr.sin_port ); 
    m_address.assign( ::inet_ntoa( addr.sin_addr ) );    
}


}; // namespace net
