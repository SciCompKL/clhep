#include "CLHEPTypes.hpp"
// -*- C++ -*-
// $Id: PhysicalConstants.h,v 1.4 2010/06/16 17:12:28 garren Exp $
// ----------------------------------------------------------------------
// HEP coherent Physical Constants
//
// This file has been provided by Geant4 (simulation toolkit for HEP).
//
// The basic units are :
//  		millimeter  
// 		nanosecond  
// 		Mega electron Volt  
// 		positon charge 
// 		degree Kelvin
//              amount of substance (mole)
//              luminous intensity (candela)
// 		radian  
//              steradian 
//
// Below is a non exhaustive list of Physical CONSTANTS,
// computed in the Internal HEP System Of Units.
//
// Most of them are extracted from the Particle Data Book :
//        Phys. Rev. D  volume 50 3-1 (1994) page 1233
// 
//        ...with a meaningful (?) name ...
//
// You can add your own constants.
//
// Author: M.Maire
//
// History:
//
// 23.02.96 Created
// 26.03.96 Added constants for standard conditions of temperature
//          and pressure; also added Gas threshold.
// 29.04.08 Use PDG 2006 values
// 03.11.08 Use PDG 2008 values
// 17.07.20 Use PDG 2019 values
// 06.05.21 Added Bohr_magneton and nuclear_magneton constants

#ifndef HEP_PHYSICAL_CONSTANTS_H
#define HEP_PHYSICAL_CONSTANTS_H

#include "CLHEP/Units/defs.h"
#include "CLHEP/Units/SystemOfUnits.h"

namespace CLHEP {

//
// 
//
static constexpr CLHEPdouble Avogadro = 6.02214076e+23/mole;

//
// c   = 299.792458 mm/ns
// c^2 = 898.7404 (mm/ns)^2 
//
static constexpr CLHEPdouble c_light   = 2.99792458e+8 * m/s;
static constexpr CLHEPdouble c_squared = c_light * c_light;

//
// h     = 4.13566e-12 MeV*ns
// hbar  = 6.58212e-13 MeV*ns
// hbarc = 197.32705e-12 MeV*mm
//
static constexpr CLHEPdouble h_Planck      = 6.62607015e-34 * joule*s;
static constexpr CLHEPdouble hbar_Planck   = h_Planck/twopi;
static constexpr CLHEPdouble hbarc         = hbar_Planck * c_light;
static constexpr CLHEPdouble hbarc_squared = hbarc * hbarc;

//
//
//
static constexpr CLHEPdouble electron_charge = - eplus; // see SystemOfUnits.h
static constexpr CLHEPdouble e_squared = eplus * eplus;

//
// amu_c2 - atomic equivalent mass unit
//        - AKA, unified atomic mass unit (u)
// amu    - atomic mass unit
//
static constexpr CLHEPdouble electron_mass_c2 = 0.510998910 * MeV;
static constexpr CLHEPdouble   proton_mass_c2 = 938.272013 * MeV;
static constexpr CLHEPdouble  neutron_mass_c2 = 939.56536 * MeV;
static constexpr CLHEPdouble           amu_c2 = 931.494028 * MeV;
static constexpr CLHEPdouble              amu = amu_c2/c_squared;

//
// permeability of free space mu0    = 2.01334e-16 Mev*(ns*eplus)^2/mm
// permittivity of free space epsil0 = 5.52636e+10 eplus^2/(MeV*mm)
//
static constexpr CLHEPdouble mu0      = 4*pi*1.e-7 * henry/m;
static constexpr CLHEPdouble epsilon0 = 1./(c_squared*mu0);

//
// electromagnetic coupling = 1.43996e-12 MeV*mm/(eplus^2)
//
static constexpr CLHEPdouble elm_coupling           = e_squared/(4*pi*epsilon0);
static constexpr CLHEPdouble fine_structure_const   = elm_coupling/hbarc;
static constexpr CLHEPdouble classic_electr_radius  = elm_coupling/electron_mass_c2;
static constexpr CLHEPdouble electron_Compton_length = hbarc/electron_mass_c2;
static constexpr CLHEPdouble Bohr_radius = electron_Compton_length/fine_structure_const;

static constexpr CLHEPdouble alpha_rcl2 = fine_structure_const
                                   *classic_electr_radius
                                   *classic_electr_radius;

static constexpr CLHEPdouble twopi_mc2_rcl2 = twopi*electron_mass_c2
                                             *classic_electr_radius
                                             *classic_electr_radius;

static constexpr CLHEPdouble Bohr_magneton = (eplus*hbarc*c_light)/(2*electron_mass_c2);
static constexpr CLHEPdouble nuclear_magneton = (eplus*hbarc*c_light)/(2*proton_mass_c2);

//
//
//
static constexpr CLHEPdouble k_Boltzmann = 8.617333e-11 * MeV/kelvin;

//
//
//
static constexpr CLHEPdouble STP_Temperature = 273.15*kelvin;
static constexpr CLHEPdouble STP_Pressure    = 1.*atmosphere;
static constexpr CLHEPdouble kGasThreshold   = 10.*mg/cm3;

//
//
//
static constexpr CLHEPdouble universe_mean_density = 1.e-25*g/cm3;

}  // namespace CLHEP

#ifdef ENABLE_BACKWARDS_COMPATIBILITY
//  backwards compatibility will be enabled ONLY in CLHEP 1.9
using namespace CLHEP;
#endif

#endif /* HEP_PHYSICAL_CONSTANTS_H */





