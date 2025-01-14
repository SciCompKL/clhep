#include "CLHEPTypes.hpp"
// -*- C++ -*-
// $Id: 
//---------------------SphericalHarmonicExpansion------------------------------------------//
//                                                                          //
// Class SphericalHarmonicExpansion.  This is a fitting function consisting of a super     //
// position of N legendre polynomials.  Cascading fractions and phases are  //
// the input parameters. Function is normalized to one (on [-1,1])          //
// Joe Boudreau, Petar Maksimovic, January 2000                             //
//                                                                          //
//--------------------------------------------------------------------------//
#ifndef SphericalHarmonicExpansion_h
#define SphericalHarmonicExpansion_h
#include "CLHEP/GenericFunctions/AbsFunction.hh"
#include "CLHEP/GenericFunctions/Parameter.hh"
#include "CLHEP/GenericFunctions/SphericalHarmonicCoefficientSet.hh"
namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class SphericalHarmonicExpansion : public AbsFunction  {

    FUNCTION_OBJECT_DEF(SphericalHarmonicExpansion)

      public:

    enum Type {REAL,IMAG,MAG, MAGSQ};

     // Constructor.  Builds all the 
    SphericalHarmonicExpansion(Type type, const SphericalHarmonicCoefficientSet & coefficients);

    // Copy constructor
    SphericalHarmonicExpansion(const SphericalHarmonicExpansion &right);
  
    // Destructor
    virtual ~SphericalHarmonicExpansion();
  
    // Dimensionality=2.  They are; cosTheta (not theta) and phi
    virtual unsigned int dimensionality() const override {return 2;}

    // Retreive function value
    virtual CLHEPdouble operator ()(CLHEPdouble argument) const override;    // Gives an error.
    virtual CLHEPdouble operator ()(const Argument & a) const override; // Must use this one

    // Get the expansion coefficients:
    SphericalHarmonicCoefficientSet & coefficientSet();
    const SphericalHarmonicCoefficientSet & coefficientSet() const;
    
  private:

    // It is illegal to assign an adjustable constant
    const SphericalHarmonicExpansion & operator=(const SphericalHarmonicExpansion &right);
    
    
    class Clockwork;
    Clockwork *c;

  };
} // namespace Genfun



#include "CLHEP/GenericFunctions/SphericalHarmonicExpansion.icc"
#endif
