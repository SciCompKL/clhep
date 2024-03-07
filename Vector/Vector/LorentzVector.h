#include "CLHEPTypes.hpp"
// -*- C++ -*-
// CLASSDOC OFF
// $Id: LorentzVector.h,v 1.2 2003/10/23 21:29:52 garren Exp $
// ---------------------------------------------------------------------------
// CLASSDOC ON
//
// This file is a part of the CLHEP - a Class Library for High Energy Physics.
//
// HepLorentzVector is a Lorentz vector consisting of Hep3Vector and
// CLHEPdouble components. Lorentz transformations (rotations and boosts)
// of these vectors are perfomed by multiplying with objects of
// the HepLorenzRotation class.
//
// .SS See Also
// ThreeVector.h, Rotation.h, LorentzRotation.h
//
// .SS Authors
// Leif Lonnblad and Anders Nilsson. Modified by Evgueni Tcherniaev, Mark Fischler
//

#ifndef HEP_LORENTZVECTOR_H
#define HEP_LORENTZVECTOR_H

#include <iostream>
#include "CLHEP/Vector/defs.h" 
#include "CLHEP/Vector/ThreeVector.h"

namespace CLHEP {

// Declarations of classes and global methods
class HepLorentzVector;
class HepLorentzRotation;
class HepRotation;
class HepAxisAngle;
class HepEulerAngles;
class Tcomponent;
HepLorentzVector rotationXOf( const HepLorentzVector & vec, CLHEPdouble delta );
HepLorentzVector rotationYOf( const HepLorentzVector & vec, CLHEPdouble delta );
HepLorentzVector rotationZOf( const HepLorentzVector & vec, CLHEPdouble delta );
HepLorentzVector rotationOf
    ( const HepLorentzVector & vec, const Hep3Vector & axis, CLHEPdouble delta );
HepLorentzVector rotationOf
    ( const HepLorentzVector & vec, const HepAxisAngle & ax );
HepLorentzVector rotationOf
    ( const HepLorentzVector & vec, const HepEulerAngles & e1 );
HepLorentzVector rotationOf
    ( const HepLorentzVector & vec, CLHEPdouble phi,
                                    CLHEPdouble theta,
                                    CLHEPdouble psi );
inline 
HepLorentzVector  boostXOf( const HepLorentzVector & vec, CLHEPdouble beta );
inline 
HepLorentzVector  boostYOf( const HepLorentzVector & vec, CLHEPdouble beta );
inline 
HepLorentzVector  boostZOf( const HepLorentzVector & vec, CLHEPdouble beta );
inline HepLorentzVector  boostOf
    ( const HepLorentzVector & vec, const Hep3Vector & betaVector );
inline HepLorentzVector  boostOf
    ( const HepLorentzVector & vec, const Hep3Vector & axis,  CLHEPdouble beta );

enum ZMpvMetric_t { TimePositive, TimeNegative };


/**
 * @author
 * @ingroup vector
 */
class HepLorentzVector {

public:

  enum { X=0, Y=1, Z=2, T=3, NUM_COORDINATES=4, SIZE=NUM_COORDINATES };
  // Safe indexing of the coordinates when using with matrices, arrays, etc.
  // (BaBar)

  inline HepLorentzVector(CLHEPdouble x, CLHEPdouble y,
			  CLHEPdouble z, CLHEPdouble t);
  // Constructor giving the components x, y, z, t.

  inline HepLorentzVector(CLHEPdouble x, CLHEPdouble y, CLHEPdouble z);
  // Constructor giving the components x, y, z with t-component set to 0.0.

  explicit HepLorentzVector(CLHEPdouble t);
  // Constructor giving the t-component with x, y and z set to 0.0.

  inline HepLorentzVector();
  // Default constructor with x, y, z and t set to 0.0.

  inline HepLorentzVector(const Hep3Vector & p, CLHEPdouble e);
  inline HepLorentzVector(CLHEPdouble e, const Hep3Vector & p);
  // Constructor giving a 3-Vector and a time component.

  inline HepLorentzVector(const HepLorentzVector &);
  inline HepLorentzVector(HepLorentzVector &&) = default;
  // Copy and move constructors.

  inline ~HepLorentzVector();
  // The destructor.

  inline operator const Hep3Vector & () const;
  inline operator Hep3Vector & ();
  // Conversion (cast) to Hep3Vector.

  inline CLHEPdouble x() const;
  inline CLHEPdouble y() const;
  inline CLHEPdouble z() const;
  inline CLHEPdouble t() const;
  // Get position and time.

  inline void setX(CLHEPdouble);
  inline void setY(CLHEPdouble);
  inline void setZ(CLHEPdouble);
  inline void setT(CLHEPdouble);
  // Set position and time.

  inline CLHEPdouble px() const;
  inline CLHEPdouble py() const;
  inline CLHEPdouble pz() const;
  inline CLHEPdouble e() const;
  // Get momentum and energy.

  inline void setPx(CLHEPdouble);
  inline void setPy(CLHEPdouble);
  inline void setPz(CLHEPdouble);
  inline void setE(CLHEPdouble);
  // Set momentum and energy.

  inline Hep3Vector vect() const;
  // Get spatial component. 

  inline void setVect(const Hep3Vector &);
  // Set spatial component. 

  inline CLHEPdouble theta() const;
  inline CLHEPdouble cosTheta() const;
  inline CLHEPdouble phi() const;
  inline CLHEPdouble rho() const;
  // Get spatial vector components in spherical coordinate system.

  inline void setTheta(CLHEPdouble);
  inline void setPhi(CLHEPdouble);
  inline void setRho(CLHEPdouble);
  // Set spatial vector components in spherical coordinate system.

  CLHEPdouble operator () (int) const;
  inline CLHEPdouble operator [] (int) const;
  // Get components by index.

  CLHEPdouble & operator () (int);
  inline CLHEPdouble & operator [] (int);
  // Set components by index.

  inline HepLorentzVector & operator = (const HepLorentzVector &);
  inline HepLorentzVector & operator = (HepLorentzVector &&) = default;
  // Copy and move assignment operators. 

  inline HepLorentzVector   operator +  (const HepLorentzVector &) const;
  inline HepLorentzVector & operator += (const HepLorentzVector &);
  // Additions.

  inline HepLorentzVector   operator -  (const HepLorentzVector &) const;
  inline HepLorentzVector & operator -= (const HepLorentzVector &);
  // Subtractions.

  inline HepLorentzVector operator - () const;
  // Unary minus.

  inline HepLorentzVector & operator *= (CLHEPdouble);
         HepLorentzVector & operator /= (CLHEPdouble);
  // Scaling with real numbers.

  inline bool operator == (const HepLorentzVector &) const;
  inline bool operator != (const HepLorentzVector &) const;
  // Comparisons.

  inline CLHEPdouble perp2() const;
  // Transverse component of the spatial vector squared.

  inline CLHEPdouble perp() const;
  // Transverse component of the spatial vector (R in cylindrical system).

  inline void setPerp(CLHEPdouble);
  // Set the transverse component of the spatial vector.

  inline CLHEPdouble perp2(const Hep3Vector &) const;
  // Transverse component of the spatial vector w.r.t. given axis squared.

  inline CLHEPdouble perp(const Hep3Vector &) const;
  // Transverse component of the spatial vector w.r.t. given axis.

  inline CLHEPdouble angle(const Hep3Vector &) const;
  // Angle wrt. another vector.

  inline CLHEPdouble mag2() const;
  // Dot product of 4-vector with itself. 
  // By default the metric is TimePositive, and mag2() is the same as m2().

  inline CLHEPdouble m2() const;
  // Invariant mass squared.

  inline CLHEPdouble mag() const;
  inline CLHEPdouble m() const;
  // Invariant mass. If m2() is negative then -sqrt(-m2()) is returned.

  inline CLHEPdouble mt2() const;
  // Transverse mass squared.

  inline CLHEPdouble mt() const;
  // Transverse mass.

  inline CLHEPdouble et2() const;
  // Transverse energy squared.

  inline CLHEPdouble et() const;
  // Transverse energy.

  inline CLHEPdouble dot(const HepLorentzVector &) const;
  inline CLHEPdouble operator * (const HepLorentzVector &) const;
  // Scalar product.

  inline CLHEPdouble invariantMass2( const HepLorentzVector & w ) const;
  // Invariant mass squared of pair of 4-vectors 

  CLHEPdouble invariantMass ( const HepLorentzVector & w ) const;
  // Invariant mass of pair of 4-vectors 

  inline void setVectMag(const Hep3Vector & spatial, CLHEPdouble magnitude);
  inline void setVectM(const Hep3Vector & spatial, CLHEPdouble mass);
  // Copy spatial coordinates, and set energy = sqrt(mass^2 + spatial^2)

  inline CLHEPdouble plus() const;
  inline CLHEPdouble minus() const;
  // Returns the positive/negative light-cone component t +/- z.

  Hep3Vector boostVector() const;
  // Boost needed from rest4Vector in rest frame to form this 4-vector
  // Returns the spatial components divided by the time component.

  HepLorentzVector & boost(CLHEPdouble, CLHEPdouble, CLHEPdouble);
  inline HepLorentzVector & boost(const Hep3Vector &);
  // Lorentz boost.

  HepLorentzVector & boostX( CLHEPdouble beta );
  HepLorentzVector & boostY( CLHEPdouble beta );
  HepLorentzVector & boostZ( CLHEPdouble beta );
  // Boost along an axis, by magnitue beta (fraction of speed of light)

  CLHEPdouble rapidity() const;
  // Returns the rapidity, i.e. 0.5*ln((E+pz)/(E-pz))

  inline CLHEPdouble pseudoRapidity() const;
  // Returns the pseudo-rapidity, i.e. -ln(tan(theta/2))

  inline bool isTimelike() const;
  // Test if the 4-vector is timelike

  inline bool isSpacelike() const;
  // Test if the 4-vector is spacelike

  inline bool isLightlike(CLHEPdouble epsilon=tolerance) const;
  // Test for lightlike is within tolerance epsilon

  HepLorentzVector &  rotateX(CLHEPdouble);
  // Rotate the spatial component around the x-axis.

  HepLorentzVector &  rotateY(CLHEPdouble);
  // Rotate the spatial component around the y-axis.

  HepLorentzVector &  rotateZ(CLHEPdouble);
  // Rotate the spatial component around the z-axis.

  HepLorentzVector &  rotateUz(const Hep3Vector &);
  // Rotates the reference frame from Uz to newUz (unit vector).

  HepLorentzVector & rotate(CLHEPdouble, const Hep3Vector &);
  // Rotate the spatial component around specified axis.

  inline HepLorentzVector & operator *= (const HepRotation &);
  inline HepLorentzVector & transform(const HepRotation &);
  // Transformation with HepRotation.

  HepLorentzVector & operator *= (const HepLorentzRotation &);
  HepLorentzVector & transform(const HepLorentzRotation &);
  // Transformation with HepLorenzRotation.

// = = = = = = = = = = = = = = = = = = = = = = = =
//
// Esoteric properties and operations on 4-vectors:  
//
// 0 - Flexible metric convention and axial unit 4-vectors
// 1 - Construct and set 4-vectors in various ways 
// 2 - Synonyms for accessing coordinates and properties
// 2a - Setting space coordinates in different ways 
// 3 - Comparisions (dictionary, near-ness, and geometric)
// 4 - Intrinsic properties 
// 4a - Releativistic kinematic properties 
// 4b - Methods combining two 4-vectors
// 5 - Properties releative to z axis and to arbitrary directions
// 7 - Rotations and Boosts
//
// = = = = = = = = = = = = = = = = = = = = = = = =

// 0 - Flexible metric convention 

  static ZMpvMetric_t setMetric( ZMpvMetric_t a1 );
  static ZMpvMetric_t getMetric();

// 1 - Construct and set 4-vectors in various ways 

  inline void set        (CLHEPdouble x, CLHEPdouble y, CLHEPdouble z, CLHEPdouble  t);
  inline void set        (CLHEPdouble x, CLHEPdouble y, CLHEPdouble z, Tcomponent t);
  inline HepLorentzVector(CLHEPdouble x, CLHEPdouble y, CLHEPdouble z, Tcomponent t);
  // Form 4-vector by supplying cartesian coordinate components

  inline void set        (Tcomponent t, CLHEPdouble x, CLHEPdouble y, CLHEPdouble z);
  inline HepLorentzVector(Tcomponent t, CLHEPdouble x, CLHEPdouble y, CLHEPdouble z);
  // Deprecated because the 4-CLHEPdoubles form uses x,y,z,t, not t,x,y,z.

  inline void set                 ( CLHEPdouble t );

  inline void set                 ( Tcomponent t );
  inline explicit HepLorentzVector( Tcomponent t );
  // Form 4-vector with zero space components, by supplying t component

  inline void set                 ( const Hep3Vector & v );
  inline explicit HepLorentzVector( const Hep3Vector & v );
  // Form 4-vector with zero time component, by supplying space 3-vector 

  inline HepLorentzVector & operator=( const Hep3Vector & v );
  // Form 4-vector with zero time component, equal to space 3-vector 

  inline void set ( const Hep3Vector & v, CLHEPdouble t );
  inline void set ( CLHEPdouble t, const Hep3Vector & v );
  // Set using specified space vector and time component

// 2 - Synonyms for accessing coordinates and properties

  inline CLHEPdouble getX() const;
  inline CLHEPdouble getY() const;
  inline CLHEPdouble getZ() const;
  inline CLHEPdouble getT() const;
  // Get position and time.

  inline Hep3Vector v() const;
  inline Hep3Vector getV() const;
  // Get spatial component.   Same as vect.

  inline void setV(const Hep3Vector &);
  // Set spatial component.   Same as setVect.

// 2a - Setting space coordinates in different ways 

  inline void setV( CLHEPdouble x, CLHEPdouble y, CLHEPdouble z );

  inline void setRThetaPhi( CLHEPdouble r, CLHEPdouble theta, CLHEPdouble phi);
  inline void setREtaPhi( CLHEPdouble r, CLHEPdouble eta, CLHEPdouble phi);
  inline void setRhoPhiZ( CLHEPdouble rho, CLHEPdouble phi, CLHEPdouble z );

// 3 - Comparisions (dictionary, near-ness, and geometric)

  int compare( const HepLorentzVector & w ) const;

  bool operator >( const HepLorentzVector & w ) const;
  bool operator <( const HepLorentzVector & w ) const;
  bool operator>=( const HepLorentzVector & w ) const;
  bool operator<=( const HepLorentzVector & w ) const;

  bool   isNear ( const HepLorentzVector & w, 
					CLHEPdouble epsilon=tolerance ) const;
  CLHEPdouble howNear( const HepLorentzVector & w ) const;
  // Is near using Euclidean measure t**2 + v**2

  bool   isNearCM ( const HepLorentzVector & w, 
					CLHEPdouble epsilon=tolerance ) const;
  CLHEPdouble howNearCM( const HepLorentzVector & w ) const;
  // Is near in CM frame:  Applicable only for two timelike HepLorentzVectors

        // If w1 and w2 are already in their CM frame, then w1.isNearCM(w2)
        // is exactly equivalent to w1.isNear(w2).
        // If w1 and w2 have T components of zero, w1.isNear(w2) is exactly
        // equivalent to w1.getV().isNear(w2.v()).  

  bool isParallel( const HepLorentzVector & w, 
					CLHEPdouble epsilon=tolerance ) const;
  // Test for isParallel is within tolerance epsilon
  CLHEPdouble howParallel (const HepLorentzVector & w) const;

  static CLHEPdouble getTolerance();
  static CLHEPdouble setTolerance( CLHEPdouble tol );
  // Set the tolerance for HepLorentzVectors to be considered near
  // The same tolerance is used for determining isLightlike, and isParallel

  CLHEPdouble deltaR(const HepLorentzVector & v) const;
  // sqrt ( (delta eta)^2 + (delta phi)^2 ) of space part

// 4 - Intrinsic properties 

         CLHEPdouble howLightlike() const;
  // Close to zero for almost lightlike 4-vectors; up to 1.

  inline CLHEPdouble euclideanNorm2()  const;
  // Sum of the squares of time and space components; not Lorentz invariant. 

  inline CLHEPdouble euclideanNorm()  const; 
  // Length considering the metric as (+ + + +); not Lorentz invariant.


// 4a - Relativistic kinematic properties 

// All Relativistic kinematic properties are independent of the sense of metric

  inline CLHEPdouble restMass2() const;
  inline CLHEPdouble invariantMass2() const; 
  // Rest mass squared -- same as m2()

  inline CLHEPdouble restMass() const;
  inline CLHEPdouble invariantMass() const; 
  // Same as m().  If m2() is negative then -sqrt(-m2()) is returned.

// The following properties are rest-frame related, 
// and are applicable only to non-spacelike 4-vectors

  HepLorentzVector rest4Vector() const;
  // This 4-vector, boosted into its own rest frame:  (0, 0, 0, m()) 
          // The following relation holds by definition:
          // w.rest4Vector().boost(w.boostVector()) == w

  // Beta and gamma of the boost vector
  CLHEPdouble beta() const;
  // Relativistic beta of the boost vector

  CLHEPdouble gamma() const;
  // Relativistic gamma of the boost vector

  inline CLHEPdouble eta() const;
  // Pseudorapidity (of the space part)

  inline CLHEPdouble eta(const Hep3Vector & ref) const;
  // Pseudorapidity (of the space part) w.r.t. specified direction

  CLHEPdouble rapidity(const Hep3Vector & ref) const;
  // Rapidity in specified direction

  CLHEPdouble coLinearRapidity() const;
  // Rapidity, in the relativity textbook sense:  atanh (|P|/E)

  Hep3Vector findBoostToCM() const;
  // Boost needed to get to center-of-mass  frame:
          // w.findBoostToCM() == - w.boostVector()
          // w.boost(w.findBoostToCM()) == w.rest4Vector()

  Hep3Vector findBoostToCM( const HepLorentzVector & w ) const;
  // Boost needed to get to combined center-of-mass frame:
          // w1.findBoostToCM(w2) == w2.findBoostToCM(w1)
          // w.findBoostToCM(w) == w.findBoostToCM()

  inline CLHEPdouble et2(const Hep3Vector &) const;
  // Transverse energy w.r.t. given axis squared.

  inline CLHEPdouble et(const Hep3Vector &) const;
  // Transverse energy w.r.t. given axis.

// 4b - Methods combining two 4-vectors

  inline CLHEPdouble diff2( const HepLorentzVector & w ) const;
  // (this - w).dot(this-w); sign depends on metric choice

  inline CLHEPdouble delta2Euclidean ( const HepLorentzVector & w ) const;
  // Euclidean norm of differnce:  (delta_T)^2  + (delta_V)^2

// 5 - Properties releative to z axis and to arbitrary directions

  CLHEPdouble  plus(  const Hep3Vector & ref ) const;
  // t + projection in reference direction

  CLHEPdouble  minus( const Hep3Vector & ref ) const;
  // t - projection in reference direction

// 7 - Rotations and boosts

  HepLorentzVector & rotate ( const Hep3Vector & axis, CLHEPdouble delta );
  // Same as rotate (delta, axis)

  HepLorentzVector & rotate ( const HepAxisAngle & ax );
  HepLorentzVector & rotate ( const HepEulerAngles & e );
  HepLorentzVector & rotate ( CLHEPdouble phi,
                              CLHEPdouble theta,
                              CLHEPdouble psi );
  // Rotate using these HepEuler angles - see Goldstein page 107 for conventions

  HepLorentzVector & boost ( const Hep3Vector & axis,  CLHEPdouble beta );
  // Normalizes the Hep3Vector to define a direction, and uses beta to
  // define the magnitude of the boost.

  friend HepLorentzVector rotationXOf
    ( const HepLorentzVector & vec, CLHEPdouble delta );
  friend HepLorentzVector rotationYOf
    ( const HepLorentzVector & vec, CLHEPdouble delta );
  friend HepLorentzVector rotationZOf
    ( const HepLorentzVector & vec, CLHEPdouble delta );
  friend HepLorentzVector rotationOf
    ( const HepLorentzVector & vec, const Hep3Vector & axis, CLHEPdouble delta );
  friend HepLorentzVector rotationOf
    ( const HepLorentzVector & vec, const HepAxisAngle & ax );
  friend HepLorentzVector rotationOf
    ( const HepLorentzVector & vec, const HepEulerAngles & e );
  friend HepLorentzVector rotationOf
    ( const HepLorentzVector & vec, CLHEPdouble phi,
                                    CLHEPdouble theta,
                                    CLHEPdouble psi );

  inline friend HepLorentzVector  boostXOf
    ( const HepLorentzVector & vec, CLHEPdouble beta );
  inline friend HepLorentzVector  boostYOf
    ( const HepLorentzVector & vec, CLHEPdouble beta );
  inline friend HepLorentzVector  boostZOf
    ( const HepLorentzVector & vec, CLHEPdouble beta );
  inline friend HepLorentzVector  boostOf
    ( const HepLorentzVector & vec, const Hep3Vector & betaVector );
  inline friend HepLorentzVector  boostOf
    ( const HepLorentzVector & vec, const Hep3Vector & axis,  CLHEPdouble beta );
 
private:

  Hep3Vector pp;
  CLHEPdouble  ee;

  static CLHEPdouble tolerance;
  static CLHEPdouble metric;

};  // HepLorentzVector

// 8 - Axial Unit 4-vectors

static const HepLorentzVector X_HAT4 = HepLorentzVector( 1, 0, 0, 0 );
static const HepLorentzVector Y_HAT4 = HepLorentzVector( 0, 1, 0, 0 );
static const HepLorentzVector Z_HAT4 = HepLorentzVector( 0, 0, 1, 0 );
static const HepLorentzVector T_HAT4 = HepLorentzVector( 0, 0, 0, 1 );

// Global methods

std::ostream & operator << (std::ostream &, const HepLorentzVector &);
// Output to a stream.

std::istream & operator >> (std::istream &, HepLorentzVector &);
// Input from a stream.

typedef HepLorentzVector HepLorentzVectorD;
typedef HepLorentzVector HepLorentzVectorF;

inline HepLorentzVector operator * (const HepLorentzVector &, CLHEPdouble a);
inline HepLorentzVector operator * (CLHEPdouble a, const HepLorentzVector &);
// Scaling LorentzVector with a real number

       HepLorentzVector operator / (const HepLorentzVector &, CLHEPdouble a);
// Dividing LorentzVector by a real number

// Tcomponent definition:

// Signature protection for 4-vector constructors taking 4 components
class Tcomponent {
private:
  CLHEPdouble t_;
public:
  explicit Tcomponent(CLHEPdouble t) : t_(t) {}
  operator CLHEPdouble() const { return t_; }
};  // Tcomponent

}  // namespace CLHEP

#include "CLHEP/Vector/LorentzVector.icc"

#ifdef ENABLE_BACKWARDS_COMPATIBILITY
//  backwards compatibility will be enabled ONLY in CLHEP 1.9
using namespace CLHEP;
#endif

#endif /* HEP_LORENTZVECTOR_H */
