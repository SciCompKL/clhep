#include "CLHEPTypes.hpp"
// -*- C++ -*-
// $Id:
//---------------------Gaussian---------------------------------------------//
//                                                                          //
// Class LogisticFunction                                                   //
// Joe Boudreau, November 2002                                              //
//                                                                          //
//--------------------------------------------------------------------------//
#ifndef LogisticFunction_h
#define LogisticFunction_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"
#include "CLHEP/GenericFunctions/Parameter.hh"
#include <vector>
namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class LogisticFunction : public AbsFunction  {

    FUNCTION_OBJECT_DEF(LogisticFunction)

      public:

    // Constructor
    LogisticFunction();

    // Copy constructor
    LogisticFunction(const LogisticFunction &right);
  
    // Destructor
    virtual ~LogisticFunction();
  
    // Retreive function value
    virtual CLHEPdouble operator ()(CLHEPdouble argument) const override;
    virtual CLHEPdouble operator ()(const Argument & arg) const override {return operator() (arg[0]); }
  
    // Get the starting value of the LogisticFunction
    Parameter & x0(); 
    const Parameter & x0() const; 

    // Get the control parameter of the LogisticFunction
    Parameter & a();
    const Parameter & a() const;

  private:

    // It is illegal to assign an adjustable constant
    const LogisticFunction & operator=(const LogisticFunction &right);

    // Here is the decay constant
    Parameter _x0;

    // Here is the sigma
    Parameter _a;

    // A vector of values.
    mutable std::vector<CLHEPdouble> fx;
    // Some cache:
    mutable CLHEPdouble __a, __x0;

  };
} // namespace Genfun

#endif
