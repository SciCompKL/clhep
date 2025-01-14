#include "CLHEPTypes.hpp"
// $Id: NonRandomEngine.h,v 1.7 2011/07/01 15:20:30 garren Exp $
// -*- C++ -*-
//
// -----------------------------------------------------------------------
//                             HEP Random
//                        --- NonRandomEngine ---
//                          class header file
// -----------------------------------------------------------------------

// This class is present EXCLUSIVELY as a means to test distributions (and
// other programs that depend on random numbers) by feeding them a stream
// of "randoms" that the testing program supplies explicitly.
//
// The testing program calls setNextRandom (CLHEPdouble) to setup the next
// value to be produced when flat() is done.  
//
// To protect against accidental use of this NON-RANDOM engine as a random
// engine, if setNextRandom () is never called, all attempts to generate
// a random will fail and exit.

// =======================================================================
// Mark Fischler  - Created: 9/30/99
// Mark Fischler    methods for distrib. instance save/restore 12/8/04    
// Mark Fischler    methods for anonymous save/restore 12/27/04    
// =======================================================================

#ifndef NonRandomEngine_h
#define NonRandomEngine_h 1

#include "CLHEP/Random/defs.h"
#include "CLHEP/Random/RandomEngine.h"
#include <vector>

namespace CLHEP {

/**
 * @author
 * @ingroup random
 */
class NonRandomEngine : public HepRandomEngine {

public:

  NonRandomEngine();
  virtual ~NonRandomEngine();
  // Constructors and destructor

  void setNextRandom     (CLHEPdouble r);
	// Preset the next random to be delivered
  void setRandomSequence (CLHEPdouble *s, int n);
	// Establish a sequence of n next randoms; 
	// replaces setNextRandom n times.
  void setRandomInterval (CLHEPdouble x);
	// Establish that if there is no sequence active each 
	// random should be bumped by this interval (mod 1) compared 
	// to the last.  x should be between 0 and 1.

  CLHEPdouble flat();
  // It returns the previously established setNextRandom and bumps that up
  // by the non-zero randomInterval supplied.  Thus repeated calls to flat()
  // generate an evenly spaced sequence (mod 1).

  void flatArray (const int size, CLHEPdouble* vect);
  // Fills the array "vect" of specified size with flat random values.

  virtual std::ostream & put (std::ostream & os) const;
  virtual std::istream & get (std::istream & is);
  static  std::string beginTag ( );
  virtual std::istream & getState ( std::istream & is );

  std::string name() const;
  static std::string engineName() {return "NonRandomEngine";}

  std::vector<unsigned long> put () const;
  bool get (const std::vector<unsigned long> & v);
  bool getState (const std::vector<unsigned long> & v);
  
private:

  bool nextHasBeenSet;
  bool sequenceHasBeenSet;
  bool intervalHasBeenSet;
  CLHEPdouble  nextRandom;
  std::vector<CLHEPdouble> sequence;
  unsigned int nInSeq;
  CLHEPdouble  randomInterval;

  // The following are necessary to fill virtual methods but should never 
  // be used:

  virtual void setSeed(long , int) {};
  virtual void setSeeds(const long * , int) {};
  virtual void saveStatus( const char* ) const {};
  virtual void restoreStatus( const char* ) {};
  virtual void showStatus() const {};

 
};

}  // namespace CLHEP

#endif
