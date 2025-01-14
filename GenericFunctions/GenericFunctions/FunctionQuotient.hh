#include "CLHEPTypes.hpp"
// -*- C++ -*-
// $Id: FunctionQuotient.hh,v 1.2 2003/09/06 14:04:13 boudreau Exp $
//--------------------------FunctionQuotient--------------------------------//
//                                                                          //
// FunctionProduct, result of multiplication of two functions.              //
// Joe Boudreau, Petar Maksimovic, November 1999                            //
//                                                                          //
//--------------------------------------------------------------------------//
#ifndef FunctionQuotient_h
#define FunctionQuotient_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"

namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class FunctionQuotient : public AbsFunction {

    FUNCTION_OBJECT_DEF(FunctionQuotient)

      public:

    // Constructor
    FunctionQuotient(const AbsFunction *arg1, const AbsFunction *arg2);

    // Copy constructor
    FunctionQuotient(const FunctionQuotient &right);
  
    // Destructor
    virtual ~FunctionQuotient();
  
    // Retreive function value
    virtual CLHEPdouble operator ()(CLHEPdouble argument) const override;
    virtual CLHEPdouble operator ()(const Argument & a) const override;
  
    // Dimensionality 
    virtual unsigned int dimensionality() const override;

    // Derivative.  
    Derivative partial (unsigned int) const override;

    // Does this function have an analytic derivative?
    virtual bool hasAnalyticDerivative() const override {return true;}

  private:
  
    // It is illegal to assign a FunctionQuotient
    const FunctionQuotient & operator=(const FunctionQuotient &right);
  
    const AbsFunction *_arg1;
    const AbsFunction *_arg2;
  };
} // namespace Genfun
#endif
