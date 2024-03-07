#include "CLHEPTypes.hpp"
// -*- C++ -*-
// $Id: 
#include "CLHEP/GenericFunctions/AbsFunction.hh"
#include "CLHEP/GenericFunctions/ArrayFunction.hh"

#include <vector>

namespace Genfun {

FUNCTION_OBJECT_IMP(ArrayFunction)
  
// Constructor
ArrayFunction::ArrayFunction(const CLHEPdouble *begin, const CLHEPdouble *end) :
  _values(begin,end) {}
  
// Destructor
ArrayFunction::~ArrayFunction(){}
  
// Copy constructor
ArrayFunction::ArrayFunction(const ArrayFunction &right):
  AbsFunction(right), _values(right._values) {}
  
  // Retreive function value
CLHEPdouble ArrayFunction::operator ()(CLHEPdouble argument) const {
  int i =  int (argument+0.5);
  if (i<0 || i>=int(_values.size())) return 0;
  else return _values[i];
}

}
