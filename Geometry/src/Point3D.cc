#include "CLHEPTypes.hpp"
// -*- C++ -*-
// $Id: Point3D.cc,v 1.3 2003/08/13 20:00:11 garren Exp $
// ---------------------------------------------------------------------------

#include "CLHEP/Geometry/defs.h"
#include "CLHEP/Geometry/Point3D.h"
#include "CLHEP/Geometry/Transform3D.h"

namespace HepGeom {
  //--------------------------------------------------------------------------
  Point3D<CLHEPfloat> &
  Point3D<CLHEPfloat>::transform(const Transform3D & m) {
    CLHEPdouble vx = x(), vy = y(), vz = z();
    set(m.xx()*vx + m.xy()*vy + m.xz()*vz + m.dx(),
	m.yx()*vx + m.yy()*vy + m.yz()*vz + m.dy(),
	m.zx()*vx + m.zy()*vy + m.zz()*vz + m.dz());
    return *this;
  }

  //--------------------------------------------------------------------------
  Point3D<CLHEPfloat>
  operator*(const Transform3D & m, const Point3D<CLHEPfloat> & v) {
    CLHEPdouble vx = v.x(), vy = v.y(), vz = v.z();
    return Point3D<CLHEPfloat>
      (m.xx()*vx + m.xy()*vy + m.xz()*vz + m.dx(),
       m.yx()*vx + m.yy()*vy + m.yz()*vz + m.dy(),
       m.zx()*vx + m.zy()*vy + m.zz()*vz + m.dz());
  }

  //--------------------------------------------------------------------------
  Point3D<CLHEPdouble> &
  Point3D<CLHEPdouble>::transform(const Transform3D & m) {
    CLHEPdouble vx = x(), vy = y(), vz = z();
    set(m.xx()*vx + m.xy()*vy + m.xz()*vz + m.dx(),
	m.yx()*vx + m.yy()*vy + m.yz()*vz + m.dy(),
	m.zx()*vx + m.zy()*vy + m.zz()*vz + m.dz());
    return *this;
  }

  //--------------------------------------------------------------------------
  Point3D<CLHEPdouble>
  operator*(const Transform3D & m, const Point3D<CLHEPdouble> & v) {
    CLHEPdouble vx = v.x(), vy = v.y(), vz = v.z();
    return Point3D<CLHEPdouble>
      (m.xx()*vx + m.xy()*vy + m.xz()*vz + m.dx(),
       m.yx()*vx + m.yy()*vy + m.yz()*vz + m.dy(),
       m.zx()*vx + m.zy()*vy + m.zz()*vz + m.dz());
  }
} /* namespace HepGeom */
