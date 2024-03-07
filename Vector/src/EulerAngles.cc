#include "CLHEPTypes.hpp"
// ----------------------------------------------------------------------
//
// EulerAngles.cc
//
// Methods for classes, and instances of globals, declared in EulerAngles.h
//
// History:
//
// 04-Dec-1997	MF	Stub with just PI
// 12-Jan-1998  WEB	PI now found in ZMutility; used ZMutility headers
//			where available
// 16-Mar-1998  WEB	Corrected ZMpvEulerAnglesRep
// 15-Jun-1998  WEB	Added namespace support
// 26-Jul-2000  MF	CLHEP version
// 12-Apr-2001  MF  	NaN-proofing
// 19-Nov-2001  MF  	Correction to ZMpvEulerAnglesRep, which was affecting
//			.isNear().  array[3] had been incorrect.
//			Note - the correct form was used in all other places 
//			including Rotation.set(phi, theta, psi).
//
// ----------------------------------------------------------------------


#include "CLHEP/Vector/defs.h"
#include "CLHEP/Vector/EulerAngles.h"

#include "CLHEP/Vector/ThreeVector.h"

#include <cmath>
#include <iostream>

namespace CLHEP  {

//-*************
// static consts
//-*************

CLHEPdouble HepEulerAngles::tolerance = Hep3Vector::ToleranceTicks * 1.0e-8;

//-*******************
// measure of distance
//-*******************


static void ZMpvEulerAnglesRep ( const HepEulerAngles & ex, CLHEPdouble array[] ) {

  CLHEPdouble sinPhi   = std::sin( ex.phi() )  , cosPhi   = std::cos( ex.phi() );
  CLHEPdouble sinTheta = std::sin( ex.theta() ), cosTheta = std::cos( ex.theta() );
  CLHEPdouble sinPsi   = std::sin( ex.psi() )  , cosPsi   = std::cos( ex.psi() );

  array[0] =   cosPsi * cosPhi   - sinPsi * cosTheta * sinPhi;
  array[1] =   cosPsi * sinPhi   + sinPsi * cosTheta * cosPhi;
  array[2] =   sinPsi * sinTheta;

  array[3] = - sinPsi * cosPhi - cosPsi * cosTheta * sinPhi;
  array[4] = - sinPsi * sinPhi   + cosPsi * cosTheta * cosPhi;
  array[5] =   cosPsi * sinTheta;

  array[6] =   sinTheta * sinPhi;
  array[7] = - sinTheta * cosPhi;
  array[8] =   cosTheta;

} // ZMpvEulerAnglesRep


CLHEPdouble HepEulerAngles::distance( const EA & ex ) const  {

  CLHEPdouble thisRep[9];
  CLHEPdouble exRep[9];

  ZMpvEulerAnglesRep ( *this, thisRep );
  ZMpvEulerAnglesRep ( ex,    exRep );

  CLHEPdouble sum = 0.0;
  for (int i = 0; i < 9; i++)  {
    sum += thisRep[i] * exRep[i];
  }

  CLHEPdouble d = 3.0 - sum;		// NaN-proofing: 
  return  (d >= 0) ? d : 0;		// std::sqrt(distance) is used in howNear()

}  // HepEulerAngles::distance()


bool HepEulerAngles::isNear( const EA & ex, CLHEPdouble epsilon ) const  {

  return  distance( ex ) <= epsilon*epsilon ;

}  // HepEulerAngles::isNear()


CLHEPdouble HepEulerAngles::howNear( const EA & ex ) const  {

  return  std::sqrt( distance( ex ) );

}  // HepEulerAngles::howNear()

//-**************
// Global Methods
//-**************

std::ostream & operator<<(std::ostream & os, const HepEulerAngles & ea)
{
  os << "(" << ea.phi() << ", " << ea.theta() << ", " << ea.psi() << ")";
  return  os;
}  // operator<<()

void ZMinput3CLHEPdoubles ( std::istream & is, const char * type,
                       CLHEPdouble & x, CLHEPdouble & y, CLHEPdouble & z );

std::istream & operator>>(std::istream & is, HepEulerAngles & ea) {
  CLHEPdouble thePhi;
  CLHEPdouble theTheta;
  CLHEPdouble thePsi;
  ZMinput3CLHEPdoubles ( is, "HepEulerAngle", thePhi , theTheta , thePsi );
  ea.set ( thePhi , theTheta , thePsi );
  return  is;
}  // operator>>()

}  // namespace CLHEP


