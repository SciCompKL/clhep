#include "CLHEPTypes.hpp"
// -*- C++ -*-
// $Id: Normal3D.h,v 1.3 2003/10/23 21:29:50 garren Exp $
// ---------------------------------------------------------------------------
//
// This file is a part of the CLHEP - a Class Library for High Energy Physics.
//
// History:
// 09.09.96 E.Chernyaev - initial version
// 12.06.01 E.Chernyaev - CLHEP-1.7: introduction of BasicVector3D to decouple
//                        the functionality from CLHEP::Hep3Vector
// 01.04.03 E.Chernyaev - CLHEP-1.9: template version
//

#ifndef HEP_NORMAL3D_H
#define HEP_NORMAL3D_H

#include <iosfwd>
#include "CLHEP/Geometry/defs.h"
#include "CLHEP/Vector/ThreeVector.h"
#include "CLHEP/Geometry/BasicVector3D.h"

namespace HepGeom {

  class Transform3D;

  /**
   * Geometrical 3D Normal.
   * This is just a declaration of the class needed to define
   * specializations Normal3D<CLHEPfloat> and Normal3D<CLHEPdouble>.
   *
   * @ingroup geometry
   * @author Evgeni Chernyaev <Evgueni.Tcherniaev@cern.ch>
   */
  template<class T>
  class Normal3D : public BasicVector3D<T> {};

  /**
   * Geometrical 3D Normal with components of CLHEPfloat type.
   *
   * @author Evgeni Chernyaev <Evgueni.Tcherniaev@cern.ch>
   * @ingroup geometry
   */
  template<>
  class Normal3D<CLHEPfloat> : public BasicVector3D<CLHEPfloat> {
  public:
    /**
     * Default constructor. */
    Normal3D() = default;

    /**
     * Constructor from three numbers. */
    Normal3D(CLHEPfloat x1, CLHEPfloat y1, CLHEPfloat z1) : BasicVector3D<CLHEPfloat>(x1,y1,z1) {}

    /**
     * Constructor from array of CLHEPfloats. */
    explicit Normal3D(const CLHEPfloat * a)
      : BasicVector3D<CLHEPfloat>(a[0],a[1],a[2]) {}

    /**
     * Copy constructor. */
    Normal3D(const Normal3D<CLHEPfloat> &) = default;

    /**
     * Move constructor. */
    Normal3D(Normal3D<CLHEPfloat> &&) = default;

    /**
     * Constructor from BasicVector3D<CLHEPfloat>. */
    Normal3D(const BasicVector3D<CLHEPfloat> & v) : BasicVector3D<CLHEPfloat>(v) {}

    /**
     * Destructor. */
    ~Normal3D() = default;

    /**
     * Assignment. */
    Normal3D<CLHEPfloat> & operator=(const Normal3D<CLHEPfloat> &) = default;

    /**
     * Assignment from BasicVector3D<CLHEPfloat>. */
    Normal3D<CLHEPfloat> & operator=(const BasicVector3D<CLHEPfloat> & v) {
      this->BasicVector3D<CLHEPfloat>::operator=(v);
      return *this;
    }

    /**
     * Move assignment. */
    Normal3D<CLHEPfloat> & operator=(Normal3D<CLHEPfloat> &&) = default;

    /**
     * Transformation by Transform3D. */
    Normal3D<CLHEPfloat> & transform(const Transform3D & m);
  };

  /**
   * Transformation of Normal<CLHEPfloat> by Transform3D.
   * @relates Normal3D
   */
  Normal3D<CLHEPfloat>
  operator*(const Transform3D & m, const Normal3D<CLHEPfloat> & n);

  /**
   * Geometrical 3D Normal with components of CLHEPdouble type.
   *
   * @author Evgeni Chernyaev <Evgueni.Tcherniaev@cern.ch>
   * @ingroup geometry
   */
  template<>
  class Normal3D<CLHEPdouble> : public BasicVector3D<CLHEPdouble> {
  public:
    /**
     * Default constructor. */
    Normal3D() = default;

    /**
     * Constructor from three numbers. */
    Normal3D(CLHEPdouble x1, CLHEPdouble y1, CLHEPdouble z1) : BasicVector3D<CLHEPdouble>(x1,y1,z1) {}

    /**
     * Constructor from array of CLHEPfloats. */
    explicit Normal3D(const CLHEPfloat * a)
      : BasicVector3D<CLHEPdouble>(a[0],a[1],a[2]) {}

    /**
     * Constructor from array of CLHEPdoubles. */
    explicit Normal3D(const CLHEPdouble * a)
      : BasicVector3D<CLHEPdouble>(a[0],a[1],a[2]) {}

    /**
     * Copy constructor. */
    Normal3D(const Normal3D<CLHEPdouble> &) = default;

    /**
     * Move constructor. */
    Normal3D(Normal3D<CLHEPdouble> &&) = default;

    /**
     * Constructor from BasicVector3D<CLHEPfloat>. */
    Normal3D(const BasicVector3D<CLHEPfloat> & v) : BasicVector3D<CLHEPdouble>(v) {}

    /**
     * Constructor from BasicVector3D<CLHEPdouble>. */
    Normal3D(const BasicVector3D<CLHEPdouble> & v) : BasicVector3D<CLHEPdouble>(v) {}

    /**
     * Destructor. */
    ~Normal3D() = default;

    /**
     * Constructor from CLHEP::Hep3Vector.
     * This constructor is needed only for backward compatibility and
     * in principle should be absent.
     */
    Normal3D(const CLHEP::Hep3Vector & v)
      : BasicVector3D<CLHEPdouble>(v.x(),v.y(),v.z()) {}

    /**
     * Conversion (cast) to CLHEP::Hep3Vector.
     * This operator is needed only for backward compatibility and
     * in principle should not exit.
     */
    operator CLHEP::Hep3Vector () const { return CLHEP::Hep3Vector(x(),y(),z()); }

    /**
     * Assignment. */
    Normal3D<CLHEPdouble> & operator=(const Normal3D<CLHEPdouble> &) = default;

    /**
     * Assignment from BasicVector3D<CLHEPfloat>. */
    Normal3D<CLHEPdouble> & operator=(const BasicVector3D<CLHEPfloat> & v) {
      this->BasicVector3D<CLHEPdouble>::operator=(v);
      return *this;
    }

    /**
     * Assignment from BasicVector3D<CLHEPdouble>. */
    Normal3D<CLHEPdouble> & operator=(const BasicVector3D<CLHEPdouble> & v) {
      this->BasicVector3D<CLHEPdouble>::operator=(v);
      return *this;
    }

    /**
     * Move assignment. */
    Normal3D<CLHEPdouble> & operator=(Normal3D<CLHEPdouble> &&) = default;

    /**
     * Transformation by Transform3D. */
    Normal3D<CLHEPdouble> & transform(const Transform3D & m);
  };

  /**
   * Transformation of Normal<CLHEPdouble> by Transform3D.
   * @relates Normal3D
   */
  Normal3D<CLHEPdouble>
  operator*(const Transform3D & m, const Normal3D<CLHEPdouble> & n);

} /* namespace HepGeom */

#ifdef ENABLE_BACKWARDS_COMPATIBILITY
//  backwards compatibility will be enabled ONLY in CLHEP 1.9
typedef HepGeom::Normal3D<CLHEPdouble> HepNormal3D;
#endif

#endif /* HEP_NORMAL3D_H */
