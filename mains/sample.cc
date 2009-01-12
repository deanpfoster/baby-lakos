// $Id: sample.cc 2013 2000-09-01 21:13:45Z foster $-*- c++ -*-


#include <iostream.h>
#include <assert.h>

#include "two/bar.h"

void
print_name(const one::Foo& obj)
{
  cout << obj << endl;
}


int
main()
{
  cout << "\n\n\n\t\t\t  SAMPLE\n\n\n"<<endl;

  one::Foo f1;
  one::Bar b1;
  two::Foo f2;
  two::Bar b2;
  print_name(f1);
  print_name(b1);
  print_name(f2);
  print_name(b2);
};
