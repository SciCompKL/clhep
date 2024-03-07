#include "CLHEPTypes.hpp"
// -*- C++ -*-
// $Id: RotationInterfaces.cc,v 1.2 2003/08/13 20:00:14 garren Exp $
// ---------------------------------------------------------------------------
//
// This file is a part of the CLHEP - a Class Library for High Energy Physics.
//
// This is the implementation of those few parts of the Hep4RotationInterface
// and Hep3RotationInterface classes which are neither inline nor pure virtual.
//

#include "CLHEP/Vector/defs.h"
#include "CLHEP/Vector/RotationInterfaces.h"

namespace CLHEP  {

//-******************************
//
// Hep4RotationInterface
//
//-******************************

CLHEPdouble Hep4RotationInterface::getTolerance() {return tolerance;} 
CLHEPdouble Hep4RotationInterface::setTolerance( CLHEPdouble tol ) {
  CLHEPdouble t = tolerance; tolerance = tol; return t;
}

CLHEPdouble Hep4RotationInterface::tolerance = 
			Hep4RotationInterface::ToleranceTicks * 1.0e-08;


//-******************************
//
// Hep3RotationInterface
//
//-******************************

}  // namespace CLHEP
