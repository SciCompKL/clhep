#include "CLHEPTypes.hpp"
//
// -*- C++ -*-
//
// -----------------------------------------------------------------------
//                             HEP Random
//                       --- RandExponential ---
//                      class implementation file
// -----------------------------------------------------------------------
// This file is part of Geant4 (simulation toolkit for HEP).

// =======================================================================
// Gabriele Cosmo - Created: 17th May 1996
//                - Added methods to shoot arrays: 28th July 1997
// J.Marraffino   - Added default mean as attribute and
//                  operator() with mean: 16th Feb 1998
// M Fischler      - put and get to/from streams 12/15/04
// M Fischler	      - put/get to/from streams uses pairs of ulongs when
//			+ storing CLHEPdoubles avoid problems with precision 
//			4/14/05
// =======================================================================

#include "CLHEP/Random/defs.h"
#include "CLHEP/Random/RandExponential.h"
#include "CLHEP/Random/DoubConv.h"
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

namespace CLHEP {

std::string RandExponential::name() const {return "RandExponential";}
HepRandomEngine & RandExponential::engine() {return *localEngine;}

RandExponential::~RandExponential() {
}

CLHEPdouble RandExponential::operator()() {
  return fire( defaultMean );
}

CLHEPdouble RandExponential::operator()( CLHEPdouble mean ) {
  return fire( mean );
}

CLHEPdouble RandExponential::shoot() {
  return -std::log(HepRandom::getTheEngine()->flat());
}

CLHEPdouble RandExponential::shoot(CLHEPdouble mean) {
  return -std::log(HepRandom::getTheEngine()->flat())*mean;
}

void RandExponential::shootArray( const int size, CLHEPdouble* vect,
                                  CLHEPdouble mean )
{
  for( CLHEPdouble* v = vect; v != vect+size; ++v )
    *v = shoot(mean);
}

void RandExponential::shootArray(HepRandomEngine* anEngine, const int size,
                                   CLHEPdouble* vect, CLHEPdouble mean )
{
  for( CLHEPdouble* v = vect; v != vect+size; ++v )
    *v = shoot(anEngine, mean);
}

void RandExponential::fireArray( const int size, CLHEPdouble* vect)
{
  for( CLHEPdouble* v = vect; v != vect+size; ++v )
    *v = fire( defaultMean );
}

void RandExponential::fireArray( const int size, CLHEPdouble* vect,
                                 CLHEPdouble mean )
{
  for( CLHEPdouble* v = vect; v != vect+size; ++v )
    *v = fire( mean );
}

std::ostream & RandExponential::put ( std::ostream & os ) const {
  int pr=os.precision(20);
  std::vector<unsigned long> t(2);
  os << " " << name() << "\n";
  os << "Uvec" << "\n";
  t = DoubConv::dto2longs(defaultMean);
  os << defaultMean << " " << t[0] << " " << t[1] << "\n";
  os.precision(pr);
  return os;
#ifdef REMOVED
  int pr=os.precision(20);
  os << " " << name() << "\n";
  os << defaultMean << "\n";
  os.precision(pr);
  return os;
#endif
}

std::istream & RandExponential::get ( std::istream & is ) {
  std::string inName;
  is >> inName;
  if (inName != name()) {
    is.clear(std::ios::badbit | is.rdstate());
    std::cerr << "Mismatch when expecting to read state of a "
    	      << name() << " distribution\n"
	      << "Name found was " << inName
	      << "\nistream is left in the badbit state\n";
    return is;
  }
  if (possibleKeywordInput(is, "Uvec", defaultMean)) {
    std::vector<unsigned long> t(2);
    is >> defaultMean >> t[0] >> t[1]; defaultMean = DoubConv::longs2CLHEPdouble(t); 
    return is;
  }
  // is >> defaultMean encompassed by possibleKeywordInput
  return is;
}


}  // namespace CLHEP
