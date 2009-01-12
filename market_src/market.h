// $Id: market.h 245 2000-03-10 22:57:54Z foster $ -*- c++ -*-

#ifndef INCLUDED_MARKET
#define INCLUDED_MARKET

#include <string>

#ifndef INCLUDED_ORDER
#include "order.h"
#endif

#ifndef INCLUDED_STL_MULTISET
#define INCLUDED_STL_MULTISET
#include <multiset.h>
#endif

#ifndef INCLUDED_STL_VECTOR
#define INCLUDED_STL_VECTOR
#include <vector.h>
#endif

class Market
{
public:
  // CONSTRUCTORS
  ~Market();
  Market();

  // MANIPULATORS
  void add(const Order&);
  void remove(const Order&);  // order n calculation!
  Shares fire_market(Shares thickness,Price);  // excess/defict shares is returned
  pair<Price,Shares> maximal_trading(Shares max_thickness);
  void  expire(double fraction);
  void  buffer(Price lower, Price upper);

  // ACCESSORS
  vector<Price> price(const vector<Shares> &,Shares offset = 0 * Shares()) const;
  void gnuplot_price_header(const vector<Shares> & offset, ostream & ostrm,const string& ="") const;
  void gnuplot_price(const vector<Shares> &, const vector<Shares> & offset, ostream & ostrm) const;
  void gnuplot_firing_header(ostream & ostrm,const string& ="") const;
  void gnuplot_firing(const vector<Shares> &, ostream & ostrm) const;
  void print_on(ostream &) const;
  pair<Price,Shares> cross(Shares thickness) const;  
  pair<Shares,int> open_contracts() const;
  Shares maximum_below(Shares upper) const;    // firing calculation
  
protected:

private:
  multiset<Order> m_buy_orders;
  multiset<Order> m_sell_orders;
  Shares maximum_between(Shares lower,Shares upper) const;  
  
  Market(const Market &);            // Don't delete this.
  Market& operator=(const Market &); // Don't delete this.
};

ostream& operator<<(ostream &,const Market &);

#endif
