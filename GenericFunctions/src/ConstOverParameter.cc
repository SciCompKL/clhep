// -*- C++ -*-
// $Id: ConstOverParameter.cc,v 1.2 2003/08/13 20:00:10 garren Exp $
#include "CLHEP/GenericFunctions/defs.h"
#include "CLHEP/GenericFunctions/ConstOverParameter.hh"
#include "CLHEP/GenericFunctions/Parameter.hh"

namespace Genfun {

PARAMETER_OBJECT_IMP(ConstOverParameter)

ConstOverParameter::ConstOverParameter(double constant, const AbsParameter *parameter):
  _constant(constant),
  _parameter(parameter->clone())
{
  if (parameter->parameter() && _parameter->parameter()) _parameter->parameter()->connectFrom(parameter->parameter());
}

ConstOverParameter::ConstOverParameter(const ConstOverParameter & right) :
_constant(right._constant),
_parameter(right._parameter->clone())
{}


ConstOverParameter::~ConstOverParameter()
{
  delete _parameter;
}


double ConstOverParameter::getValue() const {
  return _constant / _parameter->getValue();
}

} // namespace Genfun
