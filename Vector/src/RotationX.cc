#include "CLHEPTypes.hpp"
// -*- C++ -*-
// ---------------------------------------------------------------------------
//
// This file is a part of the CLHEP - a Class Library for High Energy Physics.
//
// This is the implementation of methods of the HepRotationX class which
// were introduced when ZOOM PhysicsVectors was merged in.
//

#include "CLHEP/Vector/defs.h"
#include "CLHEP/Vector/RotationX.h"
#include "CLHEP/Vector/AxisAngle.h"
#include "CLHEP/Vector/EulerAngles.h"
#include "CLHEP/Vector/LorentzRotation.h"
#include "CLHEP/Units/PhysicalConstants.h"

#include <cmath>
#include <stdlib.h>
#include <iostream>

namespace CLHEP  {

static inline CLHEPdouble safe_acos (CLHEPdouble x) {
  if (std::abs(x) <= 1.0) return std::acos(x);
  return ( (x>0) ? 0 : CLHEP::pi );
}

HepRotationX::HepRotationX(CLHEPdouble ddelta) : 
		its_d(proper(ddelta)), its_s(std::sin(ddelta)), its_c(std::cos(ddelta))
{}

HepRotationX & HepRotationX::set ( CLHEPdouble ddelta ) {
  its_d = proper(ddelta);
  its_s = std::sin(its_d);
  its_c = std::cos(its_d);
  return *this;
}

CLHEPdouble  HepRotationX::phi() const {
  if ( (its_d > 0) && (its_d < CLHEP::pi) ) {
    return CLHEP::pi;
  } else {
    return 0.0;
  }
}  // HepRotationX::phi()

CLHEPdouble  HepRotationX::theta() const {
  return  std::fabs( its_d );
}  // HepRotationX::theta()

CLHEPdouble  HepRotationX::psi() const {
  if ( (its_d > 0) && (its_d < CLHEP::pi) ) {
    return CLHEP::pi;
  } else {
    return 0.0;
  }
}  // HepRotationX::psi()

HepEulerAngles HepRotationX::eulerAngles() const {
  return HepEulerAngles(  phi(), theta(),  psi() );
}  // HepRotationX::eulerAngles()


// From the defining code in the implementation of CLHEP (in Rotation.cc)
// it is clear that thetaX, phiX form the polar angles in the original
// coordinate system of the new X axis (and similarly for phiY and phiZ).
//
// This code is taken directly from the original CLHEP. However, there are as
// shown opportunities for significant speed improvement.

CLHEPdouble HepRotationX::phiX() const {
  return (yx() == 0.0 && xx() == 0.0) ? 0.0 : std::atan2(yx(),xx());
  		// or ---- return 0;
}

CLHEPdouble HepRotationX::phiY() const {
  return (yy() == 0.0 && xy() == 0.0) ? 0.0 : std::atan2(yy(),xy());
		// or ----  return (yy() == 0.0) ? 0.0 : std::atan2(yy(),xy());
}

CLHEPdouble HepRotationX::phiZ() const {
  return (yz() == 0.0 && xz() == 0.0) ? 0.0 : std::atan2(yz(),xz());
		// or ----  return (yz() == 0.0) ? 0.0 : std::atan2(yz(),xz());
}

CLHEPdouble HepRotationX::thetaX() const {
  return safe_acos(zx());
		// or ----  return CLHEP::halfpi;
}

CLHEPdouble HepRotationX::thetaY() const {
  return safe_acos(zy());
}

CLHEPdouble HepRotationX::thetaZ() const {
  return safe_acos(zz());  
		// or ---- return d;
}

void HepRotationX::setDelta ( CLHEPdouble ddelta ) {
  set(ddelta);
}

void HepRotationX::decompose
	(HepAxisAngle & rotation, Hep3Vector & boost) const {
  boost.set(0,0,0);
  rotation = axisAngle();
}

void HepRotationX::decompose
	(Hep3Vector & boost, HepAxisAngle & rotation) const {
  boost.set(0,0,0);
  rotation = axisAngle();
}

void HepRotationX::decompose
        (HepRotation & rotation, HepBoost & boost) const {
  boost.set(0,0,0);
  rotation = HepRotation(*this);
} 

void HepRotationX::decompose
        (HepBoost & boost, HepRotation & rotation) const {
  boost.set(0,0,0);
  rotation = HepRotation(*this);
}

CLHEPdouble HepRotationX::distance2( const HepRotationX & r  ) const {
  CLHEPdouble answer = 2.0 * ( 1.0 - ( its_s * r.its_s + its_c * r.its_c ) ) ;
  return (answer >= 0) ? answer : 0;
}

CLHEPdouble HepRotationX::distance2( const HepRotation & r  ) const {
  CLHEPdouble sum =        r.xx() + 
                		  yy() * r.yy() + yz() * r.yz()
                		+ zy() * r.zy() + zz() * r.zz();
  CLHEPdouble answer = 3.0 - sum;
  return (answer >= 0 ) ? answer : 0;
}

CLHEPdouble HepRotationX::distance2( const HepLorentzRotation & lt  ) const {
  HepAxisAngle a; 
  Hep3Vector   b;
  lt.decompose(b, a);
  CLHEPdouble bet = b.beta();
  CLHEPdouble bet2 = bet*bet;
  HepRotation r(a);
  return bet2/(1-bet2) + distance2(r);
}

CLHEPdouble HepRotationX::distance2( const HepBoost & lt ) const {
  return distance2( HepLorentzRotation(lt));
}

CLHEPdouble HepRotationX::howNear( const HepRotationX & r ) const {
  return std::sqrt(distance2(r));
}
CLHEPdouble HepRotationX::howNear( const HepRotation & r ) const {
  return std::sqrt(distance2(r));
}
CLHEPdouble HepRotationX::howNear( const HepBoost & b ) const {
  return std::sqrt(distance2(b));
}
CLHEPdouble HepRotationX::howNear( const HepLorentzRotation & lt ) const {
  return std::sqrt(distance2(lt));
}
bool HepRotationX::isNear(const HepRotationX & r,CLHEPdouble epsilon)const{
  return (distance2(r) <= epsilon*epsilon);
}
bool HepRotationX::isNear(const HepRotation & r,CLHEPdouble epsilon) const{
  return (distance2(r) <= epsilon*epsilon);
}
bool HepRotationX::isNear( const HepBoost & lt,CLHEPdouble epsilon) const {
  return (distance2(lt) <= epsilon*epsilon);
}

bool HepRotationX::isNear( const HepLorentzRotation & lt,
                                     CLHEPdouble epsilon ) const {
  return (distance2(lt) <= epsilon*epsilon);
}

CLHEPdouble HepRotationX::norm2() const {
  return 2.0 - 2.0 * its_c;
}

std::ostream & HepRotationX::print( std::ostream & os ) const {
  os << "\nRotation about X (" << its_d << 
		") [cos d = " << its_c << " sin d = " << its_s << "]\n";
  return os;
}

}  // namespace CLHEP

