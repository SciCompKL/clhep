#include "CLHEPTypes.hpp"
#include "CLHEP/GenericFunctions/AdaptiveRKStepper.hh"
#include "CLHEP/GenericFunctions/EmbeddedRKStepper.hh"

#include <cmath>
#include <stdexcept>
#include <vector>

namespace Genfun {

  AdaptiveRKStepper::AdaptiveRKStepper(const EEStepper *stepper):
    eeStepper(stepper ? stepper->clone():new EmbeddedRKStepper()),
    T(1.0E-6),
    sStepsize(0.01),
    S(0.9),
    Rmin(0.0),
    Rmax(5.0),
    stepsize(sStepsize)
  {
  }

  AdaptiveRKStepper::AdaptiveRKStepper(const AdaptiveRKStepper & right):
    RKStepper(right),
    eeStepper(right.eeStepper->clone()),
    T(right.T),
    sStepsize(right.sStepsize),
    S(right.S),
    Rmin(right.Rmin),
    Rmax(right.Rmax),
    stepsize(right.sStepsize)
  {
  }


  void AdaptiveRKStepper::step(const RKIntegrator::RKData       * data, 
			      const RKIntegrator::RKData::Data & s, 
			      RKIntegrator::RKData::Data       & d,
			      CLHEPdouble                             timeLimit) const {
    //
    // Adaptive stepsize control
    //
    if (s.time==0.0) {
      stepsize=sStepsize;
    }
    const unsigned int p = eeStepper->order();              // Order of the stepper
    const CLHEPdouble deltaMax = T*std::pow(S/Rmax, (int)(p+1)); // Maximum error 4 adjustment.
    const CLHEPdouble TINY   = 1.0E-30;                          // Denominator regularization
    CLHEPdouble hnext;
    //
    // Time limited step ? 
    // 
    d.time= timeLimit==0? s.time+stepsize : timeLimit;

    //--------------------------------------//
    // Take one step, from s to d:    //
    //--------------------------------------//
    CLHEPdouble h = d.time-s.time;
    while (1) {
      std::vector<CLHEPdouble> errors;
      eeStepper->step(data, s, d, errors);
      if (timeLimit!=0.0) return;
      
      // Take absolute value:
      for (size_t e=0;e<errors.size();e++) errors[e] = fabs(errors[e]);
    
      // Select the largest:
      CLHEPdouble delta = (*std::max_element(errors.begin(),errors.end()));
      if (delta > T) {
	//
	// Bail out and try a smaller step.
	//
	h = std::max(S*h*std::pow(T/(delta + TINY), 1.0/(p+1)),Rmin*h);
	if  (!(((CLHEPdouble) (s.time+h) - (CLHEPdouble) s.time) > 0) ) {
	  throw std::runtime_error("Warning, RK Integrator step underflow");
	}
	d.time = s.time+h;
	hnext=h;
	continue;
      }
      else {
	if (delta < deltaMax) {
	  hnext = S*h*std::pow(T/(delta + TINY),1.0/(p+1));
	  // stepsize is supposed to increase;
	  if (hnext<h) hnext=h;
	}
	else {
	  hnext = Rmax*h;
	}
      }
      break;
    }
    stepsize=hnext;
    return;
  }
  


  AdaptiveRKStepper::~AdaptiveRKStepper(){
    delete eeStepper;
  }
  
  AdaptiveRKStepper *AdaptiveRKStepper::clone() const {
    return new AdaptiveRKStepper(*this);
  }

  AdaptiveRKStepper::EEStepper::~EEStepper() {
  }
 
  CLHEPdouble & AdaptiveRKStepper::tolerance(){
    return T;
  }

  const CLHEPdouble & AdaptiveRKStepper::tolerance() const{
    return T;
  }
  
  CLHEPdouble & AdaptiveRKStepper::startingStepsize(){
    return sStepsize;
  }
  const CLHEPdouble & AdaptiveRKStepper::startingStepsize() const{
    return sStepsize;
  }
  
  CLHEPdouble & AdaptiveRKStepper::safetyFactor(){
    return S;
  }

  const CLHEPdouble & AdaptiveRKStepper::safetyFactor() const{
    return S;
  }
  
  CLHEPdouble & AdaptiveRKStepper::rmin(){
    return Rmin;
  }
  const CLHEPdouble & AdaptiveRKStepper::rmin() const{
    return Rmin;
  }
  
  CLHEPdouble & AdaptiveRKStepper::rmax(){
    return Rmax;
  }
  const CLHEPdouble & AdaptiveRKStepper::rmax() const{
    return Rmax;
  }

}
