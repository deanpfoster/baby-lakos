// $Id: market_units_transformations.test.cc 219 2000-03-04 03:43:30Z foster $-*- c++ -*-

#include <iostream.h>
#include <assert.h>
#include "market_units_transformations.h"


int
main()
{
  cout << "\n\n\n\t\t\t ENGLISH_TRANFORMATIONS  ENGLISH_TRANFORMATIONS \n\n\n"<<endl;
  {
    Price p;  // testing construction
    Shares q;
    Dollars d;
    d = p * q;
    p = p;
    
    cout << p << endl;
    
    cout << "\n\nDONE." << endl;
  }
  
};
