#include "CLHEPTypes.hpp"
// -*- C++ -*-
// $Id: Point3D.h,v 1.5 2010/06/16 16:21:27 garren Exp $
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

#ifndef HEP_POINT3D_H
#define HEP_POINT3D_H

#include <iosfwd>
#include "CLHEP/Geometry/defs.h"
#include "CLHEP/Vector/ThreeVector.h"
#include "CLHEP/Geometry/BasicVector3D.h"

namespace HepGeom {

  class Transform3D;

  /**
   * Geometrical 3D Point.
   * This is just a declaration of the class needed to define
   * specializations Point3D<CLHEPfloat> and Point3D<CLHEPdouble>.
   *
   * @ingroup geometry
   * @author Evgeni Chernyaev <Evgueni.Tcherniaev@cern.ch>
   */
  template<class T>
  class Point3D : public BasicVector3D<T> {};

  /**
   * Geometrical 3D Point with components of CLHEPfloat type.
   *
   * @author Evgeni Chernyaev <Evgueni.Tcherniaev@cern.ch>
   * @ingroup geometry
   */
  template<>
  class Point3D<CLHEPfloat> : public BasicVector3D<CLHEPfloat> {
  public:
    /**
     * Default constructor. */
    Point3D() = default;

    /**
     * Constructor from three numbers. */
    Point3D(CLHEPfloat x1, CLHEPfloat y1, CLHEPfloat z1) : BasicVector3D<CLHEPfloat>(x1,y1,z1) {}

    /**
     * Constructor from array of CLHEPfloats. */
    explicit Point3D(const CLHEPfloat * a)
      : BasicVector3D<CLHEPfloat>(a[0],a[1],a[2]) {}

    /**
     * Copy constructor. */
    Point3D(const Point3D<CLHEPfloat> &) = default;

    /**
     * Move constructor. */
    Point3D(Point3D<CLHEPfloat> &&) = default;

    /**
     * Constructor from BasicVector3D<CLHEPfloat>. */
    Point3D(const BasicVector3D<CLHEPfloat> & v) : BasicVector3D<CLHEPfloat>(v) {}

    /**
     * Destructor. */
    ~Point3D() = default;

    /**
     * Assignment. */
    Point3D<CLHEPfloat> & operator=(const Point3D<CLHEPfloat> &) = default;

    /**
     * Assignment from BasicVector3D<CLHEPfloat>. */
    Point3D<CLHEPfloat> & operator=(const BasicVector3D<CLHEPfloat> & v) {
      this->BasicVector3D<CLHEPfloat>::operator=(v);
      return *this;
    }

    /**
     * Move assignment. */
    Point3D<CLHEPfloat> & operator=(Point3D<CLHEPfloat> &&) = default;

    /**
     * Returns distance to the origin squared. */
    CLHEPfloat distance2() const { return mag2(); }

    /**
     * Returns distance to the point squared. */
    CLHEPfloat distance2(const Point3D<CLHEPfloat> & p) const {
      CLHEPfloat dx = p.x()-x(), dy = p.y()-y(), dz = p.z()-z();
      return dx*dx + dy*dy + dz*dz;
    }

    /**
     * Returns distance to the origin. */
    CLHEPfloat distance() const { return std::sqrt(distance2()); }

    /**
     * Returns distance to the point. */
    CLHEPfloat distance(const Point3D<CLHEPfloat> & p) const {
      return std::sqrt(distance2(p));
    }

    /**
     * Transformation by Transform3D. */
    Point3D<CLHEPfloat> & transform(const Transform3D & m);
  };

  /**
   * Transformation of Point3D<CLHEPfloat> by Transform3D.
   * @relates Point3D
   */
  Point3D<CLHEPfloat>
  operator*(const Transform3D & m, const Point3D<CLHEPfloat> & p);

  /**
   * Geometrical 3D Point with components of CLHEPdouble type.
   *
   * @author Evgeni Chernyaev <Evgueni.Tcherniaev@cern.ch>
   * @ingroup geometry
   */
  template<>
  class Point3D<CLHEPdouble> : public BasicVector3D<CLHEPdouble> {
  public:
    /**
     * Default constructor. */
    Point3D() = default;

    /**
     * Constructor from three numbers. */
    Point3D(CLHEPdouble x1, CLHEPdouble y1, CLHEPdouble z1) : BasicVector3D<CLHEPdouble>(x1,y1,z1) {}

    /**
     * Constructor from array of CLHEPfloats. */
    explicit Point3D(const CLHEPfloat * a)
      : BasicVector3D<CLHEPdouble>(a[0],a[1],a[2]) {}

    /**
     * Constructor from array of CLHEPdoubles. */
    explicit Point3D(const CLHEPdouble * a)
      : BasicVector3D<CLHEPdouble>(a[0],a[1],a[2]) {}

    /**
     * Copy constructor. */
    Point3D(const Point3D<CLHEPdouble> &) = default;

    /**
     * Move constructor. */
    Point3D(Point3D<CLHEPdouble> &&) = default;

    /**
     * Constructor from BasicVector3D<CLHEPfloat>. */
    Point3D(const BasicVector3D<CLHEPfloat> & v) : BasicVector3D<CLHEPdouble>(v) {}

    /**
     * Constructor from BasicVector3D<CLHEPdouble>. */
    Point3D(const BasicVector3D<CLHEPdouble> & v) : BasicVector3D<CLHEPdouble>(v) {}

    /**
     * Destructor. */
    ~Point3D() = default;

    /**
     * Constructor from CLHEP::Hep3Vector.
     * This constructor is needed only for backward compatibility and
     * in principle should be absent.
     */
    Point3D(const CLHEP::Hep3Vector & v)
      : BasicVector3D<CLHEPdouble>(v.x(),v.y(),v.z()) {}

    /**
     * Conversion (cast) to CLHEP::Hep3Vector.
     * This operator is needed only for backward compatibility and
     * in principle should not exit.
     */
    operator CLHEP::Hep3Vector () const { return CLHEP::Hep3Vector(x(),y(),z()); }

    /**
     * Assignment. */
    Point3D<CLHEPdouble> & operator=(const Point3D<CLHEPdouble> &) = default;

    /**
     * Assignment from BasicVector3D<CLHEPfloat>. */
    Point3D<CLHEPdouble> & operator=(const BasicVector3D<CLHEPfloat> & v) {
      this->BasicVector3D<CLHEPdouble>::operator=(v);
      return *this;
    }

    /**
     * Assignment from BasicVector3D<CLHEPdouble>. */
    Point3D<CLHEPdouble> & operator=(const BasicVector3D<CLHEPdouble> & v) {
      this->BasicVector3D<CLHEPdouble>::operator=(v);
      return *this;
    }

    /**
     * Move assignment. */
    Point3D<CLHEPdouble> & operator=(Point3D<CLHEPdouble> &&) = default;

    /**
     * Returns distance to the origin squared. */
    CLHEPdouble distance2() const { return mag2(); }

    /**
     * Returns distance to the point squared. */
    CLHEPdouble distance2(const Point3D<CLHEPdouble> & p) const {
      CLHEPdouble dx = p.x()-x(), dy = p.y()-y(), dz = p.z()-z();
      return dx*dx + dy*dy + dz*dz;
    }

    /**
     * Returns distance to the origin. */
    CLHEPdouble distance() const { return std::sqrt(distance2()); }

    /**
     * Returns distance to the point. */
    CLHEPdouble distance(const Point3D<CLHEPdouble> & p) const {
      return std::sqrt(distance2(p));
    }

    /**
     * Transformation by Transform3D. */
    Point3D<CLHEPdouble> & transform(const Transform3D & m);
  };

  /**
   * Transformation of Point3D<CLHEPdouble> by Transform3D.
   * @relates Point3D
   */
  Point3D<CLHEPdouble>
  operator*(const Transform3D & m, const Point3D<CLHEPdouble> & p);

} /* namespace HepGeom */

#ifdef ENABLE_BACKWARDS_COMPATIBILITY
//  backwards compatibility will be enabled ONLY in CLHEP 1.9
#include "CLHEP/config/CLHEP.h"
#include "CLHEP/Geometry/Normal3D.h"
#include "CLHEP/Geometry/Transform3D.h"
typedef HepGeom::Point3D<CLHEPdouble> HepPoint3D;
#endif

#endif /* HEP_POINT3D_H */
