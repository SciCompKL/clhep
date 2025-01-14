#include "CLHEPTypes.hpp"
// -*- C++ -*-
// $Id: FunctionComposition.hh,v 1.2 2003/09/06 14:04:13 boudreau Exp $
//--------------------------FunctionComposition-----------------------------//
//                                                                          //
// FunctionComposition, result of composition of two functions.             //
// Joe Boudreau, Petar Maksimovic, November 1999                            //
//                                                                          //
//--------------------------------------------------------------------------//

#ifndef FunctionComposition_h
#define FunctionComposition_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"

namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class FunctionComposition : public AbsFunction {

    FUNCTION_OBJECT_DEF(FunctionComposition)

      public:

    // Constructor
    FunctionComposition(const AbsFunction *arg1, const AbsFunction *arg2);

    // Copy constructor
    FunctionComposition(const FunctionComposition &right);
  
    // Destructor
    virtual ~FunctionComposition();

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

    // It is illegal to assign a FunctionComposition
    const FunctionComposition & operator=(const FunctionComposition &right);

    const AbsFunction *_arg1;
    const AbsFunction *_arg2;  
  };
} // namespace Genfun
#endif
