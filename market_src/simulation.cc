// $Id: simulation.cc 246 2000-03-10 23:40:35Z foster $-*- c++ -*-


#include "simulation.h"
#include <math.h>
#include <strstream.h>

// put other includes here
#include "market.h"

////////////////////////////////////////////////////////////////////////////////////////////
//                              C O N S T R U C T O R S                         constructors
Simulation::~Simulation()
{
};
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
Simulation::Simulation(double expire_rate,const Order_generator& gen,ostream & out)
  :
  m_expire_rate(expire_rate),
  m_total_book(0*Shares()),
  m_total_volume(0*Shares()),
  m_rounds(0),
  m_total_contracts_traded(0),
  m_market(),
  m_ostrm_data(out),
  m_next_order(gen)
{
  m_market.buffer(50*Price(), 60*Price());
};
////////////////////////////////////////////////////////////////////////////////////////////
//                             M A N I P U L A T O R S                          manipulators
 
void
Simulation::do_rounds(int rounds)
{
  do_sloppy_rounds(rounds,1);  
};
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void
Simulation::do_sloppy_rounds(int rounds,int orders_between_tests)
{
  double prob = sqrt(m_expire_rate * orders_between_tests);
  assert(rounds == (rounds / orders_between_tests) * orders_between_tests);
  
  for(int time = 0; time*orders_between_tests < rounds; ++time)
    {
      for(int i = 0; i < orders_between_tests; ++i)
	add_order();

      int starting_book = m_market.open_contracts().second;
      pair<Price,Shares> fire = m_market.maximal_trading(1000000 * Shares());
      int trades = starting_book - m_market.open_contracts().second;
      m_total_contracts_traded += trades;
      m_total_volume = m_total_volume + fire.second;
      m_ostrm_data << fire.second/Shares() << "\t" << fire.first/Price() << endl;

      if((double)rand() / RAND_MAX < prob)
	{
	  m_market.expire(prob);
	  m_market.buffer(50*Price(),60*Price());
	}
    }
};
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void
Simulation::do_till_before_fire()
{
  double prob = sqrt(m_expire_rate);
  bool done = false;
  pair<Price,Shares> result;
  
  while(!done)
    {
      Order last_added = add_order();
      if(m_market.maximal_trading(1000000*Shares()).second != 0 * Shares())
	{
	  //	  m_market.remove(last_added);
	  done = true;
	}
      
      if((double)rand() / RAND_MAX < prob)
	{
	  m_market.expire(prob);
	  m_market.buffer(50*Price(),60*Price());
	}
    }
};
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
pair<Price,Shares>
Simulation::do_until_fire(int orders_between_tests)
{
  double prob = sqrt(m_expire_rate * orders_between_tests);
  bool done = false;
  pair<Price,Shares> result;
  
  while(!done)
    {
      for(int i = 0; i < orders_between_tests; ++i)
	add_order();

      int starting_book = m_market.open_contracts().second;
      pair<Price,Shares> fire = m_market.maximal_trading(1000000 * Shares());
      int trades = starting_book - m_market.open_contracts().second;
      if(trades > 0)
	{
	  done = true;
	  result = fire;
	}
      m_total_contracts_traded += trades;
      m_total_volume = m_total_volume + fire.second;
      m_ostrm_data << fire.second/Shares() << "\t" << fire.first/Price() << endl;

      if((double)rand() / RAND_MAX < prob)
	{
	  m_market.expire(prob);
	  m_market.buffer(50*Price(),60*Price());
	}
    }
  return result;
};
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
Market&
Simulation::market()
{
  return m_market;
}
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


////////////////////////////////////////////////////////////////////////////////////////////
//                               A C C E S S O R S                                 accessors
void
Simulation::print_on(ostream & ostrm) const
{
    ostrm << "Total volume = " << m_total_volume
	  << " out of " << m_total_book << "asked to trade." << endl;
    ostrm<< "Fraction succesful trades: " << m_total_volume / m_total_book << endl << endl;
    ostrm << m_total_contracts_traded << " contracts out of "
	  << m_rounds << " contracts." << endl;
    ostrm << "clearing fraction: " << (double)m_total_contracts_traded/m_rounds << endl;

};
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
const Market&
Simulation::market() const
{
  return m_market;
}
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

////////////////////////////////////////////////////////////////////////////////////////////
//                           P R O T E C T E D                                     protected

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

////////////////////////////////////////////////////////////////////////////////////////////
//                           P R I V A T E                                           private

Order
Simulation::add_order()
{
  Order o = m_next_order();
  m_market.add(o);
  if(o.buy_p())
    m_total_book = m_total_book + o.desired_at(0 * Price(), 1000000 * Shares());
  else
    m_total_book = m_total_book - o.desired_at(10000 * Price(), 1000000 * Shares());
  ++m_rounds;
  return o;
};

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
////////////////////////////////////////////////////////////////////////////////////////////
//                     F R E E   F U N C T I O N S                            free functions

ostream & operator<<(ostream & ostrm, const Simulation & object)
{
  object.print_on(ostrm);
  return ostrm;
};

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
