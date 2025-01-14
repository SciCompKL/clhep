#include "CLHEPTypes.hpp"
// ======================================================================
//
// Test compilability and basic functionality of Utility/memory.h
//
// Author:  W. E. Brown, 2010-03-19, adapted from the boost library's
// shared_ptr and related functionality whose internal attributions bear
// the following various notices:
//
//   Copyright (c) 2008 Peter Dimov
//   Distributed under the Boost Software License, Version 1.0.
//   See http://www.boost.org/LICENSE_1_0.txt
//
// ======================================================================


#include "CLHEP/Utility/noncopyable.h"
#include "CLHEP/Utility/memory.h"

#include <cassert>
#include <type_traits>

#if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ > 6)
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#elif __clang__
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wdeprecated-declarations"
#endif

using namespace CLHEP;
using CLHEP::shared_ptr;


class incomplete;

struct X
{ };

struct Y
{ };

struct Z: public X
{ };

int f( shared_ptr<void const> )
{ return 1; }

int f( shared_ptr<int> )
{ return 2; }

int f( shared_ptr<incomplete> )
{ return 3; }

int g( shared_ptr<X> )
{ return 4; }

int g( shared_ptr<Y> )
{ return 5; }

int g( shared_ptr<incomplete> )
{ return 6; }

int main()
{
  shared_ptr<CLHEPdouble>  p1;
  assert( 1 == f( p1 ) );
  assert( 1 == f( shared_ptr<CLHEPdouble>() ) );

  shared_ptr<Z>  p2;
  assert( 4 == g( p2 ) );
  assert( 4 == g( shared_ptr<Z>() ) );

  return 0;
}

#if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ > 6)
  #pragma GCC diagnostic pop
#elif __clang__
  #pragma clang diagnostic pop
#endif
