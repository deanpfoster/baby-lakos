// $Id: order_generator.cc 241 2000-03-10 15:33:06Z foster $-*- c++ -*-


#include "order_generator.h"

// put other includes here
#include "assert.h"
#include <iostream.h>

////////////////////////////////////////////////////////////////////////////////////////////
//                          U S I N G   D I R E C T I V E S                            using
////////////////////////////////////////////////////////////////////////////////////////////
//                              C O N S T R U C T O R S                         constructors
Order_generator::~Order_generator()
{
};
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
Order_generator::Order_generator()
{
};
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
////////////////////////////////////////////////////////////////////////////////////////////
//                             M A N I P U L A T O R S                          manipulators
////////////////////////////////////////////////////////////////////////////////////////////
//                               A C C E S S O R S                                 accessors
void
Order_generator::print_on(ostream & ostrm) const
{
  ostrm << "generic order generator: low = 50, high = 60, thick tailed thickness" << endl;
};
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


Order
Order_generator::operator()() const
{
  Shares s;
  s = (100 + 100 * (rand() % 50)) * Shares();
  Price p;
  p = (50 + (rand() % 40) / 4.) * Price();
  Shares thickness;
  thickness = 3*s;
  while(rand() % 2 == 0)
    thickness = 2 * thickness;
            
  if(rand() % 2 == 0)
    // buy order
    return Order(0*Price(), p , s , thickness);
  else
    // sell order 
    return Order(p, 1000*Price(), s , thickness);
}
////////////////////////////////////////////////////////////////////////////////////////////
//                           P R O T E C T E D                                     protected
////////////////////////////////////////////////////////////////////////////////////////////
//                           P R I V A T E                                           private
////////////////////////////////////////////////////////////////////////////////////////////
//                     F R E E   F U N C T I O N S                            free functions

ostream & operator<<(ostream & ostrm, const Order_generator & object)
{
  object.print_on(ostrm);
  return ostrm;
};

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
