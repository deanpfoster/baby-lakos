// $Id: market_units_transformations.cc 219 2000-03-04 03:43:30Z foster $-*- c++ -*-

#include "market_units_transformations.h"

Basic_unit<Market_units,0,0,0> Unit<Market_units,Price,1,-1,0>::s_conversion_factor = basic_pure(1.);

Basic_unit<Market_units,0,0,0> Unit<Market_units,Shares,0,1,0>::s_conversion_factor = basic_pure(1.);

Basic_unit<Market_units,0,0,0> Unit<Market_units,Dollars,1,0,0>::s_conversion_factor = basic_pure(1.);
