/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   utils.h
 * Author: kret
 *
 * Created on February 6, 2016, 11:16 PM
 */

#ifndef ESYS_UTILS_H
#define ESYS_UTILS_H

#include <cstring>
#include <stdint.h>

namespace esys
{
    /**
     * Serialize as a Low-Endian
     * @param dest
     * @param variable
     * @return number of bytes written
     */
    template<class T> size_t serialize( void* dest, const T& variable )
    {
        uint8_t* auxDest = (uint8_t*) dest;

        for( size_t i = 0U; i < sizeof( T ); i++ )
        {
            *( auxDest + i ) = static_cast<uint8_t>( ( variable >> ( 8U * i ) ) & 0xFF );
        } 

        return sizeof( T );
    }
    
    
    /**
     * Set the memory region with zeroes
     * @param object
     */
    template<typename T> void zeroMem( T& object )
    {
        ::memset( &object, 0, sizeof( T ) );
    }    
}


#endif /* ESYS_UTILS_H */

