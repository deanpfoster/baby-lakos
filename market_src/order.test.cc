// $Id: order.test.cc 229 2000-03-08 03:49:50Z foster $-*- c++ -*-


#include <iostream.h>
#include <assert.h>

#include "order.h"

int
main()
{
  cout << "\n\n\n\t\t\t ORDER  ORDER  ORDER\n\n\n"<<endl;
  {
    Order g;  // testing construction
    cout << "constructed!" << endl;

    cout << Order(0*Price(),20*Price(),50*Shares(),1000*Shares()) << endl;
    cout << Order(100*Price(),50*Shares(),1000*Shares()) << endl;
    cout << Order(100*Price(),-50*Shares(),1000*Shares()) << endl;
    
    
  };

  cout << "\n\nDONE." << endl;  
};
