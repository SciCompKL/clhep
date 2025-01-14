#include "CLHEPTypes.hpp"
// -*- C++ -*-
// $Id: ConstTimesFunction.hh,v 1.2 2003/09/06 14:04:13 boudreau Exp $
//--------------------------ConstOverFunction-------------------------------//
//                                                                          //
// ConstOverFunction, result of multiplying a constant and a function       //
// Joe Boudreau, Petar Maksimovic, November 1999                            //
//                                                                          //
//--------------------------------------------------------------------------//

#ifndef ConstTimesFunction_h
#define ConstTimesFunction_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"
namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class ConstTimesFunction : public AbsFunction  {

    FUNCTION_OBJECT_DEF(ConstTimesFunction)
  
      public:
  
    // Constructor
    ConstTimesFunction(CLHEPdouble constant, const AbsFunction *arg);
  
    // Copy constructor
    ConstTimesFunction(const ConstTimesFunction &right);

    // Destructor
    virtual ~ConstTimesFunction();
  
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

    // It is illegal to assign a ConstTimesFunction
    const ConstTimesFunction & operator=(const ConstTimesFunction &right);

    CLHEPdouble             _constant;
    const AbsFunction *_arg;
  };
} // namespace Genfun
#endif
