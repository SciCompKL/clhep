#include "CLHEPTypes.hpp"
// -*- C++ -*-
// $Id: IncompleteGamma.hh,v 1.2 2003/09/06 14:04:13 boudreau Exp $
//---------------------IncompleteGamma--------------------------------------//
//                                                                          //
// Class IncompleteGamma, the incomplete Gamma function                     //
// Joe Boudreau, October 2000                                               //
//                                                                          //
//--------------------------------------------------------------------------//
#ifndef IncompleteGamma_h
#define IncompleteGamma_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"
#include "CLHEP/GenericFunctions/Parameter.hh"
#include "CLHEP/GenericFunctions/LogGamma.hh"
namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class IncompleteGamma : public AbsFunction  {
    
    FUNCTION_OBJECT_DEF(IncompleteGamma)
      
      public:
    
    // Constructor
    IncompleteGamma();
    
    // Copy constructor
    IncompleteGamma(const IncompleteGamma &right);
    
    // Destructor
    virtual ~IncompleteGamma();
    
    // Retreive function value
    virtual CLHEPdouble operator ()(CLHEPdouble argument) const override;
    virtual CLHEPdouble operator ()(const Argument & arg) const override {return operator() (arg[0]);}
    
    // Get the paramter a
    Parameter & a(); 
    
  private:
    
    // It is illegal to assign an adjustable constant
    const IncompleteGamma & operator=(const IncompleteGamma &right);
    
    // Here is the parameter of the Incomplete Gamma Function
    Parameter _a;

    // Compute via series representation:
    CLHEPdouble  _gamser(CLHEPdouble a, CLHEPdouble x, CLHEPdouble logGamma) const;
    
    // Compute via continued fraction representation:
    CLHEPdouble  _gammcf(CLHEPdouble a, CLHEPdouble x, CLHEPdouble logGamma) const;

    // This function has a LogGamma Function;
    LogGamma _logGamma;

    static const int          ITMAX;
    static const CLHEPdouble       EPS;
    static const CLHEPdouble       FPMIN;
    
  };
} // namespace Genfun
#endif
