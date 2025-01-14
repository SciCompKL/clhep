#include "CLHEPTypes.hpp"
// -*- C++ -*-
// $Id: ConstOverFunction.hh,v 1.2 2003/09/06 14:04:13 boudreau Exp $
//--------------------------ConstOverFunction-------------------------------//
//                                                                          //
// ConstOverFunction, result of dividing a constant by a function           //
// Joe Boudreau, Petar Maksimovic, November 1999                            //
//                                                                          //
//--------------------------------------------------------------------------//

#ifndef ConstOverFunction_h
#define ConstOverFunction_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"

namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class ConstOverFunction : public AbsFunction  {

    FUNCTION_OBJECT_DEF(ConstOverFunction)
  
      public:
  
    // Constructor
    ConstOverFunction(CLHEPdouble constant, const AbsFunction *arg);
  
    // Copy constructor
    ConstOverFunction(const ConstOverFunction &right);

    // Destructor
    virtual ~ConstOverFunction();
  
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

    // It is illegal to assign a ConstOverFunction
    const ConstOverFunction & operator=(const ConstOverFunction &right);

    CLHEPdouble             _constant;
    const AbsFunction *_arg;
  };
} // namespace Genfun

#endif


