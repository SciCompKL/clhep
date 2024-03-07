#include "CLHEPTypes.hpp"
// -*- C++ -*-
// $Id: X.cc,v 1.3 2003/09/06 14:04:14 boudreau Exp $
#include "CLHEP/GenericFunctions/X.hh"

namespace Genfun {
FUNCTION_OBJECT_IMP(X_)

X_::X_()
{}

X_::X_(const X_ & right) : AbsFunction(right)
{
}

X_::~X_() {
}

CLHEPdouble X_::operator() (CLHEPdouble x) const {
  return x;
}

} // namespace Genfun
