#include "CLHEPTypes.hpp"
// -*- C++ -*-
// $Id: FunctionNumDeriv.hh,v 1.2 2003/09/06 14:04:13 boudreau Exp $
//--------------------------FunctionNumDeriv--------------------------------//
//                                                                          //
// Class FunctionNumDeriv, providing numerical derivatives                  //
// Joe Boudreau, Mark Fischler, February 2001                               //
//                                                                          //
//--------------------------------------------------------------------------//
#ifndef FunctionNumDeriv_h
#define FunctionNumDeriv_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"

namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class FunctionNumDeriv : public AbsFunction {
  
    FUNCTION_OBJECT_DEF(FunctionNumDeriv)

      public:

    // Constructor
    FunctionNumDeriv(const AbsFunction *arg1, unsigned int index=0);
  
    // Copy constructor.
    FunctionNumDeriv(const FunctionNumDeriv &right);
  
    // Destructor
    virtual ~FunctionNumDeriv();
  
    // Retreive function value
    virtual CLHEPdouble operator ()(CLHEPdouble argument) const override;
    virtual CLHEPdouble operator ()(const Argument & a) const override;
  
    // Dimensionality 
    virtual unsigned int dimensionality() const override;

  private:
  
    // It is illegal to assign a FunctionNumDeriv
    const FunctionNumDeriv & operator=(const FunctionNumDeriv &right);

    // The function we're differntiating.
    const AbsFunction        *_arg1;
    const unsigned int       _wrtIndex;

    // helper data and methods to let us code Argument and CLHEPdouble similarly
    CLHEPdouble numericalDerivative 
	( CLHEPdouble (FunctionNumDeriv::*f)(CLHEPdouble)const, CLHEPdouble x ) const;
    CLHEPdouble f_x   (CLHEPdouble x) const;
    CLHEPdouble f_Arg (CLHEPdouble x) const;
    mutable Argument 	    _xArg;

  };
} // namespace Genfun
#endif
