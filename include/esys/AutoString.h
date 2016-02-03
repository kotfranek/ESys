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

#ifndef ESYS_AUTOSTRING_H
#define ESYS_AUTOSTRING_H

#include <cstddef>
#include <cstdarg>
#include <string.h>
#include <stdint.h>

#include "sys/AutoArray.h"

namespace esys
{
    /** 
     * Automatic String class 
     */
    template <class T, size_t N>class AutoString : public ::sys::AutoArray< T, N + 1U >
    {
    public:
        typedef ::sys::AutoArray<T, N+1U> TParent;
        AutoString()
            : TParent()           
        {
        }
        
        
        AutoString( typename TParent::const_pointer src )
            : TParent()
        {
            TParent::copyFrom( src, ::strlen( src ) );
        }
       
        AutoString( const AutoString& other )
            : TParent()        
        {
            clone( other );
        }
        
        /**
         * Store the formatted value as string
         * @result size of the output string
         * 
         */
        size_t c_format( typename TParent::const_pointer formatString, ... )
        {
            va_list args;
            va_start ( args, formatString );
            
            const size_t num = ::std::vsnprintf( TParent::begin(), TParent::CAPACITY, formatString, args );            
            
            va_end ( args );                
            return num;
        }
                                              
        
        /**
         * Get C string equivalent
         * @result pointer to the c-string representation
         */
        typename TParent::const_pointer c_str() const
        {
            return TParent::begin();
        }
        
    private:
   
    };
    
    /* 31 8-bit Character String */
    typedef AutoString<char, 31U> TString31;    
    
    /* 63 8-bit Character String */
    typedef AutoString<char, 63U> TString63;
    
    /* 255 8-bit Character String */
    typedef AutoString<char, 255U> TString255;
    
    /* 511 8-bit Character String */
    typedef AutoString<char, 511U> TString511;
    
    

}; // namespace esys

#endif // ESYS_AUTOSTRING_H
