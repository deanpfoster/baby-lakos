// $Id: system.test.cc 216 2000-03-03 23:00:45Z foster $-*- c++ -*-


#include <iostream.h>
#include <assert.h>

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


int
main()
{
  cout << "\n\n\n\t\t\t SYSTEM  SYSTEM  SYSTEM\n\n\n"<<endl;
  {
    System g;  // testing construction
    cout << "constructed!" << endl;
    cout << endl;
    
    vector<int> dim;
    dim.push_back(-1);
    dim.push_back(2);
    dim.push_back(0);
    g.print_unit(cout,dim,30.);
    cout << endl;
    cout << endl;
    
    g.print_on(cout);
    
  };
  {
    English g;
    vector<int> dim;
    
    dim.push_back(-1);
    dim.push_back(2);
    dim.push_back(0);
    g.print_unit(cout,dim,30.);
    cout << endl;
    cout << endl;
    
    g.print_on(cout);
    
  }
  {
    English English_imple;
    System g(&English_imple);
    vector<int> dim;
    
    dim.push_back(-1);
    dim.push_back(2);
    dim.push_back(0);
    g.print_unit(cout,dim,30.);
    cout << endl;
    cout << endl;
    
    g.print_on(cout);
    
  }
  
  cout << "\n\nDONE." << endl;  
};
