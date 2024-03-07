#include "CLHEPTypes.hpp"
// -*- C++ -*-
// $Id: AnalyticConvolution.cc,v 1.8 2010/07/22 21:55:10 garren Exp $
#include "CLHEP/GenericFunctions/AbsFunction.hh"
#include "CLHEP/GenericFunctions/AnalyticConvolution.hh"
#include "CLHEP/GenericFunctions/Gaussian.hh"
#include "CLHEP/GenericFunctions/Exponential.hh"
#include <cmath>	// for isfinite
#if (defined _WIN32)
#include <float.h> //  Visual C++ _finite
#endif
#include <iostream>

namespace Genfun {
FUNCTION_OBJECT_IMP(AnalyticConvolution)

AnalyticConvolution::AnalyticConvolution(AnalyticConvolution::Type          type) :
  _lifetime ("Lifetime",  1.0, 0.0),  // Bounded from below by zero, by default
  _frequency("Frequency", 0.0, 0.0),  // Bounded from below by zero, by default
  _sigma    ("Sigma",     1.0, 0.0),  // Bounded from below by zero, by default
  _offset   ("Offset",    0.0),       // Offset is unbounded
  _type(type)
{
}

AnalyticConvolution::AnalyticConvolution(const AnalyticConvolution & right):
  AbsFunction(right),
  _lifetime  (right._lifetime),
  _frequency (right._frequency),
  _sigma     (right._sigma),
  _offset    (right._offset),
  _type(right._type)
{
}

AnalyticConvolution::~AnalyticConvolution() {
}

Parameter & AnalyticConvolution::frequency() {
  return _frequency;
}

const Parameter & AnalyticConvolution::frequency() const {
  return _frequency;
}

Parameter & AnalyticConvolution::lifetime() {
  return _lifetime;
}

const Parameter & AnalyticConvolution::lifetime() const {
  return _lifetime;
}

Parameter & AnalyticConvolution::sigma() {
  return _sigma;
}

const Parameter & AnalyticConvolution::sigma() const {
  return _sigma;
}

Parameter & AnalyticConvolution::offset() {
  return _offset;
}

const Parameter & AnalyticConvolution::offset() const {
  return _offset;
}
CLHEPdouble AnalyticConvolution::operator() (CLHEPdouble argument) const {
  // Fetch the paramters.  This operator does not convolve numerically.
  static const CLHEPdouble sqrtTwo = sqrt(2.0);
  CLHEPdouble xsigma  = _sigma.getValue();
  CLHEPdouble tau    = _lifetime.getValue();
  CLHEPdouble xoffset = _offset.getValue();
  CLHEPdouble x      =  argument-xoffset;
  CLHEPdouble freq   = _frequency.getValue();
 
  // smeared exponential an its asymmetry.
  CLHEPdouble expG=0.0, asymm=0.0;  
  
  if (_type==SMEARED_NEG_EXP) {
    expG = exp((xsigma*xsigma +2*tau*(/*xoffset*/x))/(2.0*tau*tau)) * 
      erfc((xsigma*xsigma+tau*(/*xoffset*/x))/(sqrtTwo*xsigma*tau))/(2.0*tau);
#if (defined _WIN32)
    if (!_finite(expG)) {
      expG=0.0;
    }
#else
    if (!std::isfinite(expG)) {
      expG=0.0;
    }
#endif
    return expG;
  }
  else {
    expG = exp((xsigma*xsigma +2*tau*(/*xoffset*/-x))/(2.0*tau*tau)) * 
      erfc((xsigma*xsigma+tau*(/*xoffset*/-x))/(sqrtTwo*xsigma*tau))/(2.0*tau);
  }
  
  // Both sign distribution=> return smeared exponential:
  if (_type==SMEARED_EXP) {
#if (defined _WIN32)
    if (!_finite(expG)) {
      expG=0.0;
    }
#else
    if (!std::isfinite(expG)) {
      expG=0.0;
    }
#endif
    return expG;
  }
   
  
  // Calcualtion of asymmetry:

  // First, if the mixing frequency is too high compared with the lifetime, we
  // cannot see this oscillation.  We abandon the complicated approach and just do
  // this instead: 
  if (xsigma>6.0*tau) {
    asymm = expG*(1/(1+tau*tau*freq*freq));
  }
  else if (xsigma==0.0) {
    if (_type==SMEARED_COS_EXP|| _type==MIXED || _type==UNMIXED ) {
      if (x>=0) asymm=  (expG*cos(freq*x));
    }
    else if (_type==SMEARED_SIN_EXP) {
      if (x>=0) asymm= (expG*sin(freq*x));
    } 
  }
  else {
    std::complex<CLHEPdouble> z(freq*xsigma/sqrtTwo, (xsigma/tau-x/xsigma)/sqrtTwo);
    if (x<0) {
      if (_type==SMEARED_COS_EXP|| _type==MIXED || _type==UNMIXED ) {
	asymm= 2.0*nwwerf(z).real()/tau/4.0*exp(-x*x/2.0/xsigma/xsigma);
      }
      else if (_type==SMEARED_SIN_EXP) {
	asymm= 2.0*nwwerf(z).imag()/tau/4.0*exp(-x*x/2.0/xsigma/xsigma);
      }
    }
    else {
      if (_type==SMEARED_COS_EXP||_type==MIXED || _type==UNMIXED) {
	asymm= -2.0*nwwerf(std::conj(z)).real()/tau/4*exp(-x*x/2.0/xsigma/xsigma) +
	  exp(xsigma*xsigma/2 *(1/tau/tau - freq*freq) - x/tau)*(1./tau)*cos(freq*x - freq/tau*xsigma*xsigma);
      }
      else if (_type==SMEARED_SIN_EXP) {
	asymm= +2.0*nwwerf(std::conj(z)).imag()/tau/4*exp(-x*x/2.0/xsigma/xsigma) +
	  exp(xsigma*xsigma/2 *(1/tau/tau - freq*freq) - x/tau)*(1./tau)*sin(freq*x - freq/tau*xsigma*xsigma);
      }
    } 
  }
  
  // Return either MIXED, UNMIXED, or ASYMMETRY function.
  if (_type==UNMIXED) {
    CLHEPdouble retVal = (expG+asymm)/2.0;
    if (retVal<0)
      std::cerr
	<< "Warning in AnalyticConvolution:  negative probablity"
	<< std::endl;
    if (retVal<0)
      std::cerr
	<< xsigma << ' ' << tau << ' ' << xoffset << ' '
	<< freq << ' '<< argument
	<< std::endl;
    if (retVal<0)
      std::cerr << retVal << std::endl;
    return retVal;
  }
  else if (_type==MIXED) {
    CLHEPdouble retVal = (expG-asymm)/2.0;
    if (retVal<0)
      std::cerr
	<< "Warning in AnalyticConvolution:  negative probablity"
	<< std::endl;
    if (retVal<0)
      std::cerr
	<< xsigma << ' ' << tau << ' ' << xoffset << ' '
	<< freq << ' ' << argument
	<< std::endl;
    if (retVal<0)
      std::cerr << retVal << std::endl;
    return retVal;
  }
  else if (_type==SMEARED_COS_EXP || _type==SMEARED_SIN_EXP) {
    return asymm;
  }
  else {
    std::cerr
      << "Unknown sign parity.  State is not allowed"
      << std::endl;
    exit(0);
    return 0.0;
  }

}

CLHEPdouble AnalyticConvolution::erfc(CLHEPdouble x) const {
// This is accurate to 7 places.
// See Numerical Recipes P 221
  CLHEPdouble t, z, ans;
  z = (x < 0) ? -x : x;
  t = 1.0/(1.0+.5*z);
  ans = t*exp(-z*z-1.26551223+t*(1.00002368+t*(0.37409196+t*(0.09678418+
        t*(-0.18628806+t*(0.27886807+t*(-1.13520398+t*(1.48851587+
        t*(-0.82215223+t*0.17087277 ))) ))) )));
  if ( x < 0 ) ans = 2.0 - ans;
  return ans;
}

CLHEPdouble AnalyticConvolution::pow(CLHEPdouble x,int n) const {
  CLHEPdouble val=1;
  for(int i=0;i<n;i++){
    val=val*x;
  }
  return val;
}

std::complex<CLHEPdouble> AnalyticConvolution::nwwerf(std::complex<CLHEPdouble> z) const {
  std::complex<CLHEPdouble>  zh,r[38],s,t,v;

  const CLHEPdouble z1 = 1;
  const CLHEPdouble hf = z1/2;
  const CLHEPdouble z10 = 10;
  const CLHEPdouble c1 = 74/z10;
  const CLHEPdouble c2 = 83/z10;
  const CLHEPdouble c3 = z10/32;
  const CLHEPdouble c4 = 16/z10;
  const CLHEPdouble c = 1.12837916709551257;
  const CLHEPdouble p = pow(2.0*c4,33);

  CLHEPdouble x=z.real();
  CLHEPdouble y=z.imag();
  CLHEPdouble xa=(x >= 0) ? x : -x;
  CLHEPdouble ya=(y >= 0) ? y : -y;
  if(ya < c1 && xa < c2){
    zh = std::complex<CLHEPdouble>(ya+c4,xa);
    r[37]= std::complex<CLHEPdouble>(0,0);
    //       do 1 n = 36,1,-1
    for(int n = 36; n>0; n--){   
      t=zh+CLHEPdouble(n)*std::conj(r[n+1]);
      r[n]=hf*t/std::norm(t);
    }
    CLHEPdouble xl=p;
    s=std::complex<CLHEPdouble>(0,0);
    //    do 2 n = 33,1,-1
    for(int k=33; k>0; k--){
      xl=c3*xl;
      s=r[k]*(s+xl);
    }
    v=c*s;
  }
  else{
      zh=std::complex<CLHEPdouble>(ya,xa);
      r[1]=std::complex<CLHEPdouble>(0,0);
       //       do 3 n = 9,1,-1
       for(int n=9;n>0;n--){
	 t=zh+CLHEPdouble(n)*std::conj(r[1]);
	 r[1]=hf*t/std::norm(t);
       }
       v=c*r[1];
  }
  if(ya == 0) v= std::complex<CLHEPdouble>(exp(-xa*xa),v.imag());
  if(y < 0) {
    v=2.0*std::exp(std::complex<CLHEPdouble>(-xa,-ya)*std::complex<CLHEPdouble>(xa,ya))-v;
    if(x > 0) v=std::conj(v);
  }
  else{
    if(x < 0) v=std::conj(v);
  }
  return v;
}
} // namespace Genfun
