#include "CLHEPTypes.hpp"
// -*- C++ -*-
// $Id: Bessel.hh,v 1.2 2003/09/06 14:04:13 boudreau Exp $
//---------------------Bessel-------------------------------------------------//
//                                                                            //
// Class Bessel, providing Bessel Functions  The Namespace "FractionalORder"  //
// and "Integral order" are nested here, so that you fully specify the class  //
// like this:                                                                 //
//                                                                            //
//                 Genfun::FractionalOrder::Bessel                            //
//                                                                            //
//                              or                                            //
//                                                                            //
//                 Genfun::IntegralOrder::Bessel                              //
//                                                                            //
//                                                                            //
// Joe Boudreau, April 2001                                                   //
//                                                                            //
//--------------------------------------------------------------------------  //
#ifndef Bessel_h
#define Bessel_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"
#include "CLHEP/GenericFunctions/Parameter.hh"
namespace Genfun {

namespace FractionalOrder { 
  /**
   * @author
   * @ingroup genfun
   */
  class Bessel : public AbsFunction  {

    FUNCTION_OBJECT_DEF(Bessel)

      public:

    // Enumerated type:
    enum Type {J, Y};

    // Constructor:  Use this one and you will get a Bessel function of
    // integer order
    Bessel (Type type);

    // Copy constructor
    Bessel(const Bessel &right);
  
    // Destructor
    virtual ~Bessel();
  
    // Retreive function value
    virtual CLHEPdouble operator ()(CLHEPdouble argument) const override;
    virtual CLHEPdouble operator ()(const Argument & a) const override {return operator() (a[0]);}
  
    // Get the order of the Bessel Function.  Default value, 0.0.  If modified the
    // Bessel function 
    Parameter & order(); 
    const Parameter & order() const; 

  private:

    // It is illegal to assign an adjustable constant
    const Bessel & operator=(const Bessel &right);

    // The type and order of the Bessel function
    Type      _type;
    Parameter _order; // the fractional order:
  
  };
} // namespace FractionalOrder

namespace IntegralOrder { 
  /**
   * @author
   * @ingroup genfun
   */
  class Bessel : public AbsFunction  {

    FUNCTION_OBJECT_DEF(Bessel)

      public:

    // Enumerated type:
    enum Type {J, Y};

    // Constructor:  Use this one and you will get a Bessel function of
    // integer order
    Bessel (Type type, unsigned int order);

    // Copy constructor
    Bessel(const Bessel &right);
  
    // Destructor
    virtual ~Bessel();
  
    // Retreive function value
    virtual CLHEPdouble operator ()(CLHEPdouble argument) const override;
    virtual CLHEPdouble operator ()(const Argument & a) const override {return operator() (a[0]);}
  
  private:

    // It is illegal to assign an adjustable constant
    const Bessel & operator=(const Bessel &right);

    // The type and order of the Bessel function
    Type                _type;
    unsigned  int       _order; 

    CLHEPdouble              _bessel_IJ_taylor(CLHEPdouble nu, 
					  CLHEPdouble x,
					  int sign,
					  int kmax,
					  CLHEPdouble threshhold) const;
  
  };
} // namespace IntegralOrder

} // namespace Genfun


#include "CLHEP/GenericFunctions/Bessel.icc"
#endif
