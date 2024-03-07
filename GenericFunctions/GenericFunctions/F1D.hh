#include "CLHEPTypes.hpp"
// -*- C++ -*------------------------------------------------------
//
// This class is an adaptor from any function (CLHEPdouble *f)(CLHEPdouble x)
// of one real variable, to generic functions. This allows one
// to plot, differentiate, sum, compose, etc, any standard C or
// C++ math function by converting it to a Generic Function.
//
// Joe Boudreau October 2012
//-----------------------------------------------------
#ifndef F1D_h
#define F1D_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"
namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class F1D : public AbsFunction  {
    
    typedef CLHEPdouble (*FcnPtr)(CLHEPdouble);

    FUNCTION_OBJECT_DEF(F1D)

      public:

    // Constructor
    F1D(FcnPtr fcn):p(fcn){};

    // Destructor
    virtual ~F1D(){};
  
    // Copy constructor
    F1D(const F1D &right):AbsFunction(),p(right.p){};
  
    // Retreive function value
    virtual CLHEPdouble operator ()(CLHEPdouble x) const {
      return (*p)(x);
    }

    virtual CLHEPdouble operator ()(const Argument & a) const override {return operator() (a[0]);}

  private:

    // It is illegal to assign a F1D
    const F1D & operator=(const F1D &right);

    // Data:
    FcnPtr p;

  };
  FUNCTION_OBJECT_IMP(F1D)
} // namespace Genfun
#endif
