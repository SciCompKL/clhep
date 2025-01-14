#include "CLHEPTypes.hpp"
// -*- C++ -*-
// $Id: Plane3D.cc,v 1.4 2003/08/13 20:00:11 garren Exp $
// ---------------------------------------------------------------------------
//
// This file is a part of the CLHEP - a Class Library for High Energy Physics.
//
// Hep geometrical 3D Plane class
//
// Author: Evgeni Chernyaev <Evgueni.Tcherniaev@cern.ch>
//
// History:
// 22.09.96 E.Chernyaev - initial version
// 19.10.96 J.Allison - added == and <<.
// 15.04.03 E.Chernyaev - CLHEP-1.9: template version

#include <iostream>
#include "CLHEP/Geometry/defs.h"
#include "CLHEP/Geometry/Plane3D.h"

namespace HepGeom {
  //--------------------------------------------------------------------------
  std::ostream &
  operator<<(std::ostream & os, const Plane3D<CLHEPfloat> & p) {
    return os
      << '(' << p.a() << ',' << p.b() << ',' << p.c() << ',' << p.d() << ')';
  }

  //--------------------------------------------------------------------------
  std::ostream &
  operator<<(std::ostream & os, const Plane3D<CLHEPdouble> & p) {
    return os
      << '(' << p.a() << ',' << p.b() << ',' << p.c() << ',' << p.d() << ')';
  }
} /* namespace HepGeom */
