#include "CLHEPTypes.hpp"
// -*- C++ -*-
// $Id: FunctionProduct.hh,v 1.2 2003/09/06 14:04:13 boudreau Exp $
//--------------------------FunctionProduct---------------------------------//
//                                                                          //
// FunctionProduct, result of multiplication of two functions.              //
// Joe Boudreau, Petar Maksimovic, November 1999                            //
//                                                                          //
//--------------------------------------------------------------------------//

#ifndef FunctionProduct_h
#define FunctionProduct_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"
namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class FunctionProduct : public AbsFunction {

    FUNCTION_OBJECT_DEF(FunctionProduct)

      public:

    // Constructor
    FunctionProduct(const AbsFunction *arg1, const AbsFunction *arg2);

    // Copy constructor
    FunctionProduct(const FunctionProduct &right);
  
    // Destructor
    virtual ~FunctionProduct();

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

    // It is illegal to assign a FunctionProduct
    const FunctionProduct & operator=(const FunctionProduct &right);

    const AbsFunction *_arg1;
    const AbsFunction *_arg2;  
  };
} // namespace Genfun

#endif
