#include "CLHEPTypes.hpp"
// -*- C++ -*-
// ---------------------------------------------------------------------------
//
// This file is a part of the CLHEP - a Class Library for High Energy Physics.
//
// This is the implementation of methods of the HepRotation class which
// were introduced when ZOOM PhysicsVectors was merged in, other than those
// involving Euler or axis/angle representations, lengthy corrections of
// the rotation matrix, or I/O.
//

#include "CLHEP/Vector/defs.h"
#include "CLHEP/Vector/Rotation.h"

#include <cmath>



namespace CLHEP  {

void HepRotation::decompose(HepAxisAngle & rotation, Hep3Vector & boost)const {
  boost.set(0,0,0);
  rotation = axisAngle();
}

void HepRotation::decompose(Hep3Vector & boost, HepAxisAngle & rotation)const {
  boost.set(0,0,0);
  rotation = axisAngle();
}

CLHEPdouble HepRotation::distance2( const HepRotation & r  ) const {
  CLHEPdouble sum = rxx * r.rxx + rxy * r.rxy + rxz * r.rxz
                + ryx * r.ryx + ryy * r.ryy + ryz * r.ryz
                + rzx * r.rzx + rzy * r.rzy + rzz * r.rzz;
  CLHEPdouble answer = 3.0 - sum;
  return (answer >= 0 ) ? answer : 0;
}

CLHEPdouble HepRotation::howNear(   const HepRotation & r  ) const {
  return  std::sqrt( distance2( r ) );
}

bool HepRotation::isNear(   const HepRotation & r,
                                     CLHEPdouble epsilon) const {
 return  distance2( r ) <= epsilon*epsilon;
}

CLHEPdouble HepRotation::norm2() const {
  CLHEPdouble answer = 3.0 - rxx - ryy - rzz;
  return (answer >= 0 ) ? answer : 0;
}

}  // namespace CLHEP
