#include "CLHEPTypes.hpp"
// -*- C++ -*-
// $Id: Normal3D.cc,v 1.3 2003/08/13 20:00:11 garren Exp $
// ---------------------------------------------------------------------------

#include "CLHEP/Geometry/defs.h"
#include "CLHEP/Geometry/Normal3D.h"
#include "CLHEP/Geometry/Transform3D.h"

namespace HepGeom {
  //--------------------------------------------------------------------------
  Normal3D<CLHEPfloat> &
  Normal3D<CLHEPfloat>::transform(const Transform3D & m) {
    CLHEPdouble vx = x(),    vy = y(),    vz = z();
    CLHEPdouble xx = m.xx(), xy = m.xy(), xz = m.xz();
    CLHEPdouble yx = m.yx(), yy = m.yy(), yz = m.yz();
    CLHEPdouble zx = m.zx(), zy = m.zy(), zz = m.zz();
    set((yy*zz-yz*zy)*vx+(yz*zx-yx*zz)*vy+(yx*zy-yy*zx)*vz,
	(zy*xz-zz*xy)*vx+(zz*xx-zx*xz)*vy+(zx*xy-zy*xx)*vz,
	(xy*yz-xz*yy)*vx+(xz*yx-xx*yz)*vy+(xx*yy-xy*yx)*vz);
    return *this;
  }

  //--------------------------------------------------------------------------
  Normal3D<CLHEPfloat>
  operator*(const Transform3D & m, const Normal3D<CLHEPfloat> & v) {
    CLHEPdouble vx = v.x(),  vy = v.y(),  vz = v.z();
    CLHEPdouble xx = m.xx(), xy = m.xy(), xz = m.xz();
    CLHEPdouble yx = m.yx(), yy = m.yy(), yz = m.yz();
    CLHEPdouble zx = m.zx(), zy = m.zy(), zz = m.zz();
    return Normal3D<CLHEPfloat>
      ((yy*zz-yz*zy)*vx+(yz*zx-yx*zz)*vy+(yx*zy-yy*zx)*vz,
       (zy*xz-zz*xy)*vx+(zz*xx-zx*xz)*vy+(zx*xy-zy*xx)*vz,
       (xy*yz-xz*yy)*vx+(xz*yx-xx*yz)*vy+(xx*yy-xy*yx)*vz);
  }

  //--------------------------------------------------------------------------
  Normal3D<CLHEPdouble> &
  Normal3D<CLHEPdouble>::transform(const Transform3D & m) {
    CLHEPdouble vx = x(),    vy = y(),    vz = z();
    CLHEPdouble xx = m.xx(), xy = m.xy(), xz = m.xz();
    CLHEPdouble yx = m.yx(), yy = m.yy(), yz = m.yz();
    CLHEPdouble zx = m.zx(), zy = m.zy(), zz = m.zz();
    set((yy*zz-yz*zy)*vx+(yz*zx-yx*zz)*vy+(yx*zy-yy*zx)*vz,
	(zy*xz-zz*xy)*vx+(zz*xx-zx*xz)*vy+(zx*xy-zy*xx)*vz,
	(xy*yz-xz*yy)*vx+(xz*yx-xx*yz)*vy+(xx*yy-xy*yx)*vz);
    return *this;
  }

  //--------------------------------------------------------------------------
  Normal3D<CLHEPdouble>
  operator*(const Transform3D & m, const Normal3D<CLHEPdouble> & v) {
    CLHEPdouble vx = v.x(),  vy = v.y(),  vz = v.z();
    CLHEPdouble xx = m.xx(), xy = m.xy(), xz = m.xz();
    CLHEPdouble yx = m.yx(), yy = m.yy(), yz = m.yz();
    CLHEPdouble zx = m.zx(), zy = m.zy(), zz = m.zz();
    return Normal3D<CLHEPdouble>
      ((yy*zz-yz*zy)*vx+(yz*zx-yx*zz)*vy+(yx*zy-yy*zx)*vz,
       (zy*xz-zz*xy)*vx+(zz*xx-zx*xz)*vy+(zx*xy-zy*xx)*vz,
       (xy*yz-xz*yy)*vx+(xz*yx-xx*yz)*vy+(xx*yy-xy*yx)*vz);
  }
} /* namespace HepGeom */
