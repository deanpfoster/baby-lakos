// $Id: foo.test.cc 2013 2000-09-01 21:13:45Z foster $-*- c++ -*-


#include <iostream.h>
#include <assert.h>

#include "foo.h"

int
main()
{
  cout << "\n\n\n\t\t\t FOO  FOO  FOO\n\n\n"<<endl;
  {
    one::Foo g;  // testing construction
    cout << g << endl;
  };

  cout << "\n\nDONE." << endl;  
};
