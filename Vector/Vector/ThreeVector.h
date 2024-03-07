#include "CLHEPTypes.hpp"
// -*- C++ -*-
// CLASSDOC OFF
// $Id: ThreeVector.h,v 1.4 2010/06/16 17:15:57 garren Exp $
// ---------------------------------------------------------------------------
// CLASSDOC ON
//
// This file is a part of the CLHEP - a Class Library for High Energy Physics.
//
// Hep3Vector is a general 3-vector class defining vectors in three
// dimension using CLHEPdouble components. Rotations of these vectors are
// performed by multiplying with an object of the HepRotation class.
//
// .SS See Also
// LorentzVector.h, Rotation.h, LorentzRotation.h 
//
// .SS Authors
// Leif Lonnblad and Anders Nilsson; Modified by Evgueni Tcherniaev;
// ZOOM additions by Mark Fischler
//

#ifndef HEP_THREEVECTOR_H
#define HEP_THREEVECTOR_H

#include <iostream>
#include "CLHEP/Vector/defs.h" 

namespace CLHEP {

class HepRotation;
class HepEulerAngles;
class HepAxisAngle;

/**
 * @author
 * @ingroup vector
 */
class Hep3Vector {

public:

// Basic properties and operations on 3-vectors:  

  enum { X=0, Y=1, Z=2, NUM_COORDINATES=3, SIZE=NUM_COORDINATES };
  // Safe indexing of the coordinates when using with matrices, arrays, etc.
  // (BaBar)

  Hep3Vector();
  explicit Hep3Vector(CLHEPdouble x);
  Hep3Vector(CLHEPdouble x, CLHEPdouble y);
  Hep3Vector(CLHEPdouble x, CLHEPdouble y, CLHEPdouble z);
  // The constructor.  

  inline Hep3Vector(const Hep3Vector &);
  inline Hep3Vector(Hep3Vector &&) = default;
  // The copy and move constructors.

  inline ~Hep3Vector();
  // The destructor.  Not virtual - inheritance from this class is dangerous.

  CLHEPdouble operator () (int) const;
  // Get components by index -- 0-based (Geant4) 

  inline CLHEPdouble operator [] (int) const;
  // Get components by index -- 0-based (Geant4) 

  CLHEPdouble & operator () (int);
  // Set components by index.  0-based.

  inline CLHEPdouble & operator [] (int);
  // Set components by index.  0-based.

  inline CLHEPdouble x() const;
  inline CLHEPdouble y() const;
  inline CLHEPdouble z() const;
  // The components in cartesian coordinate system.  Same as getX() etc.

  inline void setX(CLHEPdouble);
  inline void setY(CLHEPdouble);
  inline void setZ(CLHEPdouble);
  // Set the components in cartesian coordinate system.

  inline void set( CLHEPdouble x, CLHEPdouble y, CLHEPdouble z); 
  // Set all three components in cartesian coordinate system.

  inline CLHEPdouble phi() const;
  // The azimuth angle.

  inline CLHEPdouble theta() const;
  // The polar angle.

  inline CLHEPdouble cosTheta() const;
  // Cosine of the polar angle.

  inline CLHEPdouble cos2Theta() const;
  // Cosine squared of the polar angle - faster than cosTheta(). (ZOOM)

  inline CLHEPdouble mag2() const;
  // The magnitude squared (r^2 in spherical coordinate system).

  inline CLHEPdouble mag() const;
  // The magnitude (r in spherical coordinate system).

  inline void setPhi(CLHEPdouble);
  // Set phi keeping mag and theta constant (BaBar).

  inline void setTheta(CLHEPdouble);
  // Set theta keeping mag and phi constant (BaBar).

         void setMag(CLHEPdouble);
  // Set magnitude keeping theta and phi constant (BaBar).

  inline CLHEPdouble perp2() const;
  // The transverse component squared (rho^2 in cylindrical coordinate system).

  inline CLHEPdouble perp() const;
  // The transverse component (rho in cylindrical coordinate system).

  inline void setPerp(CLHEPdouble);
  // Set the transverse component keeping phi and z constant.

  void setCylTheta(CLHEPdouble);
  // Set theta while keeping transvers component and phi fixed 

  inline CLHEPdouble perp2(const Hep3Vector &) const;
  // The transverse component w.r.t. given axis squared.

  inline CLHEPdouble perp(const Hep3Vector &) const;
  // The transverse component w.r.t. given axis.

  inline Hep3Vector & operator = (const Hep3Vector &);
  inline Hep3Vector & operator = (Hep3Vector &&) = default;
  // The copy and move assignment operators.

  inline bool operator == (const Hep3Vector &) const;
  inline bool operator != (const Hep3Vector &) const;
  // Comparisons (Geant4). 

  bool isNear (const Hep3Vector &, CLHEPdouble epsilon=tolerance) const;
  // Check for equality within RELATIVE tolerance (default 2.2E-14). (ZOOM)
  // |v1 - v2|**2 <= epsilon**2 * |v1.dot(v2)| 

  CLHEPdouble howNear(const Hep3Vector & v ) const;
  // sqrt ( |v1-v2|**2 / v1.dot(v2) ) with a maximum of 1.
  // If v1.dot(v2) is negative, will return 1.

  CLHEPdouble deltaR(const Hep3Vector & v) const;
  // sqrt( pseudorapity_difference**2 + deltaPhi **2 )

  inline Hep3Vector & operator += (const Hep3Vector &);
  // Addition.

  inline Hep3Vector & operator -= (const Hep3Vector &);
  // Subtraction.

  inline Hep3Vector operator - () const;
  // Unary minus.

  inline Hep3Vector & operator *= (CLHEPdouble);
  // Scaling with real numbers.

         Hep3Vector & operator /= (CLHEPdouble);
  // Division by (non-zero) real number.

  inline Hep3Vector unit() const;
  // Vector parallel to this, but of length 1.

  inline Hep3Vector orthogonal() const;
  // Vector orthogonal to this (Geant4).

  inline CLHEPdouble dot(const Hep3Vector &) const;
  // CLHEPdouble product.

  inline Hep3Vector cross(const Hep3Vector &) const;
  // Cross product.

  CLHEPdouble angle(const Hep3Vector &) const;
  // The angle w.r.t. another 3-vector.

  CLHEPdouble pseudoRapidity() const;
  // Returns the pseudo-rapidity, i.e. -ln(tan(theta/2))

  void setEta  ( CLHEPdouble p );
  // Set pseudo-rapidity, keeping magnitude and phi fixed.  (ZOOM)

  void setCylEta  ( CLHEPdouble p );
  // Set pseudo-rapidity, keeping transverse component and phi fixed.  (ZOOM)

  Hep3Vector & rotateX(CLHEPdouble);
  // Rotates the Hep3Vector around the x-axis.

  Hep3Vector & rotateY(CLHEPdouble);
  // Rotates the Hep3Vector around the y-axis.

  Hep3Vector & rotateZ(CLHEPdouble);
  // Rotates the Hep3Vector around the z-axis.

  Hep3Vector & rotateUz(const Hep3Vector&);
  // Rotates reference frame from Uz to newUz (unit vector) (Geant4).

    Hep3Vector & rotate(CLHEPdouble, const Hep3Vector &);
  // Rotates around the axis specified by another Hep3Vector.
  // (Uses methods of HepRotation, forcing linking in of Rotation.cc.)

  Hep3Vector & operator *= (const HepRotation &);
  Hep3Vector & transform(const HepRotation &);
  // Transformation with a Rotation matrix.


// = = = = = = = = = = = = = = = = = = = = = = = =
//
// Esoteric properties and operations on 3-vectors:  
//
// 1 - Set vectors in various coordinate systems
// 2 - Synonyms for accessing coordinates and properties
// 3 - Comparisions (dictionary, near-ness, and geometric)
// 4 - Intrinsic properties 
// 5 - Properties releative to z axis and arbitrary directions
// 6 - Polar and azimuthal angle decomposition and deltaPhi
// 7 - Rotations 
//
// = = = = = = = = = = = = = = = = = = = = = = = =

// 1 - Set vectors in various coordinate systems

  inline void setRThetaPhi  (CLHEPdouble r, CLHEPdouble theta, CLHEPdouble phi);
  // Set in spherical coordinates:  Angles are measured in RADIANS

  inline void setREtaPhi  ( CLHEPdouble r, CLHEPdouble eta,  CLHEPdouble phi );
  // Set in spherical coordinates, but specify peudorapidiy to determine theta.

  inline void setRhoPhiZ   (CLHEPdouble rho, CLHEPdouble phi, CLHEPdouble z);
  // Set in cylindrical coordinates:  Phi angle is measured in RADIANS

  void setRhoPhiTheta ( CLHEPdouble rho, CLHEPdouble phi, CLHEPdouble theta);
  // Set in cylindrical coordinates, but specify theta to determine z.

  void setRhoPhiEta ( CLHEPdouble rho, CLHEPdouble phi, CLHEPdouble eta);
  // Set in cylindrical coordinates, but specify pseudorapidity to determine z.

// 2 - Synonyms for accessing coordinates and properties

  inline CLHEPdouble getX() const; 
  inline CLHEPdouble getY() const;
  inline CLHEPdouble getZ() const; 
  // x(), y(), and z()

  inline CLHEPdouble getR    () const;
  inline CLHEPdouble getTheta() const;
  inline CLHEPdouble getPhi  () const;
  // mag(), theta(), and phi()

  inline CLHEPdouble r       () const;
  // mag()

  inline CLHEPdouble rho     () const;
  inline CLHEPdouble getRho  () const;
  // perp()

  CLHEPdouble eta     () const;
  CLHEPdouble getEta  () const;
  // pseudoRapidity() 

  inline void setR ( CLHEPdouble s );
  // setMag()

  inline void setRho ( CLHEPdouble s );
  // setPerp()

// 3 - Comparisions (dictionary, near-ness, and geometric)

  int compare (const Hep3Vector & v) const;
  bool operator > (const Hep3Vector & v) const;
  bool operator < (const Hep3Vector & v) const;
  bool operator>= (const Hep3Vector & v) const;
  bool operator<= (const Hep3Vector & v) const;
  // dictionary ordering according to z, then y, then x component

  inline CLHEPdouble diff2 (const Hep3Vector & v) const;
  // |v1-v2|**2

  static CLHEPdouble setTolerance (CLHEPdouble tol);
  static inline CLHEPdouble getTolerance ();
  // Set the tolerance used in isNear() for Hep3Vectors 

  bool isParallel (const Hep3Vector & v, CLHEPdouble epsilon=tolerance) const;
  // Are the vectors parallel, within the given tolerance?

  bool isOrthogonal (const Hep3Vector & v, CLHEPdouble epsilon=tolerance) const;
  // Are the vectors orthogonal, within the given tolerance?

  CLHEPdouble howParallel   (const Hep3Vector & v) const;
  // | v1.cross(v2) / v1.dot(v2) |, to a maximum of 1.

  CLHEPdouble howOrthogonal (const Hep3Vector & v) const;
  // | v1.dot(v2) / v1.cross(v2) |, to a maximum of 1.

  enum { ToleranceTicks = 100 };

// 4 - Intrinsic properties 

  CLHEPdouble beta    () const;
  // relativistic beta (considering v as a velocity vector with c=1)
  // Same as mag() but will object if >= 1

  CLHEPdouble gamma() const;
  // relativistic gamma (considering v as a velocity vector with c=1)

  CLHEPdouble coLinearRapidity() const;
  // inverse tanh (beta)

// 5 - Properties relative to Z axis and to an arbitrary direction

	  // Note that the non-esoteric CLHEP provides 
	  // theta(), cosTheta(), cos2Theta, and angle(const Hep3Vector&)

  inline CLHEPdouble angle() const;
  // angle against the Z axis -- synonym for theta()

  inline CLHEPdouble theta(const Hep3Vector & v2) const;  
  // synonym for angle(v2)

  CLHEPdouble cosTheta (const Hep3Vector & v2) const;
  CLHEPdouble cos2Theta(const Hep3Vector & v2) const;
  // cos and cos^2 of the angle between two vectors

  inline Hep3Vector project () const;
         Hep3Vector project (const Hep3Vector & v2) const;
  // projection of a vector along a direction.  

  inline Hep3Vector perpPart() const;
  inline Hep3Vector perpPart (const Hep3Vector & v2) const;
  // vector minus its projection along a direction.

  CLHEPdouble rapidity () const;
  // inverse tanh(v.z())

  CLHEPdouble rapidity (const Hep3Vector & v2) const;
  // rapidity with respect to specified direction:  
  // inverse tanh (v.dot(u)) where u is a unit in the direction of v2

  CLHEPdouble eta(const Hep3Vector & v2) const;
  // - ln tan of the angle beween the vector and the ref direction.

// 6 - Polar and azimuthal angle decomposition and deltaPhi

  // Decomposition of an angle within reference defined by a direction:

  CLHEPdouble polarAngle (const Hep3Vector & v2) const;
  // The reference direction is Z: the polarAngle is abs(v.theta()-v2.theta()).

  CLHEPdouble deltaPhi (const Hep3Vector & v2) const;
  // v.phi()-v2.phi(), brought into the range (-PI,PI]

  CLHEPdouble azimAngle  (const Hep3Vector & v2) const;
  // The reference direction is Z: the azimAngle is the same as deltaPhi

  CLHEPdouble polarAngle (const Hep3Vector & v2, 
					const Hep3Vector & ref) const;
  // For arbitrary reference direction, 
  // 	polarAngle is abs(v.angle(ref) - v2.angle(ref)).

  CLHEPdouble azimAngle  (const Hep3Vector & v2, 
					const Hep3Vector & ref) const;
  // To compute azimangle, project v and v2 into the plane normal to
  // the reference direction.  Then in that plane take the angle going
  // clockwise around the direction from projection of v to that of v2.

// 7 - Rotations 

// These mehtods **DO NOT** use anything in the HepRotation class.
// Thus, use of v.rotate(axis,delta) does not force linking in Rotation.cc.

  Hep3Vector & rotate  (const Hep3Vector & axis, CLHEPdouble delta);
  // Synonym for rotate (delta, axis)

  Hep3Vector & rotate  (const HepAxisAngle & ax);
  // HepAxisAngle is a struct holding an axis direction and an angle.

  Hep3Vector & rotate (const HepEulerAngles & e);
  Hep3Vector & rotate (CLHEPdouble phi,
                        CLHEPdouble theta,
                        CLHEPdouble psi);
  // Rotate via Euler Angles. Our Euler Angles conventions are 
  // those of Goldstein Classical Mechanics page 107.

protected:
  void setSpherical (CLHEPdouble r, CLHEPdouble theta, CLHEPdouble phi);
  void setCylindrical (CLHEPdouble r, CLHEPdouble phi, CLHEPdouble z);
  CLHEPdouble negativeInfinity() const;

protected:

  CLHEPdouble data[3];
  // The components.

  static CLHEPdouble tolerance;
  // default tolerance criterion for isNear() to return true.
};  // Hep3Vector

// Global Methods

Hep3Vector rotationXOf (const Hep3Vector & vec, CLHEPdouble delta);
Hep3Vector rotationYOf (const Hep3Vector & vec, CLHEPdouble delta);
Hep3Vector rotationZOf (const Hep3Vector & vec, CLHEPdouble delta);

Hep3Vector rotationOf (const Hep3Vector & vec, 
				const Hep3Vector & axis, CLHEPdouble delta);
Hep3Vector rotationOf (const Hep3Vector & vec, const HepAxisAngle & ax);

Hep3Vector rotationOf (const Hep3Vector & vec, 
				CLHEPdouble phi, CLHEPdouble theta, CLHEPdouble psi);
Hep3Vector rotationOf (const Hep3Vector & vec, const HepEulerAngles & e);
// Return a new vector based on a rotation of the supplied vector

std::ostream & operator << (std::ostream &, const Hep3Vector &);
// Output to a stream.

std::istream & operator >> (std::istream &, Hep3Vector &);
// Input from a stream.

extern const Hep3Vector HepXHat, HepYHat, HepZHat;

typedef Hep3Vector HepThreeVectorD;
typedef Hep3Vector HepThreeVectorF;

Hep3Vector operator / (const Hep3Vector &, CLHEPdouble a);
// Division of 3-vectors by non-zero real number

inline Hep3Vector operator + (const Hep3Vector &, const Hep3Vector &);
// Addition of 3-vectors.

inline Hep3Vector operator - (const Hep3Vector &, const Hep3Vector &);
// Subtraction of 3-vectors.

inline CLHEPdouble operator * (const Hep3Vector &, const Hep3Vector &);
// CLHEPdouble product of 3-vectors.

inline Hep3Vector operator * (const Hep3Vector &, CLHEPdouble a);
inline Hep3Vector operator * (CLHEPdouble a, const Hep3Vector &);
// Scaling of 3-vectors with a real number

}  // namespace CLHEP

#include "CLHEP/Vector/ThreeVector.icc"

#ifdef ENABLE_BACKWARDS_COMPATIBILITY
//  backwards compatibility will be enabled ONLY in CLHEP 1.9
using namespace CLHEP;
#endif

#endif /* HEP_THREEVECTOR_H */
