#include "CLHEPTypes.hpp"
/*
Code adapted from:
http://www.jstatsoft.org/v05/i08/


Original disclaimer:

The ziggurat method for RNOR and REXP
Combine the code below with the main program in which you want
normal or exponential variates.   Then use of RNOR in any expression
will provide a standard normal variate with mean zero, variance 1,
while use of REXP in any expression will provide an exponential variate
with density exp(-x),x>0.
Before using RNOR or REXP in your main, insert a command such as
zigset(86947731 );
with your own choice of seed value>0, rather than 86947731.
(If you do not invoke zigset(...) you will get all zeros for RNOR and REXP.)
For details of the method, see Marsaglia and Tsang, "The ziggurat method
for generating random variables", Journ. Statistical Software.

*/


#ifndef RandGaussZiggurat_h
#define RandGaussZiggurat_h 1

#include "cmath"
#include "CLHEP/Random/defs.h"
#include "CLHEP/Random/RandGauss.h"
#include "CLHEP/Utility/thread_local.h"

namespace CLHEP {

/**
 * @author ATLAS
 * @ingroup random
 */
class RandGaussZiggurat : public RandGauss {

public:

  inline RandGaussZiggurat ( HepRandomEngine& anEngine, CLHEPdouble mean=0.0, CLHEPdouble stdDev=1.0 );
  inline RandGaussZiggurat ( HepRandomEngine* anEngine, CLHEPdouble mean=0.0, CLHEPdouble stdDev=1.0 );

  // Destructor
  virtual ~RandGaussZiggurat();

  // Static methods to shoot random values using the static generator
  
  static inline CLHEPfloat shoot() {return ziggurat_RNOR(HepRandom::getTheEngine());};
  static inline CLHEPfloat shoot( CLHEPfloat mean, CLHEPfloat stdDev ) {return shoot()*stdDev + mean;};

  static void shootArray ( const int size, CLHEPfloat* vect, CLHEPfloat mean=0.0, CLHEPfloat stdDev=1.0 );
  static void shootArray ( const int size, CLHEPdouble* vect, CLHEPdouble mean=0.0, CLHEPdouble stdDev=1.0 );

  //  Static methods to shoot random values using a given engine
  //  by-passing the static generator.

  static inline CLHEPfloat shoot( HepRandomEngine* anotherEngine ) {return ziggurat_RNOR(anotherEngine);};
  static inline CLHEPfloat shoot( HepRandomEngine* anotherEngine, CLHEPfloat mean, CLHEPfloat stdDev ) {return shoot(anotherEngine)*stdDev + mean;};

  static void shootArray ( HepRandomEngine* anotherEngine, const int size, CLHEPfloat* vect, CLHEPfloat mean=0.0, CLHEPfloat stdDev=1.0 );
  static void shootArray ( HepRandomEngine* anotherEngine, const int size, CLHEPdouble* vect, CLHEPdouble mean=0.0, CLHEPdouble stdDev=1.0 );

  //  Instance methods using the localEngine to instead of the static 
  //  generator, and the default mean and stdDev established at construction

  inline CLHEPfloat fire() {return ziggurat_RNOR(localEngine.get()) * defaultStdDev + defaultMean;};

  inline CLHEPfloat fire ( CLHEPfloat mean, CLHEPfloat stdDev ) {return ziggurat_RNOR(localEngine.get()) * stdDev + mean;};
  
  void fireArray  ( const int size, CLHEPfloat* vect);
  void fireArray  ( const int size, CLHEPdouble* vect);
  void fireArray  ( const int size, CLHEPfloat* vect, CLHEPfloat mean, CLHEPfloat stdDev );
  void fireArray  ( const int size, CLHEPdouble* vect, CLHEPdouble mean, CLHEPdouble stdDev );

  virtual CLHEPdouble operator()();
  virtual CLHEPdouble operator()( CLHEPdouble mean, CLHEPdouble stdDev );

  // Save and restore to/from streams
  
  std::ostream & put ( std::ostream & os ) const;
  std::istream & get ( std::istream & is );

  std::string name() const;
  HepRandomEngine & engine();

  static std::string distributionName() {return "RandGaussZiggurat";}  
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
  //#define RNOR (hz=SHR3, iz=hz&127, (std::fabs(hz)<kn[iz])? hz*wn[iz] : nfix())
  //#define REXP (jz=SHR3, iz=jz&255, (    jz <ke[iz])? jz*we[iz] : efix())

  static CLHEP_THREAD_LOCAL unsigned long kn[128], ke[256];
  static CLHEP_THREAD_LOCAL CLHEPfloat wn[128],fn[128], we[256],fe[256];

  static CLHEP_THREAD_LOCAL bool ziggurat_is_init;
  
  static inline unsigned long ziggurat_SHR3(HepRandomEngine* anEngine) {return (unsigned int)(*anEngine);};
  static inline CLHEPfloat ziggurat_UNI(HepRandomEngine* anEngine) {return anEngine->flat();};
  static inline CLHEPfloat ziggurat_RNOR(HepRandomEngine* anEngine) {
    if(!ziggurat_is_init) ziggurat_init();
    long hz=(signed)ziggurat_SHR3(anEngine);
    unsigned long iz=hz&127;
    return ((unsigned long)std::abs(hz)<kn[iz]) ? hz*wn[iz] : ziggurat_nfix(hz,anEngine);
  };
  static CLHEPfloat ziggurat_nfix(long hz,HepRandomEngine* anEngine);
  
private:

  // Private copy constructor. Defining it here disallows use.
  RandGaussZiggurat(const RandGaussZiggurat& d);

  // All the engine info, and the default mean and sigma, are in the RandGauss
  // base class.

};

}  // namespace CLHEP

#ifdef ENABLE_BACKWARDS_COMPATIBILITY
//  backwards compatibility will be enabled ONLY in CLHEP 1.9
using namespace CLHEP;
#endif

namespace CLHEP {

RandGaussZiggurat::RandGaussZiggurat(HepRandomEngine & anEngine, CLHEPdouble mean,CLHEPdouble stdDev ): RandGauss(anEngine, mean, stdDev) 
{
}

RandGaussZiggurat::RandGaussZiggurat(HepRandomEngine * anEngine, CLHEPdouble mean,CLHEPdouble stdDev ): RandGauss(anEngine, mean, stdDev) 
{
}

}  // namespace CLHEP

#endif
