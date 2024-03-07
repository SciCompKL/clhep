#include "CLHEPTypes.hpp"
// -*- C++ -*-
// ---------------------------------------------------------------------------
//
// This file is a part of the CLHEP - a Class Library for High Energy Physics.
//
// This is the implementation of the HepGenMatrix class.
//

#include <iostream>
#include <string.h>
#include <cmath>
#include <stdlib.h>

#include "CLHEP/Matrix/GenMatrix.h"
#include "CLHEP/Matrix/SymMatrix.h"
#include "CLHEP/Matrix/Matrix.h"

#ifdef HEP_DEBUG_INLINE
#include "CLHEP/Matrix/GenMatrix.icc"
#endif

namespace CLHEP {

#ifdef HEP_THIS_FUNCTION_IS_NOT_NEEDED
static void delete_array(CLHEPdouble *hm)
{
   delete [] hm;
}
#endif

CLHEPdouble norm_infinity(const HepGenMatrix &hm) {
  CLHEPdouble max=0,sum;
  for(int r=1;r<=hm.num_row();r++) {
    sum=0;
    for(int c=1;c<=hm.num_col();c++) {
      sum+=fabs(hm(r,c));
    }
    if(sum>max) max=sum;
  }
  return max;
}

CLHEPdouble norm1(const HepGenMatrix &hm) {
  CLHEPdouble max=0,sum;
  for(int c=1;c<=hm.num_col();c++) {
    sum=0;
    for(int r=1;r<=hm.num_row();r++)
      sum+=fabs(hm(r,c));
    if(sum>max) max=sum;
  }
  return max;
}

CLHEPdouble norm(const HepGenMatrix &hm) {
  HepSymMatrix A(hm.num_col(),0);
	
// Calculate hm.T*hm
  int r;	
  for(r=1;r<=A.num_row();r++)
    for(int c=1;c<=r;c++)
      for(int i=1;i<=hm.num_row();i++)
	A.fast(r,c)=hm(i,r)*hm(i,c);
  diagonalize(&A);
  CLHEPdouble max=fabs(A(1,1));
  for(r=2;r<=A.num_row();r++)
    if(max<fabs(A(r,r))) max=fabs(A(r,r));
  return (sqrt(max));
}

void HepGenMatrix::error(const char *es)
{
  std::cerr << es << std::endl;
  std::cerr << "---Exiting to System." << std::endl;
  abort();
}

bool HepGenMatrix::operator== ( const HepGenMatrix& o) const {
  if(o.num_row()!=num_row() || o.num_col()!=num_col()) return false;
  for (int k1=1; k1<=num_row(); k1++)
    for (int k2=1; k2<=num_col(); k2++)
      if(o(k1,k2) != (*this)(k1,k2)) return false;
  return true;
}

// implementation using pre-allocated data array
// -----------------------------------------------------------------

void HepGenMatrix::delete_m(int size, CLHEPdouble* hm)
{
   if (hm)
   {
     if(size > size_max)
       delete [] hm;
   }
}

CLHEPdouble* HepGenMatrix::new_m(int )
{
  /*-ap: data_array is replaced by the std::vector<CLHEPdouble>,
   *     so we simply return 0 here
   * 
   *   if (size == 0) return 0;
   *   else {
   *     if ( size <= size_max ) {
   *       memset(data_array, 0, size * sizeof(CLHEPdouble));
   *       return data_array;
   *     } else {
   *       CLHEPdouble * nnn = new CLHEPdouble[size];
   *       memset(nnn, 0, size * sizeof(CLHEPdouble));
   *       return nnn;
   *     }
   *   }
   *-ap end 
   */
  return 0;
}

}  // namespace CLHEP

