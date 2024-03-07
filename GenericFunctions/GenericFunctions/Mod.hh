#include "CLHEPTypes.hpp"
// -*- C++ -*-
// $Id: 
//----------------------Mod-----------------------------------------------//
//                                                                        //
//  Class Mod   (Modulo)                                                  //
//  Joe Boudreau, Petar Maksimovic, Nov. 2002                             //
//                                                                        //
//  Mod(x) returns x%y                                                    //
//------------------------------------------------------------------------//
#ifndef Mod_h
#define Mod_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"
namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class Mod : public AbsFunction  {

    FUNCTION_OBJECT_DEF(Mod)
  
      public:

    // Constructor
    Mod(CLHEPdouble y);
  
    // Copy constructor
    Mod(const Mod &right);
  
    // Destructor
    virtual ~Mod();
  
    // Retrieve function value

    virtual CLHEPdouble operator ()(CLHEPdouble argument) const override; 
    virtual CLHEPdouble operator ()(const Argument & a) const override {return operator() (a[0]);}
  
  private:

    // It is illegal to assign a fixed constant
    const Mod & operator=(const Mod &right);

    CLHEPdouble _y; // mod (as a CLHEPdouble)

  };
} // namespace Genfun
#endif
