// $Id: bar.h 2013 2000-09-01 21:13:45Z foster $ -*- c++ -*-

#ifndef INCLUDED_TWO_BAR
#define INCLUDED_TWO_BAR

class ostream;

#ifndef INCLUDED_TWO_FOO
#include "two/foo.h"
#endif

namespace two
{
  
  class Bar: public Foo
  {
  public:
    // CONSTRUCTORS
    virtual ~Bar();
    Bar();
    virtual Bar* clone() const;

    // MANIPULATORS

    // ACCESSORS
    void print_on(ostream &) const;

  protected:

  private:
    // DATA
  
    Bar(const Bar &);            // Don't delete this.
    Bar& operator=(const Bar &); // Don't delete this.
  };
}

ostream& operator<<(ostream &,const two::Bar &);

#endif
