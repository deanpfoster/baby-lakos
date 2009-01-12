// $Id: generic.h 2013 2000-09-01 21:13:45Z foster $ -*- c++ -*-

#ifndef INCLUDED_LIBRARY_GENERIC
#define INCLUDED_LIBRARY_GENERIC

class ostream;

namespace library
{
  
  class Generic
  {
  public:
    // CONSTRUCTORS
    virtual ~Generic();
    Generic();
    virtual Generic* clone() const;

    // MANIPULATORS

    // ACCESSORS
    virtual void print_on(ostream &) const;

  protected:

  private:
    // DATA
  
    Generic(const Generic &);            // Don't delete this.
    Generic& operator=(const Generic &); // Don't delete this.
  };
}

ostream& operator<<(ostream &,const library::Generic &);

#endif
