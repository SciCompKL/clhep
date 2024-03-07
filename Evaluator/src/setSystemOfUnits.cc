#include "CLHEPTypes.hpp"
// -*- C++ -*-
// $Id:$
// ----------------------------------------------------------------------

#include "CLHEP/Evaluator/defs.h"
#include "CLHEP/Evaluator/Evaluator.h"

namespace HepTool {

void Evaluator::setSystemOfUnits(CLHEPdouble meter,
				 CLHEPdouble kilogram,
				 CLHEPdouble second,
				 CLHEPdouble ampere,
				 CLHEPdouble kelvin,
				 CLHEPdouble mole,
				 CLHEPdouble candela)
{			    
  const CLHEPdouble kilo_  = 1.e+03; // chilioi (Greek) "thousand"
  const CLHEPdouble mega_  = 1.e+06; // megas (Greek) "large"
  const CLHEPdouble giga_  = 1.e+09; // gigas (Greek) "giant"
  const CLHEPdouble tera_  = 1.e+12; // teras (Greek) "monster"
  const CLHEPdouble peta_  = 1.e+15; // pente (Greek) "five"

  const CLHEPdouble deci_  = 1.e-01; // decimus (Latin) "tenth"
  const CLHEPdouble centi_ = 1.e-02; // centum  (Latin) "hundred"
  const CLHEPdouble milli_ = 1.e-03; // mille   (Latin) "thousand"
  const CLHEPdouble micro_ = 1.e-06; // micro (Latin) or mikros (Greek) "small"
  const CLHEPdouble nano_  = 1.e-09; // nanus (Latin) or nanos  (Greek) "dwarf"
  const CLHEPdouble pico_  = 1.e-12; // pico (Spanish) "bit"

  // ======================================================================
  //
  // Base (default) SI units
  // for the basic measurable quantities (dimensions):
  //
  // ======================================================================
  
  // Length
  // metrum (Latin) and metron (Greek) "measure"
  const CLHEPdouble m = meter;
  setVariable("meter", m);
  setVariable("metre", m);
  setVariable("m",     m);
  
  // Mass
  const CLHEPdouble kg = kilogram;
  setVariable("kilogram", kg);
  setVariable("kg",       kg);
  
  // Time
  // minuta secundam (Latin) "second small one"
  const CLHEPdouble s = second;
  setVariable("second", s);
  setVariable("s",      s);
  
  // Current
  // ---  honors Andre-Marie Ampere (1775-1836) of France
  const CLHEPdouble A = ampere;
  setVariable("ampere", A);
  setVariable("amp",    A);
  setVariable("A",      A);
  
  // Temperature
  // ---  honors William Thomson, 1st Baron Lord Kelvin (1824-1907) of England
  const CLHEPdouble K = kelvin;
  setVariable("kelvin", K);
  setVariable("K",      K);
  
  // Amount of substance
  const CLHEPdouble mol = mole;
  setVariable("mole", mol);
  setVariable("mol",  mol);
  
  // Luminous intensity
  const CLHEPdouble cd  = candela;
  setVariable("candela", cd);
  setVariable("cd",      cd);

  // ======================================================================
  //
  // Supplementary SI units having special symbols:
  //
  // ======================================================================

  // Plane angle 
  const CLHEPdouble rad = 1.;
  setVariable("radian", rad);
  setVariable("rad",    rad);
  setVariable("milliradian", milli_ * rad);
  setVariable("mrad",        milli_ * rad);

  const CLHEPdouble pi  = 3.14159265358979323846;
  const CLHEPdouble deg = rad*pi/180.;
  setVariable("degree", deg);
  setVariable("deg",    deg);

  // Solid angle
  const CLHEPdouble sr  = 1.;
  setVariable("steradian", sr);
  setVariable("sr",        sr);

  // ======================================================================
  //
  // Derived SI units having special symbols:
  //
  // ======================================================================

  // Frequency
  // ---  honors Heinrich Rudolf Hertz (1857-1894) of Germany
  const CLHEPdouble Hz = 1./s;
  setVariable("hertz", Hz);
  setVariable("Hz",    Hz);

  // Force
  // ---  honors Sir Isaac Newton (1642-1727) of England
  const CLHEPdouble N = m * kg / (s*s);
  setVariable("newton", N);
  setVariable("N",      N);

  // Pressure
  // ---  honors Blaise Pascal (1623-1662) of France
  const CLHEPdouble Pa = N / (m*m);
  setVariable("pascal", Pa);
  setVariable("Pa",     Pa);

  const CLHEPdouble atm = 101325. * Pa;
  setVariable("atmosphere", atm);
  setVariable("atm",        atm);

  const CLHEPdouble bar = 100000*Pa;
  setVariable("bar", bar);

  // Energy
  // ---  honors James Prescott Joule (1818-1889) of England
  const CLHEPdouble J = N * m;
  setVariable("joule", J);
  setVariable("J",     J);

  // Power
  // ---  honors James Watt (1736-1819) of Scotland
  const CLHEPdouble W = J / s;
  setVariable("watt", W);
  setVariable("W",    W);

  // Electric charge
  // ---  honors Charles-Augustin de Coulomb (1736-1806) of France
  const CLHEPdouble C = A * s;
  setVariable("coulomb", C);
  setVariable("C",       C);

  // Electric potential  
  // ---  honors Count Alessandro Volta (1745-1827) of Italy
  const CLHEPdouble V = J / C;
  setVariable("volt", V);
  setVariable("V",    V);

  // Electric resistance
  // ---  honors Georg Simon Ohm (1787-1854) of Germany
  const CLHEPdouble ohm = V / A;
  setVariable("ohm", ohm);

  // Electric conductance
  // ---  honors Ernst Werner von Siemens (1816-1892) or
  //      his brother Sir William (Karl Wilhelm von) Siemens (1823-1883)
  //      of Germany (England)
  const CLHEPdouble S = 1./ ohm;
  setVariable("siemens", S);
  setVariable("S",       S);

  // Electric capacitance
  // ---  honors Michael Faraday (1791-1867) of England
  const CLHEPdouble F = C / V;
  setVariable("farad", F);
  setVariable("F",     F);

  // Magnetic flux density
  // ---  honors Nikola Tesla (1856-1943) of Croatia (United States)
  const CLHEPdouble T = V * s / (m*m);
  setVariable("tesla", T);
  setVariable("T",     T);

  // ---  honors Karl Friedrich Gauss (1777-1855) of Germany
  const CLHEPdouble Gs = 1.e-4*T;
  setVariable("gauss", Gs);
  setVariable("Gs",    Gs);

  // Magnetic flux
  // ---  honors Wilhelm Eduard Weber (1804-1891) of Germany
  const CLHEPdouble Wb = V * s;
  setVariable("weber", Wb);
  setVariable("Wb",    Wb);

  // Inductance
  // ---  honors Joseph Henry (1797-1878) of the United States
  const CLHEPdouble H = Wb / A;
  setVariable("henry", H);
  setVariable("H",     H);

  // Luminous flux
  const CLHEPdouble lm = cd * sr;
  setVariable("lumen", lm);
  setVariable("lm",    lm);

  // Illuminace
  const CLHEPdouble lx = lm / (m*m);
  setVariable("lux", lx);
  setVariable("lx",  lx);

  // Radioactivity
  // ---  honors Antoine-Henri Becquerel (1852-1908) of France
  const CLHEPdouble Bq = 1./s;
  setVariable("becquerel", Bq);
  setVariable("Bq",        Bq);
  setVariable("kilobecquerel",  kilo_ * Bq);
  setVariable("kBq",            kilo_ * Bq);
  setVariable("megabecquerel",  mega_ * Bq);
  setVariable("MBq",            mega_ * Bq);
  setVariable("gigabecquerel",  giga_ * Bq);
  setVariable("GBq",            giga_ * Bq);

  // ---  honors Pierre Curie (1859-1906) of France
  //      and Marie Sklodowska Curie (1867-1934) of Poland
  setVariable("curie", 3.7e+10 * Bq);
  setVariable("Ci",    3.7e+10 * Bq);
  setVariable("millicurie", milli_ * 3.7e+10 * Bq);
  setVariable("mCi",        milli_ * 3.7e+10 * Bq);
  setVariable("microcurie", micro_ * 3.7e+10 * Bq);
  setVariable("uCi",        micro_ * 3.7e+10 * Bq);

  // Specific energy
  // ---  honors Louis Harold Gray, F.R.S. (1905-1965) of England
  const CLHEPdouble Gy = J / kg;
  setVariable("gray", Gy);
  setVariable("Gy",   Gy);
  setVariable("kilogray",   kilo_ * Gy);
  setVariable("milligray", milli_ * Gy);
  setVariable("microgray", micro_ * Gy);

  // Dose equivalent
  const CLHEPdouble Sv = J / kg;
  setVariable("sievert", Sv);
  setVariable("Sv",      Sv);

  // ======================================================================
  //
  // Selected units:
  //
  // ======================================================================

  // Length

  const CLHEPdouble mm = milli_ * m;
  setVariable("millimeter", mm);
  setVariable("mm",         mm);

  const CLHEPdouble cm = centi_ * m;
  setVariable("centimeter", cm);
  setVariable("cm",         cm);

  setVariable("decimeter",  deci_ * m);

  const CLHEPdouble km = kilo_ * m; 
  setVariable("kilometer",  km);
  setVariable("km",         km);

  setVariable("micrometer", micro_ * m);
  setVariable("micron",     micro_ * m);
  setVariable("nanometer",  nano_  * m);

  // ---  honors Anders Jonas Angstrom (1814-1874) of Sweden
  setVariable("angstrom",   1.e-10 * m);

  // ---  honors Enrico Fermi (1901-1954) of Italy
  setVariable("fermi",      1.e-15 * m);

  // Length^2

  setVariable("m2",  m*m);
  setVariable("mm2", mm*mm);
  setVariable("cm2", cm*cm);
  setVariable("km2", km*km);

  const CLHEPdouble barn = 1.e-28 * m*m; 
  setVariable("barn",      barn);
  setVariable("millibarn", milli_ * barn);
  setVariable("mbarn",     milli_ * barn);
  setVariable("microbarn", micro_ * barn);
  setVariable("nanobarn",  nano_  * barn);
  setVariable("picobarn",  pico_  * barn);

  // LengthL^3

  setVariable("m3",  m*m*m);
  setVariable("mm3", mm*mm*mm);
  setVariable("cm3", cm*cm*cm);
  setVariable("cc",  cm*cm*cm);
  setVariable("km3", km*km*km);

  const CLHEPdouble L = 1.e-3*m*m*m;
  setVariable("liter", L);  
  setVariable("litre", L);  
  setVariable("L",     L);  
  setVariable("centiliter",  centi_ * L);
  setVariable("cL",          centi_ * L);
  setVariable("milliliter",  milli_ * L);
  setVariable("mL",          milli_ * L);

  // Length^-1

  const CLHEPdouble dpt = 1./m;
  setVariable("diopter", dpt);
  setVariable("dioptre", dpt);
  setVariable("dpt",     dpt);

  // Mass

  const CLHEPdouble g = 0.001*kg;
  setVariable("gram", g);
  setVariable("g",    g);
  setVariable("milligram",   milli_ * g);
  setVariable("mg",          milli_ * g);
  
  // Time

  setVariable("millisecond", milli_ * s);
  setVariable("ms",          milli_ * s);
  setVariable("microsecond", micro_ * s);
  setVariable("us",          micro_ * s);
  setVariable("nanosecond",  nano_  * s);
  setVariable("ns",          nano_  * s);
  setVariable("picosecond",  pico_  * s);
  setVariable("ps",          pico_  * s);

  // Current

  setVariable("milliampere", milli_ * A);
  setVariable("mA",          milli_ * A);
  setVariable("microampere", micro_ * A);
  setVariable("nanoampere",  nano_  * A);

  // Frequency

  setVariable("kilohertz",   kilo_ * Hz);
  setVariable("kHz",         kilo_ * Hz);
  setVariable("megahertz",   mega_ * Hz);
  setVariable("MHz",         mega_ * Hz);

  // Force
  setVariable("kilonewton",  kilo_ * N);
  setVariable("kN",          kilo_ * N);

  // Pressure
  setVariable("kilobar",     kilo_ * bar);
  setVariable("kbar",        kilo_ * bar);
  setVariable("millibar",    milli_ * bar);
  setVariable("mbar",        milli_ * bar);

  // Energy
  setVariable("kilojoule",   kilo_ * J);
  setVariable("kJ",          kilo_ * J);
  setVariable("megajoule",   mega_ * J);
  setVariable("MJ",          mega_ * J);
  setVariable("gigajoule",   giga_ * J);
  setVariable("GJ",          giga_ * J);

  const CLHEPdouble e_SI  = 1.60217733e-19;  // positron charge in coulomb
  const CLHEPdouble ePlus = e_SI * C;        // positron charge
  const CLHEPdouble eV    = ePlus * V;
  setVariable("electronvolt", eV);
  setVariable("eV",           eV);
  setVariable("kiloelectronvolt", kilo_ * eV);
  setVariable("keV",              kilo_ * eV);
  setVariable("megaelectronvolt", mega_ * eV);
  setVariable("MeV",              mega_ * eV);
  setVariable("gigaelectronvolt", giga_ * eV);
  setVariable("GeV",              giga_ * eV);
  setVariable("teraelectronvolt", tera_ * eV);
  setVariable("TeV",              tera_ * eV);
  setVariable("petaelectronvolt", peta_ * eV);
  setVariable("PeV",              peta_ * eV);

  // Power
  setVariable("kilowatt",    kilo_ * W);
  setVariable("kW",          kilo_ * W);
  setVariable("megawatt",    mega_ * W);
  setVariable("MW",          mega_ * W);
  setVariable("gigawatt",    giga_ * W);
  setVariable("GW",          giga_ * W);

  // Electric potential  
  setVariable("kilovolt",    kilo_ * V);
  setVariable("kV",          kilo_ * V);
  setVariable("megavolt",    mega_ * V);
  setVariable("MV",          mega_ * V);

  // Electric capacitance
  setVariable("millifarad",  milli_ * F);
  setVariable("mF",          milli_ * F);
  setVariable("microfarad",  micro_ * F);
  setVariable("uF",          micro_ * F);
  setVariable("nanofarad",   nano_  * F);
  setVariable("nF",          nano_  * F);
  setVariable("picofarad",   pico_  * F);
  setVariable("pF",          pico_  * F);

  // Magnetic flux density
  setVariable("kilogauss",   kilo_ * Gs);
  setVariable("kGs",         kilo_ * Gs);
}

} // namespace HepTool
