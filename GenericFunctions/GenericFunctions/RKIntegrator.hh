#include "CLHEPTypes.hpp"
// -*- C++ -*-
// $Id:
//---------------------Runge-Kutte Integrator-------------------------------//
//                                                                          //
// Class RKIntegrator                                                       //
// Joe Boudreau, November 2002                                              //
//                                                                          //
// This is a Runge-Kutta Numerical integrator for a set of N autonomous     //
// first order differential equations in N variables. The point is to       //
// create one or more functions which are defined by A) the differential    //
// equations governing their time evolution, and B) their values at time    //
// t=0.                                                                     //
//                                                                          //
// You add differential eqns one at a time to this integrator.  Each one    //
// is a GENFUNCTION governing the time evolution of the i^th variable, and  //
// should depend on all of the N variables, but not on the time             //
// explicitly.  You should add N differential equations in all.   Each      //
// time you add a differential equation the integrator creates a parameter  //
// for you representing the starting value of the variable, and returns a   //
// pointer.  You may either set the values of that parameter to desired     //
// values or else connect it to an external parameter if you wish to vary   //
// the shape of the function by adjusting starting values.                  //
//                                                                          //
// In addition, you may request the integrator to create a control          //
// parameter.  The control parameter may also be set, or connected.         //
// It can be used in the equations that define the time evolution of the    //
// variables.                                                               //
//--------------------------------------------------------------------------//
#ifndef RKIntegrator_h
#define RKIntegrator_h 1
#include "CLHEP/GenericFunctions/AbsFunction.hh"
#include "CLHEP/GenericFunctions/Parameter.hh"
#include "CLHEP/GenericFunctions/RCBase.hh"
#include <vector>
#include <set>
namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */

  class RKIntegrator {

  public:

    // Some helper classes:
    class RKFunction;
    class RKData;
    class RKStepper;

    // Constructor
    RKIntegrator(const RKStepper *stepper=NULL);

    // Destructor
    virtual ~RKIntegrator();
  
    // Add a differential equation governing the time evolution of the next variable.
    // Get back a parameter representing the starting value of that variable.  You 
    // can either arrange for that parameter to have the right starting value, or you
    // can connect it to another parameter so that you may change it. 
    Parameter * addDiffEquation (const AbsFunction  * diffEquation,
				 const std::string & variableName="anon",
				 CLHEPdouble defStartingValue=0.0,
				 CLHEPdouble startingValueMin=0.0,
				 CLHEPdouble startingValueMax=0.0);


    // Create a control parameter.  You can then connnect this to some other
    // parameter.
    Parameter *createControlParameter (const std::string & variableName="anon",
				       CLHEPdouble defStartingValue=0.0,
				       CLHEPdouble startingValueMin=0.0,
				       CLHEPdouble startingValueMax=0.0);

    // Get back a function. This function will now actually change as parameters
    // are changed; this includes both control parameters and starting value 
    // parameters.
    const RKFunction *getFunction(unsigned int i) const;


  private:

    // It is illegal to assign an RKIntegrator
    const RKIntegrator & operator=(const RKIntegrator &right);

    // It is illegal to copy an RKIntegrator
    RKIntegrator(const RKIntegrator &right);
  
    // Here is the data, it belongs to the integrator and to the
    // functions, and is reference counted:
    RKData                          *_data;


    // Here are the functions:
    std::vector<const RKFunction *> _fcn;


  };


  class RKIntegrator::RKData : public Genfun::RCBase {
    

  public:
    
    // Information about solution at each mesh point.
    struct Data{

      std::vector<CLHEPdouble>         variable;             // Solution
      mutable std::vector<CLHEPdouble> firstDerivative;      // It's first derivative
      CLHEPdouble time;                                      // time
 
      Data(int size): variable(size), firstDerivative(size), time(0) {} 
      bool operator <  (const Data & right) const { return time < right.time; }
      bool operator == (const Data & right) const { return time==right.time; } 
    };

    RKData();
    void lock();
    void recache();

    std::vector<Parameter *>           _startingValParameter;
    std::vector<CLHEPdouble>                _startingValParameterCache;

    std::vector <Parameter *>          _controlParameter;
    std::vector <CLHEPdouble>               _controlParameterCache;

    std::vector<const AbsFunction *>   _diffEqn;
    std::set<Data >                    _fx;
    bool                               _locked;
    const RKStepper                   *_stepper;
  private:

    ~RKData();
    friend class ImaginaryFriend;  // Silence compiler warnings.

  };

  class RKIntegrator::RKFunction : public AbsFunction {

    FUNCTION_OBJECT_DEF(RKFunction)

      public:

    // Constructor
    RKFunction(RKData *data, unsigned int index);

    // Destructor
    virtual ~RKFunction();
  
    // Copy constructor
    RKFunction(const RKFunction &right);
  
    // Retreive function value
    virtual CLHEPdouble operator ()(CLHEPdouble argument) const override;
    virtual CLHEPdouble operator ()(const Argument & a) const override {return operator() (a[0]);}

  private:

    // It is illegal to assign a RKFunction
    const RKFunction & operator=(const RKFunction &right);

    // The shared data:
    RKData              *_data;
    const  unsigned int  _index;

};


  // An abstract base class for steppers:
  class RKIntegrator::RKStepper {
  public:

    virtual ~RKStepper();
    virtual void step (const RKIntegrator::RKData *data, 
		       const RKIntegrator::RKData::Data & sdata, 
		       RKIntegrator::RKData::Data       & ddata, 
		       CLHEPdouble timeLimit=0) const =0;
    virtual RKStepper *clone() const=0;

  };

} // namespace Genfun

#endif
