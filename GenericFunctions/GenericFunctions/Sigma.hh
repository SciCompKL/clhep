#include "CLHEPTypes.hpp"
// -*- C++ -*-
// $Id: 
//--------------------------Sigma-------------------------------------------//
//                                                                          //
// Sigma, result of addition of N functions                                 //
//                                                                          //
//--------------------------------------------------------------------------//

#ifndef Sigma_h
#define Sigma_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"

namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class Sigma : public AbsFunction  {

    FUNCTION_OBJECT_DEF(Sigma)
  
      public:
  
    // Constructor
    Sigma();
  
    // Copy constructor
    Sigma(const Sigma &right);

    // Destructor
    virtual ~Sigma();
  
    // Retreive function value
    virtual CLHEPdouble operator ()(CLHEPdouble argument) const override;
    virtual CLHEPdouble operator ()(const Argument & a) const override;

    // Dimensionality 
    virtual unsigned int dimensionality() const override;

    // Derivative.  
    Derivative partial (unsigned int) const override;

    // Does this function have an analytic derivative?
    virtual bool hasAnalyticDerivative() const override {return true;}

    // Add a function to the sum:
    void accumulate (const AbsFunction & fcn);

  private:

    // It is illegal to assign a Sigma
    const Sigma & operator=(const Sigma &right);

    std::vector<const AbsFunction *> _fcn;

  };
} // namespace Genfun
#endif
