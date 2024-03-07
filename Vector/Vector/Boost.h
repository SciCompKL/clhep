#include "CLHEPTypes.hpp"
// -*- C++ -*-
//
// This file is a part of the CLHEP - a Class Library for High Energy Physics.
//
// This is the definition of the HepBoost class for performing specialized
// Lorentz transformations which are pure boosts on objects of the
// HepLorentzVector class.
//
// HepBoost is a concrete implementation of Hep4RotationInterface.
//
// .SS See Also
// RotationInterfaces.h
// LorentzVector.h LorentzRotation.h 
//  BoostX.h BoostY.h BoostZ.h 
//
// .SS Author
// Mark Fischler

#ifndef HEP_BOOST_H
#define HEP_BOOST_H

#include "CLHEP/Vector/defs.h" 
#include "CLHEP/Vector/RotationInterfaces.h"
#include "CLHEP/Vector/BoostX.h"
#include "CLHEP/Vector/BoostY.h"
#include "CLHEP/Vector/BoostZ.h"
#include "CLHEP/Vector/LorentzVector.h"

namespace CLHEP {

// Declarations of classes and global methods
class HepBoost;
inline HepBoost inverseOf ( const HepBoost & lt );

/**
 * @author
 * @ingroup vector
 */
class HepBoost {

public:

  // ----------  Constructors and Assignment:

  inline HepBoost();
  // Default constructor. Gives a boost of 0.  

  inline HepBoost(const HepBoost & m);
  inline HepBoost(HepBoost && m) = default;
  // Copy and move constructors.

  inline HepBoost & operator = (const HepBoost & m);
  inline HepBoost & operator = (HepBoost && m) = default;
  // Copy and move assignment operators.

         HepBoost & set (CLHEPdouble betaX, CLHEPdouble betaY, CLHEPdouble betaZ);
  inline HepBoost       (CLHEPdouble betaX, CLHEPdouble betaY, CLHEPdouble betaZ);
  // Constructor from three components of beta vector

         HepBoost & set (const HepRep4x4Symmetric & m);
  inline HepBoost       (const HepRep4x4Symmetric & m);
  // Constructor from symmetric HepRep4x4

         HepBoost & set (Hep3Vector direction, CLHEPdouble beta);
  inline HepBoost       (Hep3Vector direction, CLHEPdouble beta);
  // Constructor from a three vector direction and the magnitude of beta

         HepBoost & set (const Hep3Vector & boost);
  inline HepBoost       (const Hep3Vector & boost);
  // Constructor from a 3-vector of less than unit length

  inline HepBoost & set (const HepBoostX & boost);
  inline HepBoost & set (const HepBoostY & boost);
  inline HepBoost & set (const HepBoostZ & boost);
  inline HepBoost       (const HepBoostX & boost);
  inline HepBoost       (const HepBoostY & boost);
  inline HepBoost       (const HepBoostZ & boost);

  // ----------  Accessors:

  inline CLHEPdouble  beta()  const;
  inline CLHEPdouble  gamma() const;
  inline Hep3Vector boostVector() const;
  inline Hep3Vector getDirection() const;
  inline Hep3Vector direction() const;

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

  inline HepRep4x4 rep4x4() const;
  //   4x4 representation.

  inline HepRep4x4Symmetric rep4x4Symmetric() const;
  //   Symmetric 4x4 representation.

  // ----------  Decomposition:

  void decompose (HepRotation  & rotation, HepBoost   & boost) const;
  void decompose (HepAxisAngle & rotation, Hep3Vector & boost) const;
  // Find R and B such that L = R*B -- trivial, since R is identity

  void decompose (HepBoost   & boost, HepRotation  & rotation) const;
  void decompose (Hep3Vector & boost, HepAxisAngle & rotation) const;
  // Find R and B such that L = B*R -- trivial, since R is identity

  // ----------  Comparisons:

  inline int compare( const HepBoost & b  ) const;
  // Dictionary-order comparison, in order tt,zt,zz,yt,yz,yy,xt,xz,xy,xx
  // Used in operator<, >, <=, >=

  inline bool operator == (const HepBoost & b) const;
  inline bool operator != (const HepBoost & b) const;
  inline bool operator <= (const HepBoost & b) const;
  inline bool operator >= (const HepBoost & b) const;
  inline bool operator <  (const HepBoost & b) const;
  inline bool operator >  (const HepBoost & b) const;
  // Comparisons.

  inline bool isIdentity() const;
  // Returns true if a null boost.

  inline  CLHEPdouble distance2( const HepBoost  & b  ) const;
  inline  CLHEPdouble distance2( const HepBoostX & bx ) const;
  inline  CLHEPdouble distance2( const HepBoostY & by ) const;
  inline  CLHEPdouble distance2( const HepBoostZ & bz ) const;
  // Defined as the distance2 between the vectors (gamma*betaVector)

  CLHEPdouble distance2( const HepRotation & r  ) const;
  CLHEPdouble distance2( const HepLorentzRotation & lt  ) const;
  // Distance between this and other sorts of transformations

  inline CLHEPdouble howNear(   const HepBoost & b ) const;
  inline bool isNear(   const HepBoost & b,
             CLHEPdouble epsilon=Hep4RotationInterface::tolerance) const;

  CLHEPdouble howNear( const HepRotation & r  ) const;
  CLHEPdouble howNear( const HepLorentzRotation & lt  ) const;

  bool isNear( const HepRotation & r, 
             CLHEPdouble epsilon=Hep4RotationInterface::tolerance) const;
  bool isNear( const HepLorentzRotation & lt, 
             CLHEPdouble epsilon=Hep4RotationInterface::tolerance) const;

  // ----------  Properties:

  CLHEPdouble norm2() const;
  // (beta*gamma)^2

  void rectify();
  // set as an exact boost, based on the timelike part of the boost matrix.

  // ---------- Application:

  inline HepLorentzVector operator()( const HepLorentzVector & p ) const;
  // Transform a Lorentz Vector.             

  inline HepLorentzVector operator* ( const HepLorentzVector & p ) const;
  // Multiplication with a Lorentz Vector.

  // ---------- Operations in the group of 4-Rotations

  HepLorentzRotation operator * (const HepBoost & b) const;
  HepLorentzRotation operator * (const HepRotation & r) const;
  HepLorentzRotation operator * (const HepLorentzRotation & lt) const;
  // Product of two Lorentz Rotations (this) * lt - matrix multiplication  
  // Notice that the product of two pure boosts is no longer a pure boost

  inline HepBoost inverse() const;
  // Return the inverse.

  inline friend HepBoost inverseOf ( const HepBoost & lt );
  // global methods to invert.

  inline HepBoost & invert();
  // Inverts the Boost matrix.

  // ---------- I/O:

  std::ostream & print( std::ostream & os ) const;
  // Output form is (bx, by, bz) 

  // ---------- Tolerance              

  static inline CLHEPdouble getTolerance();
  static inline CLHEPdouble setTolerance(CLHEPdouble tol);

protected:

  inline HepLorentzVector vectorMultiplication 
					( const HepLorentzVector & w ) const;
  // Multiplication with a Lorentz Vector.

  HepLorentzRotation matrixMultiplication (const HepRep4x4 & m) const;
  HepLorentzRotation matrixMultiplication (const HepRep4x4Symmetric & m) const;

  inline HepBoost
       (CLHEPdouble xx, CLHEPdouble xy, CLHEPdouble xz, CLHEPdouble xt,
		   CLHEPdouble yy, CLHEPdouble yz, CLHEPdouble yt,
			      CLHEPdouble zz, CLHEPdouble zt,
					 CLHEPdouble tt);
  // Protected constructor.
  // DOES NOT CHECK FOR VALIDITY AS A LORENTZ BOOST.

  inline void setBoost(CLHEPdouble bx, CLHEPdouble by, CLHEPdouble bz);

  HepRep4x4Symmetric rep_;

};  // HepBoost

inline   
std::ostream & operator << 
	( std::ostream & os, const HepBoost& b ) {return b.print(os);}

}  // namespace CLHEP

#include "CLHEP/Vector/Boost.icc"

#ifdef ENABLE_BACKWARDS_COMPATIBILITY
//  backwards compatibility will be enabled ONLY in CLHEP 1.9
using namespace CLHEP;
#endif

#endif /* HEP_BOOST_H */
