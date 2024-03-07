#include "CLHEPTypes.hpp"
// $Id: RandFlat.h,v 1.5 2010/06/16 17:24:53 garren Exp $
// -*- C++ -*-
//
// -----------------------------------------------------------------------
//                             HEP Random
//                           --- RandFlat ---
//                          class header file
// -----------------------------------------------------------------------
// This file is part of Geant4 (simulation toolkit for HEP).

// Class defining methods for shooting flat random numbers, CLHEPdouble or
// integers.
// It provides methods to fill with CLHEPdouble flat values arrays of
// specified size, as well as methods for shooting sequences of 0,1 (bits).
// Default boundaries ]0.1[ for operator()().

// =======================================================================
// Gabriele Cosmo - Created: 5th September 1995
// Peter Urban    - ShootBit() and related stuff added: 5th Sep 1996
// Gabriele Cosmo - Added operator() and additional methods to fill
//                  arrays specifying boundaries: 24th Jul 1997 
// J.Marraffino   - Added default arguments as attributes and
//                  operator() with arguments: 16th Feb 1998
// M. Fischler    - Moved copy constructor to protected so that
//		    derived RandBit can get at it.
// M Fischler      - put and get to/from streams 12/10/04
// =======================================================================

#ifndef RandFlat_h
#define RandFlat_h 1

#include "CLHEP/Random/defs.h"
#include "CLHEP/Random/Random.h"
#include "CLHEP/Utility/memory.h"
#include "CLHEP/Utility/thread_local.h"

namespace CLHEP {

/**
 * @author <Gabriele.Cosmo@cern.ch>
 * @ingroup random
 */
class RandFlat : public HepRandom {

public:

  inline RandFlat ( HepRandomEngine& anEngine );
  inline RandFlat ( HepRandomEngine& anEngine, CLHEPdouble width );
  inline RandFlat ( HepRandomEngine& anEngine, CLHEPdouble a, CLHEPdouble b );
  inline RandFlat ( HepRandomEngine* anEngine );
  inline RandFlat ( HepRandomEngine* anEngine, CLHEPdouble width );
  inline RandFlat ( HepRandomEngine* anEngine, CLHEPdouble a, CLHEPdouble b );
  // These constructors should be used to instantiate a RandFlat
  // distribution object defining a local engine for it.
  // The static generator will be skipped using the non-static methods
  // defined below.
  // If the engine is passed by pointer the corresponding engine object
  // will be deleted by the RandFlat destructor.
  // If the engine is passed by reference the corresponding engine object
  // will not be deleted by the RandFlat destructor.

  virtual ~RandFlat();
  // Destructor

  // Static methods to shoot random values using the static generator

  static  CLHEPdouble shoot();

  static  inline CLHEPdouble shoot( CLHEPdouble width );

  static  inline CLHEPdouble shoot( CLHEPdouble a, CLHEPdouble b );

  static  inline long shootInt( long n );

  static  inline long shootInt( long a1, long n );

  static  inline int shootBit();

  static  void shootArray ( const int size, CLHEPdouble* vect );

  static  void shootArray ( const int size, CLHEPdouble* vect,
                            CLHEPdouble lx, CLHEPdouble dx );

  //  Static methods to shoot random values using a given engine
  //  by-passing the static generator.

  static  inline CLHEPdouble shoot ( HepRandomEngine* anEngine );

  static  inline CLHEPdouble shoot( HepRandomEngine* anEngine, CLHEPdouble width );

  static  inline CLHEPdouble shoot( HepRandomEngine* anEngine,
                                  CLHEPdouble a, CLHEPdouble b );
  static  inline long shootInt( HepRandomEngine* anEngine, long n );
  
  static  inline long shootInt( HepRandomEngine* anEngine, long a1, long n );
  
  static  inline int shootBit( HepRandomEngine* );

  static  inline void shootArray ( HepRandomEngine* anEngine,
                                   const int size, CLHEPdouble* vect );

  static  void shootArray ( HepRandomEngine* anEngine, 
                            const int size, CLHEPdouble* vect,
                            CLHEPdouble lx, CLHEPdouble dx );

  //  Methods using the localEngine to shoot random values, by-passing
  //  the static generator.

  inline CLHEPdouble fire();

  inline CLHEPdouble fire( CLHEPdouble width );

  inline CLHEPdouble fire( CLHEPdouble a, CLHEPdouble b );

  inline long fireInt( long n );

  inline long fireInt( long a1, long n );

  inline int fireBit();

  void fireArray (const int size, CLHEPdouble* vect);

  void fireArray (const int size, CLHEPdouble* vect,
                  CLHEPdouble lx, CLHEPdouble dx);

  CLHEPdouble operator()();
  CLHEPdouble operator()( CLHEPdouble width );
  CLHEPdouble operator()( CLHEPdouble a, CLHEPdouble b );

  // Save and restore to/from streams
  
  std::ostream & put ( std::ostream & os ) const;
  std::istream & get ( std::istream & is );

  std::string name() const;
  HepRandomEngine & engine();

  static std::string distributionName() {return "RandFlat";}  
  // Provides the name of this distribution class 
  
  // Methods overriding the base class static saveEngineStatus ones,
  // by adding extra data so that save in one program, then further shootBit()s
  // will produce the identical sequence to restore in another program, then
  // generating shootBit() randoms there

  static void saveEngineStatus( const char filename[] = "Config.conf" );
  // Saves to file the current status of the current engine.

  static void restoreEngineStatus( const char filename[] = "Config.conf" );
  // Restores a saved status (if any) for the current engine.

  static std::ostream& saveFullState ( std::ostream & os );
  // Saves to stream the state of the engine and cached data.

  static std::istream& restoreFullState ( std::istream & is );
  // Restores from stream the state of the engine and cached data.

  static std::ostream& saveDistState ( std::ostream & os );
  // Saves to stream the state of the cached data.

  static std::istream& restoreDistState ( std::istream & is );
  // Restores from stream the state of the cached data.


protected:

#if 0
  // Protected copy constructor. Defining it here disallows use by users.
  RandFlat(const RandFlat& d);
#endif  // 0

private:

  // ShootBits generates an integer random number,
  // which is used by fireBit().
  // The number is stored in randomInt and firstUnusedBit

  inline void fireBits();
  static inline void shootBits();
  static inline void shootBits(HepRandomEngine*);

  // In MSB, the most significant bit of the integer random number
  // generated by ShootBits() is set.
  // Note:
  //   the number of significant bits must be chosen so that
  //   - an unsigned long can hold it
  //   - and it should be less than the number of bits returned 
  //     by Shoot() which are not affected by precision problems
  //     on _each_ architecture.
  //   (Aim: the random generators should be machine-independent).

  static const unsigned long MSB; 
  static const int MSBBits;
  // These two are set up in RandFlat.cc and need not be saved/restored

  unsigned long randomInt;
  unsigned long firstUnusedBit;
  static CLHEP_THREAD_LOCAL unsigned long staticRandomInt;
  static CLHEP_THREAD_LOCAL unsigned long staticFirstUnusedBit;
  
  std::shared_ptr<HepRandomEngine> localEngine;
  CLHEPdouble defaultWidth;
  CLHEPdouble defaultA;
  CLHEPdouble defaultB;

};

}  // namespace CLHEP

#ifdef ENABLE_BACKWARDS_COMPATIBILITY
//  backwards compatibility will be enabled ONLY in CLHEP 1.9
using namespace CLHEP;
#endif

#include "CLHEP/Random/RandFlat.icc"

#endif
