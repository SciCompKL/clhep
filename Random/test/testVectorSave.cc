#include "CLHEPTypes.hpp"
// -*- C++ -*-
// $Id: testVectorSave.cc,v 1.3 2010/06/16 17:24:53 garren Exp $
// ----------------------------------------------------------------------
#include "CLHEP/Random/Randomize.h"
#include "CLHEP/Random/NonRandomEngine.h"
#include "CLHEP/Random/defs.h"
#include <iostream>
#include <iomanip>
#include <vector>

#define CLEAN_OUTPUT
#ifdef CLEAN_OUTPUT
  std::ofstream output("testVectorSave.cout");  
#else
  std::ostream & output = std::cout;
#endif

// Normally on  for routine validation:

#ifdef TURNOFF
#endif

#define TEST_VECTOR_ENGINE_RESTORE

#define VERBOSER
#define VERBOSER2

using namespace CLHEP;

// Absolutely Safe Equals Without Registers Screwing Us Up
bool equals01(const std::vector<CLHEPdouble> &ab) {
  return ab[1]==ab[0];
}  
bool equals(CLHEPdouble a, CLHEPdouble b) {
  std::vector<CLHEPdouble> ab(2);
  ab[0]=a;  ab[1]=b;
  return (equals01(ab));
}

std::vector<CLHEPdouble> aSequence(int n) {
  std::vector<CLHEPdouble> v;
  DualRand e(13542);
  RandFlat f(e);
  for (int i=0; i<n; i++) {
    v.push_back(f()); 
  }
  return v;
}


// ----------- Vector restore of engines -----------

// test the problem reported in bug #44156
// Note that this test always works on a 32bit machine
template <class E>
int vectorTest64(int n) {
  output << "Vector restore 64bit test for " << E::engineName() << "\n";

  E e;				    
  CLHEPdouble x = 0;	
  for (int i=0; i<n; i++) x += e.flat();	    
  std::vector<unsigned long> v = e.put();
  x = e.flat();
  output << "x = " << x << std::endl;

  E f;
  v[0] &= 0xffffffffUL;
  f.get(v);
  CLHEPdouble y = f.flat();
  output << "y = " << y << std::endl;
  if( x != y ) return n;

  return 0;
}
// special case for NonRandomEngine
template <>
int vectorTest64<NonRandomEngine>(int n) {
  output << "Vector restore 64bit test for " << NonRandomEngine::engineName() << "\n";

  std::vector<CLHEPdouble> nonRand = aSequence(500);
  NonRandomEngine e; 
  e.setRandomSequence(&nonRand[0], nonRand.size());

  CLHEPdouble x = 0;	
  for (int i=0; i<n; i++) x += e.flat();	    
  std::vector<unsigned long> v = e.put();
  x = e.flat();
  output << "x = " << x << std::endl;

  NonRandomEngine f;
  f.setRandomSequence(&nonRand[0], nonRand.size());

  v[0] &= 0xffffffffUL;
  f.get(v);
  CLHEPdouble y = f.flat();
  output << "y = " << y << std::endl;
  if( x != y ) return n;

  return 0;
}

template <class E>
std::vector<unsigned long> vectorRestore1(int n, std::vector<CLHEPdouble> & v) {
  output << "Vector restore for " << E::engineName() << "\n";
  E e(97538466);				    
  CLHEPdouble r=0;					    
  for (int i=0; i<n; i++) r += e.flat();	    
  std::vector<unsigned long> state = e.put();	    
  for (int j=0; j<25; j++) v.push_back(e.flat());   
#ifdef VERBOSER2
  output << "First four of v are: " 
    	<< v[0] << ",  " << v[1] << ",  " << v[2] << ",  " << v[3] << "\n";
#endif
  return state;
}

template <>
std::vector<unsigned long>
vectorRestore1<NonRandomEngine> (int n, std::vector<CLHEPdouble> & v) {
#ifdef VERBOSER2
  output << "Vector restore for " << NonRandomEngine::engineName() << "\n";
#endif
  std::vector<CLHEPdouble> nonRand = aSequence(500);
  NonRandomEngine e; 
  e.setRandomSequence(&nonRand[0], nonRand.size());
  CLHEPdouble r=0;
  for (int i=0; i<n; i++) r += e.flat();
  std::vector<unsigned long> state = e.put();	    
  for (int j=0; j<25; j++) v.push_back(e.flat()); 
#ifdef VERBOSER2
  output << "First four of v are: " 
    	<< v[0] << ",  " << v[1] << ",  " << v[2] << ",  " << v[3] << "\n";
#endif
  return state;
}

template <class E>
int vectorRestore2(const std::vector<unsigned long> state,
		   const std::vector<CLHEPdouble> & v) {
  int stat = 0;
  std::vector<CLHEPdouble> k;
  HepRandomEngine * a;
  a = HepRandomEngine::newEngine(state);
  if (!a) {
      std::cout << "???? could not restore engine state from vector for " 
    		<< E::engineName() << "\n"; 
      #ifdef CLEAN_OUTPUT
      output << "???? could not restore engine state from vector for " 
             << E::engineName() << "\n"; 
      #endif
      stat |= 1048576;
      return stat;
  }
  if (a->name() != E::engineName()) {
      #ifdef CLEAN_OUTPUT
      std::cout << "???? restored engine state from vector for " 
    		<< E::engineName() << "to different type of engine: "
		<< a->name() << "\n"
	<< "There is probably a clash in CRC hashes for these two names!\n"; 
      output << "???? restored engine state from vector for " 
    		<< E::engineName() << "to different type of engine: "
		<< a->name() << "\n"
	<< "There is probably a clash in CRC hashes for these two names!\n"; 
      #endif
      stat |= 1048576;
      return stat;
  }
  for (int j=0; j<25; j++) k.push_back(a->flat());
  delete a;
#ifdef VERBOSER2
  output << "First four of k are: " 
    	<< k[0] << ",  " << k[1] << ",  " << k[2] << ",  " << k[3] << "\n";
#endif
  for (int m=0; m<25; m++) {
    if ( v[m] != k[m] ) {
      std::cout << "???? Incorrect vector restored value for anonymous engine: " 
    		<< E::engineName() << "\n"; 
      #ifdef CLEAN_OUTPUT
      output << "???? Incorrect vector restored value for anonymous engine: " 
    		<< E::engineName() << "\n"; 
      #endif
      stat |= 1048576;
      return stat;
    }
  }
  return stat;       
}


template <class E>
int vectorRestore(int n) {
  std::vector<CLHEPdouble> v;
  int status1 = vectorTest64<E>(n);
  std::vector<unsigned long> state = vectorRestore1<E>(n,v);
  int status2 = vectorRestore2<E>(state, v);  
  return (status1 | status2);  
}



// ---------------------------------------------
// ---------------------------------------------
// ---------------------------------------------


int main() {
  int stat = 0;

#ifdef TEST_VECTOR_ENGINE_RESTORE
  output << "\n=================================\n";
  output << "         Part IX \n";
  output << "Save/restore of engines to vectors\n";
  output << "=================================\n\n";

  stat |= vectorRestore<DualRand>(113);
  stat |= vectorRestore<DRand48Engine>(114);
  stat |= vectorRestore<Hurd160Engine>(115);
  stat |= vectorRestore<Hurd288Engine>(116);
  stat |= vectorRestore<HepJamesRandom>(117);
  stat |= vectorRestore<MTwistEngine>(118);
  stat |= vectorRestore<RanecuEngine>(139);
  stat |= vectorRestore<Ranlux64Engine>(119);
  stat |= vectorRestore<RanluxEngine>(120);
  stat |= vectorRestore<RanshiEngine>(121);
  stat |= vectorRestore<TripleRand>(122);
  stat |= vectorRestore<NonRandomEngine>(123);
  stat |= vectorRestore<RandEngine>(129);
#endif

  output << "\n=============================================\n\n";

  if (stat != 0) {
     std::cout << "One or more problems detected: stat = " << stat << "\n";
     output << "One or more problems detected: stat = " << stat << "\n";
  }  else {
     output << "ranRestoreTest passed with no problems detected.\n";    
  }

  if (stat == 0) return 0;
  if (stat > 0) return -(stat|1);
  return stat|1;
}	

