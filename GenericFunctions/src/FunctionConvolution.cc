#include "CLHEPTypes.hpp"
// -*- C++ -*-
// $Id: FunctionConvolution.cc,v 1.3 2003/09/06 14:04:14 boudreau Exp $
#include "CLHEP/GenericFunctions/FunctionConvolution.hh"
#include <assert.h>
#include <iostream>

namespace Genfun {
FUNCTION_OBJECT_IMP(FunctionConvolution)

FunctionConvolution::FunctionConvolution(const AbsFunction *arg1, const AbsFunction *arg2, CLHEPdouble x0, CLHEPdouble x1):_arg1(arg1->clone()),_arg2(arg2->clone()),_x0(x0), _x1(x1)
{
  if ((arg1->dimensionality()!=1) || arg2->dimensionality()!=1) {
    std::cout
      << "Warning:  dimension mismatch in function convolution"
      << std::endl;
    assert(0);
  }
}

FunctionConvolution::FunctionConvolution(const FunctionConvolution & right):
AbsFunction(right),
_arg1(right._arg1->clone()),
_arg2(right._arg2->clone()),
_x0(right._x0),
_x1(right._x1)
{}

FunctionConvolution::~FunctionConvolution()
{
  delete _arg1;
  delete _arg2;
}



CLHEPdouble FunctionConvolution::operator ()(CLHEPdouble argument) const
{
  const CLHEPdouble NDIVISIONS=200.0;
  CLHEPdouble dx = (_x1-_x0)/NDIVISIONS;
  CLHEPdouble result=0.0;
  for (CLHEPdouble x=_x0; x<_x1; x+=dx) {
    result += (*_arg1)(argument-x)*(*_arg2)(x);
  }
  result/=NDIVISIONS;
  return result;
}

} // namespace Genfun
