#include "CLHEPTypes.hpp"
// $Id: RandGaussQ.h,v 1.5 2010/06/16 17:24:53 garren Exp $
// -*- C++ -*-
//
// -----------------------------------------------------------------------
//                             HEP Random
//                          --- RandGaussQ ---
//                          class header file
// -----------------------------------------------------------------------

// Class defining methods RandGaussQ, which is derived from RandGauss.
// The user interface is identical; but RandGaussQ is faster and a bit less
// accurate.

// =======================================================================
// M. Fischler - Created: 24th Jan 2000
// M Fischler      - put and get to/from streams 12/10/04
//
// =======================================================================

#ifndef RandGaussQ_h
#define RandGaussQ_h 1

#include "CLHEP/Random/defs.h"
#include "CLHEP/Random/RandGauss.h"

namespace CLHEP {

/**
 * @author
 * @ingroup random
 */
class RandGaussQ : public RandGauss {

public:

  inline RandGaussQ ( HepRandomEngine& anEngine, CLHEPdouble mean=0.0,
                                                CLHEPdouble stdDev=1.0 );
  inline RandGaussQ ( HepRandomEngine* anEngine, CLHEPdouble mean=0.0,
                                                CLHEPdouble stdDev=1.0 );
  // These constructors should be used to instantiate a RandGaussQ
  // distribution object defining a local engine for it.
  // The static generator will be skipped using the non-static methods
  // defined below.
  // If the engine is passed by pointer the corresponding engine object
  // will be deleted by the RandGaussQ destructor.
  // If the engine is passed by reference the corresponding engine object
  // will not be deleted by the RandGaussQ destructor.

  // Destructor
  virtual ~RandGaussQ();

  //
  // Methods to generate Gaussian-distributed random deviates:
  //
  //   If a fast good engine takes 1 usec, RandGauss::fire() adds 1 usec while 
  //   RandGaussQ::fire() adds only .4 usec.
  //

  // Static methods to shoot random values using the static generator

  static  inline CLHEPdouble shoot();

  static  inline CLHEPdouble shoot( CLHEPdouble mean, CLHEPdouble stdDev );

  static  void shootArray ( const int size, CLHEPdouble* vect,
                            CLHEPdouble mean=0.0, CLHEPdouble stdDev=1.0 );

  //  Static methods to shoot random values using a given engine
  //  by-passing the static generator.

  static  inline CLHEPdouble shoot( HepRandomEngine* anotherEngine );

  static  inline CLHEPdouble shoot( HepRandomEngine* anotherEngine, 
                                  CLHEPdouble mean, CLHEPdouble stdDev );


  static  void shootArray ( HepRandomEngine* anotherEngine, 
			    const int size,
                            CLHEPdouble* vect, CLHEPdouble mean=0.0,
                            CLHEPdouble stdDev=1.0 );

  //  Instance methods using the localEngine to instead of the static 
  //  generator, and the default mean and stdDev established at construction

  inline CLHEPdouble fire();

  inline CLHEPdouble fire ( CLHEPdouble mean, CLHEPdouble stdDev );
  
  void fireArray  ( const int size, CLHEPdouble* vect);
  void fireArray  ( const int size, CLHEPdouble* vect,
                    CLHEPdouble mean, CLHEPdouble stdDev );

  virtual CLHEPdouble operator()();
  virtual CLHEPdouble operator()( CLHEPdouble mean, CLHEPdouble stdDev );

  // Save and restore to/from streams
  
  std::ostream & put ( std::ostream & os ) const;
  std::istream & get ( std::istream & is );

  std::string name() const;
  HepRandomEngine & engine();

  static std::string distributionName() {return "RandGaussQ";}  
  // Provides the name of this distribution class
  

protected:

  static CLHEPdouble transformQuick (CLHEPdouble r);
  static CLHEPdouble transformSmall (CLHEPdouble r);

private:

  // All the engine info, and the default mean and sigma, are in the RandGauss
  // base class.

};

}  // namespace CLHEP

#ifdef ENABLE_BACKWARDS_COMPATIBILITY
//  backwards compatibility will be enabled ONLY in CLHEP 1.9
using namespace CLHEP;
#endif

#include "CLHEP/Random/RandGaussQ.icc"

#endif
