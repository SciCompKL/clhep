#include "CLHEPTypes.hpp"
// $Id: RandPoisson.h,v 1.5 2010/06/16 17:24:53 garren Exp $
// -*- C++ -*-
//
// -----------------------------------------------------------------------
//                             HEP Random
//                         --- RandPoisson ---
//                          class header file
// -----------------------------------------------------------------------
// This file is part of Geant4 (simulation toolkit for HEP).

// Class defining methods for shooting numbers according to the Poisson
// distribution, given a mean (Algorithm taken from "W.H.Press et al.,
// Numerical Recipes in C, Second Edition".
// Default mean value is set to 1, value used for operator()().

// =======================================================================
// Gabriele Cosmo - Created: 5th September 1995
//                - Added not static Shoot() method: 17th May 1996
//                - Algorithm now operates on CLHEPdoubles : 31st Oct 1996
//                - Added methods to shoot arrays: 28th July 1997
// J.Marraffino   - Added default mean as attribute and
//                  operator() with mean: 16th Feb 1998
// Gabriele Cosmo - Relocated static data from HepRandom: 5th Jan 1999
// M. Fischler    - Moved meanMax and defaultMean from private to protected
//		    to accomodate derived classes RandPoissonQ & RandPoissonT
// M Fischler      - put and get to/from streams 12/10/04
// =======================================================================

#ifndef RandPoisson_h
#define RandPoisson_h 1

#include "CLHEP/Random/defs.h"
#include "CLHEP/Random/Random.h"
#include "CLHEP/Utility/memory.h"
#include "CLHEP/Utility/thread_local.h"

namespace CLHEP {

/**
 * @author
 * @ingroup random
 */
class RandPoisson : public HepRandom {

public:

  inline RandPoisson ( HepRandomEngine& anEngine, CLHEPdouble a1=1.0 );
  inline RandPoisson ( HepRandomEngine* anEngine, CLHEPdouble a1=1.0 );
  // These constructors should be used to instantiate a RandPoisson
  // distribution object defining a local engine for it.
  // The static generator will be skipped using the non-static methods
  // defined below.
  // If the engine is passed by pointer the corresponding engine object
  // will be deleted by the RandPoisson destructor.
  // If the engine is passed by reference the corresponding engine object
  // will not be deleted by the RandPoisson destructor.

  virtual ~RandPoisson();
  // Destructor

  // Save and restore to/from streams
  
  std::ostream & put ( std::ostream & os ) const;
  std::istream & get ( std::istream & is );

  // Static methods to shoot random values using the static generator

  static  long shoot( CLHEPdouble mean=1.0 );

  static  void shootArray ( const int size, long* vect, CLHEPdouble mean=1.0 );

  //  Static methods to shoot random values using a given engine
  //  by-passing the static generator.

  static  long shoot( HepRandomEngine* anEngine, CLHEPdouble mean=1.0 );

  static  void shootArray ( HepRandomEngine* anEngine,
                            const int size, long* vect, CLHEPdouble mean=1.0 );

  //  Methods using the localEngine to shoot random values, by-passing
  //  the static generator.

  long  fire();
  long  fire( CLHEPdouble mean );

  void fireArray ( const int size, long* vect );
  void fireArray ( const int size, long* vect, CLHEPdouble mean);

  CLHEPdouble operator()();
  CLHEPdouble operator()( CLHEPdouble mean );
  
  std::string name() const;
  HepRandomEngine & engine();

  static std::string distributionName() {return "RandPoisson";}  
  // Provides the name of this distribution class

protected:

  CLHEPdouble meanMax;
  CLHEPdouble defaultMean;

  static  CLHEPdouble getOldMean() {return oldm_st;}

  static  CLHEPdouble getMaxMean() {return meanMax_st;}

  static  void setOldMean( CLHEPdouble val ){oldm_st = val;}

  static  CLHEPdouble* getPStatus() {return status_st;}

  static void setPStatus(CLHEPdouble sq, CLHEPdouble alxm, CLHEPdouble g1) {
    status_st[0] = sq; status_st[1] = alxm; status_st[2] = g1;
  }

  inline HepRandomEngine* getLocalEngine();
  
private:

  std::shared_ptr<HepRandomEngine> localEngine;
  CLHEPdouble status[3], oldm;

  // static data
  static CLHEP_THREAD_LOCAL CLHEPdouble status_st[3];
  static CLHEP_THREAD_LOCAL CLHEPdouble oldm_st;
  static const CLHEPdouble meanMax_st;

};

}  // namespace CLHEP

#ifdef ENABLE_BACKWARDS_COMPATIBILITY
//  backwards compatibility will be enabled ONLY in CLHEP 1.9
using namespace CLHEP;
#endif

#include "CLHEP/Random/RandPoisson.icc"

#endif
