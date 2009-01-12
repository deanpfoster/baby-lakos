// $Id: market_units_transformations.h 219 2000-03-04 03:43:30Z foster $-*- c++ -*-

#ifndef INCLUDED_ENGLISH_TRANSFORMATIONS
#define INCLUDED_ENGLISH_TRANSFORMATIONS


#ifndef INCLUDED_STD_STRING
#define INCLUDED_STD_STRING
#include <string>
#endif

#ifndef INCLUDED_UNIT
#include "unit.h"
#endif

#ifndef INCLUDED_MARKET_UNITS
#include "market_units.h"
#endif


struct Dollars: public Unit<Market_units,Dollars,1,0,0>
{
  void operator=(const unit_name& rhs)
    {
      assign(rhs);
    }
};
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
struct pure: public Unit<Market_units,pure,0,0,0>
{
  pure(double data):
    unit_name()
    {
      m_data = data;
    }

  void operator=(const unit_name& rhs)
    {
      assign(rhs);
    }
  
};
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
struct Price: public Unit<Market_units,Price,1,-1,0>
{
  void operator=(const unit_name& rhs)
    {
      assign(rhs);
    };
  void operator=(const Price& rhs)
    {
      assign(rhs);
    };
};
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
struct Shares: public Unit<Market_units,Shares,0,1,0>
{
  void operator=(const unit_name& rhs)
    {
      assign(rhs);
    }
  void operator=(const Shares& rhs)
    {
      assign(rhs);
    }
};
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

struct basic_dollars: public Basic_unit<Market_units,1,0,0>
{
  void operator=(const unit_name& rhs)
    {
      assign(rhs);
    }
};
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
struct basic_pure: public Basic_unit<Market_units,0,0,0>
{
  basic_pure(double data):
    unit_name()
    {
      m_data = data;
    }

  void operator=(const unit_name& rhs)
    {
      assign(rhs);
    }
  
};
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
struct basic_price: public Basic_unit<Market_units,1,-1,0>
{
  void operator=(const unit_name& rhs)
    {
      assign(rhs);
    }
};
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
struct basic_shares: public Basic_unit<Market_units,0,1,0>
{
  void operator=(const unit_name& rhs)
    {
      assign(rhs);
    }
};
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#endif

