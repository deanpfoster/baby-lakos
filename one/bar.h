// $Id: bar.h 2013 2000-09-01 21:13:45Z foster $ -*- c++ -*-

#ifndef INCLUDED_ONE_BAR
#define INCLUDED_ONE_BAR

class ostream;

#ifndef INCLUDED_ONE_FOO
#include "one/foo.h"
#endif

namespace one
{
  
  class Bar: public Foo
  {
  public:
    // CONSTRUCTORS
    virtual ~Bar();
    Bar();
    virtual Bar* clone() const;
    Bar(const Bar &);

    // MANIPULATORS

    // ACCESSORS
    void print_on(ostream &) const;

  protected:

  private:
    // DATA
  
    Bar& operator=(const Bar &); // Don't delete this.
  };
}

ostream& operator<<(ostream &,const one::Bar &);

#endif
