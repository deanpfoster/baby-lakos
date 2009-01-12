// $Id: order_generator.test.cc 241 2000-03-10 15:33:06Z foster $-*- c++ -*-


#include <iostream.h>
#include <assert.h>

#include "order_generator.h"

main()
{
  cout << "\n\n\n\t\t\t ORDER_GENERATOR  ORDER_GENERATOR  ORDER_GENERATOR\n\n\n"<<endl;
  {
    Order_generator g;  // testing construction
    cout << "constructed!" << endl;
    cout << g() << endl;
    cout << g() << endl;
  };

  cout << "\n\nDONE." << endl;  
};
