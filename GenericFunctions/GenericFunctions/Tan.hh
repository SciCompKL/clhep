#include "CLHEPTypes.hpp"
// -*- C++ -*-
// $Id: Tan.hh,v 1.2 2003/09/06 14:04:13 boudreau Exp $
//---------------------Tan--------------------------------------------------//
//                                                                          //
// Class Tan                                                                //
// Joe Boudreau, Petar Maksimovic, November 1999                            //
//                                                                          //
//--------------------------------------------------------------------------//
#ifndef Tan_h
#define Tan_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"
namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class Tan : public AbsFunction  {

    FUNCTION_OBJECT_DEF(Tan)

      public:

    // Constructor
    Tan();

    // Destructor
    virtual ~Tan();
  
    // Copy constructor
    Tan(const Tan &right);
  
    // Retreive function value
    virtual CLHEPdouble operator ()(CLHEPdouble argument) const override;
    virtual CLHEPdouble operator ()(const Argument & a) const override {return operator() (a[0]);}

    // Derivative.  
    Derivative partial (unsigned int) const override;

    // Does this function have an analytic derivative?
    virtual bool hasAnalyticDerivative() const override {return true;}
  
  
  private:

    // It is illegal to assign a Tan
    const Tan & operator=(const Tan &right);

  };
} // namespace Genfun

#endif
