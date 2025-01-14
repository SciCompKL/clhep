#include "CLHEPTypes.hpp"
// -*- C++ -*-
// $Id: 

#include "CLHEP/GenericFunctions/BetaDistribution.hh"
#include <assert.h>
#include <cmath>
#include <iostream>
using namespace std;

namespace Genfun {
FUNCTION_OBJECT_IMP(BetaDistribution)


BetaDistribution::BetaDistribution():
  _alpha("a",    1.0, 0.0, 100),
  _beta ("beta", 1.0, 0.0, 100)
{}

BetaDistribution::BetaDistribution(const BetaDistribution & right):
AbsFunction( right ),
_alpha(right._alpha),
_beta (right._beta) 
{
}

BetaDistribution::~BetaDistribution() {
}

CLHEPdouble BetaDistribution::operator() (CLHEPdouble x) const {
  CLHEPdouble a = _alpha.getValue(),b=_beta.getValue();
  return pow(x,a-1)*pow((1-x),b-1)*
    exp(_logGamma(a+b)-_logGamma(a)-_logGamma(b));
  
}

Parameter & BetaDistribution::alpha() {
  return _alpha;
}


Parameter & BetaDistribution::beta() {
  return _beta;
}



} // namespace Genfun
