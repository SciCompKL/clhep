#include "CLHEPTypes.hpp"
// -*- C++ -*-
//
// This file is a part of the CLHEP - a Class Library for High Energy Physics.
//
// This is the definition of the HepBoostX class for performing specialized
// Lorentz transformations which are pure boosts in the X direction, on 
// objects of the HepLorentzVector class.
//
// HepLorentzRotation is a concrete implementation of Hep4RotationInterface.
//
// .SS See Also
// RotationInterfaces.h
// LorentzVector.h LorentzRotation.h 
// Boost.h 
//
// .SS Author
// Mark Fischler

#ifndef HEP_BOOSTX_H
#define HEP_BOOSTX_H

#include "CLHEP/Vector/defs.h" 
#include "CLHEP/Vector/RotationInterfaces.h"
#include "CLHEP/Vector/LorentzVector.h"

namespace CLHEP  {

// Declarations of classes and global methods
class HepBoostX;
inline HepBoostX inverseOf ( const HepBoostX & b );
class HepBoost;
class HepRotation;

/**
 * @author
 * @ingroup vector
 */
class HepBoostX {

public:

  // ----------  Constructors and Assignment:

  inline HepBoostX();
  // Default constructor. Gives a boost of 0.  

  inline HepBoostX(const HepBoostX & b);
  inline HepBoostX(HepBoostX && b) = default;
  // Copy and move constructors.

  inline HepBoostX & operator = (const HepBoostX & m);
  inline HepBoostX & operator = (HepBoostX && m) = default;
  // Copy and move assignment operators.

         HepBoostX & set (CLHEPdouble beta);
  inline HepBoostX       (CLHEPdouble beta);
  // Constructor from beta 

  // ----------  Accessors:

  inline CLHEPdouble  beta()  const;
  inline CLHEPdouble  gamma() const;
  inline Hep3Vector boostVector() const;
  inline Hep3Vector getDirection() const;

  inline CLHEPdouble xx() const;
  inline CLHEPdouble xy() const;
  inline CLHEPdouble xz() const;
  inline CLHEPdouble xt() const;
  inline CLHEPdouble yx() const;
  inline CLHEPdouble yy() const;
  inline CLHEPdouble yz() const;
  inline CLHEPdouble yt() const;
  inline CLHEPdouble zx() const;
  inline CLHEPdouble zy() const;
  inline CLHEPdouble zz() const;
  inline CLHEPdouble zt() const;
  inline CLHEPdouble tx() const;
  inline CLHEPdouble ty() const;
  inline CLHEPdouble tz() const;
  inline CLHEPdouble tt() const;
  // Elements of the matrix.

  inline HepLorentzVector col1() const;
  inline HepLorentzVector col2() const;
  inline HepLorentzVector col3() const;
  inline HepLorentzVector col4() const;
  // orthosymplectic column vectors

  inline HepLorentzVector row1() const;
  inline HepLorentzVector row2() const;
  inline HepLorentzVector row3() const;
  inline HepLorentzVector row4() const;
  // orthosymplectic row vectors

  HepRep4x4 rep4x4() const;
  //   4x4 representation:

  HepRep4x4Symmetric rep4x4Symmetric() const;
  //   Symmetric 4x4 representation.

  // ----------  Decomposition:

  void decompose (HepRotation  & rotation, HepBoost   & boost) const;
  void decompose (HepAxisAngle & rotation, Hep3Vector & boost) const;
  // Find R and B such that L = R*B -- trivial, since R is identity

  void decompose ( HepBoost  & boost, HepRotation  & rotation) const;
  void decompose (Hep3Vector & boost, HepAxisAngle & rotation) const;
  // Find R and B such that L = B*R -- trivial, since R is identity

  // ----------  Comparisons:

  inline int compare( const HepBoostX & b  ) const;
  // Dictionary-order comparison, in order of beta. 
  // Used in operator<, >, <=, >=

  inline bool operator == (const HepBoostX & b) const;
  inline bool operator != (const HepBoostX & b) const;
  inline bool operator <= (const HepBoostX & b) const;
  inline bool operator >= (const HepBoostX & b) const;
  inline bool operator <  (const HepBoostX & b) const;
  inline bool operator >  (const HepBoostX & b) const;
  // Comparisons.

  inline bool isIdentity() const;
  // Returns true if a null boost.

  inline CLHEPdouble distance2( const HepBoostX & b ) const;
         CLHEPdouble distance2( const HepBoost & b ) const;
  // Defined as the distance2 between the vectors (gamma*betaVector)

  CLHEPdouble distance2( const HepRotation & r  ) const;
  CLHEPdouble distance2( const HepLorentzRotation & lt  ) const;
  // Decompose lt = B*R; add norm2 to distance2 to between boosts.

  inline CLHEPdouble howNear(   const HepBoostX & b ) const;
  inline CLHEPdouble howNear(   const HepBoost  & b ) const;
  inline CLHEPdouble howNear(   const HepRotation & r ) const;
  inline CLHEPdouble howNear(   const HepLorentzRotation & lt ) const;

  inline bool isNear(   const HepBoostX & b,
             CLHEPdouble epsilon=Hep4RotationInterface::tolerance) const;
  inline bool isNear(   const HepBoost & b,
             CLHEPdouble epsilon=Hep4RotationInterface::tolerance) const;
  bool isNear(   const HepRotation & r,
             CLHEPdouble epsilon=Hep4RotationInterface::tolerance) const;
  bool isNear(   const HepLorentzRotation & lt,
             CLHEPdouble epsilon=Hep4RotationInterface::tolerance) const;

  // ----------  Properties:

  inline CLHEPdouble norm2() const;
  // distance2 (IDENTITY), which is beta^2 * gamma^2

  void rectify();
  // sets according to the stored beta

  // ---------- Application:

  inline HepLorentzVector operator()( const HepLorentzVector & w ) const;
  // Transform a Lorentz Vector.             

  inline HepLorentzVector operator* ( const HepLorentzVector & w ) const;
  // Multiplication with a Lorentz Vector.

  // ---------- Operations in the group of 4-Rotations

  HepBoostX   operator * (const HepBoostX & b) const;
  HepLorentzRotation operator * (const HepBoost & b) const;
  HepLorentzRotation operator * (const HepRotation & r) const;
  HepLorentzRotation operator * (const HepLorentzRotation & lt) const;
  // Product of two Lorentz Rotations (this) * lt - matrix multiplication
  // Notice that the product of two pure boosts in different directions
  // is no longer a pure boost.

  inline HepBoostX inverse() const;
  // Return the inverse.

  inline friend HepBoostX inverseOf ( const HepBoostX & b );
  // global methods to invert.

  inline HepBoostX & invert();
  // Inverts the Boost matrix.

  // ---------- I/O:

  std::ostream & print( std::ostream & os ) const;
  // Output form is BOOSTX (beta=..., gamma=...);  

  // ---------- Tolerance

  static inline CLHEPdouble getTolerance();
  static inline CLHEPdouble setTolerance(CLHEPdouble tol);

protected:

  inline HepLorentzVector vectorMultiplication
                                        ( const HepLorentzVector & w ) const;
  // Multiplication with a Lorentz Vector.

  HepLorentzRotation matrixMultiplication (const HepRep4x4 & m) const;
  HepLorentzRotation matrixMultiplication (const HepRep4x4Symmetric & m) const;
                   
  inline HepBoostX (CLHEPdouble beta, CLHEPdouble gamma);

  CLHEPdouble  beta_;
  CLHEPdouble  gamma_;

};  // HepBoostX

inline   
std::ostream & operator << 
	( std::ostream & os, const HepBoostX& b ) {return b.print(os);}

}  // namespace CLHEP

#include "CLHEP/Vector/BoostX.icc"

#ifdef ENABLE_BACKWARDS_COMPATIBILITY
//  backwards compatibility will be enabled ONLY in CLHEP 1.9
using namespace CLHEP;
#endif

#endif /* HEP_BOOSTX_H */
