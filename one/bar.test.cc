// $Id: bar.test.cc 2013 2000-09-01 21:13:45Z foster $-*- c++ -*-


#include <iostream.h>
#include <assert.h>

#include "bar.h"

int
main()
{
  cout << "\n\n\n\t\t\t BAR  BAR  BAR\n\n\n"<<endl;
  {
    one::Bar g;  // testing construction
    cout << g << endl;
  };

  cout << "\n\nDONE." << endl;  
};
