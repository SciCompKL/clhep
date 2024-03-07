#include "CLHEPTypes.hpp"
// -*- C++ -*-
// $Id: Vector3D.h,v 1.3 2003/10/23 21:29:50 garren Exp $
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

#ifndef HEP_VECTOR3D_H
#define HEP_VECTOR3D_H

#include <iosfwd>
#include "CLHEP/Geometry/defs.h"
#include "CLHEP/Vector/ThreeVector.h"
#include "CLHEP/Geometry/BasicVector3D.h"

namespace HepGeom {

  class Transform3D;

  /**
   * Geometrical 3D Vector.
   * This is just a declaration of the class needed to define
   * specializations Vector3D<CLHEPfloat> and Vector3D<CLHEPdouble>.
   *
   * @ingroup geometry
   * @author Evgeni Chernyaev <Evgueni.Tcherniaev@cern.ch>
   */
  template<class T>
  class Vector3D : public BasicVector3D<T> {};

  /**
   * Geometrical 3D Vector with components of CLHEPfloat type.
   *
   * @author Evgeni Chernyaev <Evgueni.Tcherniaev@cern.ch>
   * @ingroup geometry
   */
  template<>
  class Vector3D<CLHEPfloat> : public BasicVector3D<CLHEPfloat> {
  public:
    /**
     * Default constructor. */
    Vector3D() = default;

    /**
     * Constructor from three numbers. */
    Vector3D(CLHEPfloat x1, CLHEPfloat y1, CLHEPfloat z1) : BasicVector3D<CLHEPfloat>(x1,y1,z1) {}

    /**
     * Constructor from array of CLHEPfloats. */
    explicit Vector3D(const CLHEPfloat * a)
      : BasicVector3D<CLHEPfloat>(a[0],a[1],a[2]) {}

    /**
     * Copy constructor. */
    Vector3D(const Vector3D<CLHEPfloat> &) = default;

    /**
     * Move constructor. */
    Vector3D(Vector3D<CLHEPfloat> &&) = default;

    /**
     * Constructor from BasicVector3D<CLHEPfloat>. */
    Vector3D(const BasicVector3D<CLHEPfloat> & v) : BasicVector3D<CLHEPfloat>(v) {}

    /**
     * Destructor. */
    ~Vector3D() = default;

    /**
     * Assignment. */
    Vector3D<CLHEPfloat> & operator=(const Vector3D<CLHEPfloat> &) = default;

    /**
     * Assignment from BasicVector3D<CLHEPfloat>. */
    Vector3D<CLHEPfloat> & operator=(const BasicVector3D<CLHEPfloat> & v) {
      this->BasicVector3D<CLHEPfloat>::operator=(v);
      return *this;
    }

    /**
     * Move assignment. */
    Vector3D<CLHEPfloat> & operator=(Vector3D<CLHEPfloat> &&) = default;

    /**
     * Transformation by Transform3D. */
    Vector3D<CLHEPfloat> & transform(const Transform3D & m);
  };

  /**
   * Transformation of Vector<CLHEPfloat> by Transform3D.
   * @relates Vector3D
   */
  Vector3D<CLHEPfloat>
  operator*(const Transform3D & m, const Vector3D<CLHEPfloat> & v);

  /**
   * Geometrical 3D Vector with components of CLHEPdouble type.
   *
   * @author Evgeni Chernyaev <Evgueni.Tcherniaev@cern.ch>
   * @ingroup geometry
   */
  template<>
  class Vector3D<CLHEPdouble> : public BasicVector3D<CLHEPdouble> {
  public:
    /**
     * Default constructor. */
    Vector3D() = default;

    /**
     * Constructor from three numbers. */
    Vector3D(CLHEPdouble x1, CLHEPdouble y1, CLHEPdouble z1) : BasicVector3D<CLHEPdouble>(x1,y1,z1) {}

    /**
     * Constructor from array of CLHEPfloats. */
    explicit Vector3D(const CLHEPfloat * a)
      : BasicVector3D<CLHEPdouble>(a[0],a[1],a[2]) {}

    /**
     * Constructor from array of CLHEPdoubles. */
    explicit Vector3D(const CLHEPdouble * a)
      : BasicVector3D<CLHEPdouble>(a[0],a[1],a[2]) {}

    /**
     * Copy constructor. */
    Vector3D(const Vector3D<CLHEPdouble> &) = default;

    /**
     * Move constructor. */
    Vector3D(Vector3D<CLHEPdouble> &&) = default;

    /**
     * Constructor from BasicVector3D<CLHEPfloat>. */
    Vector3D(const BasicVector3D<CLHEPfloat> & v) : BasicVector3D<CLHEPdouble>(v) {}

    /**
     * Constructor from BasicVector3D<CLHEPdouble>. */
    Vector3D(const BasicVector3D<CLHEPdouble> & v) : BasicVector3D<CLHEPdouble>(v) {}

    /**
     * Destructor. */
    ~Vector3D() = default;

    /**
     * Constructor from CLHEP::Hep3Vector.
     * This constructor is needed only for backward compatibility and
     * in principle should be absent.
     */
    Vector3D(const CLHEP::Hep3Vector & v)
      : BasicVector3D<CLHEPdouble>(v.x(),v.y(),v.z()) {}

    /**
     * Conversion (cast) to CLHEP::Hep3Vector.
     * This operator is needed only for backward compatibility and
     * in principle should not exit.
     */
    operator CLHEP::Hep3Vector () const { return CLHEP::Hep3Vector(x(),y(),z()); }

    /**
     * Assignment. */
    Vector3D<CLHEPdouble> & operator=(const Vector3D<CLHEPdouble> &) = default;

    /**
     * Assignment from BasicVector3D<CLHEPfloat>. */
    Vector3D<CLHEPdouble> & operator=(const BasicVector3D<CLHEPfloat> & v) {
      this->BasicVector3D<CLHEPdouble>::operator=(v);
      return *this;
    }

    /**
     * Assignment from BasicVector3D<CLHEPdouble>. */
    Vector3D<CLHEPdouble> & operator=(const BasicVector3D<CLHEPdouble> & v) {
      this->BasicVector3D<CLHEPdouble>::operator=(v);
      return *this;
    }

    /**
     * Move assignment. */
    Vector3D<CLHEPdouble> & operator=(Vector3D<CLHEPdouble> &&) = default;

    /**
     * Transformation by Transform3D. */
    Vector3D<CLHEPdouble> & transform(const Transform3D & m);
  };

  /**
   * Transformation of Vector<CLHEPdouble> by Transform3D.
   * @relates Vector3D
   */
  Vector3D<CLHEPdouble>
  operator*(const Transform3D & m, const Vector3D<CLHEPdouble> & v);

} /* namespace HepGeom */

#ifdef ENABLE_BACKWARDS_COMPATIBILITY
//  backwards compatibility will be enabled ONLY in CLHEP 1.9
typedef HepGeom::Vector3D<CLHEPdouble> HepVector3D;
#endif

#endif /* HEP_VECTOR3D_H */
