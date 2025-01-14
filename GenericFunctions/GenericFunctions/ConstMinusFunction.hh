#include "CLHEPTypes.hpp"
// -*- C++ -*-
// $Id: ConstMinusFunction.hh,v 1.2 2003/09/06 14:04:13 boudreau Exp $
//--------------------------ConstMinusFunction------------------------------//
//                                                                          //
// ConstMinusFunction, result of subtracting a function from constant       //
// Joe Boudreau, Petar Maksimovic, November 1999                            //
//                                                                          //
//--------------------------------------------------------------------------//

#ifndef ConstMinusFunction_h
#define ConstMinusFunction_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"

namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class ConstMinusFunction : public AbsFunction  {

    FUNCTION_OBJECT_DEF(ConstMinusFunction)
  
      public:
  
    // Constructor
    ConstMinusFunction(CLHEPdouble constant, const AbsFunction *arg);
  
    // Copy constructor
    ConstMinusFunction(const ConstMinusFunction &right);

    // Destructor
    virtual ~ConstMinusFunction();
  
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

    // It is illegal to assign a ConstMinusFunction
    const ConstMinusFunction & operator=(const ConstMinusFunction &right);

    CLHEPdouble             _constant;
    const AbsFunction *_arg;
  };
} // namespace Genfun
#endif
