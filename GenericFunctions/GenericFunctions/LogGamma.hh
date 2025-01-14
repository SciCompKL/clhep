#include "CLHEPTypes.hpp"
// -*- C++ -*-
// $Id: LogGamma.hh,v 1.3 2010/06/16 18:22:01 garren Exp $
//---------------------Logarithm of Gamma Function--------------------------//
//                                                                          //
// Class LogGamma                                                           //
// Joe Boudreau October 2K                                                  //
//                                                                          //
//--------------------------------------------------------------------------//
#ifndef LogGamma_h
#define LogGamma_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"
#include "CLHEP/GenericFunctions/Parameter.hh"
namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class LogGamma : public AbsFunction  {
    
    FUNCTION_OBJECT_DEF(LogGamma)
      
      public:
    
    // Constructor
    LogGamma();
    
    // Copy constructor
    LogGamma(const LogGamma &right);
    
    // Destructor
    virtual ~LogGamma();
    
    // Retreive function value
    virtual CLHEPdouble operator ()(CLHEPdouble argument) const override;
    virtual CLHEPdouble operator ()(const Argument & a) const override {return operator() (a[0]);}
    
  private:
    
    // It is illegal to assign an adjustable constant
    const LogGamma & operator=(const LogGamma &right);

    // Constants used in evaluating the function call:
    static const CLHEPdouble _coefficient[6];
    
  };
} // namespace Genfun
#endif
