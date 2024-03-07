#include "CLHEPTypes.hpp"
// -*- C++ -*-
// $Id: Sin.hh,v 1.2 2003/09/06 14:04:13 boudreau Exp $
//---------------------Sin--------------------------------------------------//
//                                                                          //
// Class Sin                                                                //
// Joe Boudreau, Petar Maksimovic, November 1999                            //
//                                                                          //
//--------------------------------------------------------------------------//
#ifndef Sin_h
#define Sin_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"
namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class Sin : public AbsFunction  {

    FUNCTION_OBJECT_DEF(Sin)

      public:

    // Constructor
    Sin();

    // Destructor
    virtual ~Sin();
  
    // Copy constructor
    Sin(const Sin &right);
  
    // Retreive function value
    virtual CLHEPdouble operator ()(CLHEPdouble argument) const override;
    virtual CLHEPdouble operator ()(const Argument & a) const override {return operator() (a[0]);}

    // Derivative.  
    Derivative partial (unsigned int) const override;

    // Does this function have an analytic derivative?
    virtual bool hasAnalyticDerivative() const override {return true;}
  
  
  private:

    // It is illegal to assign a Sin
    const Sin & operator=(const Sin &right);

  };
} // namespace Genfun

#endif
