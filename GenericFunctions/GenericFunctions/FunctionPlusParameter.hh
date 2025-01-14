#include "CLHEPTypes.hpp"
// -*- C++ -*-
// $Id: FunctionPlusParameter.hh,v 1.2 2003/09/06 14:04:13 boudreau Exp $
//--------------------------FunctionPlusParameter---------------------------//
//                                                                          //
// ConstOverFunction, result of adding a function and a parameter           //
// Joe Boudreau, Petar Maksimovic, November 1999                            //
//                                                                          //
//--------------------------------------------------------------------------//

#ifndef FunctionPlusParameter_h
#define FunctionPlusParameter_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"

namespace Genfun {
  
  /**
   * @author
   * @ingroup genfun
   */
  class FunctionPlusParameter : public AbsFunction  {
    
    FUNCTION_OBJECT_DEF(FunctionPlusParameter)
      
      public:
    
    // Constructor
    FunctionPlusParameter(const AbsParameter *parameter, const AbsFunction *function);
  
    // Copy constructor
    FunctionPlusParameter(const FunctionPlusParameter &right);

    // Destructor
    virtual ~FunctionPlusParameter();
  
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

    // It is illegal to assign a FunctionPlusParameter
    const FunctionPlusParameter & operator=(const FunctionPlusParameter &right);

    const AbsFunction  *_function;
    AbsParameter       *_parameter;

  };
} // namespace Genfun
#endif
