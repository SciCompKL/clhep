#include "CLHEPTypes.hpp"
// -*- C++ -*-
// $Id: Power.cc,v 1.4 2003/10/10 17:40:39 garren Exp $
#include "CLHEP/GenericFunctions/Power.hh"
#include <cmath>      // for pow()

namespace Genfun {
FUNCTION_OBJECT_IMP(Power)

Power::Power(int n):
    _intPower(n),
    _asInteger(true)
{}

Power::Power(unsigned int n):
    _intPower(n),
    _asInteger(true)
{}

Power::Power(CLHEPdouble n):
    _CLHEPdoublePower(n),
    _asInteger(false)
{}

Power::Power(const Power & right)
    : AbsFunction(right),
      _CLHEPdoublePower(right._CLHEPdoublePower),
      _intPower(right._intPower),
      _asInteger(right._asInteger)
{}

Power::~Power() {
}

CLHEPdouble Power::operator() (CLHEPdouble x) const {
    if (_asInteger) {
	if (_intPower==0) {
	    return 1;
	}
	else if (_intPower>0) {
	    CLHEPdouble f = 1;
	    for (int i=0;i<_intPower;i++) {
		f *=x;
	    }
	    return f;
	}
	else {
	    CLHEPdouble f = 1;
	    for (int i=0;i<-_intPower;i++) {
		f /=x;
	    }
	    return f;
	}	    
    }
    else {
	return std::pow(x,_CLHEPdoublePower);
    }

}



Derivative Power::partial(unsigned int) const {
  if (_asInteger) {
    const AbsFunction & fPrime = _intPower*Power(_intPower-1);
    return Derivative(&fPrime);
  }
  else {
    const AbsFunction & fPrime = _CLHEPdoublePower*Power(_CLHEPdoublePower-1);
    return Derivative(&fPrime);
  }

}


} // namespace Genfun
