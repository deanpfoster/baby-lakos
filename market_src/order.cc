// $Id: order.cc 229 2000-03-08 03:49:50Z foster $-*- c++ -*-


#include "order.h"

// put other includes here
#include "assert.h"
#include <iostream.h>

////////////////////////////////////////////////////////////////////////////////////////////
//                          U S I N G   D I R E C T I V E S                            using
////////////////////////////////////////////////////////////////////////////////////////////
//                              C O N S T R U C T O R S                         constructors

Order::~Order()
{
};
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
Order::Order()
:  m_shares(),
  m_price(),
  m_buying(true),
  m_thickness()
{
  // willing to buy zero shares at a price of zero in any market
  m_shares    = 0. *Shares();
  m_price     = 0. *Price();
  m_thickness = 0. *Shares();
  
};
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
Order::Order(Price buy, Price sell, Shares shares, Shares thickness)
:  m_shares(),
   m_price(),
   m_buying(),
   m_thickness()
{
  assert(shares/Shares() >= basic_pure(0.));
  assert(sell > buy);
  m_shares = shares;
  m_thickness = thickness;
  
  if(buy == 0. * Price())
    {
      // we are a seller
      m_price = sell;
      m_buying = false;
    }
  else
    {
      m_price = buy;
      m_buying = true;
    }
};
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
Order::Order(Price trade, Shares shares, Shares thickness)
:  m_shares(shares),
   m_price(trade),
   m_buying(shares > 0 * Shares()),
   m_thickness(thickness)
{
  if(!m_buying)
    m_shares = 0 * Shares() - shares;
};
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
Order::Order(const Order & other)
  :
  m_shares(other.m_shares),
  m_price(other.m_price),
  m_buying(other.m_buying),
  m_thickness(other.m_thickness)  
{
};
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

////////////////////////////////////////////////////////////////////////////////////////////
//                             M A N I P U L A T O R S                          manipulators
 

Order&
Order::operator=(const Order & rhs)
{
  m_shares = rhs.m_shares;
  m_price = rhs.m_price;
  m_buying= rhs.m_buying;  
  m_thickness = m_thickness;
  return *this; 
};
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


////////////////////////////////////////////////////////////////////////////////////////////
//                               A C C E S S O R S                                 accessors
void
Order::print_on(ostream & ostrm) const
{
  ostrm << "Desired: " << m_shares;
  if(m_buying)
    ostrm << " buy at ";
  else
    ostrm << "sell at ";
  ostrm << m_price;
  ostrm << " if the market thickness is " << m_thickness << ". ";
};
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
Shares
Order::desired_at(Price p,Shares thickness) const
{
  Shares result;
  result = 0 * Shares();
  if(thickness > m_thickness)
    {
      if(m_buying)
	{
	  if(m_price > p)
	    result = m_shares;
	}
      else
	{
	  if(m_price < p)
	    result =  -1. * m_shares;
	}
    }
  return result;
}
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
bool
Order::operator<(const Order& other) const
{
  return (m_price < other.m_price);
}
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
bool
Order::buy_p() const
{
  return m_buying;
}
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
bool
Order::sell_p() const
{
  return !m_buying;
}
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

////////////////////////////////////////////////////////////////////////////////////////////
//                           P R O T E C T E D                                     protected

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

////////////////////////////////////////////////////////////////////////////////////////////
//                           P R I V A T E                                           private


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
////////////////////////////////////////////////////////////////////////////////////////////
//                     F R E E   F U N C T I O N S                            free functions

ostream & operator<<(ostream & ostrm, const Order & object)
{
  object.print_on(ostrm);
  return ostrm;
};

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
