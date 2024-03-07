#include "CLHEPTypes.hpp"
// -*- C++ -*-
// $Id: Vector3D.cc,v 1.3 2003/08/13 20:00:11 garren Exp $
// ---------------------------------------------------------------------------

#include "CLHEP/Geometry/defs.h"
#include "CLHEP/Geometry/Vector3D.h"
#include "CLHEP/Geometry/Transform3D.h"

namespace HepGeom {
  //--------------------------------------------------------------------------
  Vector3D<CLHEPfloat> &
  Vector3D<CLHEPfloat>::transform(const Transform3D & m) {
    CLHEPdouble vx = x(), vy = y(), vz = z();
    set(m.xx()*vx + m.xy()*vy + m.xz()*vz,
	m.yx()*vx + m.yy()*vy + m.yz()*vz,
	m.zx()*vx + m.zy()*vy + m.zz()*vz);
    return *this;
  }

  //--------------------------------------------------------------------------
  Vector3D<CLHEPfloat>
  operator*(const Transform3D & m, const Vector3D<CLHEPfloat> & v) {
    CLHEPdouble vx = v.x(), vy = v.y(), vz = v.z();
    return Vector3D<CLHEPfloat>
      (m.xx()*vx + m.xy()*vy + m.xz()*vz,
       m.yx()*vx + m.yy()*vy + m.yz()*vz,
       m.zx()*vx + m.zy()*vy + m.zz()*vz);
  }

  //--------------------------------------------------------------------------
  Vector3D<CLHEPdouble> &
  Vector3D<CLHEPdouble>::transform(const Transform3D & m) {
    CLHEPdouble vx = x(), vy = y(), vz = z();
    set(m.xx()*vx + m.xy()*vy + m.xz()*vz,
	m.yx()*vx + m.yy()*vy + m.yz()*vz,
	m.zx()*vx + m.zy()*vy + m.zz()*vz);
    return *this;
  }

  //--------------------------------------------------------------------------
  Vector3D<CLHEPdouble>
  operator*(const Transform3D & m, const Vector3D<CLHEPdouble> & v) {
    CLHEPdouble vx = v.x(), vy = v.y(), vz = v.z();
    return Vector3D<CLHEPdouble>
      (m.xx()*vx + m.xy()*vy + m.xz()*vz,
       m.yx()*vx + m.yy()*vy + m.yz()*vz,
       m.zx()*vx + m.zy()*vy + m.zz()*vz);
  }
} /* namespace HepGeom */
