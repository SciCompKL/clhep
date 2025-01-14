#include "CLHEPTypes.hpp"
// -*- C++ -*-
// $Id: FunctionTimesParameter.hh,v 1.2 2003/09/06 14:04:13 boudreau Exp $
//--------------------------FunctionTimesParameter--------------------------//
//                                                                          //
// ConstOverFunction, result of multiplying a function and a parameter      //
// Joe Boudreau, Petar Maksimovic, November 1999                            //
//                                                                          //
//--------------------------------------------------------------------------//

#ifndef FunctionTimesParameter_h
#define FunctionTimesParameter_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"

namespace Genfun {
  class Argument;

  /**
   * @author
   * @ingroup genfun
   */
  class FunctionTimesParameter : public AbsFunction  {

    FUNCTION_OBJECT_DEF(FunctionTimesParameter)
  
      public:
  
    // Constructor
    FunctionTimesParameter(const AbsParameter *parameter, const AbsFunction *function);
  
    // Copy constructor
    FunctionTimesParameter(const FunctionTimesParameter &right);

    // Destructor
    virtual ~FunctionTimesParameter();
  
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

    // It is illegal to assign a FunctionTimesParameter
    const FunctionTimesParameter & operator=(const FunctionTimesParameter &right);

    const AbsFunction  *_function;
    AbsParameter       *_parameter;

  };
} // namespace Genfun
#endif
