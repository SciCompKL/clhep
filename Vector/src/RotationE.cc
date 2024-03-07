#include "CLHEPTypes.hpp"
// -*- C++ -*-
// ---------------------------------------------------------------------------
//
// This file is a part of the CLHEP - a Class Library for High Energy Physics.
//
// This is the implementation of methods of the HepRotation class which
// were introduced when ZOOM PhysicsVectors was merged in, and which involve
// Euler Angles representation.
//
// Apr 28, 2003  mf  Modified way of computing Euler angles to avoid flawed
//                   answers in the case where theta is near 0 of pi, and
//                   the matrix is not a perfect rotation (due to roundoff).

#include "CLHEP/Vector/defs.h"
#include "CLHEP/Vector/Rotation.h"
#include "CLHEP/Vector/EulerAngles.h"
#include "CLHEP/Units/PhysicalConstants.h"

#include <cmath>
#include <iostream>
#include <stdlib.h>

namespace CLHEP  {

static inline CLHEPdouble safe_acos (CLHEPdouble x) {
  if (std::abs(x) <= 1.0) return std::acos(x);
  return ( (x>0) ? 0 : CLHEP::pi );
}

// ----------  Constructors and Assignment:

// Euler angles

HepRotation & HepRotation::set(CLHEPdouble phi1, CLHEPdouble theta1, CLHEPdouble psi1) {

  CLHEPdouble sinPhi   = std::sin( phi1   ), cosPhi   = std::cos( phi1   );
  CLHEPdouble sinTheta = std::sin( theta1 ), cosTheta = std::cos( theta1 );
  CLHEPdouble sinPsi   = std::sin( psi1   ), cosPsi   = std::cos( psi1   );

  rxx =   cosPsi * cosPhi - cosTheta * sinPhi * sinPsi;
  rxy =   cosPsi * sinPhi + cosTheta * cosPhi * sinPsi;
  rxz =   sinPsi * sinTheta;

  ryx = - sinPsi * cosPhi - cosTheta * sinPhi * cosPsi;
  ryy = - sinPsi * sinPhi + cosTheta * cosPhi * cosPsi;
  ryz =   cosPsi * sinTheta;

  rzx =   sinTheta * sinPhi;
  rzy = - sinTheta * cosPhi;
  rzz =   cosTheta;

  return  *this;

}  // Rotation::set(phi, theta, psi)

HepRotation::HepRotation( CLHEPdouble phi1, CLHEPdouble theta1, CLHEPdouble psi1 ) 
{
  set (phi1, theta1, psi1);
}
HepRotation & HepRotation::set( const HepEulerAngles & e ) {
  return set(e.phi(), e.theta(), e.psi());
}
HepRotation::HepRotation ( const HepEulerAngles & e ) 
{
  set(e.phi(), e.theta(), e.psi());
}


 
CLHEPdouble HepRotation::phi  () const {

  CLHEPdouble s2 =  1.0 - rzz*rzz;
  if (s2 < 0) {
    ZMthrowC ( ZMxpvImproperRotation (
        "HepRotation::phi() finds | rzz | > 1 "));
    s2 = 0;
  }
  const CLHEPdouble sinTheta = std::sqrt( s2 );

  if (sinTheta < .01) { // For theta close to 0 or PI, use the more stable
  			// algorithm to get all three Euler angles
    HepEulerAngles ea = eulerAngles();
    return ea.phi();
  }
  
  const CLHEPdouble cscTheta = 1/sinTheta;
  CLHEPdouble cosabsphi =  - rzy * cscTheta;
  if ( std::fabs(cosabsphi) > 1 ) {	// NaN-proofing
    ZMthrowC ( ZMxpvImproperRotation (
      "HepRotation::phi() finds | cos phi | > 1 "));
    cosabsphi = 1;
  }
  const CLHEPdouble absPhi = std::acos ( cosabsphi );
  if (rzx > 0) {
    return   absPhi;
  } else if (rzx < 0) {
    return  -absPhi;
  } else {
    return  (rzy < 0) ? 0 : CLHEP::pi;
  }

} // phi()

CLHEPdouble HepRotation::theta() const {

  return  safe_acos( rzz );

} // theta()

CLHEPdouble HepRotation::psi  () const {

  CLHEPdouble sinTheta;
  if ( std::fabs(rzz) > 1 ) {	// NaN-proofing
    ZMthrowC ( ZMxpvImproperRotation (
      "HepRotation::psi() finds | rzz | > 1"));
    sinTheta = 0;
  } else { 
    sinTheta = std::sqrt( 1.0 - rzz*rzz );
  }
  
  if (sinTheta < .01) { // For theta close to 0 or PI, use the more stable
  			// algorithm to get all three Euler angles
    HepEulerAngles ea = eulerAngles();
    return ea.psi();
  }

  const CLHEPdouble cscTheta = 1/sinTheta;
  CLHEPdouble cosabspsi =  ryz * cscTheta;
  if ( std::fabs(cosabspsi) > 1 ) {	// NaN-proofing
    ZMthrowC ( ZMxpvImproperRotation (
      "HepRotation::psi() finds | cos psi | > 1"));
    cosabspsi = 1;
  }
  const CLHEPdouble absPsi = std::acos ( cosabspsi );
  if (rxz > 0) {
    return   absPsi;
  } else if (rxz < 0) {
    return  -absPsi;
  } else {
    return  (ryz > 0) ? 0 : CLHEP::pi;
  }

} // psi()


// Helpers for eulerAngles():

static		     
void correctByPi ( CLHEPdouble& psi1, CLHEPdouble& phi1 ) {
  if (psi1 > 0) {
    psi1 -= CLHEP::pi;
  } else {
    psi1 += CLHEP::pi;
  }
  if (phi1 > 0) {
    phi1 -= CLHEP::pi;
  } else {
    phi1 += CLHEP::pi;
  }  
}

static
void correctPsiPhi ( CLHEPdouble rxz, CLHEPdouble rzx, CLHEPdouble ryz, CLHEPdouble rzy, 
		     CLHEPdouble& psi1, CLHEPdouble& phi1 ) {

  // set up quatities which would be positive if sin and cosine of
  // psi1 and phi1 were positive:
  CLHEPdouble w[4];
  w[0] = rxz; w[1] = rzx; w[2] = ryz; w[3] = -rzy;

  // find biggest relevant term, which is the best one to use in correcting.
  CLHEPdouble maxw = std::abs(w[0]); 
  int imax = 0;
  for (int i = 1; i < 4; ++i) {
    if (std::abs(w[i]) > maxw) {
      maxw = std::abs(w[i]);
      imax = i;
    }
  }
  // Determine if the correction needs to be applied:  The criteria are 
  // different depending on whether a sine or cosine was the determinor: 
  switch (imax) {
    case 0:
      if (w[0] > 0 && psi1 < 0)           correctByPi ( psi1, phi1 );
      if (w[0] < 0 && psi1 > 0)           correctByPi ( psi1, phi1 );
      break;
    case 1:
      if (w[1] > 0 && phi1 < 0)           correctByPi ( psi1, phi1 );
      if (w[1] < 0 && phi1 > 0)           correctByPi ( psi1, phi1 );
      break;
    case 2:
      if (w[2] > 0 && std::abs(psi1) > CLHEP::halfpi) correctByPi ( psi1, phi1 );    
      if (w[2] < 0 && std::abs(psi1) < CLHEP::halfpi) correctByPi ( psi1, phi1 );    
      break;
    case 3:
      if (w[3] > 0 && std::abs(phi1) > CLHEP::halfpi) correctByPi ( psi1, phi1 );    
      if (w[3] < 0 && std::abs(phi1) < CLHEP::halfpi) correctByPi ( psi1, phi1 );    
      break;
  }          
}


HepEulerAngles HepRotation::eulerAngles() const {

  // Please see the mathematical justification in eulerAngleComputations.ps

  CLHEPdouble phi1, theta1, psi1;
  CLHEPdouble psiPlusPhi, psiMinusPhi;
  
  theta1 = safe_acos( rzz );
  
  if (rzz > 1 || rzz < -1) {
    ZMthrowC ( ZMxpvImproperRotation (
        "HepRotation::eulerAngles() finds | rzz | > 1 "));
  }
  
  CLHEPdouble cosTheta = rzz;
  if (cosTheta > 1)  cosTheta = 1;
  if (cosTheta < -1) cosTheta = -1;

  if (cosTheta == 1) {
    psiPlusPhi = std::atan2 ( rxy - ryx, rxx + ryy );
    psiMinusPhi = 0;     

  } else if (cosTheta >= 0) {

    // In this realm, the atan2 expression for psi + phi is numerically stable
    psiPlusPhi = std::atan2 ( rxy - ryx, rxx + ryy );

    // psi - phi is potentially more subtle, but when unstable it is moot
    CLHEPdouble s1 = -rxy - ryx; // std::sin (psi-phi) * (1 - cos theta)
    CLHEPdouble c =  rxx - ryy; // std::cos (psi-phi) * (1 - cos theta)
    psiMinusPhi = std::atan2 ( s1, c );
        
  } else if (cosTheta > -1) {

    // In this realm, the atan2 expression for psi - phi is numerically stable
    psiMinusPhi = std::atan2 ( -rxy - ryx, rxx - ryy );

   // psi + phi is potentially more subtle, but when unstable it is moot
    CLHEPdouble s1 = rxy - ryx; // std::sin (psi+phi) * (1 + cos theta)
    CLHEPdouble c = rxx + ryy; // std::cos (psi+phi) * (1 + cos theta)
    psiPlusPhi = std::atan2 ( s1, c );

  } else { // cosTheta == -1

    psiMinusPhi = std::atan2 ( -rxy - ryx, rxx - ryy );
    psiPlusPhi = 0;

  }
  
  psi1 = .5 * (psiPlusPhi + psiMinusPhi); 
  phi1 = .5 * (psiPlusPhi - psiMinusPhi); 

  // Now correct by pi if we have managed to get a value of psiPlusPhi
  // or psiMinusPhi that was off by 2 pi:
  correctPsiPhi ( rxz, rzx, ryz, rzy, psi1, phi1 );
  
  return  HepEulerAngles( phi1, theta1, psi1 );

} // eulerAngles()



void HepRotation::setPhi (CLHEPdouble phi1) {
  set ( phi1, theta(), psi() );
}

void HepRotation::setTheta (CLHEPdouble theta1) {
  set ( phi(), theta1, psi() );
}

void HepRotation::setPsi (CLHEPdouble psi1) {
  set ( phi(), theta(), psi1 );
}

}  // namespace CLHEP

