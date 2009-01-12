// $Id: simulation.h 245 2000-03-10 22:57:54Z foster $ -*- c++ -*-

#ifndef INCLUDED_SIMULATION
#define INCLUDED_SIMULATION

#ifndef INCLUDED_STD_IOSTREAM
#define INCLUDED_STD_IOSTREAM
#include <iostream.h>
#endif

#ifndef INCLUDED_STD_VECTOR
#define INCLUDED_STD_VECTOR
#include <vector.h>
#endif

#ifndef INCLUDED_MARKET
#include "market.h"
#endif

#ifndef INCLUDED_ORDER_GENERATOR
#include "order_generator.h"
#endif

class Shares;
class ostream;

class Simulation
{
public:
  // CONSTRUCTORS
  ~Simulation();
  Simulation(double expire_rate,const Order_generator&,ostream& data);
  
  // MANIPULATORS
  void do_rounds(int rounds);
  void do_sloppy_rounds(int round, int test_interval);
  void do_till_before_fire();
  pair<Price,Shares> do_until_fire(int interval);
  
  Market& market();

  // ACCESSORS
  void print_on(ostream &) const;
  const Market& market() const;

private:
  Order add_order();
  
  Simulation(const Simulation &);            // Don't delete this.
  Simulation& operator=(const Simulation &); // Don't delete this.
  double m_expire_rate;
  Shares m_total_book;
  Shares m_total_volume;
  int    m_rounds;
  int    m_total_contracts_traded;
  Market m_market;
  ostream& m_ostrm_data;
  const Order_generator& m_next_order;
};
  
ostream& operator<<(ostream &,const Simulation &);


#endif

