// $Id: basic_unit.test.cc 216 2000-03-03 23:00:45Z foster $-*- c++ -*-


#include <iostream.h>
#include <assert.h>

#include "basic_unit.h"
#include "system.h"

class English: public System
{
  virtual std::string dim_name(int) const;
};

std::string
English::dim_name(int d) const
{
  if(d == 0)
    return "foot";
  if(d == 1)
    return "lbs";
  if(d == 2)
    return "s";

  return "not used";
}

struct foot: public Basic_unit<English,1,0,0>
{
  void operator=(const unit_name& rhs)
    {
      assign(rhs);
    }
};

struct pure_number: public Basic_unit<English,0,0,0>
{
public:
  pure_number(double data = 0):
    Basic_unit<English,0,0,0>()
    {
      m_data = data;
    };
  void operator=(const unit_name& rhs)
    {
      assign(rhs);
    }
};

struct foot_lbs: public Basic_unit<English,1,1,0>
{
  void operator=(const unit_name& rhs)
    {
      assign(rhs);
    }
};

struct lbs:public  Basic_unit<English,0,1,0> 
{
  void operator=(const unit_name& rhs)
    {
      assign(rhs);
    }
};

int
main()
{
  cout << "\n\n\n\t\t\t BASIC_UNIT  BASIC_UNIT  BASIC_UNIT\n\n\n"<<endl;
  {
    {
      foot unit_foot;
      Basic_unit<English,1,0,0> sample_foot = 3. * unit_foot;
      foot test_foot;
      test_foot = sample_foot;
      cout << test_foot << endl;
      
      foot other_foot;
      other_foot = 3. * unit_foot;
    }
    foot_lbs bu;  // testing construction
    cout << "default Foot lbs: " << bu << endl;
    
    lbs one_lbs;
    Basic_unit<English,0,1,0> one_basic_lbs;
    
    lbs x;
    x = 10. * one_basic_lbs;
    foot f1;
    foot f2;
    f2 = 2 * foot();
    f1 + f2;
    foot f3;
    cout << "f3 = " << f3 << endl;
    f3 = f1 + f2;
    cout << "f3 = " << f3 << endl;
    foot_lbs foo;
    foo = f1 * x;
    cout << "foo = " << foo << endl;
    
    //    foot_lbs bar = f1 * f2;  // this doesn't compile!
    
    cout << "constructed!" << endl;
  };

  cout << "\n\nDONE." << endl;  
};
