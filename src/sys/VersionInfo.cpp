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

/* 
 * File:   VersionInfo.cpp
 * Author: kret
 * 
 * Created on February 14, 2016, 5:23 PM
 */

#include "sys/VersionInfo.h"

namespace sys
{
    VersionInfo::VersionInfo( const uint16_t major = 0U, const uint16_t minor = 0U, const uint16_t patch = 0U )
        : m_major( major )
        , m_minor( minor )
        , m_patch( patch )
    {        
    }
    
    
    void VersionInfo::toString( ::esys::TString31& output, const ::esys::TString31& prefix ) const
    {
        if ( !prefix.empty() )
        {
            output.c_format( "%s%u.%u.%u", prefix.c_str(), m_major, m_minor, m_patch );
        }
        else
        {
            output.c_format( "%u.%u.%u", m_major, m_minor, m_patch );
        }
    }
    
    
    ::esys::TString31 VersionInfo::toString() const
    {
        ::esys::TString31 result;
        
        toString( result );
        
        return result;
    }
    
}; // namespace sys

