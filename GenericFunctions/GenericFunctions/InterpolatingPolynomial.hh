#include "CLHEPTypes.hpp"
// -*- C++ -*-
// $Id: 
// ------------------------------------------------------------------------------//
// Lagrange's Interpolating Polynomial                                           //
//                                                                               //
//                                                                               //
// Joe Boudreau.                                                                 //
//                                                                               //
// ------------------------------------------------------------------------------//
#ifndef _InterpolatingPolynomial_h_
#define _InterpolatingPolynomial_h_ 
#include "CLHEP/GenericFunctions/AbsFunction.hh"
#include "CLHEP/GenericFunctions/Parameter.hh"
#include <vector>
namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class InterpolatingPolynomial: public AbsFunction {

    FUNCTION_OBJECT_DEF(InterpolatingPolynomial)

      public:

    // Constructor
    InterpolatingPolynomial();

    // Copy constructor
    InterpolatingPolynomial(const InterpolatingPolynomial &right);
  
    // Destructor:
    virtual ~InterpolatingPolynomial();

    // Retreive function value
    virtual CLHEPdouble operator ()(CLHEPdouble argument) const override;
    virtual CLHEPdouble operator ()(const Argument & a) const override {return operator() (a[0]);}
  
    // Puncture this thing:
    void addPoint(CLHEPdouble x, CLHEPdouble y);

    // Get the range:
    void getRange(CLHEPdouble & min, CLHEPdouble & max) const;

  private:
  
    // It is illegal to assign an adjustable constant
    const InterpolatingPolynomial & operator=(const InterpolatingPolynomial &right);

    std::vector<std::pair<CLHEPdouble,CLHEPdouble> > xPoints;
  };
} // namespace Genfun
#endif
