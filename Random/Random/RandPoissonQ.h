#include "CLHEPTypes.hpp"
// $Id: RandPoissonQ.h,v 1.5 2010/06/16 17:24:53 garren Exp $
// -*- C++ -*-
//
// -----------------------------------------------------------------------
//                             HEP Random
//                         --- RandPoissonQ ---
//                          class header file
// -----------------------------------------------------------------------

// Class defining RandPoissonQ, which is derived from RandPoison.
// The user interface is identical; but RandGaussQ is much faster in all cases
// and a bit less accurate when mu > 100.

// =======================================================================
// M. Fischler - Created: 4th Feb 2000
// M Fischler      - put and get to/from streams 12/10/04
//
// =======================================================================

#ifndef RandPoissonQ_h
#define RandPoissonQ_h 1

#include "CLHEP/Random/defs.h"
#include "CLHEP/Random/Random.h"
#include "CLHEP/Random/RandPoisson.h"

namespace CLHEP {

/**
 * @author
 * @ingroup random
 */
class RandPoissonQ : public RandPoisson {

public:

  inline RandPoissonQ ( HepRandomEngine& anEngine, CLHEPdouble b1=1.0 );
  inline RandPoissonQ ( HepRandomEngine* anEngine, CLHEPdouble b1=1.0 );
  // These constructors should be used to instantiate a RandPoissonQ
  // distribution object defining a local engine for it.
  // The static generator will be skipped using the non-static methods
  // defined below.
  // If the engine is passed by pointer the corresponding engine object
  // will be deleted by the RandPoissonQ destructor.
  // If the engine is passed by reference the corresponding engine object
  // will not be deleted by the RandPoissonQ destructor.

  virtual ~RandPoissonQ();
  // Destructor

  // Save and restore to/from streams
  
  std::ostream & put ( std::ostream & os ) const;
  std::istream & get ( std::istream & is );

  // Methods to generate Poisson-distributed random deviates.

  //   The method used for mu <= 100 is exact, and 3-7 times faster than
  //   that used by RandPoisson.  
  //   For mu > 100 then we use a corrected version of a 
  //   (quick) Gaussian approximation.  Naively that would be:
  //
  //	Poisson(mu) ~ floor( mu + .5 + Gaussian(sqrt(mu)) )
  //
  //   but actually, that would give a slightly incorrect sigma and a 
  //   very different skew than a true Poisson.  Instead we return 
  // 
  //	Poisson(mu) ~ floor( a0*mu + a1*g + a2*g*g ) )
  //						(with g a gaussian normal)
  //
  //   where a0, a1, a2 are chosen to give the exctly correct mean, sigma,
  //   and skew for the Poisson distribution.

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

  static std::string distributionName() {return "RandPoissonQ";}  
  // Provides the name of this distribution class

  
  // static constants of possible interest to users:

  // RandPoisson will never return a deviate greater than this value:
  static const CLHEPdouble MAXIMUM_POISSON_DEVIATE; // Will be 2.0E9

  static inline int tableBoundary();

private:

  // constructor helper
  void setupForDefaultMu();

  // algorithm helper methods - all static since the shoot methods mayneed them
  static long poissonDeviateSmall ( HepRandomEngine * e, CLHEPdouble mean );
  static long poissonDeviateQuick ( HepRandomEngine * e, CLHEPdouble mean );
  static long poissonDeviateQuick ( HepRandomEngine * e, 
		CLHEPdouble A0, CLHEPdouble A1, CLHEPdouble A2, CLHEPdouble sig );

  // All the engine info, and the default mean, are in the 
  // RandPoisson base class.

  // quantities for approximate Poisson by corrected Gaussian
  CLHEPdouble a0;      
  CLHEPdouble a1;	    	
  CLHEPdouble a2;	
  CLHEPdouble sigma;  

  // static data - constants only, so that saveEngineStatus works properly!

  // The following MUST MATCH the corresponding values used (in 
  // poissonTables.cc) when poissonTables.cdat was created.  
  // poissonTables.cc gets these values by including this header, 
  // but we must be careful not to change these values,
  // and rebuild RandPoissonQ before re-generating poissonTables.cdat.

  // (These statics are given values near the start of the .cc file) 

  static const CLHEPdouble FIRST_MU;  // lowest mu value in table
  static const CLHEPdouble LAST_MU;   // highest mu value
  static const CLHEPdouble S;         // Spacing between mu values
  static const int BELOW;        // Starting point for N is at mu - BELOW
  static const int ENTRIES;      // Number of entries in each mu row

};

}  // namespace CLHEP

#ifdef ENABLE_BACKWARDS_COMPATIBILITY
//  backwards compatibility will be enabled ONLY in CLHEP 1.9
using namespace CLHEP;
#endif

#include "CLHEP/Random/RandPoissonQ.icc"

#endif
