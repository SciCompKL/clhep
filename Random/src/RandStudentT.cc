#include "CLHEPTypes.hpp"
//
// -*- C++ -*-
//
// -----------------------------------------------------------------------
//                             HEP Random
//                          --- RandStudentT ---
//                      class implementation file
// -----------------------------------------------------------------------

// =======================================================================
// John Marraffino - Created: 12th May 1998
// G.Cosmo         - Fixed minor bug on inline definition for shoot()
//                   methods : 20th Aug 1998
// M Fischler      - put and get to/from streams 12/13/04
// M Fischler	      - put/get to/from streams uses pairs of ulongs when
//			+ storing CLHEPdoubles avoid problems with precision 
//			4/14/05
// =======================================================================

#include <float.h>
#include "CLHEP/Random/defs.h"
#include "CLHEP/Random/RandStudentT.h"
#include "CLHEP/Random/DoubConv.h"

#include <cmath>	// for std::log() std::exp()
#include <iostream>
#include <string>
#include <vector>

namespace CLHEP {

std::string RandStudentT::name() const {return "RandStudentT";}
HepRandomEngine & RandStudentT::engine() {return *localEngine;}

RandStudentT::~RandStudentT()
{
}

CLHEPdouble RandStudentT::operator()() {
  return fire( defaultA );
}

CLHEPdouble RandStudentT::operator()( CLHEPdouble a ) {
  return fire( a );
}

CLHEPdouble RandStudentT::shoot( CLHEPdouble a ) {
/******************************************************************
 *                                                                *
 *           Student-t Distribution - Polar Method                *
 *                                                                *
 ******************************************************************
 *                                                                *
 * The polar method of Box/Muller for generating Normal variates  *
 * is adapted to the Student-t distribution. The two generated    *
 * variates are not independent and the expected no. of uniforms  *
 * per variate is 2.5464.                                         *
 *                                                                *
 ******************************************************************
 *                                                                *
 * FUNCTION :   - tpol  samples a random number from the          *
 *                Student-t distribution with parameter a > 0.    *
 * REFERENCE :  - R.W. Bailey (1994): Polar generation of random  *
 *                variates with the t-distribution, Mathematics   *
 *                of Computation 62, 779-781.                     *
 * SUBPROGRAM : -  ... (0,1)-Uniform generator                    *
 *                                                                *
 *                                                                *
 * Implemented by F. Niederl, 1994                                *
 ******************************************************************/

 CLHEPdouble u,v,w;

// Check for valid input value

 if( a < 0.0) return (DBL_MAX);

 do
 {
	 u = 2.0 * HepRandom::getTheEngine()->flat() - 1.0;
	 v = 2.0 * HepRandom::getTheEngine()->flat() - 1.0;
 }
 while ((w = u * u + v * v) > 1.0);

 return(u * std::sqrt( a * ( std::exp(- 2.0 / a * std::log(w)) - 1.0) / w));
}

void RandStudentT::shootArray( const int size, CLHEPdouble* vect,
                            CLHEPdouble a )
{
  for( CLHEPdouble* v = vect; v != vect + size; ++v )
    *v = shoot(a);
}

void RandStudentT::shootArray( HepRandomEngine* anEngine,
                            const int size, CLHEPdouble* vect,
                            CLHEPdouble a )
{
  for( CLHEPdouble* v = vect; v != vect + size; ++v )
    *v = shoot(anEngine,a);
}

CLHEPdouble RandStudentT::fire( CLHEPdouble a ) {

 CLHEPdouble u,v,w;

 do
 {
	 u = 2.0 * localEngine->flat() - 1.0;
	 v = 2.0 * localEngine->flat() - 1.0;
 }
 while ((w = u * u + v * v) > 1.0);

 return(u * std::sqrt( a * ( std::exp(- 2.0 / a * std::log(w)) - 1.0) / w));
}

void RandStudentT::fireArray( const int size, CLHEPdouble* vect)
{
  for( CLHEPdouble* v = vect; v != vect + size; ++v )
    *v = fire(defaultA);
}

void RandStudentT::fireArray( const int size, CLHEPdouble* vect,
                           CLHEPdouble a )
{
  for( CLHEPdouble* v = vect; v != vect + size; ++v )
    *v = fire(a);
}

CLHEPdouble RandStudentT::shoot( HepRandomEngine *anEngine, CLHEPdouble a ) {

 CLHEPdouble u,v,w;

 do
 {
	 u = 2.0 * anEngine->flat() - 1.0;
	 v = 2.0 * anEngine->flat() - 1.0;
 }
 while ((w = u * u + v * v) > 1.0);

 return(u * std::sqrt( a * ( std::exp(- 2.0 / a * std::log(w)) - 1.0) / w));
}

std::ostream & RandStudentT::put ( std::ostream & os ) const {
  int pr=os.precision(20);
  std::vector<unsigned long> t(2);
  os << " " << name() << "\n";
  os << "Uvec" << "\n";
  t = DoubConv::dto2longs(defaultA);
  os << defaultA << " " << t[0] << " " << t[1] << "\n";
  os.precision(pr);
  return os;
#ifdef REMOVED
  int pr=os.precision(20);
  os << " " << name() << "\n";
  os << defaultA << "\n";
  os.precision(pr);
  return os;
#endif
}

std::istream & RandStudentT::get ( std::istream & is ) {
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
    return is;
  }
  // is >> defaultA encompassed by possibleKeywordInput
  return is;
}

}  // namespace CLHEP
