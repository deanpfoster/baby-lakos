// $Id: market.cc 245 2000-03-10 22:57:54Z foster $-*- c++ -*-


#include "market.h"

// put other includes here
#include "assert.h"
#include <iostream.h>
#include <function.h>
#include <numeric>
#include <algo.h>
////////////////////////////////////////////////////////////////////////////////////////////
//                          U S I N G   D I R E C T I V E S                            using
////////////////////////////////////////////////////////////////////////////////////////////
//                              C O N S T R U C T O R S                         constructors

Market::~Market()
{
};
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
Market::Market()
:
  m_buy_orders(),
  m_sell_orders()
{
};
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
////////////////////////////////////////////////////////////////////////////////////////////
//                             M A N I P U L A T O R S                          manipulators
void
Market::add(const Order& order)
{
  if(order.buy_p())
    m_buy_orders.insert(order);
  else
    {
      assert(order.sell_p());
      m_sell_orders.insert(order);
    }
}
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void
Market::remove(const Order&)
{
  cout << "oops!  not implemented yet!" << endl;
  assert(false);
}
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
Shares
Market::fire_market(Shares thickness, Price p)
{
  Shares total;
  total = 0 * Shares();
  for(multiset<Order>::iterator i = m_buy_orders.begin(); i != m_buy_orders.end();)
    {
      multiset<Order>::iterator next = i;
      ++next;
      Shares desired = i->desired_at(p,thickness);
      if(desired != 0 * Shares())
	{
	  m_buy_orders.erase(i);
	  total = total + desired;
	}
      i = next;      
    }
  for(multiset<Order>::iterator i = m_sell_orders.begin(); i != m_sell_orders.end();)
    {
      multiset<Order>::iterator next = i;
      ++next;
      Shares desired = i->desired_at(p,thickness);
      if(desired != 0 * Shares())
	{
	  m_sell_orders.erase(i);
	  total = total + desired;
	}
      i = next;      
    }
  return total;
}
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
pair<Price,Shares>
Market::maximal_trading(Shares max_thickness)
{
  pair<Price,Shares> result = make_pair(0*Price(),0*Shares());
  
  Shares fires_at;
  fires_at = maximum_below(max_thickness);
  if(fires_at != 0 * Shares())
    {
      result = cross(fires_at);
      fire_market(fires_at,result.first);
    }
  return result;
}
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void
Market::expire(double fraction)
{
  for(multiset<Order>::iterator i = m_buy_orders.begin(); i != m_buy_orders.end();)
    {
      multiset<Order>::iterator current = i;
      ++i;
      if((double)rand() / RAND_MAX < fraction)
	m_buy_orders.erase(current);
    }
  for(multiset<Order>::iterator i = m_sell_orders.begin(); i != m_sell_orders.end();)
    {
      multiset<Order>::iterator current = i;
      ++i;
      if((double)rand() / RAND_MAX < fraction)
	m_sell_orders.erase(current);
    }
}
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void
Market::buffer(Price lower, Price upper)
{
  assert(lower < upper);
  add(Order(lower - 1*Price(), 100000*Shares(), 0 * Shares()));  // market maker buyer
  add(Order(upper + 1*Price(),-100000*Shares(), 0 * Shares()));  // market maker seller
}

////////////////////////////////////////////////////////////////////////////////////////////
//                               A C C E S S O R S                                 accessors
struct operation_cross:public binary_function<Shares, Order, Shares>
{
  const Market& m_market;
  operation_cross(const Market& market):
    m_market(market)
    {
    }
  Price operator()(Shares s)
    {
      return m_market.cross(s).first;
    };
};


vector<Price>
Market::price(const vector<Shares> & x,Shares offset) const
{
  vector<Price> result(x.size());
  operation_cross cross_it(*this);
  if(offset == 0 * Shares())
    transform(x.begin(),x.end(),result.begin(),cross_it);
  else if(offset > 0 * Shares())
    {
      // need to buy some shares
      Order order(100000*Price(),offset,0*Shares());
      multiset<Order>& orders = const_cast<multiset<Order>&>(m_buy_orders);
      multiset<Order>::iterator where = orders.insert(order);
      transform(x.begin(),x.end(),result.begin(),cross_it);
      orders.erase(where);
    }
  else
    {
      // need to sell some shares
      Order order(0*Price(),offset,0*Shares());
      multiset<Order>& orders = const_cast<multiset<Order>&>(m_sell_orders);
      multiset<Order>::iterator where = orders.insert(order);
      transform(x.begin(),x.end(),result.begin(),cross_it);
      orders.erase(where);
    }

  return result;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void
Market::gnuplot_price_header(const vector<Shares> & offset,
			     ostream & ostrm,
			     const string& par) const
{
  // generate a line that looks like:  plot "-", "-", "-"
  // where the number of "-" is the number of offsets to plot
  ostrm << endl;
  ostrm << "plot " + par;
  

  for(vector<Shares>::const_iterator i = offset.begin(); i != offset.end(); ++i)
    {
      if(i != offset.begin())
	ostrm << ",";
      assert(*i >= 0 * Shares());
      if(*i == 0)
	 ostrm << "'-' t 'market' with lines";
      else
	 ostrm << "'-' t '+/-" << *i << "shares' with lines";
	
    }
  ostrm << endl;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void
Market::gnuplot_price(const vector<Shares> & x,
		      const vector<Shares> & offset,
		      ostream & ostrm) const
{
  for(vector<Shares>::const_iterator i = offset.begin(); i != offset.end(); ++i)
    {
      vector<Price> y = price(x,*i);
      for(unsigned int j = 0; j < x.size();++j)
	if(y[j] != -1 * Price())
	  // only print out prices for markets that actually have a price defined
	  ostrm << x[j]/Shares() << y[j]/Price() << endl;

      ostrm << endl;  // "pen up"
      y = price(x,0*Shares() - *i);
      for(unsigned int j = 0; j < x.size();++j)
	if(y[j] != -1 * Price())
	  // only print out prices for markets that actually have a price defined
	  ostrm << x[j]/Shares() << y[j]/Price() << endl;
      ostrm << "e" << endl;
    }
  
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void
Market::gnuplot_firing_header(ostream & ostrm,
			      const string& par) const
{
  ostrm << endl;
  ostrm << "plot " + par + " '-' t 'fraction of firing' with lines, '-' t 'one' with lines" << endl;
}
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void
Market::gnuplot_firing(const vector<Shares> & x,
		       ostream & ostrm) const
{
  for(vector<Shares>::const_iterator i = x.begin(); i != x.end(); ++i)
    {
      if((*i) == 0 * Shares())
	// convert to 1 share
	ostrm << "1 " << cross(Shares()).second/Shares() << endl;
      else
	ostrm << *i/Shares() << (cross(*i).second/(*i)) << endl;
    }
  ostrm << "e" << endl;
  for(vector<Shares>::const_iterator i = x.begin(); i != x.end(); ++i)
    {
	ostrm << *i/Shares() << 1 << endl;
    }
  ostrm << "e" << endl;
}
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void
Market::print_on(ostream & ostrm) const
{
  ostream_iterator<Order> out(ostrm,"\n\t");
  ostrm << m_buy_orders.size() << " buy orders:\n\t";
  copy(m_buy_orders.rbegin(),m_buy_orders.rend(),out);
  ostrm << "\n" << m_sell_orders.size() << " sell orders:\n\t";
  copy(m_sell_orders.begin(),m_sell_orders.end(),out);
  ostrm << endl;
};
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
pair<Price,Shares>
Market::cross(Shares thickness) const
{
  Shares trading = 0 * Shares();
  Price  buy_price =  100000 * Price();
  Price  sell_price = 0 * Price();
  Price  last_trade_price = -1 * Price();
  Shares buyer_used = 0 * Shares();
  Shares seller_used = 0 * Shares();

  multiset<Order>::const_reverse_iterator buyers = m_buy_orders.rbegin();
  multiset<Order>::const_iterator sellers = m_sell_orders.begin();

  while((buyers != m_buy_orders.rend())
	&& (sellers != m_sell_orders.end())
	&& (buy_price >= sell_price))
    {
      //we know we have a seller and a buyer who want to trade
      if(buy_price == sell_price)
	{
	  if(buyers->worst_price(1000000*Shares(),0 * Shares()) < sell_price)
	    break;
	  if(sellers->worst_price(1000000*Shares(),0 * Shares()) > buy_price)
	    break;
	}

      Shares buy_desired =  buyers->desired_at(sell_price,thickness);
      Shares shares_to_buy  = buy_desired - buyer_used;
      if(shares_to_buy > 0 * Shares())
	buy_price = buyers->worst_price(thickness,0 * Shares());
      Shares sell_desired =  0 * Shares() - sellers->desired_at(buy_price,thickness);
      Shares shares_to_sell = sell_desired - seller_used;
      if(shares_to_sell > 0 * Shares())
	sell_price = sellers->worst_price(thickness,0 * Shares());

      Shares shares_to_trade;
      if(shares_to_buy > shares_to_sell)
	shares_to_trade = shares_to_sell;
      else
	shares_to_trade = shares_to_buy;
      if(shares_to_trade > 0 * Shares())
	{
	  buyer_used  = buyer_used + shares_to_trade;
	  seller_used = seller_used + shares_to_trade;
	  if(buyer_used == buy_desired)
	    last_trade_price = sell_price;
	  else 
	    last_trade_price = buy_price;
	  trading = trading + shares_to_trade;
	}
      
      if(buyer_used == buy_desired)
	 {
	   ++buyers;
	   buyer_used = 0* Shares();
	 }
      if(seller_used == sell_desired)
	 {
	   ++sellers;
	   seller_used = 0* Shares();
	 }
    }
  return make_pair(last_trade_price,trading);
};
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

////////////////////////////////////////////////////////////////////////////////////////////
//                           P R O T E C T E D                                     protected

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

////////////////////////////////////////////////////////////////////////////////////////////
//                           P R I V A T E                                           private
struct add_on:public binary_function<Shares, Order, Shares>
{
  add_on(Price p,Shares thickness)
    :    m_p(p),
	 m_thickness(thickness)
    {
    }
  Shares
  operator()(Shares s, Order o)
    {
      return s + o.desired_at(m_p,m_thickness); 
    }
  Price m_p;
  Shares m_thickness;  
};
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
pair<Shares,int> 
Market::open_contracts() const
{
    Shares zero;
  zero = 0 * Shares();
  Shares total;
  total = 0 * Shares();
  Shares thickness;
  int count = m_buy_orders.size() + m_sell_orders.size();
  thickness = 100000000 * Shares();
  Price low;
  Price high;
  low = 0 * Price();
  high = 1000000 * Price();
  total =         accumulate(m_buy_orders.begin(), m_buy_orders.end(), zero, add_on(low,thickness));
  total = total - accumulate(m_sell_orders.begin(),m_sell_orders.end(),zero, add_on(high,thickness));
  return make_pair(total,count);
};
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

Shares 
Market::maximum_below(Shares upper) const
{
  if(upper < 99)
    return 0 * Shares();
  Shares traded = cross(upper).second;
  if(traded >= upper)
    return upper;
  if(traded < .9 * upper)
    return maximum_below(traded);
  
  Shares part_traded = cross(upper * .9).second;
  if(part_traded > upper * .9)
    return maximum_between(upper*.9,upper);
  else
    {
      // This is an efficiency hack
      return maximum_below(upper*.9);
    }
};
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
Shares
Market::maximum_between(Shares lower, Shares upper) const
{
  if(upper - lower < Shares())
    return upper;

  Shares middle = (lower + upper)/2;

  if(cross(middle).second > middle)
    return maximum_between(middle,upper);
  else
    return maximum_between(lower,middle);
};
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
////////////////////////////////////////////////////////////////////////////////////////////
//                     F R E E   F U N C T I O N S                            free functions

ostream & operator<<(ostream & ostrm, const Market & object)
{
  object.print_on(ostrm);
  return ostrm;
};

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
