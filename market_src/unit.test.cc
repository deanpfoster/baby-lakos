// $Id: unit.test.cc 216 2000-03-03 23:00:45Z foster $-*- c++ -*-


#include <iostream.h>
#include <assert.h>

#include "unit.h"
#include "market_units.h"

// // // // // // // // // // // // // // // // // // // // // // // // // // // // 
struct foot: public Basic_unit<Market_units,1,0,0>
{
  void operator=(const unit_name& rhs)
    {
      assign(rhs);
    }
};
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
struct pure: public Basic_unit<Market_units,0,0,0>
{
  pure(double data):
    unit_name()
    {
      m_data = data;
    }

  void operator=(const unit_name& rhs)
    {
      assign(rhs);
    }
  
};
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
struct mile: public Unit<Market_units,mile,1,0,0>
{
  typedef string naming_source;

  void operator=(const unit_name& rhs)
    {
      assign(rhs);
    }
  static string s_name;
};
string mile::s_name = "mile";
Basic_unit<Market_units,0,0,0> Unit<Market_units,mile,1,0,0>::s_conversion_factor = pure(5280.);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
struct yard: public Unit<Market_units,yard,1,0,0>
{
  typedef string naming_source;
  
  void operator=(const unit_name& rhs)
    {
      assign(rhs);
    }
  static string s_name;
};
string yard::s_name = "yard";
Basic_unit<Market_units,0,0,0> Unit<Market_units,yard,1,0,0>::s_conversion_factor = pure(3.);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
struct foot_lbs: public Basic_unit<Market_units,1,1,0>
{
  void operator=(const unit_name& rhs)
    {
      assign(rhs);
    }
};
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

struct lbs: public Basic_unit<Market_units,0,1,0>
{
  void operator=(const unit_name& rhs)
    {
      assign(rhs);
    }
};
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


int
main()
{
  cout << "\n\n\n\t\t\t UNIT  UNIT  UNIT  UNIT  UNIT\n\n\n"<<endl;
  {
    foot_lbs bu;  // testing construction
    lbs weight;
    
    weight = 10. * lbs();
    foot f1;
    foot f2;
    f2 = 2. * foot();
    cout << "f2: " << f2 << endl;
    
    mile m = mile();
    cout << "m: " << m << endl;    
    m = 10. * mile();
    cout << "m: " << m << endl;
    foot f_mile;
    f_mile = m;
    cout << "m: " << f_mile << endl;

    cout << "miles converter: " << mile::s_conversion_factor << endl;
    cout << "yards converter: " << yard::s_conversion_factor << endl;
    
    cout << "miles/feet: " << mile()/foot() << endl;
    cout << "yards/feet: " << yard()/foot() << endl;
    cout << "miles/miles: " << mile()/mile() << endl;
    cout << "miles/yards: " << mile()/yard() << endl;
    cout << "feet/miles: " << foot()/mile() << endl;
    
    f1 + f2;
    foot f3;
    f3 = f1 + f2;
    foot_lbs foo;
    foo = f1 * lbs();
    // foot_lbs bar = f1 * f2;
    
    mile m2;
    m2 = m + m;
    mile m3;
    m3 = f3;
    
    cout << "constructed!" << endl;
  };
  {
    // checking everything is defined correctly
    cout << yard() * yard() << endl;
    cout << foot() * yard() << endl;
    cout << yard() * foot() << endl;
    cout << foot() * foot() << endl;

    cout << 10 * yard() << endl;
    cout << yard() * 10. << endl;
    cout << 10 * foot() << endl;
    cout << foot() * 10. << endl;
    
    cout << 10. / yard() << endl;
    cout << yard() / 10. << endl;
    cout << 10. / foot() << endl;
    cout << foot() / 10. << endl;
    
    cout << yard() + yard() << endl;
    cout << foot() + yard() << endl;
    cout << yard() + foot() << endl;
    cout << foot() + foot() << endl;

    cout << yard() - yard() << endl;
    cout << foot() - yard() << endl;
    cout << yard() - foot() << endl;
    cout << foot() - foot() << endl;

    cout << yard() / yard() << endl;
    cout << foot() / yard() << endl;
    cout << yard() / foot() << endl;
    cout << foot() / foot() << endl;
  }
  {
    // checking construction pairs
    yard y;
    foot f;
    y = f;
    f = y;
    y = f + f + f;
    f = y + y + y;
  }
  

  cout << "\n\nDONE." << endl;  
};
