#include "CLHEPTypes.hpp"
// -*- C++ -*-
// ---------------------------------------------------------------------------
//
// This file is a part of the CLHEP - a Class Library for High Energy Physics.
//
// This is part of the implementation of the HepLorentzVector class:
// Those methods which originated from ZOOM and which deal with relativistic
// kinematic properties.
//

#include "CLHEP/Vector/defs.h"
#include "CLHEP/Vector/LorentzVector.h"
#include "CLHEP/Vector/ZMxpv.h"

#include <cmath>
#include <iostream>

namespace CLHEP  {

//-******************
// Metric flexibility
//-******************

ZMpvMetric_t HepLorentzVector::setMetric( ZMpvMetric_t a1 ) {
  ZMpvMetric_t oldMetric = (metric > 0) ? TimePositive : TimeNegative;
  if ( a1 == TimeNegative ) {
    metric = -1.0;
  } else {
    metric =  1.0;
  }
  return oldMetric;
}

ZMpvMetric_t HepLorentzVector::getMetric() {
  return ( (metric > 0) ? TimePositive : TimeNegative );
}

//-********
// plus
// minus
//-********

CLHEPdouble HepLorentzVector::plus (const Hep3Vector & ref) const {
  CLHEPdouble r = ref.mag();
  if (r == 0) {
    ZMthrowA (ZMxpvZeroVector(
      "A zero vector used as reference to LorentzVector plus-part"));
    return ee;
  }
  return ee + pp.dot(ref)/r;
} /* plus */

CLHEPdouble HepLorentzVector::minus (const Hep3Vector & ref) const {
  CLHEPdouble r = ref.mag();
  if (r == 0) {
    ZMthrowA (ZMxpvZeroVector(
      "A zero vector used as reference to LorentzVector minus-part"));
    return ee;
  }
  return ee - pp.dot(ref)/r;
} /* plus */

HepLorentzVector HepLorentzVector::rest4Vector() const {
  return HepLorentzVector (0, 0, 0, (t() < 0.0 ? -m() : m()));
}

//-********
// beta
// gamma
//-********

CLHEPdouble HepLorentzVector::beta() const {
  if (ee == 0) {
    if (pp.mag2() == 0) {
      return 0;
    } else {
    ZMthrowA (ZMxpvInfiniteVector(
      "beta computed for HepLorentzVector with t=0 -- infinite result"));
    return 1./ee;
    }
  }
  if (restMass2() <= 0) {
    ZMthrowC (ZMxpvTachyonic(
      "beta computed for a non-timelike HepLorentzVector"));
        // result will make analytic sense but is physically meaningless
  }
  return std::sqrt (pp.mag2() / (ee*ee)) ;
} /* beta */

CLHEPdouble HepLorentzVector::gamma() const {
  CLHEPdouble v2 = pp.mag2();
  CLHEPdouble t2 = ee*ee;
  if (ee == 0) {
    if (pp.mag2() == 0) {
      return 1;
    } else {
    ZMthrowC (ZMxpvInfiniteVector(
      "gamma computed for HepLorentzVector with t=0 -- zero result"));
    return 0;
    }
  }
  if (t2 < v2) {
    ZMthrowA (ZMxpvSpacelike(
      "gamma computed for a spacelike HepLorentzVector -- imaginary result"));
        // analytic result would be imaginary.
    return 0;
  } else if ( t2 == v2 ) {
    ZMthrowA (ZMxpvInfinity(
      "gamma computed for a lightlike HepLorentzVector -- infinite result"));
  }
  return 1./std::sqrt(1. - v2/t2 );
} /* gamma */


//-***************
// rapidity
// pseudorapidity
// eta
//-***************

CLHEPdouble HepLorentzVector::rapidity() const {
  CLHEPdouble z1 = pp.getZ();
  if (std::fabs(ee) == std::fabs(z1)) {
    ZMthrowA (ZMxpvInfinity(
      "rapidity for 4-vector with |E| = |Pz| -- infinite result"));
  }
  if (std::fabs(ee) < std::fabs(z1)) {
    ZMthrowA (ZMxpvSpacelike(
      "rapidity for spacelike 4-vector with |E| < |Pz| -- undefined"));
    return 0;
  }
  CLHEPdouble q = (ee + z1) / (ee - z1);
        //-| This cannot be negative now, since both numerator
        //-| and denominator have the same sign as ee.
  return .5 * std::log(q);
} /* rapidity */

CLHEPdouble HepLorentzVector::rapidity(const Hep3Vector & ref) const {
  CLHEPdouble r = ref.mag2();
  if (r == 0) {
    ZMthrowA (ZMxpvZeroVector(
      "A zero vector used as reference to LorentzVector rapidity"));
    return 0;
  }
  CLHEPdouble vdotu = pp.dot(ref)/std::sqrt(r);
  if (std::fabs(ee) == std::fabs(vdotu)) {
    ZMthrowA (ZMxpvInfinity(
      "rapidity for 4-vector with |E| = |Pu| -- infinite result"));
  }
  if (std::fabs(ee) < std::fabs(vdotu)) {
    ZMthrowA (ZMxpvSpacelike(
      "rapidity for spacelike 4-vector with |E| < |P*ref| -- undefined "));
    return 0;
  }
  CLHEPdouble q = (ee + vdotu) / (ee - vdotu);
  return .5 * std::log(q);
} /* rapidity(ref) */

CLHEPdouble HepLorentzVector::coLinearRapidity() const {
  CLHEPdouble v1 = pp.mag();
  if (std::fabs(ee) == std::fabs(v1)) {
    ZMthrowA (ZMxpvInfinity(
      "co-Linear rapidity for 4-vector with |E| = |P| -- infinite result"));
  }
  if (std::fabs(ee) < std::fabs(v1)) {
    ZMthrowA (ZMxpvSpacelike(
      "co-linear rapidity for spacelike 4-vector -- undefined"));
    return 0;
  }
  CLHEPdouble q = (ee + v1) / (ee - v1);
  return .5 * std::log(q);
} /* rapidity */

//-*************
// invariantMass
//-*************

CLHEPdouble HepLorentzVector::invariantMass(const HepLorentzVector & w) const {
  CLHEPdouble m1 = invariantMass2(w);
  if (m1 < 0) {
    // We should find out why:
    if ( ee * w.ee < 0 ) {
      ZMthrowA (ZMxpvNegativeMass(
        "invariant mass meaningless: \n"
        "a negative-mass input led to spacelike 4-vector sum" ));
      return 0;
    } else if ( (isSpacelike() && !isLightlike()) ||
                (w.isSpacelike() && !w.isLightlike()) ) {
      ZMthrowA (ZMxpvSpacelike(
        "invariant mass meaningless because of spacelike input"));
      return 0;
    } else {
      // Invariant mass squared for a pair of timelike or lightlike vectors
      // mathematically cannot be negative.  If the vectors are within the
      // tolerance of being lightlike or timelike, we can assume that prior
      // or current roundoffs have caused the negative result, and return 0
      // without comment.
      return 0;
    }
  }
  return (ee+w.ee >=0 ) ? std::sqrt(m1) : - std::sqrt(m1);
} /* invariantMass */

//-***************
// findBoostToCM
//-***************

Hep3Vector HepLorentzVector::findBoostToCM() const {
  return -boostVector();
} /* boostToCM() */

Hep3Vector HepLorentzVector::findBoostToCM (const HepLorentzVector & w) const {
  CLHEPdouble t1 = ee + w.ee;
  Hep3Vector v1 = pp + w.pp;
  if (t1 == 0) {
    if (v1.mag2() == 0) {
      return Hep3Vector(0,0,0);
    } else {
    ZMthrowA (ZMxpvInfiniteVector(
    "boostToCM computed for two 4-vectors with combined t=0 -- "
        "infinite result"));
    return Hep3Vector(v1*(1./t1)); // Yup, 1/0 -- that is how we return infinity
    }
  }
  if (t1*t1 - v1.mag2() <= 0) {
    ZMthrowC (ZMxpvTachyonic(
    "boostToCM  computed for pair of HepLorentzVectors with non-timelike sum"));
        // result will make analytic sense but is physically meaningless
  }
  return Hep3Vector(v1 * (-1./t1));
} /* boostToCM(w) */

}  // namespace CLHEP

