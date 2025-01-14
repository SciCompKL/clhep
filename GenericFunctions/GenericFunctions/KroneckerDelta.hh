#include "CLHEPTypes.hpp"
// -*- C++ -*-
// $Id: KroneckerDelta.hh,v 1.1 2007/01/21 20:54:33 boudreau Exp $
//---------------------Rectangular------------------------------------------//
//                                                                          //
// Class KroneckerDelta by Joe Boudreau                                     //
//                                                                          //
//--------------------------------------------------------------------------//
#ifndef KroneckerDelta_h
#define KroneckerDelta_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"
#include "CLHEP/GenericFunctions/Parameter.hh"
namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class KroneckerDelta : public AbsFunction  {

    FUNCTION_OBJECT_DEF(KroneckerDelta)

      public:

    // Constructor
    KroneckerDelta();

    // Copy constructor
    KroneckerDelta(const KroneckerDelta &right);
  
    // Destructor
    virtual ~KroneckerDelta();
  
    // Retreive function value
    virtual CLHEPdouble operator ()(CLHEPdouble argument) const override;
    virtual CLHEPdouble operator ()(const Argument & a) const override {return operator() (a[0]);}
  
    // Derivative.  
    Derivative partial (unsigned int) const override;

    // Does this function have an analytic derivative?
    virtual bool hasAnalyticDerivative() const override {return true;}

  private:

    // It is illegal to assign an adjustable constant
    const KroneckerDelta & operator=(const KroneckerDelta &right);

 
  };
} // namespace Genfun
#endif
