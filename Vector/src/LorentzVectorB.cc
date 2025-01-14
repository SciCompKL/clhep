#include "CLHEPTypes.hpp"
// -*- C++ -*-
// $Id: LorentzVectorB.cc,v 1.2 2003/08/13 20:00:14 garren Exp $
// ---------------------------------------------------------------------------
//
// This file is a part of the CLHEP - a Class Library for High Energy Physics.
//
// This is the implementation of the HepLorentzVector class:
// Those methods originating in ZOOM dealing with simple boosts and rotations.
// Use of one of these methods will not force loading of the HepRotation or
// HepLorentzRotation class.
//

#include "CLHEP/Vector/defs.h"
#include "CLHEP/Vector/LorentzVector.h"
#include "CLHEP/Vector/ZMxpv.h"

#include <cmath>
#include <iostream>
namespace CLHEP  {

//-*********
// rotationOf()
//-*********

// Each of these is a shell over a rotate method.

HepLorentzVector rotationXOf
	(const HepLorentzVector & vec, CLHEPdouble phi){
  HepLorentzVector vv (vec);
  return vv.rotateX (phi);
}

HepLorentzVector rotationYOf
	(const HepLorentzVector & vec, CLHEPdouble phi){
  HepLorentzVector vv (vec);
  return vv.rotateY (phi);
}

HepLorentzVector rotationZOf
	(const HepLorentzVector & vec, CLHEPdouble phi){
  HepLorentzVector vv (vec);
  return vv.rotateZ (phi);
}

//-********
// boost
//-********

HepLorentzVector & HepLorentzVector::boost 
			( const Hep3Vector & aaxis,  CLHEPdouble bbeta ) {
  if (bbeta==0) {
    return *this; // do nothing for a 0 boost
  }
  CLHEPdouble r2 = aaxis.mag2();
  if ( r2 == 0 ) {
    ZMthrowA (ZMxpvZeroVector(
      "A zero vector used as axis defining a boost -- no boost done"));
    return *this;
  } 
  CLHEPdouble b2 = bbeta*bbeta;
  if (b2 >= 1) {
    ZMthrowA (ZMxpvTachyonic(
      "LorentzVector boosted with beta >= 1 (speed of light) -- \n"
      "no boost done"));
  } else {
    Hep3Vector u = aaxis.unit();
    CLHEPdouble ggamma = std::sqrt(1./(1.-b2));
    CLHEPdouble betaDotV = u.dot(pp)*bbeta;
    CLHEPdouble tt = ee;

    ee = ggamma * (tt + betaDotV);
    pp += ( ((ggamma-1)/b2)*betaDotV*bbeta + ggamma*bbeta*tt ) * u;
    // Note:  I have verified the behavior of this even when beta is very
    //        small -- (gamma-1)/b2 becomes inaccurate by O(1), but it is then
    //        multiplied by O(beta**2) and added to an O(beta) term, so the
    //        inaccuracy does not affect the final result.
  }
  return *this;
} /* boost (axis, beta) */

}  // namespace CLHEP
