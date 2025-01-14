#include "CLHEPTypes.hpp"
// -*- C++ -*-
// $Id: Rectangular.hh,v 1.2 2003/09/06 14:04:13 boudreau Exp $
//---------------------Rectangular------------------------------------------//
//                                                                          //
// Class Exponential                                                        //
// Joe Boudreau, Petar Maksimovic, November 1999                            //
//                                                                          //
//--------------------------------------------------------------------------//
#ifndef Rectangular_h
#define Rectangular_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"
#include "CLHEP/GenericFunctions/Parameter.hh"
namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class Rectangular : public AbsFunction  {

    FUNCTION_OBJECT_DEF(Rectangular)

      public:

    // Constructor
    Rectangular();

    // Copy constructor
    Rectangular(const Rectangular &right);
  
    // Destructor
    virtual ~Rectangular();
  
    // Retreive function value
    virtual CLHEPdouble operator ()(CLHEPdouble argument) const override;
    virtual CLHEPdouble operator ()(const Argument & a) const override {return operator() (a[0]);}
  
    // Get the position of the first discontinuity
    const Parameter & x0() const; 
    Parameter & x0(); 

    // Get the position of the second discontinuity
    const Parameter & x1() const; 
    Parameter & x1(); 

    // Get the value of the function at its baseline
    const Parameter & baseline() const; 
    Parameter & baseline(); 

    // Get the value of the function at its top
    const Parameter & height() const; 
    Parameter & height(); 
  
    // Derivative.  
    Derivative partial (unsigned int) const override;

    // Does this function have an analytic derivative?
    virtual bool hasAnalyticDerivative() const override {return true;}

  private:

    // It is illegal to assign an adjustable constant
    const Rectangular & operator=(const Rectangular &right);

    // Here is the decay constant
    Parameter _x0;
    Parameter _x1;
    Parameter _baseline;
    Parameter _height;

  };
} // namespace Genfun
#endif
