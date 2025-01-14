#include "CLHEPTypes.hpp"
// -*- C++ -*-
// ---------------------------------------------------------------------------
//
// This file is a part of the CLHEP - a Class Library for High Energy Physics.
//
// This is the implementation of the HepBoostZ class.
//

#include "CLHEP/Vector/defs.h"
#include "CLHEP/Vector/BoostZ.h"
#include "CLHEP/Vector/Boost.h"
#include "CLHEP/Vector/Rotation.h"
#include "CLHEP/Vector/LorentzRotation.h"
#include "CLHEP/Vector/ZMxpv.h"

#include <cmath>
#include <iostream>

namespace CLHEP  {

// ----------  Constructors and Assignment:

HepBoostZ & HepBoostZ::set (CLHEPdouble bbeta) {
  CLHEPdouble b2 = bbeta*bbeta;
  if (b2 >= 1) {
    ZMthrowA (ZMxpvTachyonic(
    "Beta supplied to set HepBoostZ represents speed >= c."));
    beta_  = 1.0 - 1.0E-8;              // NaN-proofing
    gamma_ = 1.0 / std::sqrt(1.0 - b2);
    return *this;
  }    
  beta_  = bbeta;
  gamma_ = 1.0 / std::sqrt(1.0 - b2);
  return *this;
}

// ----------  Accessors:

HepRep4x4 HepBoostZ::rep4x4() const {
  CLHEPdouble bg = beta_*gamma_;
  return HepRep4x4(   1,      0,    0,    0,
		      0,      1,    0,    0,
                      0,      0,  gamma_, bg, 
		      0,      0,   bg,  gamma_ );
}

HepRep4x4Symmetric HepBoostZ::rep4x4Symmetric() const {
  CLHEPdouble bg = beta_*gamma_;
  return HepRep4x4Symmetric(   1,      0,    0,    0,
		      		       1,    0,    0,
                      		           gamma_, bg, 
		      				  gamma_ );
}

// ----------  Decomposition:

void HepBoostZ::decompose (HepRotation & rotation, HepBoost & boost) const {
  HepAxisAngle vdelta = HepAxisAngle();
  rotation = HepRotation(vdelta);
  Hep3Vector bbeta = boostVector();
  boost = HepBoost(bbeta);
}

void HepBoostZ::decompose (HepAxisAngle & rotation, Hep3Vector & boost) const {
  rotation = HepAxisAngle();
  boost = boostVector();
}

void HepBoostZ::decompose (HepBoost & boost, HepRotation & rotation) const {
  HepAxisAngle vdelta = HepAxisAngle();
  rotation = HepRotation(vdelta);
  Hep3Vector bbeta = boostVector();
  boost = HepBoost(bbeta);
}

void HepBoostZ::decompose (Hep3Vector & boost, HepAxisAngle & rotation) const {
  rotation = HepAxisAngle();
  boost = boostVector();
}

// ----------  Comparisons:

CLHEPdouble HepBoostZ::distance2( const HepBoost & b ) const {
  return b.distance2(*this);
}

CLHEPdouble HepBoostZ::distance2( const HepRotation & r ) const {
  CLHEPdouble db2 = norm2();
  CLHEPdouble dr2  = r.norm2();
  return (db2 + dr2);
}

CLHEPdouble HepBoostZ::distance2( const HepLorentzRotation & lt ) const {
  HepBoost b1;
  HepRotation r1;
  lt.decompose(b1,r1);
  CLHEPdouble db2 = distance2(b1);
  CLHEPdouble dr2  = r1.norm2();
  return (db2 + dr2);
}

bool HepBoostZ::isNear (const HepRotation & r, CLHEPdouble epsilon) const {
  CLHEPdouble db2 = norm2();
  if (db2 > epsilon*epsilon) return false;
  CLHEPdouble dr2  = r.norm2();
  return (db2+dr2 <= epsilon*epsilon);
}

bool HepBoostZ::isNear ( const HepLorentzRotation & lt, 
					CLHEPdouble epsilon  ) const {
  HepBoost b1;
  HepRotation r1;
  CLHEPdouble db2 = distance2(b1);
  lt.decompose(b1,r1);
  if (db2 > epsilon*epsilon) return false;
  CLHEPdouble dr2  = r1.norm2();
  return (bool)(db2 + dr2);
}

// ----------  Properties:

void HepBoostZ::rectify() {
  // Assuming the representation of this is close to a true pure boost,
  // but may have drifted due to round-off error from many operations,
  // this forms an "exact" pure BoostZ matrix for again.
  
  CLHEPdouble b2 = beta_*beta_;
  if (b2 >= 1) {
    beta_ = 1.0 - 1.0e-8;			// NaN-proofing
    b2 = beta_*beta_;
  } 
  gamma_ = 1.0 / std::sqrt(1.0 - b2);
}

// ---------- Application:

// ---------- Operations in the group of 4-Rotations

HepBoostZ HepBoostZ::operator * (const HepBoostZ & b) const {
  return HepBoostZ ( (beta()+b.beta()) / (1+beta()*b.beta()) );
}
HepLorentzRotation HepBoostZ::operator * (const HepBoost & b) const {
  HepLorentzRotation me (*this);
  return me*b;
}
HepLorentzRotation HepBoostZ::operator * (const HepRotation & r) const {
  HepLorentzRotation me (*this);
  return me*r;
}
HepLorentzRotation HepBoostZ::operator * (const HepLorentzRotation & lt) const {
  HepLorentzRotation me (*this);
  return me*lt;
}
 
// ---------- I/O
 
std::ostream & HepBoostZ::print( std::ostream & os ) const {
  os << "Boost in Z direction (beta = " << beta_ 
			<< ", gamma = " << gamma_ << ") ";
  return os;
}

}  // namespace CLHEP
