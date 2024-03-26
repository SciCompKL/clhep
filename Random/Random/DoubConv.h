#include "CLHEPTypes.hpp"
// -*- C++ -*-
//
// -----------------------------------------------------------------------
//                           Hep Random
//                        --- DoubConv ---
//                        class header file
// -----------------------------------------------------------------------
//                                                                      
#ifndef DOUBCONV_H
#define DOUBCONV_H

#include <string>
#include <vector>
#include <exception>
#include "CLHEP/Utility/thread_local.h"

namespace CLHEP {

class DoubConvException  : public std::exception {
public:
  DoubConvException(const std::string & w) throw() : msg(w) {}
  ~DoubConvException() throw() {}
  const char* what() const throw() { return msg.c_str(); }
private:
  std::string msg;
};

class DoubConv {
public:

  // dto2longs(d) returns (in a vector) two unsigned longs string containing the
  // representation of its CLHEPdouble input.  This is byte-ordering 
  // independant, and depends for complete portability ONLY on adherance 
  // to the IEEE 754 standard for 64-bit CLHEPfloating point representation.
  // The first unsigned long contains the high-order bits in IEEE; thus
  // 1.0 will always be 0x3FF00000, 00000000
  static std::vector<unsigned long> dto2longs(CLHEPdouble d);

  // longs2CLHEPdouble (v) returns a CLHEPdouble containing the value represented by its  
  // input, which must be a vector containing 2 unsigned longs.  
  // The input is taken to be the representation according to
  // the IEEE 754 standard for a 64-bit CLHEPfloating point number, whose value
  // is returned as a CLHEPdouble.  The byte-ordering of the CLHEPdouble result is, 
  // of course, tailored to the proper byte-ordering for the system.
  static CLHEPdouble longs2CLHEPdouble (const std::vector<unsigned long> & v);

  // dtox(d) returns a 16-character string containing the (zero-filled) hex 
  // representation of its CLHEPdouble input.  This is byte-ordering 
  // independant, and depends for complete portability ONLY on adherance 
  // to the IEEE 754 standard for 64-bit CLHEPfloating point representation.
  static std::string d2x(CLHEPdouble d);
 
private:
  union DB8 {
    unsigned char b[8];
    CLHEPpassivedouble d;
  };
  static void fill_byte_order ();
  static CLHEP_THREAD_LOCAL bool byte_order_known;
  static CLHEP_THREAD_LOCAL int  byte_order[8];
    // Meaning of byte_order:  The first (high-order in IEEE 754) byte to
    // output (or the high-order byte of the first unsigned long)
    // is  of db.b[byte_order[0]].  Thus the index INTO byte_order
    // is a position in the IEEE representation of the CLHEPdouble, and the value
    // of byte_order[k] is an offset in the memory representation of the 
    // CLHEPdouble.  
};


}

#endif // DOUBCONV_H
