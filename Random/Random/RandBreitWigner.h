#include "CLHEPTypes.hpp"
// $Id: RandBreitWigner.h,v 1.5 2010/06/16 17:24:53 garren Exp $
// -*- C++ -*-
//
// -----------------------------------------------------------------------
//                             HEP Random
//                        --- RandBreitWigner ---
//                           class header file
// -----------------------------------------------------------------------
// This file is part of Geant4 (simulation toolkit for HEP).
//
// Class defining methods for shooting numbers according to the
// Breit-Wigner distribution algorithms (plain or mean^2).
// Default values are set: mean=1, gamma=.2, cut=1.
// Plain algorithm is used for shootArray() and fireArray().
// Plain algorithm with default values is used for operator()(). 

// =======================================================================
// Gabriele Cosmo - Created: 5th September 1995
//                - Added methods to shoot arrays: 28th July 1997
// J.Marraffino   - Added default arguments as attributes and
//                  operator() with arguments: 16th Feb 1998
// M Fischler      - put and get to/from streams 12/10/04
// =======================================================================

#ifndef RandBreitWigner_h
#define RandBreitWigner_h 1

#include "CLHEP/Random/defs.h"
#include "CLHEP/Random/RandFlat.h"
#include "CLHEP/Utility/memory.h"

namespace CLHEP {

/**
 * @author <Gabriele.Cosmo@cern.ch>
 * @ingroup random
 */
class RandBreitWigner : public HepRandom {

public:

  inline RandBreitWigner ( HepRandomEngine& anEngine, CLHEPdouble a=1.0,
                                       CLHEPdouble b=0.2 );
  inline RandBreitWigner ( HepRandomEngine* anEngine, CLHEPdouble a=1.0,
                                       CLHEPdouble b=0.2 );
  // These constructors should be used to instantiate a RandBreitWigner
  // distribution object defining a local engine for it.
  // The static generator will be skipped using the non-static methods
  // defined below.
  // If the engine is passed by pointer the corresponding engine object
  // will be deleted by the RandBreitWigner destructor.
  // If the engine is passed by reference the corresponding engine object
  // will not be deleted by the RandBreitWigner destructor.

  virtual ~RandBreitWigner();
  // Destructor

  // Static methods to shoot random values using the static generator

  static  CLHEPdouble shoot( CLHEPdouble a=1.0, CLHEPdouble b=0.2 );

  static  CLHEPdouble shoot( CLHEPdouble a, CLHEPdouble b, CLHEPdouble c );

  static  CLHEPdouble shootM2( CLHEPdouble a=1.0, CLHEPdouble b=0.2 );

  static  CLHEPdouble shootM2( CLHEPdouble a, CLHEPdouble b, CLHEPdouble c );

  static  void shootArray ( const int size, CLHEPdouble* vect);

  static  void shootArray ( const int size, CLHEPdouble* vect,
                            CLHEPdouble a, CLHEPdouble b );

  static  void shootArray ( const int size, CLHEPdouble* vect,
                            CLHEPdouble a, CLHEPdouble b, CLHEPdouble c );
                           
  //  Static methods to shoot random values using a given engine
  //  by-passing the static generator.

  static  CLHEPdouble shoot( HepRandomEngine* anEngine, CLHEPdouble a=1.0,
                           CLHEPdouble b=0.2 );
  static  CLHEPdouble shoot( HepRandomEngine* anEngine, CLHEPdouble a,
                           CLHEPdouble b, CLHEPdouble c );
  static  CLHEPdouble shootM2( HepRandomEngine* anEngine, CLHEPdouble a=1.0,
                             CLHEPdouble b=0.2 );
  static  CLHEPdouble shootM2( HepRandomEngine* anEngine, CLHEPdouble a,
                             CLHEPdouble b, CLHEPdouble c );
  static  void shootArray ( HepRandomEngine* anEngine,
                            const int size, CLHEPdouble* vect );
  static  void shootArray ( HepRandomEngine* anEngine,
                            const int size, CLHEPdouble* vect,
                            CLHEPdouble a, CLHEPdouble b );
  static  void shootArray ( HepRandomEngine* anEngine,
                            const int size, CLHEPdouble* vect,
                            CLHEPdouble a, CLHEPdouble b, CLHEPdouble c );

  //  Methods using the localEngine to shoot random values, by-passing
  //  the static generator. These methods respect distribution parameters
  //  passed by the user at instantiation unless superseded by actual
  //  arguments in the call.

  CLHEPdouble fire();

  CLHEPdouble fire( CLHEPdouble a, CLHEPdouble b );

  CLHEPdouble fire( CLHEPdouble a, CLHEPdouble b, CLHEPdouble c );

  CLHEPdouble fireM2();

  CLHEPdouble fireM2( CLHEPdouble a, CLHEPdouble b );

  CLHEPdouble fireM2( CLHEPdouble a, CLHEPdouble b, CLHEPdouble c );

  void fireArray ( const int size, CLHEPdouble* vect);

  void fireArray ( const int size, CLHEPdouble* vect,
                   CLHEPdouble a, CLHEPdouble b );

  void fireArray ( const int size, CLHEPdouble* vect,
                   CLHEPdouble a, CLHEPdouble b, CLHEPdouble c );
  CLHEPdouble operator()();
  CLHEPdouble operator()( CLHEPdouble a, CLHEPdouble b );
  CLHEPdouble operator()( CLHEPdouble a, CLHEPdouble b, CLHEPdouble c );

  // Save and restore to/from streams
  
  std::ostream & put ( std::ostream & os ) const;
  std::istream & get ( std::istream & is );

  std::string name() const;
  HepRandomEngine & engine();

  static std::string distributionName() {return "RandBreitWigner";}  
  // Provides the name of this distribution class
         
private:

  std::shared_ptr<HepRandomEngine> localEngine;
  CLHEPdouble defaultA;
  CLHEPdouble defaultB;

};

}  // namespace CLHEP

#ifdef ENABLE_BACKWARDS_COMPATIBILITY
//  backwards compatibility will be enabled ONLY in CLHEP 1.9
using namespace CLHEP;
#endif

#include "CLHEP/Random/RandBreitWigner.icc"

#endif
