#include "CLHEPTypes.hpp"
// -*- C++ -*-
// $Id: setStdMath.cc,v 1.2 2003/08/13 20:00:10 garren Exp $
// ----------------------------------------------------------------------

#include "CLHEP/Evaluator/defs.h"
#include "CLHEP/Evaluator/Evaluator.h"

#include <cmath>	// for sqrt and pow

static CLHEPdouble eval_abs  (CLHEPdouble a)           { return (a < 0) ? -a : a; } 
static CLHEPdouble eval_min  (CLHEPdouble a, CLHEPdouble b) { return (a < b) ?  a : b; } 
static CLHEPdouble eval_max  (CLHEPdouble a, CLHEPdouble b) { return (a > b) ?  a : b; } 
static CLHEPdouble eval_sqrt (CLHEPdouble a)           { return std::sqrt(a); } 
static CLHEPdouble eval_pow  (CLHEPdouble a, CLHEPdouble b) { return std::pow(a,b); } 
static CLHEPdouble eval_sin  (CLHEPdouble a)           { return std::sin(a); } 
static CLHEPdouble eval_cos  (CLHEPdouble a)           { return std::cos(a); } 
static CLHEPdouble eval_tan  (CLHEPdouble a)           { return std::tan(a); } 
static CLHEPdouble eval_asin (CLHEPdouble a)           { return std::asin(a); } 
static CLHEPdouble eval_acos (CLHEPdouble a)           { return std::acos(a); } 
static CLHEPdouble eval_atan (CLHEPdouble a)           { return std::atan(a); } 
static CLHEPdouble eval_atan2(CLHEPdouble a, CLHEPdouble b) { return std::atan2(a,b); } 
static CLHEPdouble eval_sinh (CLHEPdouble a)           { return std::sinh(a); } 
static CLHEPdouble eval_cosh (CLHEPdouble a)           { return std::cosh(a); } 
static CLHEPdouble eval_tanh (CLHEPdouble a)           { return std::tanh(a); } 
static CLHEPdouble eval_exp  (CLHEPdouble a)           { return std::exp(a); } 
static CLHEPdouble eval_log  (CLHEPdouble a)           { return std::log(a); } 
static CLHEPdouble eval_log10(CLHEPdouble a)           { return std::log10(a); } 

namespace HepTool {

void Evaluator::setStdMath() {

  //   S E T   S T A N D A R D   C O N S T A N T S

  setVariable("pi",     3.14159265358979323846);
  setVariable("e",      2.7182818284590452354);
  setVariable("gamma",  0.577215664901532861);
  setVariable("radian", 1.0);
  setVariable("rad",    1.0);
  setVariable("degree", 3.14159265358979323846/180.);
  setVariable("deg",    3.14159265358979323846/180.);

  //   S E T   S T A N D A R D   F U N C T I O N S

  setFunction("abs",   eval_abs);
  setFunction("min",   eval_min);
  setFunction("max",   eval_max);
  setFunction("sqrt",  eval_sqrt);
  setFunction("pow",   eval_pow);
  setFunction("sin",   eval_sin);
  setFunction("cos",   eval_cos);
  setFunction("tan",   eval_tan);
  setFunction("asin",  eval_asin);
  setFunction("acos",  eval_acos);
  setFunction("atan",  eval_atan);
  setFunction("atan2", eval_atan2);
  setFunction("sinh",  eval_sinh);
  setFunction("cosh",  eval_cosh);
  setFunction("tanh",  eval_tanh);
  setFunction("exp",   eval_exp);
  setFunction("log",   eval_log);
  setFunction("log10", eval_log10);
}

} // namespace HepTool
