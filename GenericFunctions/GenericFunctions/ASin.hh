#include "CLHEPTypes.hpp"
// -*- C++ -*-
// $Id: ASin.hh,v 1.2 2003/09/06 14:04:13 boudreau Exp $
//---------------------ASin-------------------------------------------------//
//                                                                          //
// Class ASin                                                               //
// Joe Boudreau, Petar Maksimovic, November 1999                            //
//                                                                          //
//--------------------------------------------------------------------------//
#ifndef ASin_h
#define ASin_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"
namespace Genfun {
  class ASin : public AbsFunction  {

    FUNCTION_OBJECT_DEF(ASin)

      public:

    // Constructor
    ASin();

    // Destructor
    virtual ~ASin();
  
    // Copy constructor
    ASin(const ASin &right);
  
    // Retreive function value
    virtual CLHEPdouble operator ()(CLHEPdouble argument) const override;
    virtual CLHEPdouble operator ()(const Argument & a) const override {return operator() (a[0]);}

    // Derivative.  
    Derivative partial (unsigned int) const override;

    // Does this function have an analytic derivative?
    virtual bool hasAnalyticDerivative() const override {return true;}
  
  
  private:

    // It is illegal to assign a ASin
    const ASin & operator=(const ASin &right);

  };
} // end namespace Genfun

#endif
