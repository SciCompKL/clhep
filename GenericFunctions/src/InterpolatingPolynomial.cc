#include "CLHEPTypes.hpp"
// -*- C++ -*-
// $Id: 
#include "CLHEP/GenericFunctions/InterpolatingPolynomial.hh"
#include <cassert>
#include <cmath>
#include <cfloat>
#include <iostream>
#include <vector>

namespace Genfun {
  FUNCTION_OBJECT_IMP(InterpolatingPolynomial)
  
  InterpolatingPolynomial::InterpolatingPolynomial()
  :Genfun::AbsFunction()
  {}
  
  InterpolatingPolynomial::InterpolatingPolynomial(const InterpolatingPolynomial & right)
    :Genfun::AbsFunction(),xPoints(right.xPoints)
  {}
  
  InterpolatingPolynomial::~InterpolatingPolynomial() {
  }
  
  CLHEPdouble InterpolatingPolynomial::operator() (CLHEPdouble x) const {
    CLHEPdouble y=0.0;
    CLHEPdouble deltay=0;  // also gives error;
    CLHEPdouble dif = fabs(x-xPoints[0].first),dift;
    const unsigned int _K=xPoints.size(),_KP=_K+1;
    std::vector<CLHEPdouble>c(_KP),d(_KP);
    int ns=0;
    for (unsigned int i=0;i<_K;i++) {
      dift=fabs(x-xPoints[i].first);
      if (dift<dif) {
	ns=i;
	dif=dift;
      }
      c[i]=d[i]=xPoints[i].second;
    }
    y = xPoints[ns--].second;
    for (unsigned int m=0;m<_K-1;m++) {
      for (unsigned int i=0;i<_K-m-1;i++) {
	CLHEPdouble ho = xPoints[i].first-x;
	CLHEPdouble hp=  xPoints[i+m+1].first-x;
	CLHEPdouble w=c[i+1]-d[i];
	CLHEPdouble den=ho-hp;
	if (den==0)
	  std::cerr
	    << "Error in polynomial extrapolation"
	    << std::endl;
	den=w/den;
	d[i]=hp*den;
	c[i]=ho*den;
      }
      deltay = 2*(ns+1) < (int)(_K-m-1) ? c[ns+1]: d[ns--];
      y += deltay;
    }
    return y;
  }
  
  void InterpolatingPolynomial::addPoint( CLHEPdouble x, CLHEPdouble y) {
    xPoints.push_back(std::make_pair(x,y));
  }

  void InterpolatingPolynomial::getRange( CLHEPdouble & min, CLHEPdouble & max) const {
    min=DBL_MAX, max=-DBL_MAX;
    for (unsigned int i=0;i<xPoints.size();i++) {
      min = std::min(min,xPoints[i].first);
      max = std::max(max,xPoints[i].first);
    }
  }
} // namespace Genfun
