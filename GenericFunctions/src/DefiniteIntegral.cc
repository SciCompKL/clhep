#include "CLHEPTypes.hpp"
// -*- C++ -*-
// $Id: DefiniteIntegral.cc,v 1.6 2010/06/16 18:22:01 garren Exp $

#include "CLHEP/GenericFunctions/AbsFunction.hh"
#include "CLHEP/GenericFunctions/DefiniteIntegral.hh"

#include <cmath>
#include <iostream>
#include <vector>
#include <stdexcept>

namespace Genfun {


  class DefiniteIntegral::Clockwork {
    
    //
    // This class has limited visibility its functions, data,
    // and nested classes are all public:
    // 
    
  public:
    
    class QuadratureRule {
      
    public:
      
      // Constructorctor:
      QuadratureRule() {};
      
      // Destructor:
      virtual ~QuadratureRule() {};
      
      // Integrate at the j^th level of refinement:
      virtual CLHEPdouble integrate(const AbsFunction & function, 
			       CLHEPdouble a,
			       CLHEPdouble b,
			       unsigned int j) const=0;
      
      // Return the step multiplier:
      virtual unsigned int stepMultiplier () const=0;

      // Return the number of function calls:
      virtual unsigned int numFunctionCalls() const =0;

    };
    
    class TrapezoidQuadratureRule:public QuadratureRule {
      
    public:
      
      // Constructor:
      TrapezoidQuadratureRule():retVal(0),nFunctionCalls(0) {};
      
      // Destructor:
      ~TrapezoidQuadratureRule() {};
      
      // Integrate at the j^th level of refinement:
      virtual CLHEPdouble integrate(const AbsFunction & function, 
			       CLHEPdouble a,
			       CLHEPdouble b,
			       unsigned int j) const;
      
      // The step is CLHEPdoubled at each level of refinement:
      virtual unsigned int stepMultiplier () const {return 2;}

      // Returns number of function calls:
      virtual unsigned int numFunctionCalls() const {return nFunctionCalls;};
      
    private:

      mutable CLHEPdouble retVal;
      mutable unsigned int nFunctionCalls;

    };
    
    class XtMidpointQuadratureRule:public QuadratureRule {
      
    public:
      
      // Constructor:
      XtMidpointQuadratureRule():retVal(0),nFunctionCalls(0) {};
      
      // Destructorctor:
      ~XtMidpointQuadratureRule() {};
      
      // Integrate at the j^th level of refinement:
      virtual CLHEPdouble integrate(const AbsFunction & function, 
			       CLHEPdouble a,
			       CLHEPdouble b,
			       unsigned int j) const;
      
      // The step is tripled at each level of refinement:
      virtual unsigned int stepMultiplier () const {return 3;}

      // Returns number of function calls:
      virtual unsigned int numFunctionCalls() const {return nFunctionCalls;};
      
    private:

      mutable CLHEPdouble retVal;
      mutable unsigned int nFunctionCalls;
    };
    
    CLHEPdouble                              a;              // lower limit of integration
    CLHEPdouble                              b;              // upper limit of integration
    DefiniteIntegral::Type              type;           // open or closed
    mutable unsigned int                nFunctionCalls; // bookkeeping
    unsigned int                        MAXITER;        // Max no of step doubling, tripling, etc.
    CLHEPdouble                              EPS;            // Target precision
    unsigned int                        K;              // Minimum order =2*5=10

    // Polynomial interpolation with Neville's method:
    void polint(std::vector<CLHEPdouble>::iterator xArray, std::vector<CLHEPdouble>::iterator yArray, CLHEPdouble x, CLHEPdouble & y, CLHEPdouble & deltay) const;
    
  };

  
  DefiniteIntegral::DefiniteIntegral(CLHEPdouble a, CLHEPdouble b, Type type):
    c(new Clockwork()) {
    c->a              = a;
    c->b              = b;
    c->type           = type;
    c->nFunctionCalls = 0;
    c->MAXITER        = type==OPEN ? 20 : 14; 
    c->EPS            = 1.0E-6;
    c->K              = 5;
  }
  
  DefiniteIntegral::~DefiniteIntegral() {
    delete c;
  }

  DefiniteIntegral::DefiniteIntegral(const DefiniteIntegral & right) 
  :AbsFunctional(right), c(new Clockwork(*right.c)) {
  }

  DefiniteIntegral & DefiniteIntegral::operator = (const DefiniteIntegral & right) {
    if (this!=&right) {
      delete c;
      c = new Clockwork(*right.c);
    }
    return *this;
  }
  
  void DefiniteIntegral::setEpsilon(CLHEPdouble eps) {
    c->EPS=eps;
  }

  void DefiniteIntegral::setMaxIter(unsigned int maxIter) {
    c->MAXITER=maxIter;
  }

  void DefiniteIntegral::setMinOrder(unsigned int minOrder) {
    c->K=(minOrder+1)/2;
  }

  CLHEPdouble DefiniteIntegral::operator [] (const AbsFunction & function) const {

    const Clockwork::QuadratureRule * rule = c->type==OPEN ? 
      (Clockwork::QuadratureRule *) new Clockwork::XtMidpointQuadratureRule() : 
      (Clockwork::QuadratureRule *) new Clockwork::TrapezoidQuadratureRule();
    CLHEPdouble xMult=rule->stepMultiplier();

    c->nFunctionCalls=0;
    std::vector<CLHEPdouble> s(c->MAXITER+2),h(c->MAXITER+2);
    h[1]=1.0;
    for (unsigned int j=1;j<=c->MAXITER;j++) {
      s[j]=rule->integrate(function, c->a, c->b, j);
      c->nFunctionCalls=rule->numFunctionCalls();
      if (j>=c->K) {
	CLHEPdouble ss(0.), dss(0.);
	c->polint(h.begin()+j-c->K,s.begin()+j-c->K,0.0,ss, dss);
	if (fabs(dss) <= c->EPS*fabs(ss)) {
	  delete rule;
	  return ss;
	}
      }
      s[j+1]=s[j];
      h[j+1]=h[j]/xMult/xMult;
    }
    delete rule;
    throw std::runtime_error("DefiniteIntegral:  too many steps.  No convergence");
    return 0.0;                   // Never get here.
  }
  
  void DefiniteIntegral::Clockwork::polint(std::vector<CLHEPdouble>::iterator xArray, std::vector<CLHEPdouble>::iterator yArray, CLHEPdouble x, CLHEPdouble & y, CLHEPdouble & deltay) const {
    CLHEPdouble dif = fabs(x-xArray[1]),dift;
    std::vector<CLHEPdouble> cc(K+1),d(K+1);
    unsigned int ns=1;
    for (unsigned int i=1;i<=K;i++) {
      dift=fabs(x-xArray[i]);
      if (dift<dif) {
	ns=i;
	dif=dift;
      }
      cc[i]=d[i]=yArray[i];
    }
    y = yArray[ns--];
    for (unsigned int m=1;m<K;m++) {
      for (unsigned int i=1;i<=K-m;i++) {
	CLHEPdouble ho = xArray[i]-x;
	CLHEPdouble hp=  xArray[i+m]-x;
	CLHEPdouble w=cc[i+1]-d[i];
	CLHEPdouble den=ho-hp;
	if (den==0)
	  std::cerr
	    << "Error in polynomial extrapolation"
	    << std::endl;
	den=w/den;
	d[i]=hp*den;
	cc[i]=ho*den;
      }
      deltay = 2*ns < (K-m) ? cc[ns+1]: d[ns--];
      y += deltay;
    }
  }
  
  unsigned int DefiniteIntegral::numFunctionCalls() const {
    return c->nFunctionCalls;
  }

  // Quadrature rules:
  CLHEPdouble DefiniteIntegral::Clockwork::TrapezoidQuadratureRule::integrate(const AbsFunction & function, CLHEPdouble aa, CLHEPdouble bb, unsigned int n) const {
    unsigned int it, j;
    if (n==1) {
      retVal = 0.5*(bb-aa)*(function(aa)+function(bb));
      nFunctionCalls+=2;
    }
    else { 
      for (it=1,j=1;j<n-1;j++)  it <<=1;
      CLHEPdouble tnm=it;
      CLHEPdouble del = (bb-aa)/tnm;
      CLHEPdouble x=aa+0.5*del;
      CLHEPdouble sum;
      for (sum=0.0,j=1;j<=it;j++,x+=del) {
	sum +=function(x);
	nFunctionCalls++;
      }
      retVal = 0.5*(retVal+(bb-aa)*sum/tnm);
    }
    return retVal;
  }

  // Quadrature rules:
  CLHEPdouble DefiniteIntegral::Clockwork::XtMidpointQuadratureRule::integrate(const AbsFunction & function, CLHEPdouble aa, CLHEPdouble bb, unsigned int n) const {
    unsigned int it, j;
    if (n==1) {
      retVal = (bb-aa)*(function((aa+bb)/2.0));
      nFunctionCalls+=1;
    }
    else { 
      for (it=1,j=1;j<n-1;j++)  it *=3;
      CLHEPdouble tnm=it;
      CLHEPdouble del  = (bb-aa)/(3.0*tnm);
      CLHEPdouble ddel = del+del;
      CLHEPdouble x=aa+0.5*del;
      CLHEPdouble sum=0;
      for (j=1;j<=it;j++) {
	sum +=function(x);
	x+=ddel;
	sum +=function(x);
	x+=del;
	nFunctionCalls+=2;
      }
      retVal = (retVal+(bb-aa)*sum/tnm)/3.0;
    }
    return retVal;
  }
  
  

} // namespace Genfun
