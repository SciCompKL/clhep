#include "CLHEPTypes.hpp"
// -*- C++ -*-
// $Id: LorentzVectorC.cc,v 1.4 2010/06/16 17:15:57 garren Exp $
// ---------------------------------------------------------------------------
//
// This file is a part of the CLHEP - a Class Library for High Energy Physics.
//
// This is the implementation of the HepLorentzVector class:
// Those methods originating with ZOOM dealing with comparison (other than
// isSpaceLike, isLightlike, isTimelike, which are in the main part.)
//
// 11/29/05 mf in deltaR, replaced the direct subtraction 
// pp.phi() - w.getV().phi() with pp.deltaRPhi(w.getV()) which behaves 
// correctly across the 2pi boundary.

#include "CLHEP/Vector/defs.h"
#include "CLHEP/Vector/LorentzVector.h"

#include <cmath>
#include <iostream>

namespace CLHEP  {

//-***********
// Comparisons
//-***********

int HepLorentzVector::compare (const HepLorentzVector & w) const {
  if       ( ee > w.ee ) {
    return 1;
  } else if ( ee < w.ee ) {
    return -1;
  } else {
    return ( pp.compare(w.pp) );
  }
} /* Compare */

bool HepLorentzVector::operator > (const HepLorentzVector & w) const {
        return (compare(w)  > 0);
}
bool HepLorentzVector::operator < (const HepLorentzVector & w) const {
        return (compare(w)  < 0);
}
bool HepLorentzVector::operator>= (const HepLorentzVector & w) const {
        return (compare(w) >= 0);
}
bool HepLorentzVector::operator<= (const HepLorentzVector & w) const {
        return (compare(w) <= 0);
}

//-********
// isNear
// howNear
//-********

bool HepLorentzVector::isNear(const HepLorentzVector & w, 
						CLHEPdouble epsilon) const {
  CLHEPdouble limit = std::fabs(pp.dot(w.pp));
  limit += .25*((ee+w.ee)*(ee+w.ee));
  limit *= epsilon*epsilon;
  CLHEPdouble delta = (pp - w.pp).mag2();
  delta +=  (ee-w.ee)*(ee-w.ee);
  return (delta <= limit );
} /* isNear() */

CLHEPdouble HepLorentzVector::howNear(const HepLorentzVector & w) const {
  CLHEPdouble wdw = std::fabs(pp.dot(w.pp)) + .25*((ee+w.ee)*(ee+w.ee));
  CLHEPdouble delta = (pp - w.pp).mag2() + (ee-w.ee)*(ee-w.ee);
  if ( (wdw > 0) && (delta < wdw)  ) {
    return std::sqrt (delta/wdw);
  } else if ( (wdw == 0) && (delta == 0) ) {
    return 0;
  } else {
    return 1;
  }
} /* howNear() */

//-*********
// isNearCM
// howNearCM
//-*********

bool HepLorentzVector::isNearCM
			(const HepLorentzVector & w, CLHEPdouble epsilon) const {

  CLHEPdouble tTotal = (ee + w.ee);
  Hep3Vector vTotal (pp + w.pp);
  CLHEPdouble vTotal2 = vTotal.mag2();

  if ( vTotal2 >= tTotal*tTotal ) {
    // Either one or both vectors are spacelike, or the dominant T components
    // are in opposite directions.  So boosting and testing makes no sense;
    // but we do consider two exactly equal vectors to be equal in any frame,
    // even if they are spacelike and can't be boosted to a CM frame.
    return (*this == w);
  }

  if ( vTotal2 == 0 ) {  // no boost needed!
    return (isNear(w, epsilon));
  }

  // Find the boost to the CM frame.  We know that the total vector is timelike.

  CLHEPdouble tRecip = 1./tTotal;
  Hep3Vector bboost ( vTotal * (-tRecip) );

        //-| Note that you could do pp/t and not be terribly inefficient since
        //-| SpaceVector/t itself takes 1/t and multiplies.  The code here saves
        //-| a redundant check for t=0.

  // Boost both vectors.  Since we have the same boost, there is no need
  // to repeat the beta and gamma calculation; and there is no question
  // about beta >= 1.  That is why we don't just call w.boosted().

  CLHEPdouble b2 = vTotal2*tRecip*tRecip;

  CLHEPdouble ggamma = std::sqrt(1./(1.-b2));
  CLHEPdouble boostDotV1 = bboost.dot(pp);
  CLHEPdouble gm1_b2 = (ggamma-1)/b2;

  HepLorentzVector w1 ( pp   + ((gm1_b2)*boostDotV1+ggamma*ee) * bboost,
                     ggamma * (ee + boostDotV1) );

  CLHEPdouble boostDotV2 = bboost.dot(w.pp);
  HepLorentzVector w2 ( w.pp + ((gm1_b2)*boostDotV2+ggamma*w.ee) * bboost,
                     ggamma * (w.ee + boostDotV2) );

  return (w1.isNear(w2, epsilon));

} /* isNearCM() */

CLHEPdouble HepLorentzVector::howNearCM(const HepLorentzVector & w) const {

  CLHEPdouble tTotal = (ee + w.ee);
  Hep3Vector vTotal (pp + w.pp);
  CLHEPdouble vTotal2 = vTotal.mag2();

  if ( vTotal2 >= tTotal*tTotal ) {
    // Either one or both vectors are spacelike, or the dominant T components
    // are in opposite directions.  So boosting and testing makes no sense;
    // but we do consider two exactly equal vectors to be equal in any frame,
    // even if they are spacelike and can't be boosted to a CM frame.
    if (*this == w) {
      return 0;
    } else {
      return 1;
    }
  }

  if ( vTotal2 == 0 ) {  // no boost needed!
    return (howNear(w));
  }

  // Find the boost to the CM frame.  We know that the total vector is timelike.

  CLHEPdouble tRecip = 1./tTotal;
  Hep3Vector bboost ( vTotal * (-tRecip) );

        //-| Note that you could do pp/t and not be terribly inefficient since
        //-| SpaceVector/t itself takes 1/t and multiplies.  The code here saves
        //-| a redundant check for t=0.

  // Boost both vectors.  Since we have the same boost, there is no need
  // to repeat the beta and gamma calculation; and there is no question
  // about beta >= 1.  That is why we don't just call w.boosted().

  CLHEPdouble b2 = vTotal2*tRecip*tRecip;
  if ( b2 >= 1 ) {			// NaN-proofing
    ZMthrowC ( ZMxpvTachyonic (
	"boost vector in howNearCM appears to be tachyonic"));
  }
  CLHEPdouble ggamma = std::sqrt(1./(1.-b2));
  CLHEPdouble boostDotV1 = bboost.dot(pp);
  CLHEPdouble gm1_b2 = (ggamma-1)/b2;

  HepLorentzVector w1 ( pp   + ((gm1_b2)*boostDotV1+ggamma*ee) * bboost,
                     ggamma * (ee + boostDotV1) );

  CLHEPdouble boostDotV2 = bboost.dot(w.pp);
  HepLorentzVector w2 ( w.pp + ((gm1_b2)*boostDotV2+ggamma*w.ee) * bboost,
                     ggamma * (w.ee + boostDotV2) );

  return (w1.howNear(w2));

} /* howNearCM() */

//-************
// deltaR
// isParallel
// howParallel
// howLightlike
//-************

CLHEPdouble HepLorentzVector::deltaR ( const HepLorentzVector & w ) const {

  CLHEPdouble a = eta() - w.eta();
  CLHEPdouble b = pp.deltaPhi(w.getV());

  return std::sqrt ( a*a + b*b );

} /* deltaR */

// If the difference (in the Euclidean norm) of the normalized (in Euclidean
// norm) 4-vectors is small, then those 4-vectors are considered nearly
// parallel.

bool HepLorentzVector::isParallel (const HepLorentzVector & w, CLHEPdouble epsilon) const {
  CLHEPdouble norm = euclideanNorm();
  CLHEPdouble wnorm = w.euclideanNorm();
  if ( norm == 0 ) {
    if ( wnorm == 0 ) {
      return true;
    } else {
      return false;
    }
  }
  if ( wnorm == 0 ) {
    return false;
  }
  HepLorentzVector w1 = *this / norm;
  HepLorentzVector w2 = w / wnorm;
  return ( (w1-w2).euclideanNorm2() <= epsilon*epsilon );
} /* isParallel */


CLHEPdouble HepLorentzVector::howParallel (const HepLorentzVector & w) const {

  CLHEPdouble norm = euclideanNorm();
  CLHEPdouble wnorm = w.euclideanNorm();
  if ( norm == 0 ) {
    if ( wnorm == 0 ) {
      return 0;
    } else {
      return 1;
    }
  }
  if ( wnorm == 0 ) {
    return 1;
  }

  HepLorentzVector w1 = *this / norm;
  HepLorentzVector w2 = w / wnorm;
  CLHEPdouble x1 = (w1-w2).euclideanNorm();
  return (x1 < 1) ? x1 : 1;

} /* howParallel */

CLHEPdouble HepLorentzVector::howLightlike() const {
  CLHEPdouble m1 = std::fabs(restMass2());
  CLHEPdouble twoT2 = 2*ee*ee;
  if (m1 < twoT2) {
    return m1/twoT2;
  } else {
    return 1;
  }
} /* HowLightlike */

}  // namespace CLHEP
