// $Id: order_generator.h 241 2000-03-10 15:33:06Z foster $ -*- c++ -*-

#ifndef INCLUDED_ORDER_GENERATOR
#define INCLUDED_ORDER_GENERATOR

class ostream;
#ifndef INCLUDED_ORDER
#include "order.h"
#endif

class Order_generator
{
public:
  // CONSTRUCTORS
  virtual ~Order_generator();
  Order_generator();

  // MANIPULATORS
  // ACCESSORS
  virtual Order operator()() const;
  void print_on(ostream &) const;

protected:

private:
  Order_generator(const Order_generator &);            // Don't delete this.
  Order_generator& operator=(const Order_generator &); // Don't delete this.
};

ostream& operator<<(ostream &,const Order_generator &);

#endif
