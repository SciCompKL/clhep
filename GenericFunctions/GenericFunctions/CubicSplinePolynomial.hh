#include "CLHEPTypes.hpp"
// -*- C++ -*-
// $Id: 
// ------------------------------------------------------------------------------//
// Natural cubic spline function, used for interpolation                         //
//                                                                               //
//                                                                               //
// Joe Boudreau.                                                                 //
//                                                                               //
// ------------------------------------------------------------------------------//
#ifndef _CubicSplinePolynomial_h_
#define _CubicSplinePolynomial_h_ 
#include "CLHEP/GenericFunctions/AbsFunction.hh"
#include "CLHEP/GenericFunctions/Parameter.hh"
#include <vector>
namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class CubicSplinePolynomial: public AbsFunction {

    FUNCTION_OBJECT_DEF(CubicSplinePolynomial)

      public:

    // Constructor
    CubicSplinePolynomial();

    // Copy constructor
    CubicSplinePolynomial(const CubicSplinePolynomial &right);
  
    // Destructor:
    virtual ~CubicSplinePolynomial();

    // Retreive function value
    virtual CLHEPdouble operator ()(CLHEPdouble argument) const override;
    virtual CLHEPdouble operator ()(const Argument & a) const override {return operator() (a[0]);}
  
    // Puncture this thing:
    void addPoint(CLHEPdouble x, CLHEPdouble y);

    // Get the range:
    void getRange(CLHEPdouble & min, CLHEPdouble & max) const;

  private:
  
    // It is illegal to assign an adjustable constant
    const CubicSplinePolynomial & operator=(const CubicSplinePolynomial &right);

    class Clockwork;
    Clockwork *c;

  };
} // namespace Genfun
#include "CLHEP/GenericFunctions/CubicSplinePolynomial.icc"
#endif
