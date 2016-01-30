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

#ifndef AUTOARRAY_H
#define AUTOARRAY_H

#include <cstddef>
#include <algorithm>
#include <stdint.h>

namespace sys
{

    template <class T, size_t N>class AutoArray
    {
    public:
        
        static const size_t CAPACITY = N;
        
        AutoArray()
            : m_size( 0U )
        {
        }
       
        AutoArray( const AutoArray& other )
        {
            copyFrom( other.m_data, other.m_size );
        }
        
        const T* begin() const
        {
            return m_data;
        }
        
        T* end()
        {
            return m_data + m_size;
        }
        
        /**
         * Array operator
         * @result const element reference
         */
        T const& operator []( const std::size_t n ) const
        {
            return m_data[ n ];
        }
        
        /**
         * Array operator
         * @result element reference
         */
        T& operator []( const std::size_t n )
        {
            return m_data[ n ];
        } 
        
        
        /**
         * Fill the data using the raw source 
         * @arg src
         * @arg num
         */
        void copyFrom( const T* src, const size_t num )
        {
            for ( m_size = 0U; m_size < ::std::min( num, N ); m_size++ )
            {
                m_data[ m_size ] = src[ m_size ];
            }
        }
        
        /**
         * Assignment operator
         */
        AutoArray& operator=( const AutoArray& other )
        {
            copyFrom( other.m_data, other.m_size );
        }
        
        
        bool operator==(const AutoArray& other) const;
        
        /**
         * Get the number of used elements
         * @result number of used elements
         */
        constexpr size_t size() const
        {
            return m_size;
        }
        
        /**
         * Get the capacity
         * @result maximum number of elements
         */
        constexpr size_t capacity() const
        {
            return N;
        }        
        
    private:
        
        /* Number of elements in use */
        size_t m_size;
        
        /* Automatic buffer of N capacity */
        T m_data[ N ];        
    };
    
    
    typedef AutoArray< uint8_t, 1024U> TByteBuffer1024;

}; // namespace sys

#endif // AUTOARRAY_H
