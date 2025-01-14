#include "CLHEPTypes.hpp"
// -*- C++ -*-
// $Id: Exp.hh,v 1.2 2003/09/06 14:04:13 boudreau Exp $
//---------------------Exp--------------------------------------------------//
//                                                                          //
// Class Exp                                                                //
// Joe Boudreau, Petar Maksimovic, November 1999                            //
//                                                                          //
//--------------------------------------------------------------------------//
#ifndef Exp_h
#define Exp_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"
#include "CLHEP/GenericFunctions/Parameter.hh"

namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class Exp : public AbsFunction  {

    FUNCTION_OBJECT_DEF(Exp)

      public:

    // Constructor
    Exp();

    // Copy constructor
    Exp(const Exp &right);
  
    // Destructor
    virtual ~Exp();
  
    // Retreive function value
    virtual CLHEPdouble operator ()(CLHEPdouble argument) const override;
    virtual CLHEPdouble operator ()(const Argument & a) const override {return operator() (a[0]);}
  
    // Derivative.  
    Derivative partial (unsigned int) const override;

    // Does this function have an analytic derivative?
    virtual bool hasAnalyticDerivative() const override {return true;}

  private:

    // It is illegal to assign an adjustable constant
    const Exp & operator=(const Exp &right);

  };
} // namespace Genfun
#endif
