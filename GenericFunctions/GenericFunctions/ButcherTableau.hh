#include "CLHEPTypes.hpp"
#ifndef _ButcherTableau_h_
#define _ButcherTableau_h_
// This class defines a Butcher Tableau, which completely specifies
// a Runge-Kutte integration scheme. Butcher Tableau are described
// in Numerical Methods for Ordinary Differential Equations, John
// Wiley & sons, West Sussex England.
//
// General form is :
// 
//      c|A
//      ---
//       |b^T
//
// where A is a matrix and b, c are column vectors. 
// 
// The Butcher Tableau Class presents itself as an empty structure
// that the user has to fill up.  One can blithely fill write into
// any element of A, b, or c. Space is automatically allocated.

#include <vector>
#include <string>
namespace Genfun {
  class ButcherTableau {
    
  public:
    
    // Constructor:
    inline ButcherTableau(const std::string &name, unsigned int order);
    
    // Returns the name:
    inline const std::string & name() const;
    
    // Returns the order:
    inline unsigned int order() const;
    
    // Returns the number of steps:
    inline unsigned int nSteps() const;
    
    // Write access to elements:
    inline CLHEPdouble & A(unsigned int i, unsigned int j);
    inline CLHEPdouble & b(unsigned int i);
    inline CLHEPdouble & c(unsigned int i);
    
    // Read access to elements (inline for speed)
    inline const CLHEPdouble & A(unsigned int i, unsigned int j) const;
    inline const CLHEPdouble & b(unsigned int i) const;
    inline const CLHEPdouble & c(unsigned int i) const;
    
    
  private:
    
    std::vector< std::vector<CLHEPdouble> > _A;
    std::vector<CLHEPdouble>                _b;
    std::vector<CLHEPdouble>                _c;
    std::string                        _name;
    unsigned int                       _order;
  };


  class EulerTableau: public ButcherTableau {
    // Constructor:
  public:
    inline EulerTableau();
  };

  class MidpointTableau: public ButcherTableau {
    // Constructor:
  public:
    inline MidpointTableau();
  };

  class TrapezoidTableau: public ButcherTableau {
    // Constructor:
  public:
    inline TrapezoidTableau();
  };

  class RK31Tableau: public ButcherTableau {
    // Constructor:
  public:
    inline RK31Tableau();
  };

  class RK32Tableau: public ButcherTableau {
    // Constructor:
  public:
    inline RK32Tableau();
  };

  class ClassicalRungeKuttaTableau: public ButcherTableau {
    // Constructor:
  public:
    inline ClassicalRungeKuttaTableau();
  };

  class ThreeEighthsRuleTableau: public ButcherTableau {
    // Constructor:
  public:
    inline ThreeEighthsRuleTableau();
  };

}

inline std::ostream & operator << (std::ostream & o, const Genfun::ButcherTableau & b);


#include "CLHEP/GenericFunctions/ButcherTableau.icc"

#endif
