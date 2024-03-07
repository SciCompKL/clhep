#include "CLHEPTypes.hpp"
// -*- C++ -*-
// $Id: 
#include "CLHEP/GenericFunctions/HermitePolynomial.hh"
#include "CLHEP/GenericFunctions/FixedConstant.hh"
#include <assert.h>
#include <cmath>

namespace Genfun {
FUNCTION_OBJECT_IMP(HermitePolynomial)

HermitePolynomial::HermitePolynomial(unsigned int N)
:_N(N)
{}

HermitePolynomial::~HermitePolynomial() {
}

HermitePolynomial::HermitePolynomial(const HermitePolynomial & right) 
  :AbsFunction(), _N(right._N)
{  }


CLHEPdouble HermitePolynomial::operator() (CLHEPdouble x) const {
  const static CLHEPdouble h00=0.0;
  const static CLHEPdouble h0=sqrt(M_PI/4.0);
  CLHEPdouble p0=h00;
  CLHEPdouble p1=h00;
  CLHEPdouble pn=h0;
  for (unsigned int i=1;i<=_N;i++) {
    p0=p1;
    p1=pn;
    pn=x*sqrt(2.0/i)*p1-sqrt((i-1.0)/i)*p0;
  }
  return pn;
}

unsigned int HermitePolynomial::N() const {
  return _N;
}

Derivative HermitePolynomial::partial(unsigned int index) const {
  assert(index==0);
  if (_N>0) {
    const AbsFunction & fPrime = sqrt(2.0*_N)*HermitePolynomial(_N-1);
    return Derivative(& fPrime);
  }
  else {
    const AbsFunction & fPrime   = FixedConstant(0.0);
    return Derivative(& fPrime);
  }
}

} // namespace Genfun
