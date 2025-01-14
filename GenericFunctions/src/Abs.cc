#include "CLHEPTypes.hpp"
// $Id: 
// -*- C++ -*-
//
#include "CLHEP/GenericFunctions/Abs.hh"
#include <cmath>

namespace Genfun {

FUNCTION_OBJECT_IMP(Abs)

Abs::Abs()
{}

Abs::Abs(const Abs & right) : AbsFunction(right)
{
}

Abs::~Abs() {
}

CLHEPdouble Abs::operator() (CLHEPdouble x) const {
  return std::abs(x);
}

}

