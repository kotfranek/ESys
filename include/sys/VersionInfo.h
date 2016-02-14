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
 * File:   VersionInfo.h
 * Author: kret
 *
 * Created on February 14, 2016, 5:23 PM
 */

#include "esys/AutoString.h"

#ifndef VERSIONINFO_H
#define VERSIONINFO_H
namespace sys
{
    /**
     * VersionInfo
     * 
     * Holds the version information according to the
     * Semantic Versioning 2.0.0
     * 
     * For details see: http://semver.org/
     */
    class VersionInfo 
    {
    public:
        /**
         * Create the version info
         * @param major 
         * @param minor
         * @param patch
         */
        explicit VersionInfo( const uint16_t major, const uint16_t minor, const uint16_t patch );
        
        /**
         * Convert the version information to string in format:
         * prefixMAJOR.MINOR.PATCH
         * @param output Output String
         * @param prefix Prefix String, added before the version info
         */
        void toString( ::esys::TString31& output, const ::esys::TString31& prefix = "" ) const;
        
        /**
         * Convert the version information to string in format:
         * MAJOR.MINOR.PATCH
         * @return AutoString
         */
        ::esys::TString31 toString() const;
        
    private:
        
        /* Major Version */
        uint16_t m_major;
        
        /* Minor Version */
        uint16_t m_minor;
        
        /* Patch Version */
        uint16_t m_patch;
    };
}; // namespace sys
#endif /* VERSIONINFO_H */

