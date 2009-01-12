// $Id: market_units.h 219 2000-03-04 03:43:30Z foster $ -*- c++ -*-

#ifndef INCLUDED_MARKET_UNITS
#define INCLUDED_MARKET_UNITS

#ifndef INCLUDED_SYSTEM
#include "system.h"
#endif

class ostream;

class Market_units: public System
{
  virtual std::string dim_name(int) const;
};

class Dollars;
class Shares;
class Price;

#endif
