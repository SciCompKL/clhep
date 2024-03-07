#include "CLHEPTypes.hpp"
// -*- C++ -*-
// $Id: Landau.cc,v 1.4 2003/10/10 17:40:39 garren Exp $
// ---------------------------------------------------------------------------
 
#include "CLHEP/GenericFunctions/Landau.hh"
#include "CLHEP/GenericFunctions/Variable.hh"
#include <cmath>
#include <assert.h>
#include <iostream>

using namespace std;

namespace Genfun {
FUNCTION_OBJECT_IMP(Landau)

Landau::Landau():
  _peak("Peak", 5.0 ,0, 10),
  _width("Width",1.0,0, 10)
{}

Landau::~Landau() {
}

Landau::Landau(const Landau & right):
AbsFunction(right),
_peak(right._peak),
_width(right._width)
{
}

CLHEPdouble Landau::operator() (CLHEPdouble x) const {
  CLHEPdouble s   = _width.getValue();
  CLHEPdouble x0  = _peak.getValue();
  CLHEPdouble xs  = x0 + 0.222782*s;
  return _denlan((x-xs)/s)/s;
}

Parameter & Landau::peak() {
  return _peak;
}

Parameter & Landau::width() {
  return _width;
}

const Parameter & Landau::peak() const {
  return _peak;
}

const Parameter & Landau::width() const {
  return _width;
}

CLHEPdouble Landau::_denlan(CLHEPdouble x) const {
    /* Initialized data */

    static CLHEPfloat p1[5] = { (CLHEPfloat).4259894875,(CLHEPfloat)-.124976255,(CLHEPfloat)
            .039842437,(CLHEPfloat)-.006298287635,(CLHEPfloat).001511162253 };
    static CLHEPfloat q5[5] = { (CLHEPfloat)1.,(CLHEPfloat)156.9424537,(CLHEPfloat)3745.310488,(
            CLHEPfloat)9834.698876,(CLHEPfloat)66924.28357 };
    static CLHEPfloat p6[5] = { (CLHEPfloat)1.000827619,(CLHEPfloat)664.9143136,(CLHEPfloat)
            62972.92665,(CLHEPfloat)475554.6998,(CLHEPfloat)-5743609.109 };
    static CLHEPfloat q6[5] = { (CLHEPfloat)1.,(CLHEPfloat)651.4101098,(CLHEPfloat)56974.73333,(
            CLHEPfloat)165917.4725,(CLHEPfloat)-2815759.939 };
    static CLHEPfloat a1[3] = { (CLHEPfloat).04166666667,(CLHEPfloat)-.01996527778,(CLHEPfloat)
            .02709538966 };
    static CLHEPfloat a2[2] = { (CLHEPfloat)-1.84556867,(CLHEPfloat)-4.284640743 };
    static CLHEPfloat q1[5] = { (CLHEPfloat)1.,(CLHEPfloat)-.3388260629,(CLHEPfloat).09594393323,(
            CLHEPfloat)-.01608042283,(CLHEPfloat).003778942063 };
    static CLHEPfloat p2[5] = { (CLHEPfloat).1788541609,(CLHEPfloat).1173957403,(CLHEPfloat)
            .01488850518,(CLHEPfloat)-.001394989411,(CLHEPfloat)1.283617211e-4 };
    static CLHEPfloat q2[5] = { (CLHEPfloat)1.,(CLHEPfloat).7428795082,(CLHEPfloat).3153932961,(
            CLHEPfloat).06694219548,(CLHEPfloat).008790609714 };
    static CLHEPfloat p3[5] = { (CLHEPfloat).1788544503,(CLHEPfloat).09359161662,(CLHEPfloat)
            .006325387654,(CLHEPfloat)6.611667319e-5,(CLHEPfloat)-2.031049101e-6 };
    static CLHEPfloat q3[5] = { (CLHEPfloat)1.,(CLHEPfloat).6097809921,(CLHEPfloat).2560616665,(
            CLHEPfloat).04746722384,(CLHEPfloat).006957301675 };
    static CLHEPfloat p4[5] = { (CLHEPfloat).9874054407,(CLHEPfloat)118.6723273,(CLHEPfloat)
            849.279436,(CLHEPfloat)-743.7792444,(CLHEPfloat)427.0262186 };
    static CLHEPfloat q4[5] = { (CLHEPfloat)1.,(CLHEPfloat)106.8615961,(CLHEPfloat)337.6496214,(
            CLHEPfloat)2016.712389,(CLHEPfloat)1597.063511 };
    static CLHEPfloat p5[5] = { (CLHEPfloat)1.003675074,(CLHEPfloat)167.5702434,(CLHEPfloat)
            4789.711289,(CLHEPfloat)21217.86767,(CLHEPfloat)-22324.9491 };

    /* System generated locals */
    CLHEPfloat ret_val, r__1;

    /* Local variables */
    static CLHEPfloat u, v;
    v = x;
    if (v < (CLHEPfloat)-5.5) {
        u = exp(v + (CLHEPfloat)1.);
        ret_val = exp(-1 / u) / sqrt(u) * (CLHEPfloat).3989422803 * ((a1[0] + (a1[
                1] + a1[2] * u) * u) * u + 1);
    } else if (v < (CLHEPfloat)-1.) {
        u = exp(-v - 1);
        ret_val = exp(-u) * sqrt(u) * (p1[0] + (p1[1] + (p1[2] + (p1[3] + p1[
                4] * v) * v) * v) * v) / (q1[0] + (q1[1] + (q1[2] + (q1[3] + 
                q1[4] * v) * v) * v) * v);
    } else if (v < (CLHEPfloat)1.) {
        ret_val = (p2[0] + (p2[1] + (p2[2] + (p2[3] + p2[4] * v) * v) * v) * 
                v) / (q2[0] + (q2[1] + (q2[2] + (q2[3] + q2[4] * v) * v) * v) 
                * v);
    } else if (v < (CLHEPfloat)5.) {
        ret_val = (p3[0] + (p3[1] + (p3[2] + (p3[3] + p3[4] * v) * v) * v) * 
                v) / (q3[0] + (q3[1] + (q3[2] + (q3[3] + q3[4] * v) * v) * v) 
                * v);
    } else if (v < (CLHEPfloat)12.) {
        u = 1 / v;
/* Computing 2nd power */
        r__1 = u;
        ret_val = r__1 * r__1 * (p4[0] + (p4[1] + (p4[2] + (p4[3] + p4[4] * u)
                 * u) * u) * u) / (q4[0] + (q4[1] + (q4[2] + (q4[3] + q4[4] * 
                u) * u) * u) * u);
    } else if (v < (CLHEPfloat)50.) {
        u = 1 / v;
/* Computing 2nd power */
        r__1 = u;
        ret_val = r__1 * r__1 * (p5[0] + (p5[1] + (p5[2] + (p5[3] + p5[4] * u)
                 * u) * u) * u) / (q5[0] + (q5[1] + (q5[2] + (q5[3] + q5[4] * 
                u) * u) * u) * u);
    } else if (v < (CLHEPfloat)300.) {
        u = 1 / v;
/* Computing 2nd power */
        r__1 = u;
        ret_val = r__1 * r__1 * (p6[0] + (p6[1] + (p6[2] + (p6[3] + p6[4] * u)
                 * u) * u) * u) / (q6[0] + (q6[1] + (q6[2] + (q6[3] + q6[4] * 
                u) * u) * u) * u);
    } else {
        u = 1 / (v - v * log(v) / (v + 1));
/* Computing 2nd power */
        r__1 = u;
        ret_val = r__1 * r__1 * ((a2[0] + a2[1] * u) * u + 1);
    }
    return ret_val;

}

} // namespace Genfun
