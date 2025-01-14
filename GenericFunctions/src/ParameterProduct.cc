#include "CLHEPTypes.hpp"
// -*- C++ -*-
// $Id: ParameterProduct.cc,v 1.3 2003/09/06 14:04:14 boudreau Exp $
#include "CLHEP/GenericFunctions/ParameterProduct.hh"
#include "CLHEP/GenericFunctions/Parameter.hh"

namespace Genfun {
PARAMETER_OBJECT_IMP(ParameterProduct)

ParameterProduct::ParameterProduct(const AbsParameter *arg1, const AbsParameter *arg2):
  _arg1(arg1->clone()),
  _arg2(arg2->clone())
{
  if (arg1->parameter() && _arg1->parameter()) _arg1->parameter()->connectFrom(arg1->parameter());
  if (arg2->parameter() && _arg2->parameter()) _arg2->parameter()->connectFrom(arg2->parameter());
}

ParameterProduct::ParameterProduct(const ParameterProduct & right) :
AbsParameter(),
_arg1(right._arg1->clone()),
_arg2(right._arg2->clone())
{}


ParameterProduct::~ParameterProduct()
{
  delete _arg1;
  delete _arg2;
}


CLHEPdouble ParameterProduct::getValue() const {
  return _arg1->getValue()*_arg2->getValue();
}

} // namespace Genfun
