// $Id: foo.h 2013 2000-09-01 21:13:45Z foster $ -*- c++ -*-

#ifndef INCLUDED_TWO_FOO
#define INCLUDED_TWO_FOO

// oops!  The following uses an incorrect include guard
// run include_guarding to detect such errors.

#ifndef INCLUDED_BAR
#include "one/bar.h"
#endif

class ostream;

namespace two
{
  class Foo: public one::Bar
  {
  public:
    // CONSTRUCTORS
    ~Foo();
    Foo();
    Foo(const Foo &);            

    // MANIPULATORS
    Foo& operator=(const Foo &); 

    // ACCESSORS
    void print_on(ostream &) const;

  protected:

  private:
  };
}

ostream& operator<<(ostream &,const two::Foo &);

#endif
