#include "CLHEPTypes.hpp"
////////////////////////////////////////////////////////////////////////
//
// File: pretend.hh
// Purpose: This is to fake out the gcc -pedantic switch 
//
// Author:  Walter Brown
//
////////////////////////////////////////////////////////////////////////

#ifndef PRETEND_HH
#define PRETEND_HH

template< class T >
inline
void  pretend_to_use( T const & )
{}

#endif // #ifndef PRETEND_HH
