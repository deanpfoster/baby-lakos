// $Id: foo.h 2013 2000-09-01 21:13:45Z foster $ -*- c++ -*-

#ifndef INCLUDED_ONE_FOO
#define INCLUDED_ONE_FOO

class ostream;

namespace one
{
  class Foo
  {
  public:
    // CONSTRUCTORS
    virtual ~Foo();
    Foo();
    Foo(const Foo &);            

    // MANIPULATORS
    Foo& operator=(const Foo &); 

    // ACCESSORS
    virtual void print_on(ostream &) const;

  protected:

  private:
  };
}

ostream& operator<<(ostream &,const one::Foo &);

#endif
