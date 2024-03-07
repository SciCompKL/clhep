#include "CLHEPTypes.hpp"
#include "CLHEP/GenericFunctions/VoigtProfile.hh"
#include "CLHEP/GenericFunctions/Variable.hh"
#include <cmath>
#include <complex>

#if (defined __STRICT_ANSI__) || (defined _WIN32)
#ifndef M_PI
#define M_PI            3.14159265358979323846
#endif // M_PI
#endif // __STRICT_ANSI__

using namespace std;

inline CLHEPdouble Pow(CLHEPdouble x,int n) {
  CLHEPdouble val=1;
  for(int i=0;i<n;i++){
    val=val*x;
  }
  return val;
}

inline std::complex<CLHEPdouble> nwwerf(std::complex<CLHEPdouble> z) {
  std::complex<CLHEPdouble>  zh,r[38],s,t,v;

  const CLHEPdouble z1 = 1;
  const CLHEPdouble hf = z1/2;
  const CLHEPdouble z10 = 10;
  const CLHEPdouble c1 = 74/z10;
  const CLHEPdouble c2 = 83/z10;
  const CLHEPdouble c3 = z10/32;
  const CLHEPdouble c4 = 16/z10;
  const CLHEPdouble c = 1.12837916709551257;
  const CLHEPdouble p = Pow(2.0*c4,33);

  CLHEPdouble x=z.real();
  CLHEPdouble y=z.imag();
  CLHEPdouble xa=(x >= 0) ? x : -x;
  CLHEPdouble ya=(y >= 0) ? y : -y;
  if(ya < c1 && xa < c2){
    zh = std::complex<CLHEPdouble>(ya+c4,xa);
    r[37]= std::complex<CLHEPdouble>(0,0);
    //       do 1 n = 36,1,-1
    for(int n = 36; n>0; n--){   
      t=zh+CLHEPdouble(n)*std::conj(r[n+1]);
      r[n]=hf*t/std::norm(t);
    }
    CLHEPdouble xl=p;
    s=std::complex<CLHEPdouble>(0,0);
    //    do 2 n = 33,1,-1
    for(int k=33; k>0; k--){
      xl=c3*xl;
      s=r[k]*(s+xl);
    }
    v=c*s;
  }
  else{
      zh=std::complex<CLHEPdouble>(ya,xa);
      r[1]=std::complex<CLHEPdouble>(0,0);
       //       do 3 n = 9,1,-1
       for(int n=9;n>0;n--){
         t=zh+CLHEPdouble(n)*std::conj(r[1]);
         r[1]=hf*t/std::norm(t);
       }
       v=c*r[1];
  }
  if(ya == 0) v= std::complex<CLHEPdouble>(exp(-xa*xa),v.imag());
  if(y < 0) {
    v=CLHEPdouble(2.0)*std::exp(std::complex<CLHEPdouble>(-xa,-ya)*std::complex<CLHEPdouble>(xa,ya))-v;
    if(x > 0) v=std::conj(v);
  }
  else{
    if(x < 0) v=std::conj(v);
  }
  return v;
}



namespace Genfun {
FUNCTION_OBJECT_IMP(VoigtProfile)


VoigtProfile::VoigtProfile():
  _mass("mass",    50, 10, 90),
  _width ("width", 5, 0,   100),
  _sigma("sigma",  5, 0,   100)
{}

  VoigtProfile::VoigtProfile(const VoigtProfile & right):
    AbsFunction(),
    _mass(right._mass),
    _width (right._width),
    _sigma(right._sigma)
{
}

VoigtProfile::~VoigtProfile() {
}

CLHEPdouble VoigtProfile::operator() (CLHEPdouble x) const {
  CLHEPdouble M=_mass.getValue();
  CLHEPdouble G=_width.getValue()/2.0;
  CLHEPdouble s=_sigma.getValue();
  static const CLHEPdouble sqrt2=sqrt(2.0);
  static const CLHEPdouble sqrt2PI=sqrt(2.0*M_PI);
  static const std::complex<CLHEPdouble> I(0,1);
  std::complex<CLHEPdouble> z = ((x-M) + I*G)/sqrt2/s;
  
  CLHEPdouble f=nwwerf(z).real()/s/sqrt2PI;

  return f;

}

Parameter & VoigtProfile::mass() {
  return _mass;
}


Parameter & VoigtProfile::width() {
  return _width;
}

Parameter & VoigtProfile::sigma() {
  return _sigma;
}


} // namespace Genfun
