#include "CLHEPTypes.hpp"
// -*- C++ -*-
// CLASSDOC OFF
// ---------------------------------------------------------------------------
// CLASSDOC ON
//
// This file is a part of the CLHEP - a Class Library for High Energy Physics.
//
// This is the definition of the HepRotationZ class for performing rotations
// around the X axis on objects of the Hep3Vector (and HepLorentzVector) class.
//
// HepRotationZ is a concrete implementation of Hep3RotationInterface.
//
// .SS See Also
// RotationInterfaces.h
// ThreeVector.h, LorentzVector.h, LorentzRotation.h
//
// .SS Author
// Mark Fischler

#ifndef HEP_ROTATIONZ_H
#define HEP_ROTATIONZ_H

#include "CLHEP/Vector/defs.h" 
#include "CLHEP/Vector/RotationInterfaces.h"

namespace CLHEP {

class HepRotationZ;
class HepRotation;
class HepBoost;

inline HepRotationZ inverseOf(const HepRotationZ & r);
// Returns the inverse of a RotationZ.

/**
 * @author
 * @ingroup vector
 */
class HepRotationZ {

public:

  // ----------  Constructors and Assignment:

  inline HepRotationZ();
  // Default constructor. Gives an identity rotation. 

  HepRotationZ(CLHEPdouble delta);
  // supply angle of rotation 

  inline HepRotationZ(const HepRotationZ & orig);
  inline HepRotationZ(HepRotationZ && orig) = default;
  // Copy and move constructors.

  inline HepRotationZ & operator = (const HepRotationZ & r);
  inline HepRotationZ & operator = (HepRotationZ && r) = default;
  // Copy and move assignments from a Rotation, which must be RotationZ

  HepRotationZ & set ( CLHEPdouble delta );
  // set angle of rotation 

  inline ~HepRotationZ();
  // Trivial destructor.

  // ----------  Accessors:

  inline Hep3Vector colX() const;
  inline Hep3Vector colY() const;
  inline Hep3Vector colZ() const;
  // orthogonal unit-length column vectors

  inline Hep3Vector rowX() const;
  inline Hep3Vector rowY() const;
  inline Hep3Vector rowZ() const;
  // orthogonal unit-length row vectors
                                
  inline CLHEPdouble xx() const;
  inline CLHEPdouble xy() const;
  inline CLHEPdouble xz() const;
  inline CLHEPdouble yx() const;
  inline CLHEPdouble yy() const;
  inline CLHEPdouble yz() const;
  inline CLHEPdouble zx() const;
  inline CLHEPdouble zy() const;
  inline CLHEPdouble zz() const;
  // Elements of the rotation matrix (Geant4).

  inline HepRep3x3 rep3x3() const;
  //   3x3 representation:

  // ------------  Euler angles:
  inline  CLHEPdouble getPhi  () const;
  inline  CLHEPdouble getTheta() const;
  inline  CLHEPdouble getPsi  () const;
  CLHEPdouble    phi  () const;
  CLHEPdouble    theta() const;
  CLHEPdouble    psi  () const;
  HepEulerAngles eulerAngles() const;

  // ------------  axis & angle of rotation:
  inline  CLHEPdouble  getDelta() const;
  inline  Hep3Vector getAxis () const;
  inline  CLHEPdouble     delta() const;
  inline  Hep3Vector    axis () const;
  inline  HepAxisAngle  axisAngle() const;
  inline  void getAngleAxis(CLHEPdouble & delta, Hep3Vector & axis) const;
  // Returns the rotation angle and rotation axis (Geant4). 	

  // ------------- Angles of rotated axes
  CLHEPdouble phiX() const;
  CLHEPdouble phiY() const;
  CLHEPdouble phiZ() const;
  CLHEPdouble thetaX() const;
  CLHEPdouble thetaY() const;
  CLHEPdouble thetaZ() const;
  // Return angles (RADS) made by rotated axes against original axes (Geant4).

  // ----------  Other accessors treating pure rotation as a 4-rotation

  inline HepLorentzVector col1() const;
  inline HepLorentzVector col2() const;
  inline HepLorentzVector col3() const;
  //  orthosymplectic 4-vector columns - T component will be zero

  inline HepLorentzVector col4() const;
  // Will be (0,0,0,1) for this pure Rotation.

  inline HepLorentzVector row1() const;
  inline HepLorentzVector row2() const;
  inline HepLorentzVector row3() const;
  //  orthosymplectic 4-vector rows - T component will be zero

  inline HepLorentzVector row4() const;
  // Will be (0,0,0,1) for this pure Rotation.

  inline CLHEPdouble xt() const;
  inline CLHEPdouble yt() const;
  inline CLHEPdouble zt() const;
  inline CLHEPdouble tx() const;
  inline CLHEPdouble ty() const;
  inline CLHEPdouble tz() const;
  // Will be zero for this pure Rotation

  inline CLHEPdouble tt() const;
  // Will be one for this pure Rotation

  inline HepRep4x4 rep4x4() const;
  //   4x4 representation.

  // ---------   Mutators 

  void setDelta (CLHEPdouble delta);
  // change angle of rotation, leaving rotation axis unchanged.

  // ----------  Decomposition:

  void decompose (HepAxisAngle & rotation, Hep3Vector & boost) const;
  void decompose (Hep3Vector & boost, HepAxisAngle & rotation) const;
  void decompose (HepRotation & rotation, HepBoost & boost) const;
  void decompose (HepBoost & boost, HepRotation & rotation) const;
   // These are trivial, as the boost vector is 0.		

  // ----------  Comparisons: 
  
  inline bool isIdentity() const;				
  // Returns true if the identity matrix (Geant4).	

  inline int compare( const HepRotationZ & r  ) const;
  // Dictionary-order comparison, in order of delta
  // Used in operator<, >, <=, >=

  inline bool operator== ( const HepRotationZ & r ) const;
  inline bool operator!= ( const HepRotationZ & r ) const;
  inline bool operator<  ( const HepRotationZ & r ) const;
  inline bool operator>  ( const HepRotationZ & r ) const;
  inline bool operator<= ( const HepRotationZ & r ) const;
  inline bool operator>= ( const HepRotationZ & r ) const;

  CLHEPdouble distance2( const HepRotationZ & r  ) const; 
  // 3 - Tr ( this/r )

  CLHEPdouble distance2( const HepRotation &  r  ) const;
  // 3 - Tr ( this/r ) -- This works with RotationY or Z also

  CLHEPdouble howNear( const HepRotationZ & r ) const;
  CLHEPdouble howNear( const HepRotation  & r ) const;
  bool isNear( const HepRotationZ & r,
             CLHEPdouble epsilon=Hep4RotationInterface::tolerance) const;
  bool isNear( const HepRotation  & r,
             CLHEPdouble epsilon=Hep4RotationInterface::tolerance) const;
                                     
  CLHEPdouble distance2( const HepBoost           & lt  ) const;
  // 3 - Tr ( this ) + |b|^2 / (1-|b|^2)
  CLHEPdouble distance2( const HepLorentzRotation & lt  ) const;
  // 3 - Tr ( this/r ) + |b|^2 / (1-|b|^2) where b is the boost vector of lt

  CLHEPdouble howNear( const HepBoost           & lt ) const;
  CLHEPdouble howNear( const HepLorentzRotation & lt ) const;
  bool isNear( const HepBoost           & lt,
             CLHEPdouble epsilon=Hep4RotationInterface::tolerance) const;
  bool isNear( const HepLorentzRotation & lt,
             CLHEPdouble epsilon=Hep4RotationInterface::tolerance) const;

  // ----------  Properties:

  CLHEPdouble norm2() const; 
  // distance2 (IDENTITY), which is 3 - Tr ( *this )

  inline void rectify();
  // non-const but logically moot correction for accumulated roundoff errors

  // ---------- Application:

  inline Hep3Vector operator() (const Hep3Vector & p) const;
  // Rotate a Hep3Vector.					

  inline  Hep3Vector operator * (const Hep3Vector & p) const;
  // Multiplication with a Hep3Vector.

  inline HepLorentzVector operator()( const HepLorentzVector & w ) const;
  // Rotate (the space part of) a HepLorentzVector.		

  inline  HepLorentzVector operator* ( const HepLorentzVector & w ) const;
  // Multiplication with a HepLorentzVector.

 // ---------- Operations in the group of Rotations

  inline HepRotationZ operator * (const HepRotationZ & rz) const;
  // Product of two Z rotations:  (this) * rz is known to be RotationZ.

  // Product of two rotations (this) * b - matrix multiplication  

  inline  HepRotationZ & operator *= (const HepRotationZ & r);
  inline  HepRotationZ & transform   (const HepRotationZ & r);
  // Matrix multiplication.
  // Note a *= b; <=> a = a * b; while a.transform(b); <=> a = b * a;
  // However, in this special case, they commute:  Both just add deltas.

  inline HepRotationZ inverse() const;
  // Returns the inverse.

  friend HepRotationZ inverseOf(const HepRotationZ & r);
  // Returns the inverse of a RotationZ.

  inline HepRotationZ & invert();
  // Inverts the Rotation matrix (be negating delta).

  // ---------- I/O: 

  std::ostream & print( std::ostream & os ) const;
  // Output, identifying type of rotation and delta.

  // ---------- Tolerance

  static inline CLHEPdouble getTolerance();
  static inline CLHEPdouble setTolerance(CLHEPdouble tol);

protected:

  CLHEPdouble its_d;
  // The angle of rotation.

  CLHEPdouble its_s;
  CLHEPdouble its_c;
  // Cache the trig functions, for rapid operations.

  inline HepRotationZ ( CLHEPdouble dd, CLHEPdouble ss, CLHEPdouble cc );
  // Unchecked load-the-data-members

  static inline CLHEPdouble proper (CLHEPdouble delta);
  // Put an angle into the range of (-PI, PI].  Useful helper method.

};  // HepRotationZ

inline   
std::ostream & operator << 
	( std::ostream & os, const HepRotationZ & r ) {return r.print(os);}

// ---------- Free-function operations in the group of Rotations

}  // namespace CLHEP

#include "CLHEP/Vector/RotationZ.icc"

#ifdef ENABLE_BACKWARDS_COMPATIBILITY
//  backwards compatibility will be enabled ONLY in CLHEP 1.9
using namespace CLHEP;
#endif

#endif /* HEP_ROTATIONZ_H */

