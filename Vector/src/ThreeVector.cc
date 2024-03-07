#include "CLHEPTypes.hpp"
// -*- C++ -*-
// $Id: ThreeVector.cc,v 1.3 2003/08/13 20:00:14 garren Exp $
// ---------------------------------------------------------------------------
//
// This file is a part of the CLHEP - a Class Library for High Energy Physics.
//
// This is the implementation of the Hep3Vector class.
//
// See also ThreeVectorR.cc for implementation of Hep3Vector methods which 
// would couple in all the HepRotation methods.
//

#include "CLHEP/Vector/defs.h"
#include "CLHEP/Vector/ThreeVector.h"
#include "CLHEP/Vector/ZMxpv.h"
#include "CLHEP/Units/PhysicalConstants.h"

#include <cmath>
#include <iostream>

namespace CLHEP  {

void Hep3Vector::setMag(CLHEPdouble ma) {
  CLHEPdouble factor = mag();
  if (factor == 0) {
    ZMthrowA ( ZMxpvZeroVector (
    "Hep3Vector::setMag : zero vector can't be stretched"));
  }else{
    factor = ma/factor;
    setX(x()*factor);
    setY(y()*factor);
    setZ(z()*factor);
  }
}

Hep3Vector & Hep3Vector::rotateUz(const Hep3Vector& NewUzVector) {
  // NewUzVector must be normalized !

  CLHEPdouble u1 = NewUzVector.x();
  CLHEPdouble u2 = NewUzVector.y();
  CLHEPdouble u3 = NewUzVector.z();
  CLHEPdouble up = u1*u1 + u2*u2;

  if (up > 0) {
    up = std::sqrt(up);
    CLHEPdouble px = (u1 * u3 * x() - u2 * y()) / up + u1 * z();
    CLHEPdouble py = (u2 * u3 * x() + u1 * y()) / up + u2 * z();
    CLHEPdouble pz = -up * x() + u3 * z();
    set(px, py, pz);
  } else if (u3 < 0.) {
    setX(-x());
    setZ(-z());
  } // phi=0  teta=pi

  return *this;
}

CLHEPdouble Hep3Vector::pseudoRapidity() const {
  CLHEPdouble m1 = mag();
  if ( m1==  0   ) return  0.0;   
  if ( m1==  z() ) return  1.0E72;
  if ( m1== -z() ) return -1.0E72;
  return 0.5*std::log( (m1+z())/(m1-z()) );
}

std::ostream & operator<< (std::ostream & os, const Hep3Vector & v) {
  return os << "(" << v.x() << "," << v.y() << "," << v.z() << ")";
}

void ZMinput3CLHEPdoubles ( std::istream & is, const char * type,
                       CLHEPdouble & x, CLHEPdouble & y, CLHEPdouble & z );

std::istream & operator>>(std::istream & is, Hep3Vector & v) {
  CLHEPdouble x, y, z;
  ZMinput3CLHEPdoubles ( is, "Hep3Vector", x, y, z );
  v.set(x, y, z);
  return  is;
}  // operator>>()

const Hep3Vector HepXHat(1.0, 0.0, 0.0);
const Hep3Vector HepYHat(0.0, 1.0, 0.0);
const Hep3Vector HepZHat(0.0, 0.0, 1.0);

//-------------------
//
// New methods introduced when ZOOM PhysicsVectors was merged in:
//
//-------------------

Hep3Vector & Hep3Vector::rotateX (CLHEPdouble phi1) {
  CLHEPdouble sinphi = std::sin(phi1);
  CLHEPdouble cosphi = std::cos(phi1);
  CLHEPdouble ty = y() * cosphi - z() * sinphi;
  CLHEPdouble tz = z() * cosphi + y() * sinphi;
  setY(ty);
  setZ(tz);
  return *this;
} /* rotateX */

Hep3Vector & Hep3Vector::rotateY (CLHEPdouble phi1) {
  CLHEPdouble sinphi = std::sin(phi1);
  CLHEPdouble cosphi = std::cos(phi1);
  CLHEPdouble tx = x() * cosphi + z() * sinphi;
  CLHEPdouble tz = z() * cosphi - x() * sinphi;
  setX(tx);
  setZ(tz);
  return *this;
} /* rotateY */

Hep3Vector & Hep3Vector::rotateZ (CLHEPdouble phi1) {
  CLHEPdouble sinphi = std::sin(phi1);
  CLHEPdouble cosphi = std::cos(phi1);
  CLHEPdouble tx = x() * cosphi - y() * sinphi;
  CLHEPdouble ty = y() * cosphi + x() * sinphi;
  setX(tx);
  setY(ty);
  return *this;
} /* rotateZ */

bool Hep3Vector::isNear(const Hep3Vector & v, CLHEPdouble epsilon) const {
  CLHEPdouble limit = dot(v)*epsilon*epsilon;
  return ( (*this - v).mag2() <= limit );
} /* isNear() */

CLHEPdouble Hep3Vector::howNear(const Hep3Vector & v ) const {
  // | V1 - V2 | **2  / V1 dot V2, up to 1
  CLHEPdouble d   = (*this - v).mag2();
  CLHEPdouble vdv = dot(v);
  if ( (vdv > 0) && (d < vdv)  ) {
    return std::sqrt (d/vdv);
  } else if ( (vdv == 0) && (d == 0) ) {
    return 0;
  } else {
    return 1;
  }
} /* howNear */

CLHEPdouble Hep3Vector::deltaPhi  (const Hep3Vector & v2) const {
  CLHEPdouble dphi = v2.getPhi() - getPhi();
  if ( dphi > CLHEP::pi ) {
    dphi -= CLHEP::twopi;
  } else if ( dphi <= -CLHEP::pi ) {
    dphi += CLHEP::twopi;
  }
  return dphi;
} /* deltaPhi */

CLHEPdouble Hep3Vector::deltaR ( const Hep3Vector & v ) const {
  CLHEPdouble a = eta() - v.eta();
  CLHEPdouble b = deltaPhi(v); 
  return std::sqrt ( a*a + b*b );
} /* deltaR */

CLHEPdouble Hep3Vector::cosTheta(const Hep3Vector & q) const {
  CLHEPdouble arg;
  CLHEPdouble ptot2 = mag2()*q.mag2();
  if(ptot2 <= 0) {
    arg = 0.0;
  }else{
    arg = dot(q)/std::sqrt(ptot2);
    if(arg >  1.0) arg =  1.0;
    if(arg < -1.0) arg = -1.0;
  }
  return arg;
}

CLHEPdouble Hep3Vector::cos2Theta(const Hep3Vector & q) const {
  CLHEPdouble arg;
  CLHEPdouble ptot2 = mag2();
  CLHEPdouble qtot2 = q.mag2();
  if ( ptot2 == 0 || qtot2 == 0 )  {
    arg = 1.0;
  }else{
    CLHEPdouble pdq = dot(q);
    arg = (pdq/ptot2) * (pdq/qtot2);
        // More naive methods overflow on vectors which can be squared
        // but can't be raised to the 4th power.
    if(arg >  1.0) arg =  1.0;
 }
 return arg;
}

void Hep3Vector::setEta (CLHEPdouble eta1) {
  CLHEPdouble phi1 = 0;
  CLHEPdouble r1;
  if ( (x() == 0) && (y() == 0) ) {
    if (z() == 0) {
      ZMthrowC (ZMxpvZeroVector(
        "Attempt to set eta of zero vector -- vector is unchanged"));
      return;
    }
    ZMthrowC (ZMxpvZeroVector(
      "Attempt to set eta of vector along Z axis -- will use phi = 0"));
    r1 = std::fabs(z());
  } else {
    r1 = getR();
    phi1 = getPhi();
  }
  CLHEPdouble tanHalfTheta = std::exp ( -eta1 );
  CLHEPdouble cosTheta1 =
        (1 - tanHalfTheta*tanHalfTheta) / (1 + tanHalfTheta*tanHalfTheta);
  CLHEPdouble rho1 = r1*std::sqrt(1 - cosTheta1*cosTheta1);
  setZ(r1 * cosTheta1);
  setY(rho1 * std::sin (phi1));
  setX(rho1 * std::cos (phi1));
  return;
}

void Hep3Vector::setCylTheta (CLHEPdouble theta1) {

  // In cylindrical coords, set theta while keeping rho and phi fixed

  if ( (x() == 0) && (y() == 0) ) {
    if (z() == 0) {
      ZMthrowC (ZMxpvZeroVector(
        "Attempt to set cylTheta of zero vector -- vector is unchanged"));
      return;
    }
    if (theta1 == 0) {
      setZ(std::fabs(z()));
      return;
    }
    if (theta1 == CLHEP::pi) {
      setZ(-std::fabs(z()));
      return;
    }
    ZMthrowC (ZMxpvZeroVector(
      "Attempt set cylindrical theta of vector along Z axis "
      "to a non-trivial value, while keeping rho fixed -- "
      "will return zero vector"));
    setZ(0.0);
    return;
  }
  if ( (theta1 < 0) || (theta1 > CLHEP::pi) ) {
    ZMthrowC (ZMxpvUnusualTheta(
      "Setting Cyl theta of a vector based on a value not in [0, PI]"));
        // No special return needed if warning is ignored.
  }
  CLHEPdouble phi1 (getPhi());
  CLHEPdouble rho1 = getRho();
  if ( (theta1 == 0) || (theta1 == CLHEP::pi) ) {
    ZMthrowC (ZMxpvInfiniteVector(
      "Attempt to set cylindrical theta to 0 or PI "
      "while keeping rho fixed -- infinite Z will be computed"));
      setZ((theta1==0) ? 1.0E72 : -1.0E72);
    return;
  }
  setZ(rho1 / std::tan (theta1));
  setY(rho1 * std::sin (phi1));
  setX(rho1 * std::cos (phi1));

} /* setCylTheta */

void Hep3Vector::setCylEta (CLHEPdouble eta1) {

  // In cylindrical coords, set eta while keeping rho and phi fixed

  CLHEPdouble theta1 = 2 * std::atan ( std::exp (-eta1) );

        //-| The remaining code is similar to setCylTheta,  The reason for
        //-| using a copy is so as to be able to change the messages in the
        //-| ZMthrows to say eta rather than theta.  Besides, we assumedly
        //-| need not check for theta of 0 or PI.

  if ( (x() == 0) && (y() == 0) ) {
    if (z() == 0) {
      ZMthrowC (ZMxpvZeroVector(
        "Attempt to set cylEta of zero vector -- vector is unchanged"));
      return;
    }
    if (theta1 == 0) {
      setZ(std::fabs(z()));
      return;
    }
    if (theta1 == CLHEP::pi) {
      setZ(-std::fabs(z()));
      return;
    }
    ZMthrowC (ZMxpvZeroVector(
      "Attempt set cylindrical eta of vector along Z axis "
      "to a non-trivial value, while keeping rho fixed -- "
      "will return zero vector"));
    setZ(0.0);
    return;
  }
  CLHEPdouble phi1 (getPhi());
  CLHEPdouble rho1 = getRho();
  setZ(rho1 / std::tan (theta1));
  setY(rho1 * std::sin (phi1));
  setX(rho1 * std::cos (phi1));

} /* setCylEta */


Hep3Vector operator/ ( const Hep3Vector & v1, CLHEPdouble c ) {
  if (c == 0) {
    ZMthrowA ( ZMxpvInfiniteVector (
      "Attempt to divide vector by 0 -- "
      "will produce infinities and/or NANs"));
  } 
  return v1 * (1.0/c);
} /* v / c */

Hep3Vector & Hep3Vector::operator/= (CLHEPdouble c) {
  if (c == 0) {
    ZMthrowA (ZMxpvInfiniteVector(
      "Attempt to do vector /= 0 -- "
      "division by zero would produce infinite or NAN components"));
  }
  *this *= 1.0/c;
  return *this;
}

CLHEPdouble Hep3Vector::tolerance = Hep3Vector::ToleranceTicks * 2.22045e-16;

}  // namespace CLHEP



