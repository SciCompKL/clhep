#include "CLHEPTypes.hpp"
//
// -*- C++ -*-
//
// -----------------------------------------------------------------------
//                             HEP Random
//                       --- RandBreitWigner ---
//                      class implementation file
// -----------------------------------------------------------------------
// This file is part of Geant4 (simulation toolkit for HEP).

// =======================================================================
// Gabriele Cosmo - Created: 5th September 1995
//                - Added methods to shoot arrays: 28th July 1997
// J.Marraffino   - Added default arguments as attributes and
//                  operator() with arguments: 16th Feb 1998
// M Fischler     - put and get to/from streams 12/10/04
// M Fischler	      - put/get to/from streams uses pairs of ulongs when
//			+ storing CLHEPdoubles avoid problems with precision 
//			4/14/05
// =======================================================================

#include "CLHEP/Random/defs.h"
#include "CLHEP/Random/RandBreitWigner.h"
#include "CLHEP/Units/PhysicalConstants.h"
#include "CLHEP/Random/DoubConv.h"
#include <algorithm>	// for min() and max()
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

namespace CLHEP {

std::string RandBreitWigner::name() const {return "RandBreitWigner";}
HepRandomEngine & RandBreitWigner::engine() {return *localEngine;}

RandBreitWigner::~RandBreitWigner() {
}

CLHEPdouble RandBreitWigner::operator()() {
   return fire( defaultA, defaultB );
}

CLHEPdouble RandBreitWigner::operator()( CLHEPdouble a, CLHEPdouble b ) {
   return fire( a, b );
}

CLHEPdouble RandBreitWigner::operator()( CLHEPdouble a, CLHEPdouble b, CLHEPdouble c ) {
   return fire( a, b, c );
}

CLHEPdouble RandBreitWigner::shoot(CLHEPdouble mean, CLHEPdouble gamma)
{
   CLHEPdouble rval, displ;

   rval = 2.0*HepRandom::getTheEngine()->flat()-1.0;
   displ = 0.5*gamma*std::tan(rval*CLHEP::halfpi);

   return mean + displ;
}

CLHEPdouble RandBreitWigner::shoot(CLHEPdouble mean, CLHEPdouble gamma, CLHEPdouble cut)
{
   CLHEPdouble val, rval, displ;

   if ( gamma == 0.0 ) return mean;
   val = std::atan(2.0*cut/gamma);
   rval = 2.0*HepRandom::getTheEngine()->flat()-1.0;
   displ = 0.5*gamma*std::tan(rval*val);

   return mean + displ;
}

CLHEPdouble RandBreitWigner::shootM2(CLHEPdouble mean, CLHEPdouble gamma )
{
   CLHEPdouble val, rval, displ;

   if ( gamma == 0.0 ) return mean;
   val = std::atan(-mean/gamma);
   rval = RandFlat::shoot(val, CLHEP::halfpi);
   displ = gamma*std::tan(rval);

   return std::sqrt(mean*mean + mean*displ);
}

CLHEPdouble RandBreitWigner::shootM2(CLHEPdouble mean, CLHEPdouble gamma, CLHEPdouble cut )
{
   CLHEPdouble rval, displ;
   CLHEPdouble lower, upper, tmp;

   if ( gamma == 0.0 ) return mean;
   tmp = std::max(0.0,(mean-cut));
   lower = std::atan( (tmp*tmp-mean*mean)/(mean*gamma) );
   upper = std::atan( ((mean+cut)*(mean+cut)-mean*mean)/(mean*gamma) );
   rval = RandFlat::shoot(lower, upper);
   displ = gamma*std::tan(rval);

   return std::sqrt(std::max(0.0, mean*mean + mean*displ));
}

void RandBreitWigner::shootArray ( const int size, CLHEPdouble* vect )
{
  for( CLHEPdouble* v = vect; v != vect + size; ++v )
    *v = shoot( 1.0, 0.2 );
}

void RandBreitWigner::shootArray ( const int size, CLHEPdouble* vect,
                                   CLHEPdouble a, CLHEPdouble b )
{
  for( CLHEPdouble* v = vect; v != vect + size; ++v )
    *v = shoot( a, b );
}

void RandBreitWigner::shootArray ( const int size, CLHEPdouble* vect,
                                   CLHEPdouble a, CLHEPdouble b,
                                   CLHEPdouble c )
{
  for( CLHEPdouble* v = vect; v != vect + size; ++v )
    *v = shoot( a, b, c );
}

//----------------

CLHEPdouble RandBreitWigner::shoot(HepRandomEngine* anEngine,
                                 CLHEPdouble mean, CLHEPdouble gamma)
{
   CLHEPdouble rval, displ;

   rval = 2.0*anEngine->flat()-1.0;
   displ = 0.5*gamma*std::tan(rval*CLHEP::halfpi);

   return mean + displ;
}

CLHEPdouble RandBreitWigner::shoot(HepRandomEngine* anEngine,
                                 CLHEPdouble mean, CLHEPdouble gamma, CLHEPdouble cut )
{
   CLHEPdouble val, rval, displ;

   if ( gamma == 0.0 ) return mean;
   val = std::atan(2.0*cut/gamma);
   rval = 2.0*anEngine->flat()-1.0;
   displ = 0.5*gamma*std::tan(rval*val);

   return mean + displ;
}

CLHEPdouble RandBreitWigner::shootM2(HepRandomEngine* anEngine,
                                   CLHEPdouble mean, CLHEPdouble gamma )
{
   CLHEPdouble val, rval, displ;

   if ( gamma == 0.0 ) return mean;
   val = std::atan(-mean/gamma);
   rval = RandFlat::shoot(anEngine,val, CLHEP::halfpi);
   displ = gamma*std::tan(rval);

   return std::sqrt(mean*mean + mean*displ);
}

CLHEPdouble RandBreitWigner::shootM2(HepRandomEngine* anEngine,
                                   CLHEPdouble mean, CLHEPdouble gamma, CLHEPdouble cut )
{
   CLHEPdouble rval, displ;
   CLHEPdouble lower, upper, tmp;

   if ( gamma == 0.0 ) return mean;
   tmp = std::max(0.0,(mean-cut));
   lower = std::atan( (tmp*tmp-mean*mean)/(mean*gamma) );
   upper = std::atan( ((mean+cut)*(mean+cut)-mean*mean)/(mean*gamma) );
   rval = RandFlat::shoot(anEngine, lower, upper);
   displ = gamma*std::tan(rval);

   return std::sqrt( std::max(0.0, mean*mean+mean*displ) );
}

void RandBreitWigner::shootArray ( HepRandomEngine* anEngine,
                                   const int size, CLHEPdouble* vect )
{
  for( CLHEPdouble* v = vect; v != vect + size; ++v )
    *v = shoot( anEngine, 1.0, 0.2 );
}

void RandBreitWigner::shootArray ( HepRandomEngine* anEngine,
                                   const int size, CLHEPdouble* vect,
                                   CLHEPdouble a, CLHEPdouble b )
{
  for( CLHEPdouble* v = vect; v != vect + size; ++v )
    *v = shoot( anEngine, a, b );
}

void RandBreitWigner::shootArray ( HepRandomEngine* anEngine,
                                   const int size, CLHEPdouble* vect,
                                   CLHEPdouble a, CLHEPdouble b, CLHEPdouble c )
{
  for( CLHEPdouble* v = vect; v != vect + size; ++v )
    *v = shoot( anEngine, a, b, c );
}

//----------------

CLHEPdouble RandBreitWigner::fire()
{
  return fire( defaultA, defaultB );
}

CLHEPdouble RandBreitWigner::fire(CLHEPdouble mean, CLHEPdouble gamma)
{
   CLHEPdouble rval, displ;

   rval = 2.0*localEngine->flat()-1.0;
   displ = 0.5*gamma*std::tan(rval*CLHEP::halfpi);

   return mean + displ;
}

CLHEPdouble RandBreitWigner::fire(CLHEPdouble mean, CLHEPdouble gamma, CLHEPdouble cut)
{
   CLHEPdouble val, rval, displ;

   if ( gamma == 0.0 ) return mean;
   val = std::atan(2.0*cut/gamma);
   rval = 2.0*localEngine->flat()-1.0;
   displ = 0.5*gamma*std::tan(rval*val);

   return mean + displ;
}

CLHEPdouble RandBreitWigner::fireM2()
{
  return fireM2( defaultA, defaultB );
}

CLHEPdouble RandBreitWigner::fireM2(CLHEPdouble mean, CLHEPdouble gamma )
{
   CLHEPdouble val, rval, displ;

   if ( gamma == 0.0 ) return mean;
   val = std::atan(-mean/gamma);
   rval = RandFlat::shoot(localEngine.get(),val, CLHEP::halfpi);
   displ = gamma*std::tan(rval);

   return std::sqrt(mean*mean + mean*displ);
}

CLHEPdouble RandBreitWigner::fireM2(CLHEPdouble mean, CLHEPdouble gamma, CLHEPdouble cut )
{
   CLHEPdouble rval, displ;
   CLHEPdouble lower, upper, tmp;

   if ( gamma == 0.0 ) return mean;
   tmp = std::max(0.0,(mean-cut));
   lower = std::atan( (tmp*tmp-mean*mean)/(mean*gamma) );
   upper = std::atan( ((mean+cut)*(mean+cut)-mean*mean)/(mean*gamma) );
   rval = RandFlat::shoot(localEngine.get(),lower, upper);
   displ = gamma*std::tan(rval);

   return std::sqrt(std::max(0.0, mean*mean + mean*displ));
}

void RandBreitWigner::fireArray ( const int size, CLHEPdouble* vect)
{
  for( CLHEPdouble* v = vect; v != vect + size; ++v )
    *v = fire(defaultA, defaultB );
}

void RandBreitWigner::fireArray ( const int size, CLHEPdouble* vect,
                                  CLHEPdouble a, CLHEPdouble b )
{
  for( CLHEPdouble* v = vect; v != vect + size; ++v )
    *v = fire( a, b );
}

void RandBreitWigner::fireArray ( const int size, CLHEPdouble* vect,
                                  CLHEPdouble a, CLHEPdouble b, CLHEPdouble c )
{
  for( CLHEPdouble* v = vect; v != vect + size; ++v )
    *v = fire( a, b, c );
}


std::ostream & RandBreitWigner::put ( std::ostream & os ) const {
  int pr=os.precision(20);
  std::vector<unsigned long> t(2);
  os << " " << name() << "\n";
  os << "Uvec" << "\n";
  t = DoubConv::dto2longs(defaultA);
  os << defaultA << " " << t[0] << " " << t[1] << "\n";
  t = DoubConv::dto2longs(defaultB);
  os << defaultB << " " << t[0] << " " << t[1] << "\n";
  os.precision(pr);
  return os;
#ifdef REMOVED
  int pr=os.precision(20);
  os << " " << name() << "\n";
  os << defaultA << " " << defaultB << "\n";
  os.precision(pr);
  return os;
#endif
}

std::istream & RandBreitWigner::get ( std::istream & is ) {
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
  if (possibleKeywordInput(is, "Uvec", defaultA)) {
    std::vector<unsigned long> t(2);
    is >> defaultA >> t[0] >> t[1]; defaultA = DoubConv::longs2CLHEPdouble(t); 
    is >> defaultB >> t[0] >> t[1]; defaultB = DoubConv::longs2CLHEPdouble(t); 
    return is;
  }
  // is >> defaultA encompassed by possibleKeywordInput
  is >> defaultB;
  return is;
}


}  // namespace CLHEP

