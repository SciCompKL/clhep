#include "CLHEPTypes.hpp"
// -*- C++ -*-
// $Id: 
#ifndef _ArrayFunction_h_
#define _ArrayFunction_h_
//-------------------------------------------------------//
// This one dimensional function takes its values from   //
// an array..which it copies in.                         //
//-------------------------------------------------------//


#include "CLHEP/GenericFunctions/AbsFunction.hh"
#include <vector>
namespace Genfun {
class ArrayFunction : public AbsFunction  {
  
  FUNCTION_OBJECT_DEF(ArrayFunction)
    
    public:
  
  // Constructor
  ArrayFunction(const CLHEPdouble *begin, const CLHEPdouble *end);
  
  // Destructor
  virtual ~ArrayFunction();
  
  // Copy constructor
  ArrayFunction(const ArrayFunction &right);
  
  // Retreive function value
  virtual CLHEPdouble operator ()(CLHEPdouble argument) const override;
  virtual CLHEPdouble operator ()(const Argument & a) const override {return operator() (a[0]);}
  
 private:
  
  // It is illegal to assign a ArrayFunction
  const ArrayFunction & operator=(const ArrayFunction &right);

  std::vector<CLHEPdouble> _values;
};
}
#endif
