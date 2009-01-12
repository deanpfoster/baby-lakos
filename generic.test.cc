// $Id: generic.test.cc 2013 2000-09-01 21:13:45Z foster $-*- c++ -*-


#include <iostream.h>
#include <assert.h>

#include "generic.h"

int
main()
{
  cout << "\n\n\n\t\t\t GENERIC  GENERIC  GENERIC\n\n\n"<<endl;
  {
    Generic g;  // testing construction
    cout << "constructed!" << endl;
  };

  cout << "\n\nDONE." << endl;  
};
