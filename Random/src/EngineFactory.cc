#include "CLHEPTypes.hpp"
// $Id: 
// -*- C++ -*-
//
// -----------------------------------------------------------------------
//                             HEP Random
//                      --- EngineFactory ---
//                      class implementation file
// -----------------------------------------------------------------------
//
// =======================================================================
// Mark Fischler  - Created: Dec. 21, 2004
// =======================================================================

#include "CLHEP/Random/defs.h"
#include "CLHEP/Random/EngineFactory.h"
#include "CLHEP/Random/DRand48Engine.h"
#include "CLHEP/Random/DualRand.h"
#include "CLHEP/Random/Hurd160Engine.h"
#include "CLHEP/Random/Hurd288Engine.h"
#include "CLHEP/Random/JamesRandom.h"
#include "CLHEP/Random/JamesRandom.h"
#include "CLHEP/Random/MixMaxRng.h"
#include "CLHEP/Random/MTwistEngine.h"
#include "CLHEP/Random/RandEngine.h"
#include "CLHEP/Random/RanecuEngine.h"
#include "CLHEP/Random/Ranlux64Engine.h"
#include "CLHEP/Random/RanluxppEngine.h"
#include "CLHEP/Random/RanluxEngine.h"
#include "CLHEP/Random/RanshiEngine.h"
#include "CLHEP/Random/TripleRand.h"
#include "CLHEP/Random/NonRandomEngine.h"
#include "CLHEP/Random/engineIDulong.h"
#include <iostream>
#include <string>
#include <vector>

namespace CLHEP {

template<class E>
static HepRandomEngine* 
makeAnEngine (const std::string & tag, 
              std::istream & is) {
  if ( tag != E::beginTag() ) return 0;
  HepRandomEngine* eptr = new E;
  eptr->getState(is);
  if (!is) return 0;
  return eptr;	      
}	      

template<class E>
static HepRandomEngine* 
makeAnEngine (const std::vector<unsigned long> & v) {
  if ( (v[0] & 0xffffffffUL) != engineIDulong<E>() ) return 0;
  HepRandomEngine* eptr = new E;
  bool success = eptr->getState(v);
  if (!success) return 0;
  // std::cerr << "makeAnEngine made " << E::engineName() << "\n"; 
  return eptr;	      
}	      

HepRandomEngine* EngineFactory::newEngine(std::istream& is) {
  HepRandomEngine* eptr; 
  std::string tag;
  is >> tag;
  eptr = makeAnEngine <HepJamesRandom>  (tag, is); if (eptr) return eptr;
  eptr = makeAnEngine <RanecuEngine>    (tag, is); if (eptr) return eptr;
  eptr = makeAnEngine <Ranlux64Engine>  (tag, is); if (eptr) return eptr;
  eptr = makeAnEngine <RanluxppEngine>  (tag, is); if (eptr) return eptr;
  eptr = makeAnEngine <MixMaxRng>       (tag, is); if (eptr) return eptr;
  eptr = makeAnEngine <MTwistEngine>    (tag, is); if (eptr) return eptr;
  eptr = makeAnEngine <DRand48Engine>   (tag, is); if (eptr) return eptr;
  eptr = makeAnEngine <TripleRand>      (tag, is); if (eptr) return eptr;
  eptr = makeAnEngine <DualRand>        (tag, is); if (eptr) return eptr;
  eptr = makeAnEngine <Hurd160Engine>   (tag, is); if (eptr) return eptr;
  eptr = makeAnEngine <Hurd288Engine>   (tag, is); if (eptr) return eptr;
  eptr = makeAnEngine <RandEngine>      (tag, is); if (eptr) return eptr;
  eptr = makeAnEngine <RanluxEngine>    (tag, is); if (eptr) return eptr;
  eptr = makeAnEngine <RanshiEngine>    (tag, is); if (eptr) return eptr;
  eptr = makeAnEngine <NonRandomEngine> (tag, is); if (eptr) return eptr;
  is.clear(std::ios::badbit | is.rdstate());
  std::cerr << 
  	"Input mispositioned or bad in reading anonymous engine\n"
	    << "\nBegin-tag read was: " << tag 
	    << "\nInput stream is probably fouled up\n";
  return eptr;
}

HepRandomEngine* 
EngineFactory::newEngine(std::vector<unsigned long> const & v) {
  HepRandomEngine* eptr; 
  eptr = makeAnEngine <HepJamesRandom>  (v); if (eptr) return eptr;
  eptr = makeAnEngine <RanecuEngine>    (v); if (eptr) return eptr;
  eptr = makeAnEngine <Ranlux64Engine>  (v); if (eptr) return eptr;
  eptr = makeAnEngine <RanluxppEngine>  (v); if (eptr) return eptr;
  eptr = makeAnEngine <MixMaxRng>       (v); if (eptr) return eptr;
  eptr = makeAnEngine <MTwistEngine>    (v); if (eptr) return eptr;
  eptr = makeAnEngine <DRand48Engine>   (v); if (eptr) return eptr;
  eptr = makeAnEngine <TripleRand>      (v); if (eptr) return eptr;
  eptr = makeAnEngine <DualRand>        (v); if (eptr) return eptr;
  eptr = makeAnEngine <Hurd160Engine>   (v); if (eptr) return eptr;
  eptr = makeAnEngine <Hurd288Engine>   (v); if (eptr) return eptr;
  eptr = makeAnEngine <RandEngine>      (v); if (eptr) return eptr;
  eptr = makeAnEngine <RanluxEngine>    (v); if (eptr) return eptr;
  eptr = makeAnEngine <RanshiEngine>    (v); if (eptr) return eptr;
  eptr = makeAnEngine <NonRandomEngine> (v); if (eptr) return eptr;
  std::cerr << 
  	"Cannot correctly get anonymous engine from vector\n"
	    << "First unsigned long was: " << v[0] 
	    << " Vector size was: " << v.size() <<"\n";
  return eptr;
}

}  // namespace CLHEP

