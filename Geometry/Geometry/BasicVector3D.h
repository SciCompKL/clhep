#include "CLHEPTypes.hpp"
// -*- C++ -*-
// $Id: BasicVector3D.h,v 1.5 2010/06/16 16:21:27 garren Exp $
// ---------------------------------------------------------------------------
//
// This file is a part of the CLHEP - a Class Library for High Energy Physics.
//
// History:
// 12.06.01 E.Chernyaev - CLHEP-1.7: initial  version
// 14.03.03 E.Chernyaev - CLHEP-1.9: template version
//

#ifndef BASIC_VECTOR3D_H
#define BASIC_VECTOR3D_H

#include <iosfwd>
#include <type_traits>
#include "CLHEP/Geometry/defs.h"
#include "CLHEP/Vector/ThreeVector.h"

namespace HepGeom {
  /**
   * Base class for Point3D<T>, Vector3D<T> and Normal3D<T>.
   * It defines only common functionality for those classes and
   * should not be used as separate class.
   *
   * @author Evgeni Chernyaev <Evgueni.Tcherniaev@cern.ch>
   * @ingroup geometry
   */
  template<class T> class BasicVector3D {
  protected:
    T v_[3];

    /**
     * Default constructor.
     * It is protected - this class should not be instantiated directly.
     */
    BasicVector3D() { v_[0] = 0; v_[1] = 0; v_[2] = 0; }

  public:
    /**
     * Safe indexing of the coordinates when using with matrices, arrays, etc.
     */
    enum {
      X = 0,                 /**< index for x-component */
      Y = 1,                 /**< index for y-component */
      Z = 2,                 /**< index for z-component */
      NUM_COORDINATES = 3,   /**< number of components  */
      SIZE = NUM_COORDINATES /**< number of components  */
    };

    /**
     * Constructor from three numbers. */
    BasicVector3D(T x1, T y1, T z1) { v_[0] = x1; v_[1] = y1; v_[2] = z1; }

    /**
     * Copy constructor. */
    BasicVector3D(const BasicVector3D<T> &) = default;

    /**
     * Constructor for BasicVector3D<CLHEPdouble> from BasicVector3D<CLHEPfloat>. */
    template<typename U = T,
             typename = typename std::enable_if<!std::is_same<U,CLHEPfloat>::value >::type>
    BasicVector3D(const BasicVector3D<CLHEPfloat> & v) {
      v_[0] = v.x(); v_[1] = v.y(); v_[2] = v.z();
    }

    /**
     * Move constructor. */
    BasicVector3D(BasicVector3D<T> &&) = default;

    /**
     * Destructor. */
    virtual ~BasicVector3D() = default;

    // -------------------------
    // Interface to "good old C"
    // -------------------------

    /**
     * Conversion (cast) to ordinary array. */
    operator T * () { return v_; }

    /**
     * Conversion (cast) to ordinary const array. */
    operator const T * () const { return v_; }

    /**
     * Conversion (cast) to CLHEP::Hep3Vector.
     * This operator is needed only for backward compatibility and
     * in principle should not exit.
     */
    operator CLHEP::Hep3Vector () const { return CLHEP::Hep3Vector(x(),y(),z()); }

    // -----------------------------
    // General arithmetic operations
    // -----------------------------

    /**
     * Assignment. */
    BasicVector3D<T> & operator= (const BasicVector3D<T> &) = default;
    /**
     * Move assignment. */
    BasicVector3D<T> & operator= (BasicVector3D<T> &&) = default;
    /**
     * Addition. */
    BasicVector3D<T> & operator+=(const BasicVector3D<T> & v) {
      v_[0] += v.v_[0]; v_[1] += v.v_[1]; v_[2] += v.v_[2]; return *this;
    }
    /**
     * Subtraction. */
    BasicVector3D<T> & operator-=(const BasicVector3D<T> & v) {
      v_[0] -= v.v_[0]; v_[1] -= v.v_[1]; v_[2] -= v.v_[2]; return *this;
    }
    /**
     * Multiplication by scalar. */
    BasicVector3D<T> & operator*=(CLHEPdouble a) {
      v_[0] *= a; v_[1] *= a; v_[2] *= a; return *this;
    }
    /**
     * Division by scalar. */
    BasicVector3D<T> & operator/=(CLHEPdouble a) {
      v_[0] /= a; v_[1] /= a; v_[2] /= a; return *this;
    }

    // ------------
    // Subscripting
    // ------------

    /**
     * Gets components by index. */
    T operator()(int i) const { return v_[i]; }
    /**
     * Gets components by index. */
    T operator[](int i) const { return v_[i]; }

    /**
     * Sets components by index. */
    T & operator()(int i) { return v_[i]; }
    /**
     * Sets components by index. */
    T & operator[](int i) { return v_[i]; }

    // ------------------------------------
    // Cartesian coordinate system: x, y, z
    // ------------------------------------

    /**
     * Gets x-component in cartesian coordinate system. */
    T x() const { return v_[0]; }
    /**
     * Gets y-component in cartesian coordinate system. */
    T y() const { return v_[1]; }
    /**
     * Gets z-component in cartesian coordinate system. */
    T z() const { return v_[2]; }

    /**
     * Sets x-component in cartesian coordinate system. */
    void setX(T a) { v_[0] = a; }
    /**
     * Sets y-component in cartesian coordinate system. */
    void setY(T a) { v_[1] = a; }
    /**
     * Sets z-component in cartesian coordinate system. */
    void setZ(T a) { v_[2] = a; }

    /**
     * Sets components in cartesian coordinate system.  */
    void set(T x1, T y1, T z1) { v_[0] = x1; v_[1] = y1; v_[2] = z1; }

    // ------------------------------------------
    // Cylindrical coordinate system: rho, phi, z
    // ------------------------------------------

    /**
     * Gets transverse component squared. */
    T perp2() const { return x()*x()+y()*y(); }
    /**
     * Gets transverse component. */
    T perp() const { return std::sqrt(perp2()); }
    /**
     * Gets rho-component in cylindrical coordinate system */
    T rho() const { return perp(); }

    /**
     * Sets transverse component keeping phi and z constant. */
    void setPerp(T rh) {
      T factor = perp();
      if (factor > 0) {
	factor = rh/factor; v_[0] *= factor; v_[1] *= factor;
      }
    }

    // ------------------------------------------
    // Spherical coordinate system: r, phi, theta
    // ------------------------------------------

    /**
     * Gets magnitude squared of the vector. */
    T mag2() const { return x()*x()+y()*y()+z()*z(); }
    /**
     * Gets magnitude of the vector. */
    T mag() const { return std::sqrt(mag2()); }
    /**
     * Gets r-component in spherical coordinate system */
    T r() const { return mag(); }
    /**
     * Gets azimuth angle. */
    T phi() const {
      return x() == 0 && y() == 0 ? 0 : std::atan2(y(),x());
    }
    /**
     * Gets polar angle. */
    T theta() const {
      return x() == 0 && y() == 0 && z() == 0 ? 0 : std::atan2(perp(),z());
    }
    /**
     * Gets cosine of polar angle. */
    T cosTheta() const { T ma = mag(); return ma == 0 ? 1 : z()/ma; }

    /**
     * Gets r-component in spherical coordinate system */
    T getR() const { return r(); }
    /**
     * Gets phi-component in spherical coordinate system */
    T getPhi() const { return phi(); }
    /**
     * Gets theta-component in spherical coordinate system */
    T getTheta() const { return theta(); }

    /**
     * Sets magnitude. */
    void setMag(T ma) {
      T factor = mag();
      if (factor > 0) {
	factor = ma/factor; v_[0] *= factor; v_[1] *= factor; v_[2] *= factor;
      }
    }
    /**
     * Sets r-component in spherical coordinate system. */
    void setR(T ma) { setMag(ma); }
    /**
     * Sets phi-component in spherical coordinate system. */
    void setPhi(T ph) { T xy = perp(); setX(xy*std::cos(ph)); setY(xy*std::sin(ph)); }
    /**
     * Sets theta-component in spherical coordinate system. */
    void setTheta(T th) {
      T ma = mag();
      T ph = phi();
      set(ma*std::sin(th)*std::cos(ph), ma*std::sin(th)*std::sin(ph), ma*std::cos(th));
    }

    // ---------------
    // Pseudo rapidity
    // ---------------

    /**
     * Gets pseudo-rapidity: -ln(tan(theta/2)) */
    T pseudoRapidity() const;
    /**
     * Gets pseudo-rapidity. */
    T eta() const { return pseudoRapidity(); }
    /**
     * Gets pseudo-rapidity. */
    T getEta() const { return pseudoRapidity(); }

    /**
     * Sets pseudo-rapidity, keeping magnitude and phi fixed. */
    void setEta(T a);

    // -------------------
    // Combine two vectors
    // -------------------

    /**
     * Scalar product. */
    T dot(const BasicVector3D<T> & v) const {
      return x()*v.x()+y()*v.y()+z()*v.z();
    }

    /**
     * Vector product. */
    BasicVector3D<T> cross(const BasicVector3D<T> & v) const {
      return BasicVector3D<T>(y()*v.z()-v.y()*z(),
			      z()*v.x()-v.z()*x(),
			      x()*v.y()-v.x()*y());
    }

    /**
     * Returns transverse component w.r.t. given axis squared. */
    T perp2(const BasicVector3D<T> & v) const {
      T tot = v.mag2(), s = dot(v);
      return tot > 0 ? mag2()-s*s/tot : mag2();
    }

    /**
     * Returns transverse component w.r.t. given axis. */
    T perp(const BasicVector3D<T> & v) const {
      return std::sqrt(perp2(v));
    }

    /**
     * Returns angle w.r.t. another vector. */
    T angle(const BasicVector3D<T> & v) const;

    // ---------------
    // Related vectors
    // ---------------

    /**
     * Returns unit vector parallel to this. */
    BasicVector3D<T> unit() const {
      T len = mag();
      return (len > 0) ?
	BasicVector3D<T>(x()/len, y()/len, z()/len) : BasicVector3D<T>();
    }

    /**
     * Returns orthogonal vector. */
    BasicVector3D<T> orthogonal() const {
      T dx = x() < 0 ? -x() : x();
      T dy = y() < 0 ? -y() : y();
      T dz = z() < 0 ? -z() : z();
      if (dx < dy) {
	return dx < dz ?
	  BasicVector3D<T>(0,z(),-y()) : BasicVector3D<T>(y(),-x(),0);
      }else{
	return dy < dz ?
	  BasicVector3D<T>(-z(),0,x()) : BasicVector3D<T>(y(),-x(),0);
      }
    }

    // ---------
    // Rotations
    // ---------

    /**
     * Rotates around x-axis. */
    BasicVector3D<T> & rotateX(T a);
    /**
     * Rotates around y-axis. */
    BasicVector3D<T> & rotateY(T a);
    /**
     * Rotates around z-axis. */
    BasicVector3D<T> & rotateZ(T a);
    /**
     * Rotates around the axis specified by another vector. */
    BasicVector3D<T> & rotate(T a, const BasicVector3D<T> & v);
  };

  /*************************************************************************
   *                                                                       *
   * Non-member functions for BasicVector3D<CLHEPfloat>                         *
   *                                                                       *
   *************************************************************************/

  /**
   * Output to stream.
   * @relates BasicVector3D
   */
  std::ostream &
  operator<<(std::ostream &, const BasicVector3D<CLHEPfloat> &);

  /**
   * Input from stream.
   * @relates BasicVector3D
   */
  std::istream &
  operator>>(std::istream &, BasicVector3D<CLHEPfloat> &);

  /**
   * Unary plus.
   * @relates BasicVector3D
   */
  inline BasicVector3D<CLHEPfloat>
  operator+(const BasicVector3D<CLHEPfloat> & v) { return v; }

  /**
   * Addition of two vectors.
   * @relates BasicVector3D
   */
  inline BasicVector3D<CLHEPfloat>
  operator+(const BasicVector3D<CLHEPfloat> & a, const BasicVector3D<CLHEPfloat> & b) {
    return BasicVector3D<CLHEPfloat>(a.x()+b.x(), a.y()+b.y(), a.z()+b.z());
  }

  /**
   * Unary minus.
   * @relates BasicVector3D
   */
  inline BasicVector3D<CLHEPfloat>
  operator-(const BasicVector3D<CLHEPfloat> & v) {
    return BasicVector3D<CLHEPfloat>(-v.x(), -v.y(), -v.z());
  }

  /**
   * Subtraction of two vectors.
   * @relates BasicVector3D
   */
  inline BasicVector3D<CLHEPfloat>
  operator-(const BasicVector3D<CLHEPfloat> & a, const BasicVector3D<CLHEPfloat> & b) {
    return BasicVector3D<CLHEPfloat>(a.x()-b.x(), a.y()-b.y(), a.z()-b.z());
  }

  /**
   * Multiplication vector by scalar.
   * @relates BasicVector3D
   */
  inline BasicVector3D<CLHEPfloat>
  operator*(const BasicVector3D<CLHEPfloat> & v, CLHEPdouble a) {
    return BasicVector3D<CLHEPfloat>(v.x()*static_cast<CLHEPfloat>(a), v.y()*static_cast<CLHEPfloat>(a), v.z()*static_cast<CLHEPfloat>(a));
  }

  /**
   * Scalar product of two vectors.
   * @relates BasicVector3D
   */
  inline CLHEPfloat
  operator*(const BasicVector3D<CLHEPfloat> & a, const BasicVector3D<CLHEPfloat> & b) {
    return a.dot(b);
  }

  /**
   * Multiplication scalar by vector.
   * @relates BasicVector3D
   */
  inline BasicVector3D<CLHEPfloat>
  operator*(CLHEPdouble a, const BasicVector3D<CLHEPfloat> & v) {
    return BasicVector3D<CLHEPfloat>(static_cast<CLHEPfloat>(a)*v.x(), static_cast<CLHEPfloat>(a)*v.y(), static_cast<CLHEPfloat>(a)*v.z());
  }

  /**
   * Division vector by scalar.
   * @relates BasicVector3D
   */
  inline BasicVector3D<CLHEPfloat>
  operator/(const BasicVector3D<CLHEPfloat> & v, CLHEPdouble a) {
    return BasicVector3D<CLHEPfloat>(v.x()/static_cast<CLHEPfloat>(a), v.y()/static_cast<CLHEPfloat>(a), v.z()/static_cast<CLHEPfloat>(a));
  }

  /**
   * Comparison of two vectors for equality.
   * @relates BasicVector3D
   */
  inline bool
  operator==(const BasicVector3D<CLHEPfloat> & a, const BasicVector3D<CLHEPfloat> & b) {
    return (a.x()==b.x() && a.y()==b.y() && a.z()==b.z());
  }

  /**
   * Comparison of two vectors for inequality.
   * @relates BasicVector3D
   */
  inline bool
  operator!=(const BasicVector3D<CLHEPfloat> & a, const BasicVector3D<CLHEPfloat> & b) {
    return (a.x()!=b.x() || a.y()!=b.y() || a.z()!=b.z());
  }

  /*************************************************************************
   *                                                                       *
   * Non-member functions for BasicVector3D<CLHEPdouble>                        *
   *                                                                       *
   *************************************************************************/

  /**
   * Output to stream.
   * @relates BasicVector3D
   */
  std::ostream &
  operator<<(std::ostream &, const BasicVector3D<CLHEPdouble> &);

  /**
   * Input from stream.
   * @relates BasicVector3D
   */
  std::istream &
  operator>>(std::istream &, BasicVector3D<CLHEPdouble> &);

  /**
   * Unary plus.
   * @relates BasicVector3D
   */
  inline BasicVector3D<CLHEPdouble>
  operator+(const BasicVector3D<CLHEPdouble> & v) { return v; }

  /**
   * Addition of two vectors.
   * @relates BasicVector3D
   */
  inline BasicVector3D<CLHEPdouble>
  operator+(const BasicVector3D<CLHEPdouble> & a,const BasicVector3D<CLHEPdouble> & b) {
    return BasicVector3D<CLHEPdouble>(a.x()+b.x(), a.y()+b.y(), a.z()+b.z());
  }

  /**
   * Unary minus.
   * @relates BasicVector3D
   */
  inline BasicVector3D<CLHEPdouble>
  operator-(const BasicVector3D<CLHEPdouble> & v) {
    return BasicVector3D<CLHEPdouble>(-v.x(), -v.y(), -v.z());
  }

  /**
   * Subtraction of two vectors.
   * @relates BasicVector3D
   */
  inline BasicVector3D<CLHEPdouble>
  operator-(const BasicVector3D<CLHEPdouble> & a,const BasicVector3D<CLHEPdouble> & b) {
    return BasicVector3D<CLHEPdouble>(a.x()-b.x(), a.y()-b.y(), a.z()-b.z());
  }

  /**
   * Multiplication vector by scalar.
   * @relates BasicVector3D
   */
  inline BasicVector3D<CLHEPdouble>
  operator*(const BasicVector3D<CLHEPdouble> & v, CLHEPdouble a) {
    return BasicVector3D<CLHEPdouble>(v.x()*a, v.y()*a, v.z()*a);
  }

  /**
   * Scalar product of two vectors.
   * @relates BasicVector3D
   */
  inline CLHEPdouble
  operator*(const BasicVector3D<CLHEPdouble> & a,const BasicVector3D<CLHEPdouble> & b) {
    return a.dot(b);
  }

  /**
   * Multiplication scalar by vector.
   * @relates BasicVector3D
   */
  inline BasicVector3D<CLHEPdouble>
  operator*(CLHEPdouble a, const BasicVector3D<CLHEPdouble> & v) {
    return BasicVector3D<CLHEPdouble>(a*v.x(), a*v.y(), a*v.z());
  }

  /**
   * Division vector by scalar.
   * @relates BasicVector3D
   */
  inline BasicVector3D<CLHEPdouble>
  operator/(const BasicVector3D<CLHEPdouble> & v, CLHEPdouble a) {
    return BasicVector3D<CLHEPdouble>(v.x()/a, v.y()/a, v.z()/a);
  }

  /**
   * Comparison of two vectors for equality.
   * @relates BasicVector3D
   */
  inline bool
  operator==(const BasicVector3D<CLHEPdouble> & a, const BasicVector3D<CLHEPdouble> & b)
  {
    return (a.x()==b.x() && a.y()==b.y() && a.z()==b.z());
  }

  /**
   * Comparison of two vectors for inequality.
   * @relates BasicVector3D
   */
  inline bool
  operator!=(const BasicVector3D<CLHEPdouble> & a, const BasicVector3D<CLHEPdouble> & b)
  {
    return (a.x()!=b.x() || a.y()!=b.y() || a.z()!=b.z());
  }
} /* namespace HepGeom */

#ifdef ENABLE_BACKWARDS_COMPATIBILITY
//  backwards compatibility will be enabled ONLY in CLHEP 1.9
using namespace HepGeom;
#endif

#endif /* BASIC_VECTOR3D_H */
