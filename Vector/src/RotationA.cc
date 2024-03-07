#include "CLHEPTypes.hpp"
// -*- C++ -*-
// ---------------------------------------------------------------------------
//
// This file is a part of the CLHEP - a Class Library for High Energy Physics.
//
// This is the implementation of those methods of the HepRotation class which
// were introduced when ZOOM PhysicsVectors was merged in, and which involve 
// the angle/axis representation of a Rotation.
//

#include "CLHEP/Vector/defs.h"
#include "CLHEP/Vector/Rotation.h"
#include "CLHEP/Units/PhysicalConstants.h"

#include <iostream>
#include <cmath>

namespace CLHEP  {

// ----------  Constructors and Assignment:

// axis and angle

HepRotation & HepRotation::set( const Hep3Vector & aaxis, CLHEPdouble ddelta ) {

  CLHEPdouble sinDelta = std::sin(ddelta), cosDelta = std::cos(ddelta);
  CLHEPdouble oneMinusCosDelta = 1.0 - cosDelta;

  Hep3Vector u = aaxis.unit();

  CLHEPdouble uX = u.getX();
  CLHEPdouble uY = u.getY();
  CLHEPdouble uZ = u.getZ();

  rxx = oneMinusCosDelta * uX * uX  +  cosDelta;
  rxy = oneMinusCosDelta * uX * uY  -  sinDelta * uZ;
  rxz = oneMinusCosDelta * uX * uZ  +  sinDelta * uY;

  ryx = oneMinusCosDelta * uY * uX  +  sinDelta * uZ;
  ryy = oneMinusCosDelta * uY * uY  +  cosDelta;
  ryz = oneMinusCosDelta * uY * uZ  -  sinDelta * uX;

  rzx = oneMinusCosDelta * uZ * uX  -  sinDelta * uY;
  rzy = oneMinusCosDelta * uZ * uY  +  sinDelta * uX;
  rzz = oneMinusCosDelta * uZ * uZ  +  cosDelta;

  return  *this;

} // HepRotation::set(axis, delta)

HepRotation::HepRotation ( const Hep3Vector & aaxis, CLHEPdouble ddelta ) 
{
  set( aaxis, ddelta );
}  
HepRotation & HepRotation::set( const HepAxisAngle & ax ) {
  return  set ( ax.axis(), ax.delta() );
}
HepRotation::HepRotation ( const HepAxisAngle & ax ) 
{
  set ( ax.axis(), ax.delta() );
}

CLHEPdouble    HepRotation::delta() const {

  CLHEPdouble cosdelta = (rxx + ryy + rzz - 1.0) / 2.0;
  if (cosdelta > 1.0) {
    return 0;
  } else if (cosdelta < -1.0) {
    return CLHEP::pi;
  } else {
    return  std::acos( cosdelta ); // Already safe due to the cosdelta > 1 check
  }

} // delta()

Hep3Vector HepRotation::axis () const {

  const CLHEPdouble eps = 1e-15;

  CLHEPdouble Ux = rzy - ryz;
  CLHEPdouble Uy = rxz - rzx;
  CLHEPdouble Uz = ryx - rxy;
  if (std::abs(Ux) < eps && std::abs(Uy) < eps && std::abs(Uz) < eps) {

    CLHEPdouble cosdelta = (rxx + ryy + rzz - 1.0) / 2.0;
    if (cosdelta > 0.0) return Hep3Vector(0,0,1); // angle = 0, any axis is good

    CLHEPdouble xxt = (rxx + 1)/2;
    CLHEPdouble yyt = (ryy + 1)/2;
    CLHEPdouble zzt = (rzz + 1)/2;
    CLHEPdouble xyt = (rxy + ryx)/4;
    CLHEPdouble xzt = (rxz + rzx)/4;
    CLHEPdouble yzt = (ryz + rzy)/4;
    CLHEPdouble x, y, z;

    if (xxt > ryy && xxt > rzz) {
      x = std::sqrt(xxt);
      if (rzy - ryz < 0) x = -x;
      y = xyt/x;
      z = xzt/x;
      return  Hep3Vector( x, y, z ).unit();
    } else if (yyt > zzt) {
      y = std::sqrt(yyt);
      if (rxz - rzx < 0) y = -y;
      x = xyt/y;
      z = yzt/y;
      return  Hep3Vector( x, y, z ).unit();
    } else {
      z = std::sqrt(zzt);
      if (ryx - rxy < 0) z = -z;
      x = xzt/z;
      y = yzt/z;
      return  Hep3Vector( x, y, z ).unit();
    }
  } else {
    return  Hep3Vector( Ux, Uy, Uz ).unit();
  }

} // axis()

HepAxisAngle HepRotation::axisAngle() const {

  return HepAxisAngle (axis(), delta());

} // axisAngle() 


void HepRotation::setAxis (const Hep3Vector & aaxis) {
  set ( aaxis, delta() );
}

void HepRotation::setDelta (CLHEPdouble ddelta) {
  set ( axis(), ddelta );
}

}  // namespace CLHEP
