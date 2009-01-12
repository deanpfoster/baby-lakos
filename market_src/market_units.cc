// $Id: market_units.cc 216 2000-03-03 23:00:45Z foster $-*- c++ -*-

#include "market_units.h"

std::string
Market_units::dim_name(int d) const
{
  if(d == 0)
    return "dollars";
  if(d == 1)
    return "shares";

  return "not used";
}
