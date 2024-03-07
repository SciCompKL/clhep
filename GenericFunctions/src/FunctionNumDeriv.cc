#include "CLHEPTypes.hpp"
// -*- C++ -*-
// $Id: FunctionNumDeriv.cc,v 1.4 2003/10/10 17:40:39 garren Exp $
// ---------------------------------------------------------------------------
 
#include "CLHEP/GenericFunctions/FunctionNumDeriv.hh"
#include <assert.h>
#include <cmath>      // for pow()

namespace Genfun {
FUNCTION_OBJECT_IMP(FunctionNumDeriv)

FunctionNumDeriv::FunctionNumDeriv(const AbsFunction *arg1, unsigned int index):
  _arg1(arg1->clone()),
  _wrtIndex(index)
{
}

FunctionNumDeriv::FunctionNumDeriv(const FunctionNumDeriv & right):
  AbsFunction(right),
  _arg1(right._arg1->clone()),
  _wrtIndex(right._wrtIndex)
{
}


FunctionNumDeriv::~FunctionNumDeriv()
{
  delete _arg1;
}

unsigned int FunctionNumDeriv::dimensionality() const {
  return _arg1->dimensionality();
}

#define ROBUST_DERIVATIVES 
#ifdef  ROBUST_DERIVATIVES

CLHEPdouble FunctionNumDeriv::f_x (CLHEPdouble x) const   { 
  return (*_arg1)(x);
}


CLHEPdouble FunctionNumDeriv::f_Arg (CLHEPdouble x) const { 
  _xArg [_wrtIndex] = x;
  return (*_arg1)(_xArg);
}


CLHEPdouble FunctionNumDeriv::operator ()(CLHEPdouble x) const
{
  assert (_wrtIndex==0);
  return numericalDerivative ( &FunctionNumDeriv::f_x, x );
}

CLHEPdouble FunctionNumDeriv::operator ()(const Argument & x) const
{
  assert (_wrtIndex<x.dimension());
  _xArg = x;
  CLHEPdouble xx = x[_wrtIndex];
  return numericalDerivative ( &FunctionNumDeriv::f_Arg, xx );
}


CLHEPdouble FunctionNumDeriv::numericalDerivative
        ( CLHEPdouble (FunctionNumDeriv::*f)(CLHEPdouble)const, CLHEPdouble x ) const {

  const CLHEPdouble h0 = 5 * std::pow(2.0, -17);

  const CLHEPdouble maxErrorA = .0012;    // These are the largest errors in steps 
  const CLHEPdouble maxErrorB = .0000026; // A, B consistent with 8-digit accuracy.

  const CLHEPdouble maxErrorC = .0003; // Largest acceptable validation discrepancy.

  // This value of gives 8-digit accuracy for 1250 > curvature scale < 1/1250.

  const int nItersMax = 6;
  int nIters;
  CLHEPdouble bestError = 1.0E30;
  CLHEPdouble bestAns = 0;

  const CLHEPdouble valFactor  = std::pow(2.0, -16);

  const CLHEPdouble w   = 5.0/8;
  const CLHEPdouble wi2 = 64.0/25.0;
  const CLHEPdouble wi4 = wi2*wi2;

  CLHEPdouble size    = fabs((this->*f)(x));
  if (size==0) size = std::pow(2.0, -53);

  const CLHEPdouble adjustmentFactor[nItersMax] = {
    1.0,
    std::pow(2.0, -17),
    std::pow(2.0, +17),
    std::pow(2.0, -34),
    std::pow(2.0, +34),
    std::pow(2.0, -51)  };

  for ( nIters = 0; nIters < nItersMax; ++nIters ) {

    CLHEPdouble h = h0 * adjustmentFactor[nIters];

    // Step A: Three estimates based on h and two smaller values:

    CLHEPdouble A1 = ((this->*f)(x+h) - (this->*f)(x-h))/(2.0*h);
//    size = max(fabs(A1), size);
    if (fabs(A1) > size) size = fabs(A1);

    CLHEPdouble hh = w*h;
    CLHEPdouble A2 = ((this->*f)(x+hh) - (this->*f)(x-hh))/(2.0*hh);
//    size = max(fabs(A2), size);
    if (fabs(A2) > size) size = fabs(A2);

    hh *= w; 
    CLHEPdouble A3 = ((this->*f)(x+hh) - (this->*f)(x-hh))/(2.0*hh);
//    size = max(fabs(A3), size);
    if (fabs(A3) > size) size = fabs(A3);

    if ( (fabs(A1-A2)/size > maxErrorA) || (fabs(A1-A3)/size > maxErrorA) ) { 
      continue;
    }

    // Step B: Two second-order estimates based on h h*w, from A estimates

    CLHEPdouble B1 = ( A2 * wi2 - A1 ) / ( wi2 - 1 );
    CLHEPdouble B2 = ( A3 * wi2 - A2 ) / ( wi2 - 1 );
    if ( fabs(B1-B2)/size > maxErrorB ) { 
      continue;
    }

    // Step C: Third-order estimate, from B estimates:

    CLHEPdouble ans = ( B2 * wi4 - B1 ) / ( wi4 - 1 );
    CLHEPdouble err = fabs ( ans - B1 );
    if ( err < bestError ) {
      bestError = err;
      bestAns = ans;
    }

    // Validation estimate based on much smaller h value:

    hh = h * valFactor;
    CLHEPdouble val = ((this->*f)(x+hh) - (this->*f)(x-hh))/(2.0*hh);
    if ( fabs(val-ans)/size > maxErrorC ) {
      continue;
    }

    // Having passed both apparent accuracy and validation, we are finished:
    break;
  }

  return bestAns;

}
#endif // ROBUST_DERIVATIVES



#ifdef SIMPLER_DERIVATIVES
CLHEPdouble FunctionNumDeriv::operator ()(CLHEPdouble x) const
{
  assert (_wrtIndex==0);
  const CLHEPdouble h=1.0E-6;
  return ((*_arg1)(x+h) - (*_arg1)(x-h))/(2.0*h);
}

CLHEPdouble FunctionNumDeriv::operator ()(const Argument & x) const
{
  assert (_wrtIndex<x.dimension());
  const CLHEPdouble h=1.0E-6;
  Argument x1=x, x0=x;
  x1[_wrtIndex] +=h;
  x0[_wrtIndex] -=h; 
  return ((*_arg1)(x1) - (*_arg1)(x0))/(2.0*h);
}
#endif // SIMPLER_DERIVATIVES

} // namespace Genfun
