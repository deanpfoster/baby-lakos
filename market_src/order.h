// $Id: order.h 225 2000-03-05 19:50:30Z foster $ -*- c++ -*-

#ifndef INCLUDED_ORDER
#define INCLUDED_ORDER

#ifndef INCLUDED_MARKET_TRANSFORMATIONS_UNITS
#include "market_units_transformations.h"
#endif

class ostream;

class Order
{
public:
  // CONSTRUCTORS
  ~Order();
  Order();
  Order(Price buy, Price sell, Shares, Shares thickness);
  Order(Price trade, Shares, Shares thickness);
  Order(const Order &);            // Don't delete this.

  // MANIPULATORS
  Shares desired_at(Price,Shares thickness) const;

  // ACCESSORS
  void print_on(ostream &) const;
  bool operator<(const Order &) const;
  bool buy_p() const;
  bool sell_p() const;
  Price worst_price(Shares thickness, Shares to_trade) const
    {
      assert(thickness >= m_thickness);  // make sure we want to be part of this market
      assert(to_trade <= m_shares);      // make sure we want to do this much business
      return m_price;
    }
  
protected:

private:
  Shares m_shares;
  Price  m_price;
  bool   m_buying;
  Shares m_thickness;
  
  Order& operator=(const Order &); // Don't delete this.
};

ostream& operator<<(ostream &,const Order &);

#endif
