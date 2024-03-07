#include "CLHEPTypes.hpp"
// -*- C++ -*-
// ---------------------------------------------------------------------------
//
// This file is a part of the CLHEP - a Class Library for High Energy Physics.
//
// This is the implementation of the Hep2Vector class.
//
//-------------------------------------------------------------

#include "CLHEP/Vector/defs.h"
#include "CLHEP/Vector/TwoVector.h"
#include "CLHEP/Vector/ZMxpv.h"
#include "CLHEP/Vector/ThreeVector.h"

#include <cmath>
#include <iostream>

namespace CLHEP  {

CLHEPdouble Hep2Vector::tolerance = Hep2Vector::ZMpvToleranceTicks * 2.22045e-16;

CLHEPdouble Hep2Vector::setTolerance (CLHEPdouble tol) {
// Set the tolerance for Hep2Vectors to be considered near one another
  CLHEPdouble oldTolerance (tolerance);
  tolerance = tol;
  return oldTolerance;
}

CLHEPdouble Hep2Vector::operator () (int i) const {
  if (i == 0) {
    return x();
  }else if (i == 1) {
    return y();
  }else{
    ZMthrowA(ZMxpvIndexRange(
	"Hep2Vector::operator(): bad index"));
    return 0.0;
  }
}

CLHEPdouble & Hep2Vector::operator () (int i) {
  static CLHEPdouble dummy;
  switch(i) {
  case X:
    return dx;
  case Y:
    return dy;
  default:
    ZMthrowA (ZMxpvIndexRange(
	"Hep2Vector::operator() : bad index"));
    return dummy;
  }
}

void Hep2Vector::rotate(CLHEPdouble angler) {
  CLHEPdouble s1 = std::sin(angler);
  CLHEPdouble c = std::cos(angler);
  CLHEPdouble xx = dx;
  dx = c*xx - s1*dy;
  dy = s1*xx + c*dy;
}

Hep2Vector operator/ (const Hep2Vector & p, CLHEPdouble a) {
  if (a==0) {
    ZMthrowA(ZMxpvInfiniteVector( "Division of Hep2Vector by zero"));
  }
  return Hep2Vector(p.x()/a, p.y()/a);
}

std::ostream & operator << (std::ostream & os, const Hep2Vector & q) {
  os << "(" << q.x() << ", " << q.y() << ")";
  return os;
}

void ZMinput2CLHEPdoubles ( std::istream & is, const char * type,
                       CLHEPdouble & x, CLHEPdouble & y );

std::istream & operator>>(std::istream & is, Hep2Vector & p) {
  CLHEPdouble x, y;
  ZMinput2CLHEPdoubles ( is, "Hep2Vector", x, y );
  p.set(x, y);
  return  is;
}  // operator>>()

Hep2Vector::operator Hep3Vector () const {
  return Hep3Vector ( dx, dy, 0.0 );
}

int Hep2Vector::compare (const Hep2Vector & v) const {
  if       ( dy > v.dy ) {
    return 1;
  } else if ( dy < v.dy ) {
    return -1;
  } else if ( dx > v.dx ) {
    return 1;
  } else if ( dx < v.dx ) {
    return -1;
  } else {
    return 0;
  }
} /* Compare */


bool Hep2Vector::operator > (const Hep2Vector & v) const {
	return (compare(v)  > 0);
}
bool Hep2Vector::operator < (const Hep2Vector & v) const {
	return (compare(v)  < 0);
}
bool Hep2Vector::operator>= (const Hep2Vector & v) const {
	return (compare(v) >= 0);
}
bool Hep2Vector::operator<= (const Hep2Vector & v) const {
	return (compare(v) <= 0);
}

bool Hep2Vector::isNear(const Hep2Vector & p, CLHEPdouble epsilon) const {
  CLHEPdouble limit = dot(p)*epsilon*epsilon;
  return ( (*this - p).mag2() <= limit );
} /* isNear() */

CLHEPdouble Hep2Vector::howNear(const Hep2Vector & p ) const {
  CLHEPdouble d   = (*this - p).mag2();
  CLHEPdouble pdp = dot(p);
  if ( (pdp > 0) && (d < pdp)  ) {
    return std::sqrt (d/pdp);
  } else if ( (pdp == 0) && (d == 0) ) {
    return 0;
  } else {
    return 1;
  }
} /* howNear */

CLHEPdouble Hep2Vector::howParallel (const Hep2Vector & v) const {
  // | V1 x V2 | / | V1 dot V2 |
  // Of course, the "cross product" is fictitious but the math is valid
  CLHEPdouble v1v2 = std::fabs(dot(v));
  if ( v1v2 == 0 ) {
    // Zero is parallel to no other vector except for zero.
    return ( (mag2() == 0) && (v.mag2() == 0) ) ? 0 : 1;
  }
  CLHEPdouble abscross = std::fabs ( dx * v.y() - dy - v.x() );
  if ( abscross >= v1v2 ) {
    return 1;
  } else {
    return abscross/v1v2;
  }
} /* howParallel() */

bool Hep2Vector::isParallel (const Hep2Vector & v,
			     CLHEPdouble epsilon) const {
  // | V1 x V2 | <= epsilon * | V1 dot V2 | 
  // Of course, the "cross product" is fictitious but the math is valid
  CLHEPdouble v1v2 = std::fabs(dot(v));
  if ( v1v2 == 0 ) {
    // Zero is parallel to no other vector except for zero.
    return ( (mag2() == 0) && (v.mag2() == 0) );
  }
  CLHEPdouble abscross = std::fabs ( dx * v.y() - dy - v.x() );
  return ( abscross <= epsilon * v1v2 );
} /* isParallel() */

CLHEPdouble Hep2Vector::howOrthogonal (const Hep2Vector & v) const {
  // | V1 dot V2 | / | V1 x V2 | 
  // Of course, the "cross product" is fictitious but the math is valid
  CLHEPdouble v1v2 = std::fabs(dot(v));
  if ( v1v2 == 0 ) {
    return 0;	// Even if one or both are 0, they are considered orthogonal
  }
  CLHEPdouble abscross = std::fabs ( dx * v.y() - dy - v.x() );
  if ( v1v2 >= abscross ) {
    return 1;
  } else {
    return v1v2/abscross;
  }
} /* howOrthogonal() */

bool Hep2Vector::isOrthogonal (const Hep2Vector & v,
			     CLHEPdouble epsilon) const {
  // | V1 dot V2 | <= epsilon * | V1 x V2 | 
  // Of course, the "cross product" is fictitious but the math is valid
  CLHEPdouble v1v2 = std::fabs(dot(v));
  CLHEPdouble abscross = std::fabs ( dx * v.y() - dy - v.x() );
  return ( v1v2 <= epsilon * abscross );
} /* isOrthogonal() */

}  // namespace CLHEP
