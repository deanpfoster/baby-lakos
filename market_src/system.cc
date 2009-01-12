// $Id: system.cc 216 2000-03-03 23:00:45Z foster $-*- c++ -*-


#include "system.h"

// put other includes here
#include <assert.h>
#include <iostream.h>
#include <strstream.h>

////////////////////////////////////////////////////////////////////////////////////////////
//                              C O N S T R U C T O R S                         constructors

System::~System()
{
};
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
System::System():
  mp_imple(0)
{
};
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
System::System(System* imple)
  :
  mp_imple(imple)
{
};

////////////////////////////////////////////////////////////////////////////////////////////
//                             M A N I P U L A T O R S                          manipulators
////////////////////////////////////////////////////////////////////////////////////////////
//                               A C C E S S O R S                                 accessors
void
System::print_on(ostream & ostrm) const
{
  if(mp_imple)
    {
      mp_imple->print_on(ostrm);
      return;
    }
  ostrm << "Table of named dimensions:" << endl;
  
  for(int i = 0;i < 10; ++i)
    ostrm << "\t" << i << " = " << dim_name(i) << endl;
  ostrm << endl;  
};
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void
System::print_unit(ostream & ostrm,const vector<int>& dim,double value) const
{
  if(mp_imple)
    {
      mp_imple->print_unit(ostrm,dim,value);
      return;
    }
  ostrm << value << " " << dim_to_string(dim);
};
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

////////////////////////////////////////////////////////////////////////////////////////////
//                           P R O T E C T E D                                     protected

string
System::dim_to_string(const vector<int>& dim) const
{
  std::strstream tmp;

  bool need_negatives = false;
  int  num_dims = 0;
  
  for(int i = 0; i < (int)dim.size(); ++i)
    {
      if(dim[i] < 0)
	need_negatives = true;
      
      if(dim[i] == 1)
	tmp << dim_name(i) << " ";

      if(dim[i] > 1)
	tmp << dim_name(i) << "^" << dim[i] << " ";

      num_dims += (dim[i] != 0);
    }
  
  if(need_negatives)
    {
      tmp << "/";
      for(int i = 0; i < (int)dim.size(); ++i)
	{
	  if(dim[i] == -1)
	    tmp << dim_name(i) << " ";

	  if(dim[i] <  -1)
	    tmp << dim_name(i) << "^" << dim[i] << " ";
	}
    }
  
  string s;
  getline(tmp,s);
  if(num_dims >= 2)
    s = "(" + s + ")";
  
  return s;
};
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

string
System::dim_name(int d) const
{
  std::strstream tmp;
  tmp << "none";
  tmp << d;
  string s;
  getline(tmp,s);
  return s;
};
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

////////////////////////////////////////////////////////////////////////////////////////////
//                           P R I V A T E                                           private


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
////////////////////////////////////////////////////////////////////////////////////////////
//                     F R E E   F U N C T I O N S                            free functions

ostream & operator<<(ostream & ostrm, const System & object)
{
  object.print_on(ostrm);
  return ostrm;
};

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
