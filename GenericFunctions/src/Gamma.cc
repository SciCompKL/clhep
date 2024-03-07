#include "CLHEPTypes.hpp"
// -*- C++ -*-
// $Id: 

#include "CLHEP/GenericFunctions/Gamma.hh"
#include <assert.h>
#include <cmath>
using namespace std;

namespace Genfun {
FUNCTION_OBJECT_IMP(Gamma)


Gamma::Gamma()

{}

Gamma::Gamma(const Gamma & right) : AbsFunction(right)
{
}

Gamma::~Gamma() {
}

CLHEPdouble Gamma::operator() (CLHEPdouble x) const {
  return  exp(_logGamma(x));

}




} // namespace Genfun
