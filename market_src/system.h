// $Id: system.h 216 2000-03-03 23:00:45Z foster $ -*- c++ -*-

#ifndef INCLUDED_SYSTEM
#define INCLUDED_SYSTEM
class ostream;

#include <vector.h>
#include <string>

class System
{
public:
  // CONSTRUCTORS
  virtual ~System();
  System();
  System(System*);

  // MANIPULATORS

  // ACCESSORS
  virtual void print_unit(ostream &, const vector<int>&, double) const;
  
  void print_on(ostream &) const;

protected:
  virtual std::string dim_to_string(const vector<int>& ) const;
  virtual std::string dim_name(int) const;

private:
  System* mp_imple;      // this pathetic form of inheretence is due to template problems in G++
  
  System(const System &);            // Don't delete this.
  System& operator=(const System &); // Don't delete this.
};

ostream& operator<<(ostream &,const System &);

#endif
