#include "CLHEPTypes.hpp"
// -*- C++ -*-
// $Id: SphericalNeumann.hh,v 1.2 2003/09/06 14:04:13 boudreau Exp $
//---------------------SphericalNeumann-------------------------------------//
//                                                                          //
// Class SphericalNeumann.  An spherical neumann function of integral order //
// Joe Boudreau, Petar Maksimovic, January 2000                             //
//                                                                          //
//--------------------------------------------------------------------------//
#ifndef SphericalNeumann_h
#define SphericalNeumann_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"
#include "CLHEP/GenericFunctions/Parameter.hh"
namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class SphericalNeumann : public AbsFunction  {

    FUNCTION_OBJECT_DEF(SphericalNeumann)

      public:

    // Constructor
    SphericalNeumann(unsigned int l);

    // Copy constructor
    SphericalNeumann(const SphericalNeumann &right);
  
    // Destructor
    virtual ~SphericalNeumann();
  
    // Retreive function value
    virtual CLHEPdouble operator ()(CLHEPdouble argument) const override;
    virtual CLHEPdouble operator ()(const Argument & a) const override {return operator() (a[0]);}
  
    // Get the integer variable l
    unsigned int l() const;

  private:

    // It is illegal to assign a spherical neumann
    const SphericalNeumann & operator=(const SphericalNeumann &right);

    // Here is the index
    unsigned int _l;
  
  };
} // namespace Genfun
#include "CLHEP/GenericFunctions/SphericalNeumann.icc"
#endif
