#include "CLHEPTypes.hpp"
// $Id:$
// -*- C++ -*-
//
// -----------------------------------------------------------------------
//                             HEP Random
//                       --- RandExpZiggurat ---
//                          class header file
// -----------------------------------------------------------------------
// This file is part of Geant4 (simulation toolkit for HEP).

// Class defining methods for shooting or firing Landau distributed 
// random values.   

// =======================================================================
//
// Code adapted from:
// http://www.jstatsoft.org/v05/i08/
//
//
// Original disclaimer:

// The ziggurat method for RNOR and REXP
// Combine the code below with the main program in which you want
// normal or exponential variates.   Then use of RNOR in any expression
// will provide a standard normal variate with mean zero, variance 1,
// while use of REXP in any expression will provide an exponential variate
// with density exp(-x),x>0.
// Before using RNOR or REXP in your main, insert a command such as
// zigset(86947731 );
// with your own choice of seed value>0, rather than 86947731.
// (If you do not invoke zigset(...) you will get all zeros for RNOR and REXP.)
// For details of the method, see Marsaglia and Tsang, "The ziggurat method
// for generating random variables", Journ. Statistical Software.

// =======================================================================

#ifndef RandExpZiggurat_h
#define RandExpZiggurat_h 1

#include "CLHEP/Random/defs.h"
#include "CLHEP/Random/Random.h"
#include "CLHEP/Utility/memory.h"
#include "CLHEP/Utility/thread_local.h"

namespace CLHEP {

/**
 * @author ATLAS
 * @ingroup random
 */
class RandExpZiggurat : public HepRandom {

public:

  inline RandExpZiggurat ( HepRandomEngine& anEngine, CLHEPdouble mean=1.0 );
  inline RandExpZiggurat ( HepRandomEngine* anEngine, CLHEPdouble mean=1.0 );
  // These constructors should be used to instantiate a RandExpZiggurat
  // distribution object defining a local engine for it.
  // The static generator will be skipped using the non-static methods
  // defined below.
  // If the engine is passed by pointer the corresponding engine object
  // will be deleted by the RandExpZiggurat destructor.
  // If the engine is passed by reference the corresponding engine object
  // will not be deleted by the RandExpZiggurat destructor.

  virtual ~RandExpZiggurat();
  // Destructor

  // Static methods to shoot random values using the static generator

  static CLHEPfloat shoot() {return shoot(HepRandom::getTheEngine());};
  static CLHEPfloat shoot( CLHEPfloat mean ) {return shoot(HepRandom::getTheEngine(),mean);};

  /* ENGINE IS INTRINSIC FLOAT
  static CLHEPdouble shoot() {return shoot(HepRandom::getTheEngine());};
  static CLHEPdouble shoot( CLHEPdouble mean ) {return shoot(HepRandom::getTheEngine(),mean);};
  */

  static void shootArray ( const int size, CLHEPfloat* vect, CLHEPfloat mean=1.0 );
  static void shootArray ( const int size, CLHEPdouble* vect, CLHEPdouble mean=1.0 );

  //  Static methods to shoot random values using a given engine
  //  by-passing the static generator.

  static inline CLHEPfloat shoot( HepRandomEngine* anEngine ) {return ziggurat_REXP(anEngine);};
  static inline CLHEPfloat shoot( HepRandomEngine* anEngine, CLHEPfloat mean ) {return shoot(anEngine)*mean;};
  
  /* ENGINE IS INTRINSIC FLOAT
  static inline CLHEPdouble shoot( HepRandomEngine* anEngine ) {return ziggurat_REXP(anEngine);};

  static inline CLHEPdouble shoot( HepRandomEngine* anEngine, CLHEPdouble mean ) {return shoot(anEngine)*mean;};
  */
  
  static void shootArray ( HepRandomEngine* anEngine, const int size, CLHEPfloat* vect, CLHEPfloat mean=1.0 );
  static void shootArray ( HepRandomEngine* anEngine, const int size, CLHEPdouble* vect, CLHEPdouble mean=1.0 );

  //  Methods using the localEngine to shoot random values, by-passing
  //  the static generator.

  inline CLHEPfloat fire() {return fire(defaultMean);};
  inline CLHEPfloat fire( CLHEPfloat mean ) {return ziggurat_REXP(localEngine.get())*mean;};
  
  /* ENGINE IS INTRINSIC FLOAT
  inline CLHEPdouble fire() {return fire(defaultMean);};
  inline CLHEPdouble fire( CLHEPdouble mean ) {return ziggurat_REXP(localEngine.get())*mean;};
  */
  
  void fireArray ( const int size, CLHEPfloat* vect );
  void fireArray ( const int size, CLHEPdouble* vect );
  void fireArray ( const int size, CLHEPfloat* vect, CLHEPfloat mean );
  void fireArray ( const int size, CLHEPdouble* vect, CLHEPdouble mean );
  
  virtual CLHEPdouble operator()();
  inline CLHEPfloat operator()( CLHEPfloat mean ) {return fire( mean );};

  // Save and restore to/from streams
  
  std::ostream & put ( std::ostream & os ) const;
  std::istream & get ( std::istream & is );

  std::string name() const;
  HepRandomEngine & engine();

  static std::string distributionName() {return "RandExpZiggurat";}  
  // Provides the name of this distribution class
  
  static bool ziggurat_init();
protected:
  //////////////////////////
  // Ziggurat Original code:
  //////////////////////////
  //static unsigned long jz,jsr=123456789;
  //
  //#define SHR3 (jz=jsr, jsr^=(jsr<<13), jsr^=(jsr>>17), jsr^=(jsr<<5),jz+jsr)
  //#define UNI (.5 + (signed) SHR3*.2328306e-9)
  //#define IUNI SHR3
  //
  //static long hz;
  //static unsigned long iz, kn[128], ke[256];
  //static CLHEPfloat wn[128],fn[128], we[256],fe[256];
  //
  //#define RNOR (hz=SHR3, iz=hz&127, (fabs(hz)<kn[iz])? hz*wn[iz] : nfix())
  //#define REXP (jz=SHR3, iz=jz&255, (    jz <ke[iz])? jz*we[iz] : efix())

  static CLHEP_THREAD_LOCAL unsigned long kn[128], ke[256];
  static CLHEP_THREAD_LOCAL CLHEPfloat wn[128],fn[128], we[256],fe[256];

  static CLHEP_THREAD_LOCAL bool ziggurat_is_init;

  static inline unsigned long ziggurat_SHR3(HepRandomEngine* anEngine) {return (unsigned int)(*anEngine);};
  static inline CLHEPfloat ziggurat_UNI(HepRandomEngine* anEngine) {return anEngine->flat();};
  static inline CLHEPfloat ziggurat_REXP(HepRandomEngine* anEngine) {
    if(!ziggurat_is_init) ziggurat_init();
    unsigned long jz=ziggurat_SHR3(anEngine);
    unsigned long iz=jz&255;
    return (jz<ke[iz]) ? jz*we[iz] : ziggurat_efix(jz,anEngine);
  };
  static CLHEPfloat ziggurat_efix(unsigned long jz,HepRandomEngine* anEngine);

private:

  // Private copy constructor. Defining it here disallows use.
  RandExpZiggurat(const RandExpZiggurat& d);

  std::shared_ptr<HepRandomEngine> localEngine;
  CLHEPdouble defaultMean;
};

}  // namespace CLHEP

#ifdef ENABLE_BACKWARDS_COMPATIBILITY
//  backwards compatibility will be enabled ONLY in CLHEP 1.9
using namespace CLHEP;
#endif

namespace CLHEP {

inline RandExpZiggurat::RandExpZiggurat(HepRandomEngine & anEngine, CLHEPdouble mean ) : localEngine(&anEngine, do_nothing_deleter()), defaultMean(mean) 
{
}

inline RandExpZiggurat::RandExpZiggurat(HepRandomEngine * anEngine, CLHEPdouble mean ) : localEngine(anEngine), defaultMean(mean) 
{
}

}  // namespace CLHEP

#endif
