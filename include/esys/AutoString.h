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
#include <ostream>

#include "sys/AutoArray.h"

namespace esys
{
    /** 
     * Automatic String class.
     * The intention is to mimic the ::std::string API without the heap 
     * allocator.
     */
    template <class T, size_t N>class AutoString : public ::sys::AutoArray< T, N + 1U >
    {
        /* Parent class typename */
        typedef ::sys::AutoArray<T, N+1U> TParent;
        
        /* NULL-terminating Character */
        static const T CHAR_0 = '\0';
        
        /* Other AutoString specialization */
        //typedef AutoString<T, R> TAutoStringOther;
        
    public:
        /* Maximum value for size_t */
        static const size_t npos = TParent::CAPACITY;
        
        /**
         * Default constructor.
         * Creates empty string.
         */
        AutoString()
            : TParent()           
        {
            clear();
        }
        
        
        AutoString( typename TParent::const_pointer src )
            : TParent()
        {
            assign( src );
        }
       
        
        /**
         * Copy-constructor
         * @param other source
         */
        AutoString( const AutoString& other )
            : TParent()        
        {
            assign( other );
        }
        
        /**
         * Return length of string
         * @return length in bytes
         */
        size_t length() const
        {
            return ::strlen( TParent::begin() );
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
         * Clear string
         * Erases the contents of the string, which becomes an empty 
         * string (with a length of 0 characters).
         */
        void clear()
        {
            TParent::at( 0U ) = CHAR_0;
        }
        
        /**
         * Assign content to string
         * Assigns a new value to the string, replacing its current contents.
         * @param str
         * @return *this
         */
        AutoString& assign( typename TParent::const_pointer str )
        {
            const size_t end = ::std::min( N, ::strlen( str ) );
            ::strncpy( TParent::begin(), str, end );
            TParent::at( end ) = CHAR_0;
            
            return *this;
        }
        
        
        /**
         * Assign content to string
         * Assigns a new value to the string, replacing its current contents.
         * @param str
         * @return *this
         */
        template <size_t R>AutoString& assign( const AutoString<T,R>& str )
        {
            return assign( str.c_str() );
        }
        
        
        /**
         * Append to string
         * Extends the string by appending additional characters at 
         * the end of its current value
         * @param src
         * @return 
         */
        AutoString& append( typename TParent::const_pointer src )
        {
            safeCopyFrom( length(), src );
            return *this;
        }
        

        /**
         * Append to string
         * Extends the string by appending additional characters at 
         * the end of its current value
         * @param src
         * @return 
         */        
        template <size_t R>AutoString& append( const AutoString<T,R>& str )
        {
            return append( str.c_str() );
        }  
        
        
        /**
         * Check, if the string is empty
         * @return 
         */
        bool empty() const
        {
            return CHAR_0 == TParent::at( 0U );
        }
        
        
        /**
         * Compare two strings
         * @param str
         * @return true, if equal
         */
        template <size_t R> bool equals( const AutoString<T,R>& str ) const
        {
            bool result = false;
            
            if ( length() == str.length() )
            {
                result = 0 == ::strncmp( c_str(), str.c_str(), ::std::min( N, R ) );
            }
            
            return result;
        }
        
        
        /**
         * Find content in string
         * Searches the string for the first occurrence of the sequence 
         * specified by its arguments.
         * When pos is specified, the search only includes characters at or 
         * after position pos, ignoring any possible occurrences that include 
         * characters before pos.
         * @param s
         * @param pos
         * @return The position of the first character of the first match.
         */
        size_t find( typename TParent::const_pointer s, size_t pos = 0U ) const
        {
            size_t result = npos;
            
            if ( pos < length() )
            {
                typename TParent::const_pointer ptr = ::strstr( c_str() + pos, s ); 

                if ( NULL != ptr )
                {
                    result = ptr - TParent::begin();
                }
            }
            
            return result;
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
        void safeCopyFrom( const size_t index, typename TParent::const_pointer str )
        {
            const size_t myLength = length();
            const size_t end = ::std::min( N - myLength, ::strlen( str ) );
            
            ::strncpy( TParent::begin() + myLength, str, end );
            
            TParent::at( myLength + end ) = CHAR_0;            
        }
   
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

/**
 * Stream operator overload to let the ::esys::AutoString type string to be 
 * used in the native C++ environment
 * @param os ostream
 * @param str ::esys::AutoString instance
 * @return ostream reference 
 */
template <class T, size_t N> ::std::ostream& operator<< (::std::ostream& os, const ::esys::AutoString<T, N>& str)
{
    os << str.c_str();
    return os;
}

#endif // ESYS_AUTOSTRING_H
