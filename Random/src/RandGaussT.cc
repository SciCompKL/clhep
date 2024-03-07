#include "CLHEPTypes.hpp"
// $Id: RandGaussT.cc,v 1.5 2010/06/16 17:24:53 garren Exp $
// -*- C++ -*-
//
// -----------------------------------------------------------------------
//                             HEP Random
//                          --- RandGaussT ---
//                      class implementation file
// -----------------------------------------------------------------------

// =======================================================================
// M Fischler	  - Created 04 Feb 2000
// M Fischler     - put and get to/from streams 12/13/04
// M Fischler	  - operator() modified to use localEngine 12/13/04
// =======================================================================

#include "CLHEP/Random/defs.h"
#include "CLHEP/Random/RandGaussT.h"
#include <iostream>

namespace CLHEP {

std::string RandGaussT::name() const {return "RandGaussT";}
HepRandomEngine & RandGaussT::engine() {return RandGauss::engine();}

RandGaussT::~RandGaussT() {
}

CLHEPdouble RandGaussT::operator()() {
  return HepStat::flatToGaussian(localEngine->flat()) * defaultStdDev 
								+ defaultMean;
}

CLHEPdouble RandGaussT::operator()( CLHEPdouble mean, CLHEPdouble stdDev ) {
  return HepStat::flatToGaussian(localEngine->flat()) * stdDev + mean;
}

void RandGaussT::shootArray( const int size, CLHEPdouble* vect,
                            CLHEPdouble mean, CLHEPdouble stdDev )
{
  for( CLHEPdouble* v = vect; v != vect + size; ++v )
    *v = shoot(mean,stdDev);
}

void RandGaussT::shootArray( HepRandomEngine* anEngine,
                            const int size, CLHEPdouble* vect,
                            CLHEPdouble mean, CLHEPdouble stdDev )
{
  for( CLHEPdouble* v = vect; v != vect + size; ++v )
    *v = shoot(anEngine,mean,stdDev);
}

void RandGaussT::fireArray( const int size, CLHEPdouble* vect)
{
  for( CLHEPdouble* v = vect; v != vect + size; ++v )
    *v = fire( defaultMean, defaultStdDev );
}

void RandGaussT::fireArray( const int size, CLHEPdouble* vect,
                           CLHEPdouble mean, CLHEPdouble stdDev )
{
  for( CLHEPdouble* v = vect; v != vect + size; ++v )
    *v = fire( mean, stdDev );
}

std::ostream & RandGaussT::put ( std::ostream & os ) const {
  int pr=os.precision(20);
  os << " " << name() << "\n";
  RandGauss::put(os);
  os.precision(pr);
  return os;
}

std::istream & RandGaussT::get ( std::istream & is ) {
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
  RandGauss::get(is);
  return is;
}

}  // namespace CLHEP

