#include "CLHEPTypes.hpp"
// -*- C++ -*-
// ---------------------------------------------------------------------------
//
// This file is a part of the CLHEP - a Class Library for High Energy Physics.
//
// This is the implementation of the subset of those methods of the Hep3Vector 
// class which originated from the ZOOM SpaceVector class *and* which involve
// the concepts of rotation.
//

#include "CLHEP/Vector/defs.h"
#include "CLHEP/Vector/ThreeVector.h"
#include "CLHEP/Vector/AxisAngle.h"
#include "CLHEP/Vector/EulerAngles.h"
#include "CLHEP/Vector/ZMxpv.h"

#include <cmath>
#include <iostream>

namespace CLHEP  {

//-************************
// rotate about axis
//-************************

Hep3Vector & Hep3Vector::rotate (const Hep3Vector & axis,
				   CLHEPdouble ddelta) {
  CLHEPdouble r1 = axis.mag();
  if ( r1 == 0 ) {
    ZMthrowA (ZMxpvZeroVector(
      "Attempt to rotate around a zero vector axis! "));
    return *this;
  }
  CLHEPdouble scale=1.0/r1;
  CLHEPdouble ux = scale*axis.getX();
  CLHEPdouble uy = scale*axis.getY();
  CLHEPdouble uz = scale*axis.getZ();
  CLHEPdouble cd = std::cos(ddelta);
  CLHEPdouble sd = std::sin(ddelta);
  CLHEPdouble ocd = 1 - cd;
  CLHEPdouble rx;
  CLHEPdouble ry;
  CLHEPdouble rz;

  { CLHEPdouble  ocdux = ocd * ux;
    rx = x() * ( cd + ocdux * ux           ) +
         y() * (      ocdux * uy - sd * uz ) +
         z() * (      ocdux * uz + sd * uy ) ;
  }

  { CLHEPdouble  ocduy = ocd * uy;
    ry = y() * ( cd + ocduy * uy           ) +
         z() * (      ocduy * uz - sd * ux ) +
         x() * (      ocduy * ux + sd * uz ) ;
  }

  { CLHEPdouble  ocduz = ocd * uz;
    rz = z() * ( cd + ocduz * uz           ) +
         x() * (      ocduz * ux - sd * uy ) +
         y() * (      ocduz * uy + sd * ux ) ;
  }

  set(rx, ry, rz);
  return *this;
} /* rotate */


//-****************************
// rotate by three euler angles
//-****************************


Hep3Vector & Hep3Vector::rotate (CLHEPdouble phi1, 
				 CLHEPdouble theta1, 
				 CLHEPdouble psi1)  {

  CLHEPdouble rx;
  CLHEPdouble ry;
  CLHEPdouble rz;

  CLHEPdouble sinPhi   = std::sin( phi1   ), cosPhi   = std::cos( phi1   );
  CLHEPdouble sinTheta = std::sin( theta1 ), cosTheta1 = std::cos( theta1 );
  CLHEPdouble sinPsi   = std::sin( psi1   ), cosPsi   = std::cos( psi1   );

  rx = 	(cosPsi * cosPhi   - cosTheta1 * sinPsi * sinPhi)   * x()  +
	(cosPsi * sinPhi   + cosTheta1 * sinPsi * cosPhi)   * y()  +
  	(sinPsi * sinTheta)				   * z()  ;

  ry = 	(- sinPsi * cosPhi - cosTheta1 * cosPsi * sinPhi)   * x()  +
	(- sinPsi * sinPhi + cosTheta1 * cosPsi * cosPhi)   * y()  +
  	(cosPsi * sinTheta)				   * z()  ;

  rz = 	(sinTheta * sinPhi)				   * x()  +
  	(- sinTheta * cosPhi)				   * y()  +
	(cosTheta1)					   * z()  ;

  set(rx, ry, rz);
  return *this;

} /* rotate */



//-*******************
// rotate(HepAxisAngle)
// rotate(HepEulerAngles)
//-*******************

Hep3Vector & Hep3Vector::rotate (const HepAxisAngle & ax ) {
  return rotate( ax.getAxis(), ax.delta() );
}

Hep3Vector & Hep3Vector::rotate (const HepEulerAngles & ex ) {
  return rotate( ex.phi(), ex.theta(), ex.psi() );
}


//-***********************
// rotationOf(HepAxisAngle)
// rotationOf(HepEulerAngles)
// and coordinate axis rotations
//-***********************

Hep3Vector rotationOf (const Hep3Vector & vec, const HepAxisAngle & ax) {
  Hep3Vector vv(vec);
  return vv.rotate (ax);
}

Hep3Vector rotationOf (const Hep3Vector & vec,
                       const Hep3Vector & axis, CLHEPdouble ddelta) {
  Hep3Vector vv(vec);
  return vv.rotate(axis, ddelta);
}

Hep3Vector rotationOf (const Hep3Vector & vec, const HepEulerAngles & ex) {
  Hep3Vector vv(vec);
  return vv.rotate (ex);
}

Hep3Vector rotationOf (const Hep3Vector & vec,
                       CLHEPdouble phi, CLHEPdouble theta, CLHEPdouble psi) {
  Hep3Vector vv(vec);
  return vv.rotate(phi, theta, psi);
}

Hep3Vector rotationXOf (const Hep3Vector & vec, CLHEPdouble ddelta) {
  Hep3Vector vv(vec);
  return vv.rotateX (ddelta);
}

Hep3Vector rotationYOf (const Hep3Vector & vec, CLHEPdouble ddelta) {
  Hep3Vector vv(vec);
  return vv.rotateY (ddelta);
}

Hep3Vector rotationZOf (const Hep3Vector & vec, CLHEPdouble ddelta) {
  Hep3Vector vv(vec);
  return vv.rotateZ (ddelta);
}

}  // namespace CLHEP

