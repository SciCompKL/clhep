#include "CLHEPTypes.hpp"
#ifndef _AdaptiveRKStepper_h_
#define _AdaptiveRKStepper_h_
#include "CLHEP/GenericFunctions/RKIntegrator.hh"
//
// This is the default RKStepper routine, used within the RKIntegrator
// when no other stepper is provided.  
//
namespace Genfun {

  class AdaptiveRKStepper:public RKIntegrator::RKStepper {
    
  public:
    
    class EEStepper;

    // Constructor. A default stepper is created if none
    // is specified--it is an Embedded Runge Kutta stepper
    // using a Cash-Karp extended Butcher Tableau, which
    // is fourth-order.
    AdaptiveRKStepper(const EEStepper *eeStepper=NULL);

    // Copy constructor:
    AdaptiveRKStepper(const AdaptiveRKStepper & right);

    // Destructor:
    virtual ~AdaptiveRKStepper();

    // Takes *multiple* steps if needed up to or exceeding the
    // specified time.  This called from the RKFunction and not
    // by users.    If a time limit is specified, only one step
    // is taken--this mode is used to interpolate between cached
    // meshpoints.

    // Input:  data contains diffEqn information and cache:
    //         sData a summary of starting point information
    //         timeLimit (if nonzero) time limit for step 
    // Output  dData a summary of into at the ending point.
    // 

    virtual void step (const RKIntegrator::RKData       * data, 
		       const RKIntegrator::RKData::Data & sdata, 
		       RKIntegrator::RKData::Data       & ddata, 
		       CLHEPdouble                             timeLimit) const ;
    // Clone
    virtual AdaptiveRKStepper *clone() const;

    // Accessors and modifiers to algorithmic parameters.  Roughly
    // speaking these are ordered according to importance: the user
    // will often wish to modify the tolerance and the starting 
    // stepsize, but rarely should need to touch any of the others.
    
    // The tolerance:
    CLHEPdouble & tolerance();
    const CLHEPdouble & tolerance() const;

    // The starting stepsize:
    CLHEPdouble & startingStepsize();
    const CLHEPdouble & startingStepsize() const;

    // The safety factor.  Step size increases are moderated by this
    // factor:
    CLHEPdouble & safetyFactor();
    const CLHEPdouble & safetyFactor() const;

    // The minimum amount by which a step size is decreased:
    CLHEPdouble & rmin();
    const CLHEPdouble & rmin() const;

    // The maximum amount by which a step size is increased:
    CLHEPdouble & rmax();
    const CLHEPdouble & rmax() const;
    
    
  private:
    
    // It is illegal to assign an AdaptiveRKStepper:
    AdaptiveRKStepper & operator=(const AdaptiveRKStepper & right);

    const        EEStepper   *eeStepper;
    CLHEPdouble       T;
    CLHEPdouble       sStepsize;
    CLHEPdouble       S;
    CLHEPdouble       Rmin;
    CLHEPdouble       Rmax;
    mutable      CLHEPdouble       stepsize;
  };


  // 
  // An abstract base class for steppers that return an error
  // estimate at each step:
  //
  class AdaptiveRKStepper::EEStepper {
  public:
    
    virtual ~EEStepper();
    virtual void step   (const RKIntegrator::RKData       * data, 
			 const RKIntegrator::RKData::Data & sdata, 
			 RKIntegrator::RKData::Data       & ddata, 
			 std::vector<CLHEPdouble> & errors) const = 0;
    virtual EEStepper *clone() const=0;
    virtual unsigned int order() const=0;
  };
}

#endif
