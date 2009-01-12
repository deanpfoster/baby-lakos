// $Id: market_units.test.cc 216 2000-03-03 23:00:45Z foster $-*- c++ -*-


#include <iostream.h>
#include <assert.h>

#include "market_units.h"

int
main()
{
  cout << "\n\n\n\t\t\t  MARKET_UNITS  MARKET_UNITS  MARKET_UNITS\n\n\n"<<endl;
  {
    Market_units g;
    vector<int> dim;
    
    dim.push_back(-1);
    dim.push_back(2);
    dim.push_back(0);
    g.print_unit(cout,dim,30.);
    cout << endl;
    cout << endl;
    
    g.print_on(cout);
    
  }
  cout << "\n\nDONE." << endl;  
};
