#include "CLHEPTypes.hpp"
// -*- C++ -*-
// $Id: BasicVector3D.cc,v 1.3 2003/08/13 20:00:11 garren Exp $
// ---------------------------------------------------------------------------

#include <math.h>
#include <float.h>
#include <iostream>
#include "CLHEP/Geometry/defs.h"
#include "CLHEP/Geometry/BasicVector3D.h"

namespace HepGeom {
  //--------------------------------------------------------------------------
  template<>
  CLHEPfloat BasicVector3D<CLHEPfloat>::pseudoRapidity() const {
    CLHEPfloat ma = mag(), dz = z();
    if (ma ==  0)  return  0;
    if (ma ==  dz) return  FLT_MAX;
    if (ma == -dz) return -FLT_MAX;
    return 0.5*std::log((ma+dz)/(ma-dz));
  }

  //--------------------------------------------------------------------------
  template<>
  void BasicVector3D<CLHEPfloat>::setEta(CLHEPfloat a) {
    CLHEPdouble ma = mag();
    if (ma == 0) return;
    CLHEPdouble tanHalfTheta  = std::exp(-a);
    CLHEPdouble tanHalfTheta2 = tanHalfTheta * tanHalfTheta;
    CLHEPdouble cosTheta1      = (1 - tanHalfTheta2) / (1 + tanHalfTheta2);
    CLHEPdouble rh            = ma * std::sqrt(1 - cosTheta1*cosTheta1);
    CLHEPdouble ph            = phi();
    set(rh*std::cos(ph), rh*std::sin(ph), ma*cosTheta1);
  }

  //--------------------------------------------------------------------------
  template<>
  CLHEPfloat BasicVector3D<CLHEPfloat>::angle(const BasicVector3D<CLHEPfloat> & v) const {
    CLHEPdouble cosa = 0;
    CLHEPdouble ptot = mag()*v.mag();
    if(ptot > 0) {
      cosa = dot(v)/ptot;
      if(cosa >  1) cosa =  1;
      if(cosa < -1) cosa = -1;
    }
    return std::acos(cosa);
  }

  //--------------------------------------------------------------------------
  template<>
  BasicVector3D<CLHEPfloat> & BasicVector3D<CLHEPfloat>::rotateX(CLHEPfloat a) {
    CLHEPdouble sina = std::sin(a), cosa = std::cos(a), dy = y(), dz = z();
    setY(dy*cosa-dz*sina);
    setZ(dz*cosa+dy*sina);
    return *this;
  }

  //--------------------------------------------------------------------------
  template<>
  BasicVector3D<CLHEPfloat> & BasicVector3D<CLHEPfloat>::rotateY(CLHEPfloat a) {
    CLHEPdouble sina = std::sin(a), cosa = std::cos(a), dz = z(), dx = x();
    setZ(dz*cosa-dx*sina);
    setX(dx*cosa+dz*sina);
    return *this;
  }

  //--------------------------------------------------------------------------
  template<>
  BasicVector3D<CLHEPfloat> & BasicVector3D<CLHEPfloat>::rotateZ(CLHEPfloat a) {
    CLHEPdouble sina = std::sin(a), cosa = std::cos(a), dx = x(), dy = y();
    setX(dx*cosa-dy*sina);
    setY(dy*cosa+dx*sina);
    return *this;
  }

  //--------------------------------------------------------------------------
  template<>
  BasicVector3D<CLHEPfloat> &
  BasicVector3D<CLHEPfloat>::rotate(CLHEPfloat a, const BasicVector3D<CLHEPfloat> & v) {
    if (a  == 0) return *this;
    CLHEPdouble cx = v.x(), cy = v.y(), cz = v.z();
    CLHEPdouble ll = std::sqrt(cx*cx + cy*cy + cz*cz);
    if (ll == 0) {
      std::cerr << "BasicVector<CLHEPfloat>::rotate() : zero axis" << std::endl;
      return *this;
    }
    CLHEPdouble cosa = std::cos(a), sina = std::sin(a);
    cx /= ll; cy /= ll; cz /= ll;   

    CLHEPdouble xx = cosa + (1-cosa)*cx*cx;
    CLHEPdouble xy =        (1-cosa)*cx*cy - sina*cz;
    CLHEPdouble xz =        (1-cosa)*cx*cz + sina*cy;
    
    CLHEPdouble yx =        (1-cosa)*cy*cx + sina*cz;
    CLHEPdouble yy = cosa + (1-cosa)*cy*cy; 
    CLHEPdouble yz =        (1-cosa)*cy*cz - sina*cx;
    
    CLHEPdouble zx =        (1-cosa)*cz*cx - sina*cy;
    CLHEPdouble zy =        (1-cosa)*cz*cy + sina*cx;
    CLHEPdouble zz = cosa + (1-cosa)*cz*cz;

    cx = x(); cy = y(); cz = z();   
    set(xx*cx+xy*cy+xz*cz, yx*cx+yy*cy+yz*cz, zx*cx+zy*cy+zz*cz);
    return *this;
  }

  //--------------------------------------------------------------------------
  std::ostream &
  operator<<(std::ostream & os, const BasicVector3D<CLHEPfloat> & a)
  {
    return os << "(" << a.x() << "," << a.y() << "," << a.z() << ")";
  }

  //--------------------------------------------------------------------------
  std::istream &
  operator>> (std::istream & is, BasicVector3D<CLHEPfloat> & a)
  {
    // Required format is ( a, b, c ) that is, three numbers, preceded by
    // (, followed by ), and separated by commas.  The three numbers are
    // taken as x, y, z.

    CLHEPfloat x, y, z;
    char c;

    is >> std::ws >> c;
    // ws is defined to invoke eatwhite(istream & )
    // see (Stroustrup gray book) page 333 and 345.
    if (is.fail() || c != '(' ) {
      std::cerr
	<< "Could not find required opening parenthesis "
	<< "in input of a BasicVector3D<CLHEPfloat>"
	<< std::endl;
      return is;
    }

    is >> x >> std::ws >> c;
    if (is.fail() || c != ',' ) {
      std::cerr
	<< "Could not find x value and required trailing comma "
	<< "in input of a BasicVector3D<CLHEPfloat>"
	<< std::endl; 
      return is;
    }

    is >> y >> std::ws >> c;
    if (is.fail() || c != ',' ) {
      std::cerr
	<< "Could not find y value and required trailing comma "
	<<  "in input of a BasicVector3D<CLHEPfloat>"
	<< std::endl;
      return is;
    }

    is >> z >> std::ws >> c;
    if (is.fail() || c != ')' ) {
      std::cerr
	<< "Could not find z value and required close parenthesis "
	<< "in input of a BasicVector3D<CLHEPfloat>"
	<< std::endl;
      return is;
    }

    a.setX(x);
    a.setY(y);
    a.setZ(z);
    return is;
  }
  
  //--------------------------------------------------------------------------
  template<>
  CLHEPdouble BasicVector3D<CLHEPdouble>::pseudoRapidity() const {
    CLHEPdouble ma = mag(), dz = z();
    if (ma ==  0)  return  0;
    if (ma ==  dz) return  DBL_MAX;
    if (ma == -dz) return -DBL_MAX;
    return 0.5*std::log((ma+dz)/(ma-dz));
  }

  //--------------------------------------------------------------------------
  template<>
  void BasicVector3D<CLHEPdouble>::setEta(CLHEPdouble a) {
    CLHEPdouble ma = mag();
    if (ma == 0) return;
    CLHEPdouble tanHalfTheta  = std::exp(-a);
    CLHEPdouble tanHalfTheta2 = tanHalfTheta * tanHalfTheta;
    CLHEPdouble cosTheta1      = (1 - tanHalfTheta2) / (1 + tanHalfTheta2);
    CLHEPdouble rh            = ma * std::sqrt(1 - cosTheta1*cosTheta1);
    CLHEPdouble ph            = phi();
    set(rh*std::cos(ph), rh*std::sin(ph), ma*cosTheta1);
  }

  //--------------------------------------------------------------------------
  template<>
  CLHEPdouble BasicVector3D<CLHEPdouble>::angle(const BasicVector3D<CLHEPdouble> & v) const {
    CLHEPdouble cosa = 0;
    CLHEPdouble ptot = mag()*v.mag();
    if(ptot > 0) {
      cosa = dot(v)/ptot;
      if(cosa >  1) cosa =  1;
      if(cosa < -1) cosa = -1;
    }
    return std::acos(cosa);
  }

  //--------------------------------------------------------------------------
  template<>
  BasicVector3D<CLHEPdouble> & BasicVector3D<CLHEPdouble>::rotateX(CLHEPdouble a) {
    CLHEPdouble sina = std::sin(a), cosa = std::cos(a), dy = y(), dz = z();
    setY(dy*cosa-dz*sina);
    setZ(dz*cosa+dy*sina);
    return *this;
  }

  //--------------------------------------------------------------------------
  template<>
  BasicVector3D<CLHEPdouble> & BasicVector3D<CLHEPdouble>::rotateY(CLHEPdouble a) {
    CLHEPdouble sina = std::sin(a), cosa = std::cos(a), dz = z(), dx = x();
    setZ(dz*cosa-dx*sina);
    setX(dx*cosa+dz*sina);
    return *this;
  }

  //--------------------------------------------------------------------------
  template<>
  BasicVector3D<CLHEPdouble> & BasicVector3D<CLHEPdouble>::rotateZ(CLHEPdouble a) {
    CLHEPdouble sina = std::sin(a), cosa = std::cos(a), dx = x(), dy = y();
    setX(dx*cosa-dy*sina);
    setY(dy*cosa+dx*sina);
    return *this;
  }

  //--------------------------------------------------------------------------
  template<>
  BasicVector3D<CLHEPdouble> &
  BasicVector3D<CLHEPdouble>::rotate(CLHEPdouble a, const BasicVector3D<CLHEPdouble> & v) {
    if (a  == 0) return *this;
    CLHEPdouble cx = v.x(), cy = v.y(), cz = v.z();
    CLHEPdouble ll = std::sqrt(cx*cx + cy*cy + cz*cz);
    if (ll == 0) {
      std::cerr << "BasicVector<CLHEPdouble>::rotate() : zero axis" << std::endl;
      return *this;
    }
    CLHEPdouble cosa = std::cos(a), sina = std::sin(a);
    cx /= ll; cy /= ll; cz /= ll;   

    CLHEPdouble xx = cosa + (1-cosa)*cx*cx;
    CLHEPdouble xy =        (1-cosa)*cx*cy - sina*cz;
    CLHEPdouble xz =        (1-cosa)*cx*cz + sina*cy;
    
    CLHEPdouble yx =        (1-cosa)*cy*cx + sina*cz;
    CLHEPdouble yy = cosa + (1-cosa)*cy*cy; 
    CLHEPdouble yz =        (1-cosa)*cy*cz - sina*cx;
    
    CLHEPdouble zx =        (1-cosa)*cz*cx - sina*cy;
    CLHEPdouble zy =        (1-cosa)*cz*cy + sina*cx;
    CLHEPdouble zz = cosa + (1-cosa)*cz*cz;

    cx = x(); cy = y(); cz = z();   
    set(xx*cx+xy*cy+xz*cz, yx*cx+yy*cy+yz*cz, zx*cx+zy*cy+zz*cz);
    return *this;
  }

  //--------------------------------------------------------------------------
  std::ostream &
  operator<< (std::ostream & os, const BasicVector3D<CLHEPdouble> & a)
  {
    return os << "(" << a.x() << "," << a.y() << "," << a.z() << ")";
  }
  
  //--------------------------------------------------------------------------
  std::istream &
  operator>> (std::istream & is, BasicVector3D<CLHEPdouble> & a)
  {
    // Required format is ( a, b, c ) that is, three numbers, preceded by
    // (, followed by ), and separated by commas.  The three numbers are
    // taken as x, y, z.
    
    CLHEPdouble x, y, z;
    char c;
    
    is >> std::ws >> c;
    // ws is defined to invoke eatwhite(istream & )
    // see (Stroustrup gray book) page 333 and 345.
    if (is.fail() || c != '(' ) {
      std::cerr
	<< "Could not find required opening parenthesis "
	<< "in input of a BasicVector3D<CLHEPdouble>"
	<< std::endl;
      return is;
    }

    is >> x >> std::ws >> c;
    if (is.fail() || c != ',' ) {
      std::cerr
	<< "Could not find x value and required trailing comma "
	<< "in input of a BasicVector3D<CLHEPdouble>"
	<< std::endl; 
      return is;
    }

    is >> y >> std::ws >> c;
    if (is.fail() || c != ',' ) {
      std::cerr
	<< "Could not find y value and required trailing comma "
	<<  "in input of a BasicVector3D<CLHEPdouble>"
	<< std::endl;
      return is;
    }

    is >> z >> std::ws >> c;
    if (is.fail() || c != ')' ) {
      std::cerr
	<< "Could not find z value and required close parenthesis "
	<< "in input of a BasicVector3D<CLHEPdouble>"
	<< std::endl;
      return is;
    }

    a.setX(x);
    a.setY(y);
    a.setZ(z);
    return is;
  }
} /* namespace HepGeom */
