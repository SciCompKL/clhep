#include "CLHEPTypes.hpp"
// -*- C++ -*-
// $Id: PeriodicRectangular.hh,v 1.2 2003/09/06 14:04:13 boudreau Exp $
//---------------------Rectangular------------------------------------------//
//                                                                          //
// Class Exponential                                                        //
// Joe Boudreau, Petar Maksimovic, November 1999                            //
//                                                                          //
//--------------------------------------------------------------------------//
#ifndef PeriodicRectangular_h_
#define PeriodicRectangular_h_ 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"
#include "CLHEP/GenericFunctions/Parameter.hh"
namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class PeriodicRectangular : public AbsFunction  {

    FUNCTION_OBJECT_DEF(PeriodicRectangular)


    public:

    // Constructor
    PeriodicRectangular();

    // Copy constructor
    PeriodicRectangular(const PeriodicRectangular &right);
  
    // Destructor
    virtual ~PeriodicRectangular();
  
    // Retreive function value
    virtual CLHEPdouble operator ()(CLHEPdouble argument) const override;
    virtual CLHEPdouble operator ()(const Argument & arg) const override {return operator() (arg[0]);}
  
    // Get the position of the first discontinuity
    Parameter & a(); 

    // Get the position of the second discontinuity
    Parameter & b(); 

    // Get the value of the function at its top
    Parameter & height(); 
  
    // Derivative.  
    Derivative partial (unsigned int) const override;

    // Does this function have an analytic derivative?
    virtual bool hasAnalyticDerivative() const override {return true;}

  private:

    // It is illegal to assign an adjustable constant
    const PeriodicRectangular & operator=(const PeriodicRectangular &right);

    // Here is the decay constant
    Parameter _a;
    Parameter _b;
    Parameter _height;

  };
} // namespace Genfun
#endif
