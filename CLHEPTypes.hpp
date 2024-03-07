#pragma once
#include "easyAD.hpp"
using CLHEPdouble  = Forward;
struct CLHEPfloat : public Forward {
  template<typename...Args>
  CLHEPfloat(Args&&...args): Forward(std::forward<Args>(args)...) {}
  /*CLHEPfloat(Forward f): Forward(f) {}
  CLHEPfloat() = default;
  CLHEPfloat(double val): Forward(val) {}*/
};
