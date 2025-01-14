#include "CLHEPTypes.hpp"
// -*- C++ -*-
// $Id: FixedConstant.hh,v 1.2 2003/09/06 14:04:13 boudreau Exp $
//----------------------FixedConstant --------------------------------------//
//                                                                          //
//  Class FixedConstant                                                     //
//  Joe Boudreau, Petar Maksimovic, Nov. 1999                               //
//                                                                          //
//  FixedConstant allows use to treat "promote" fixed contants to constant  //
//  functions so that they automatically will inherit all the algebraic     //
//  operations we have so painstakingly defined for functions.              //
//                                                                          //
//--------------------------------------------------------------------------//
#ifndef FixedConstant_h
#define FixedConstant_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"

namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class FixedConstant : public AbsFunction  {
  
    FUNCTION_OBJECT_DEF(FixedConstant)

      public:

    // Constructor
    FixedConstant(CLHEPdouble value);
  
    // Copy constructor
    FixedConstant(const FixedConstant &right);
  
    // Destructor
    virtual ~FixedConstant();
  
    // Retrieve function value
    virtual CLHEPdouble operator ()(CLHEPdouble argument) const override;
    virtual CLHEPdouble operator ()(const Argument & a) const override {return operator() (a[0]);}
  
    // Derivative.  
    Derivative partial (unsigned int) const override;

    // Does this function have an analytic derivative?
    virtual bool hasAnalyticDerivative() const override {return true;}
  
  private:

    // It is illegal to assign a fixed constant
    const FixedConstant & operator=(const FixedConstant &right);

    // The value of the constant:
    CLHEPdouble _value;
  };
} // namespace Genfun
#endif
