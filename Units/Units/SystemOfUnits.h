#include "CLHEPTypes.hpp"
// -*- C++ -*-
// $Id: SystemOfUnits.h,v 1.4 2010/06/16 17:12:28 garren Exp $
// ----------------------------------------------------------------------
// HEP coherent system of Units
//
// This file has been provided to CLHEP by Geant4 (simulation toolkit for HEP).
//
// The basic units are :
// millimeter              (millimeter)
// nanosecond              (nanosecond)
// Mega electron Volt      (MeV)
// positron charge         (eplus)
// degree Kelvin           (kelvin)
// the amount of substance (mole)
// luminous intensity      (candela)
// radian                  (radian)
// steradian               (steradian)
//
// Below is a non exhaustive list of derived and pratical units
// (i.e. mostly the SI units).
// You can add your own units.
//
// The SI numerical value of the positron charge is defined here,
// as it is needed for conversion factor : positron charge = e_SI (coulomb)
//
// The others physical constants are defined in the header file :
// PhysicalConstants.h
//
// Authors: M.Maire, S.Giani
//
// History:
//
// 06.02.96   Created.
// 28.03.96   Added miscellaneous constants.
// 05.12.97   E.Tcherniaev: Redefined pascal (to avoid warnings on WinNT)
// 20.05.98   names: meter, second, gram, radian, degree
//            (from Brian.Lasiuk@yale.edu (STAR)). Added luminous units.
// 05.08.98   angstrom, picobarn, microsecond, picosecond, petaelectronvolt
// 01.03.01   parsec    
// 31.01.06   kilogray, milligray, microgray    
// 29.04.08   use PDG 2006 value of e_SI
// 03.11.08   use PDG 2008 value of e_SI
// 19.08.15   added liter and its sub units (mma)
// 12.01.16   added symbols for microsecond (us) and picosecond (ps) (mma)
// 17.07.20   use PDG 2019 value of e_SI
// 06.05.21   added minute, hour, day, year and millielectronvolt (mma)

#ifndef HEP_SYSTEM_OF_UNITS_H
#define HEP_SYSTEM_OF_UNITS_H

#include "CLHEP/Units/defs.h"

namespace CLHEP {

  //
  //
  //
  static constexpr CLHEPdouble     pi  = 3.14159265358979323846;
  static constexpr CLHEPdouble  twopi  = 2*pi;
  static constexpr CLHEPdouble halfpi  = pi/2;
  static constexpr CLHEPdouble     pi2 = pi*pi;

  // 
  // Length [L]
  //
  static constexpr CLHEPdouble millimeter  = 1.;                        
  static constexpr CLHEPdouble millimeter2 = millimeter*millimeter;
  static constexpr CLHEPdouble millimeter3 = millimeter*millimeter*millimeter;

  static constexpr CLHEPdouble centimeter  = 10.*millimeter;   
  static constexpr CLHEPdouble centimeter2 = centimeter*centimeter;
  static constexpr CLHEPdouble centimeter3 = centimeter*centimeter*centimeter;

  static constexpr CLHEPdouble meter  = 1000.*millimeter;                  
  static constexpr CLHEPdouble meter2 = meter*meter;
  static constexpr CLHEPdouble meter3 = meter*meter*meter;

  static constexpr CLHEPdouble kilometer = 1000.*meter;                   
  static constexpr CLHEPdouble kilometer2 = kilometer*kilometer;
  static constexpr CLHEPdouble kilometer3 = kilometer*kilometer*kilometer;

  static constexpr CLHEPdouble parsec = 3.0856775807e+16*meter;

  static constexpr CLHEPdouble micrometer = 1.e-6 *meter;             
  static constexpr CLHEPdouble  nanometer = 1.e-9 *meter;
  static constexpr CLHEPdouble  angstrom  = 1.e-10*meter;
  static constexpr CLHEPdouble  fermi     = 1.e-15*meter;

  static constexpr CLHEPdouble      barn = 1.e-28*meter2;
  static constexpr CLHEPdouble millibarn = 1.e-3 *barn;
  static constexpr CLHEPdouble microbarn = 1.e-6 *barn;
  static constexpr CLHEPdouble  nanobarn = 1.e-9 *barn;
  static constexpr CLHEPdouble  picobarn = 1.e-12*barn;

  // symbols
  static constexpr CLHEPdouble nm  = nanometer;                        
  static constexpr CLHEPdouble um  = micrometer;                        

  static constexpr CLHEPdouble mm  = millimeter;                        
  static constexpr CLHEPdouble mm2 = millimeter2;
  static constexpr CLHEPdouble mm3 = millimeter3;

  static constexpr CLHEPdouble cm  = centimeter;   
  static constexpr CLHEPdouble cm2 = centimeter2;
  static constexpr CLHEPdouble cm3 = centimeter3;

  static constexpr CLHEPdouble liter = 1.e+3*cm3;
  static constexpr CLHEPdouble  L = liter;
  static constexpr CLHEPdouble dL = 1.e-1*liter;
  static constexpr CLHEPdouble cL = 1.e-2*liter;
  static constexpr CLHEPdouble mL = 1.e-3*liter;       

  static constexpr CLHEPdouble m  = meter;                  
  static constexpr CLHEPdouble m2 = meter2;
  static constexpr CLHEPdouble m3 = meter3;

  static constexpr CLHEPdouble km  = kilometer;                   
  static constexpr CLHEPdouble km2 = kilometer2;
  static constexpr CLHEPdouble km3 = kilometer3;

  static constexpr CLHEPdouble pc = parsec;

  //
  // Angle
  //
  static constexpr CLHEPdouble radian      = 1.;                  
  static constexpr CLHEPdouble milliradian = 1.e-3*radian;
  static constexpr CLHEPdouble degree = (pi/180.0)*radian;

  static constexpr CLHEPdouble   steradian = 1.;
  
  // symbols
  static constexpr CLHEPdouble rad  = radian;
  static constexpr CLHEPdouble mrad = milliradian;
  static constexpr CLHEPdouble sr   = steradian;
  static constexpr CLHEPdouble deg  = degree;

  //
  // Time [T]
  //
  static constexpr CLHEPdouble nanosecond  = 1.;
  static constexpr CLHEPdouble second      = 1.e+9 *nanosecond;
  static constexpr CLHEPdouble millisecond = 1.e-3 *second;
  static constexpr CLHEPdouble microsecond = 1.e-6 *second;
  static constexpr CLHEPdouble  picosecond = 1.e-12*second;

  static constexpr CLHEPdouble minute = 60*second;
  static constexpr CLHEPdouble hour   = 60*minute;
  static constexpr CLHEPdouble day    = 24*hour;
  static constexpr CLHEPdouble year   = 365*day;  

  static constexpr CLHEPdouble hertz = 1./second;
  static constexpr CLHEPdouble kilohertz = 1.e+3*hertz;
  static constexpr CLHEPdouble megahertz = 1.e+6*hertz;

  // symbols
  static constexpr CLHEPdouble ns = nanosecond;
  static constexpr CLHEPdouble  s = second;
  static constexpr CLHEPdouble ms = millisecond;
  static constexpr CLHEPdouble us = microsecond;
  static constexpr CLHEPdouble ps = picosecond;

  //
  // Electric charge [Q]
  //
  static constexpr CLHEPdouble eplus = 1. ;// positron charge
  static constexpr CLHEPdouble e_SI  = 1.602176634e-19;// positron charge in coulomb
  static constexpr CLHEPdouble coulomb = eplus/e_SI;// coulomb = 6.24150 e+18 * eplus

  //
  // Energy [E]
  //
  static constexpr CLHEPdouble megaelectronvolt = 1. ;
  static constexpr CLHEPdouble     electronvolt = 1.e-6*megaelectronvolt;
  static constexpr CLHEPdouble kiloelectronvolt = 1.e-3*megaelectronvolt;
  static constexpr CLHEPdouble gigaelectronvolt = 1.e+3*megaelectronvolt;
  static constexpr CLHEPdouble teraelectronvolt = 1.e+6*megaelectronvolt;
  static constexpr CLHEPdouble petaelectronvolt = 1.e+9*megaelectronvolt;
  static constexpr CLHEPdouble millielectronvolt = 1.e-9*megaelectronvolt;  

  static constexpr CLHEPdouble joule = electronvolt/e_SI;// joule = 6.24150 e+12 * MeV

  // symbols
  static constexpr CLHEPdouble MeV = megaelectronvolt;
  static constexpr CLHEPdouble  eV = electronvolt;
  static constexpr CLHEPdouble keV = kiloelectronvolt;
  static constexpr CLHEPdouble GeV = gigaelectronvolt;
  static constexpr CLHEPdouble TeV = teraelectronvolt;
  static constexpr CLHEPdouble PeV = petaelectronvolt;

  //
  // Mass [E][T^2][L^-2]
  //
  static constexpr CLHEPdouble  kilogram = joule*second*second/(meter*meter);   
  static constexpr CLHEPdouble      gram = 1.e-3*kilogram;
  static constexpr CLHEPdouble milligram = 1.e-3*gram;

  // symbols
  static constexpr CLHEPdouble  kg = kilogram;
  static constexpr CLHEPdouble   g = gram;
  static constexpr CLHEPdouble  mg = milligram;

  //
  // Power [E][T^-1]
  //
  static constexpr CLHEPdouble watt = joule/second;// watt = 6.24150 e+3 * MeV/ns

  //
  // Force [E][L^-1]
  //
  static constexpr CLHEPdouble newton = joule/meter;// newton = 6.24150 e+9 * MeV/mm

  //
  // Pressure [E][L^-3]
  //
#define pascal hep_pascal                          // a trick to avoid warnings 
  static constexpr CLHEPdouble hep_pascal = newton/m2;   // pascal = 6.24150 e+3 * MeV/mm3
  static constexpr CLHEPdouble bar        = 100000*pascal; // bar    = 6.24150 e+8 * MeV/mm3
  static constexpr CLHEPdouble atmosphere = 101325*pascal; // atm    = 6.32420 e+8 * MeV/mm3

  //
  // Electric current [Q][T^-1]
  //
  static constexpr CLHEPdouble      ampere = coulomb/second; // ampere = 6.24150 e+9 * eplus/ns
  static constexpr CLHEPdouble milliampere = 1.e-3*ampere;
  static constexpr CLHEPdouble microampere = 1.e-6*ampere;
  static constexpr CLHEPdouble  nanoampere = 1.e-9*ampere;

  //
  // Electric potential [E][Q^-1]
  //
  static constexpr CLHEPdouble megavolt = megaelectronvolt/eplus;
  static constexpr CLHEPdouble kilovolt = 1.e-3*megavolt;
  static constexpr CLHEPdouble     volt = 1.e-6*megavolt;

  //
  // Electric resistance [E][T][Q^-2]
  //
  static constexpr CLHEPdouble ohm = volt/ampere;// ohm = 1.60217e-16*(MeV/eplus)/(eplus/ns)

  //
  // Electric capacitance [Q^2][E^-1]
  //
  static constexpr CLHEPdouble farad = coulomb/volt;// farad = 6.24150e+24 * eplus/Megavolt
  static constexpr CLHEPdouble millifarad = 1.e-3*farad;
  static constexpr CLHEPdouble microfarad = 1.e-6*farad;
  static constexpr CLHEPdouble  nanofarad = 1.e-9*farad;
  static constexpr CLHEPdouble  picofarad = 1.e-12*farad;

  //
  // Magnetic Flux [T][E][Q^-1]
  //
  static constexpr CLHEPdouble weber = volt*second;// weber = 1000*megavolt*ns

  //
  // Magnetic Field [T][E][Q^-1][L^-2]
  //
  static constexpr CLHEPdouble tesla     = volt*second/meter2;// tesla =0.001*megavolt*ns/mm2

  static constexpr CLHEPdouble gauss     = 1.e-4*tesla;
  static constexpr CLHEPdouble kilogauss = 1.e-1*tesla;

  //
  // Inductance [T^2][E][Q^-2]
  //
  static constexpr CLHEPdouble henry = weber/ampere;// henry = 1.60217e-7*MeV*(ns/eplus)**2

  //
  // Temperature
  //
  static constexpr CLHEPdouble kelvin = 1.;

  //
  // Amount of substance
  //
  static constexpr CLHEPdouble mole = 1.;

  //
  // Activity [T^-1]
  //
  static constexpr CLHEPdouble becquerel = 1./second ;
  static constexpr CLHEPdouble curie = 3.7e+10 * becquerel;
  static constexpr CLHEPdouble kilobecquerel = 1.e+3*becquerel;
  static constexpr CLHEPdouble megabecquerel = 1.e+6*becquerel;
  static constexpr CLHEPdouble gigabecquerel = 1.e+9*becquerel;
  static constexpr CLHEPdouble millicurie = 1.e-3*curie;
  static constexpr CLHEPdouble microcurie = 1.e-6*curie;
  static constexpr CLHEPdouble Bq = becquerel;
  static constexpr CLHEPdouble kBq = kilobecquerel;
  static constexpr CLHEPdouble MBq = megabecquerel;
  static constexpr CLHEPdouble GBq = gigabecquerel;
  static constexpr CLHEPdouble Ci = curie;
  static constexpr CLHEPdouble mCi = millicurie;
  static constexpr CLHEPdouble uCi = microcurie;

  //
  // Absorbed dose [L^2][T^-2]
  //
  static constexpr CLHEPdouble      gray = joule/kilogram ;
  static constexpr CLHEPdouble  kilogray = 1.e+3*gray;
  static constexpr CLHEPdouble milligray = 1.e-3*gray;
  static constexpr CLHEPdouble microgray = 1.e-6*gray;

  //
  // Luminous intensity [I]
  //
  static constexpr CLHEPdouble candela = 1.;

  //
  // Luminous flux [I]
  //
  static constexpr CLHEPdouble lumen = candela*steradian;

  //
  // Illuminance [I][L^-2]
  //
  static constexpr CLHEPdouble lux = lumen/meter2;

  //
  // Miscellaneous
  //
  static constexpr CLHEPdouble perCent     = 0.01 ;
  static constexpr CLHEPdouble perThousand = 0.001;
  static constexpr CLHEPdouble perMillion  = 0.000001;

}  // namespace CLHEP

#ifdef ENABLE_BACKWARDS_COMPATIBILITY
//  backwards compatibility will be enabled ONLY in CLHEP 1.9
using namespace CLHEP;
#endif

#endif /* HEP_SYSTEM_OF_UNITS_H */
