// $Id: Random.cc,v 1.4 2003/08/13 20:00:12 garren Exp $
// -*- C++ -*-
//
// -----------------------------------------------------------------------
//                             HEP Random
//                          --- HepRandom ---
//                      class implementation file
// -----------------------------------------------------------------------
// This file is part of Geant4 (simulation toolkit for HEP).

// =======================================================================
// Gabriele Cosmo - Created: 5th September 1995
//                - Minor corrections: 31st October 1996
//                - Added methods for engine status: 19th November 1996
//                - HepRandom defined as singleton, constructors are
//                  kept public for backward compatibility: 27th Feb 1998
//                - Relocated Poisson and Gauss data and simplified
//                  initialisation of static generator: 5th Jan 1999
// =======================================================================

#include "CLHEP/Random/defs.h"
#include "CLHEP/Random/JamesRandom.h"
#include "CLHEP/Random/Random.h"

// -----------------------------
// Static members initialisation
// -----------------------------

#include "CLHEP/Random/SeedTable.h"

namespace CLHEP {

HepRandomEngine* HepRandom::theEngine = 0;
HepRandom* HepRandom::theGenerator = 0;
int HepRandom::isActive = HepRandom::createInstance();

//---------------------------- HepRandom ---------------------------------

HepRandom::HepRandom()
: deleteEngine(false)
{
  createInstance();
}

HepRandom::HepRandom(long seed)
: deleteEngine(false)
{
  createInstance();
  setTheSeed(seed);
}

HepRandom::HepRandom(HepRandomEngine & algorithm)
: deleteEngine(false)
{
  theGenerator = this;
  theEngine = &algorithm;
  isActive = 1;
}

HepRandom::HepRandom(HepRandomEngine * algorithm)
: deleteEngine(true)
{
  createInstance();
  theEngine = algorithm;
}

HepRandom::~HepRandom() {
  if ( deleteEngine ) delete theEngine;
}

double HepRandom::flat()
{
  return theEngine->flat();
}

void HepRandom::flatArray(const int size, double* vect)
{
  theEngine->flatArray(size,vect);
}

double HepRandom::operator()() {
  return flat();
}

// --------------------------
// Static methods definitions
// --------------------------

void HepRandom::setTheSeed(long seed, int lux)
{
  theEngine->setSeed(seed,lux);
}

long HepRandom::getTheSeed()
{
  return theEngine->getSeed();
}

void HepRandom::setTheSeeds(const long* seeds, int aux)
{
  theEngine->setSeeds(seeds,aux);
}

const long* HepRandom::getTheSeeds ()
{
  return theEngine->getSeeds();
}

void HepRandom::getTheTableSeeds(long* seeds, int index)
{
  if ((index >= 0) && (index < 215)) {
    seeds[0] = seedTable[index][0];
    seeds[1] = seedTable[index][1];
  }
  else seeds = NULL;
}

HepRandom * HepRandom::getTheGenerator()
{
  return theGenerator;
}

HepRandomEngine * HepRandom::getTheEngine()
{
  return theEngine;
}

void HepRandom::setTheEngine (HepRandomEngine* theNewEngine)
{
  theEngine = theNewEngine;
}

void HepRandom::saveEngineStatus( const char filename[] )
{
  theEngine->saveStatus( filename );
}  

void HepRandom::restoreEngineStatus( const char filename[] )
{
  theEngine->restoreStatus( filename );
}  

void HepRandom::showEngineStatus()
{
  theEngine->showStatus();
}  

int HepRandom::createInstance()
{
  static HepJamesRandom mainEngine;
  static HepRandom randGen(mainEngine);

  if (theGenerator) return 1;  // should always be true

  return 0;
}

}  // namespace CLHEP
