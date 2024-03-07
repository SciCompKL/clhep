#include "CLHEPTypes.hpp"
#ifndef _ExtendedButcherTableau_h_
#define _ExtendedButcherTableau_h_
// This class defines a ExtendedButcher Tableau, which completely specifies
// an *embedded* Runge-Kutte integration scheme. ExtendedButcher Tableau 
// are described in Numerical Methods for Ordinary Differential Equations, 
// John Wiley & sons, West Sussex England.
//
// General form is :
// 
//      c|A
//      ---
//       |b^T
//       |bHat^T
//
// where A is a matrix and b, bHat, and c are column vectors. 
// 
// The ExtendedButcher Tableau Class presents itself as an empty structure
// that the user has to fill up.  One can blithely fill write into
// any element of A, b, bHat or c. Space is automatically allocated.

#include <vector>
#include <string>
namespace Genfun {
  class ExtendedButcherTableau {
    
  public:
    
    // Constructor:
    inline ExtendedButcherTableau(const std::string &name, unsigned int order, unsigned int orderHat);
    
    // Returns the name:
    inline const std::string & name() const;
    
    // Returns the order of the main formula
    inline unsigned int order() const;

    // Returns the order of the controlling formula
    inline unsigned int orderHat() const;
    
    // Returns the number of steps:
    inline unsigned int nSteps() const;
    
    // Write access to elements:
    inline CLHEPdouble & A(unsigned int i, unsigned int j);
    inline CLHEPdouble & b(unsigned int i);
    inline CLHEPdouble & bHat(unsigned int i);
    inline CLHEPdouble & c(unsigned int i);
    
    // Read access to elements (inline for speed)
    inline const CLHEPdouble & A(unsigned int i, unsigned int j) const;
    inline const CLHEPdouble & b(unsigned int i) const;
    inline const CLHEPdouble & bHat(unsigned int i) const;
    inline const CLHEPdouble & c(unsigned int i) const;
    
    
  private:
    
    std::vector< std::vector<CLHEPdouble> > _A;
    std::vector<CLHEPdouble>                _b;
    std::vector<CLHEPdouble>                _bHat;
    std::vector<CLHEPdouble>                _c;
    std::string                        _name;
    unsigned int                       _order;
    unsigned int                       _orderHat;

  };


  class HeunEulerXtTableau: public ExtendedButcherTableau {
    // Constructor:
  public:
    inline HeunEulerXtTableau();
  };

  class BogackiShampineXtTableau: public ExtendedButcherTableau {
    // Constructor:
  public:
    inline BogackiShampineXtTableau();
  };

  class FehlbergRK45F2XtTableau: public ExtendedButcherTableau {
    // Constructor:
  public:
    inline FehlbergRK45F2XtTableau();
  };

  class CashKarpXtTableau: public ExtendedButcherTableau {
    // Constructor:
  public:
    inline CashKarpXtTableau();
  };

}

inline std::ostream & operator << (std::ostream & o, const Genfun::ExtendedButcherTableau & b);


#include "CLHEP/GenericFunctions/ExtendedButcherTableau.icc"

#endif
