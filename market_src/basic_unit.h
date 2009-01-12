// $Id: basic_unit.h 219 2000-03-04 03:43:30Z foster $ -*- c++ -*-

#ifndef INCLUDED_BASIC_UNIT
#define INCLUDED_BASIC_UNIT
#include <vector.h>
class ostream;

template<class T, int i1, int i2 = 0, int i3 = 0>
class Basic_unit
{
  typedef Basic_unit<T,i1,i2,i3> unit_name;
  
public:
  // CONSTRUCTORS
  ~Basic_unit(){};

  Basic_unit():
    m_data(1.)
    {};

  Basic_unit(const unit_name & other):
    m_data(other.m_data)
    {
    }
  
  // MANIPULATORS
  void assign(const unit_name & other)
    {
      m_data = other.m_data;
    }

  // ACCESSORS

  bool operator>=(const unit_name &other) const
    {
      return m_data >= other.m_data;
    }
  
  
  double m_data; // shouldn't be public--but too many friends at the moment

protected:

private:
};


template<class T, int i1, int i2, int i3>
ostream&
operator<<(ostream& ostrm,Basic_unit<T,i1,i2,i3> obj)
{
  T printer;
  vector<int> dim;
  dim.push_back(i1);
  dim.push_back(i2);
  dim.push_back(i3);
  printer.print_unit(ostrm,dim,obj.m_data);
  return ostrm;
}
//////////////////////////////////////////////////////////////////////////////////////
// x+y   x+y   x+y   x+y   x+y   x+y   x+y   x+y   x+y   x+y   x+y   x+y   x+y   x+y  

template<class T, int i1, int i2, int i3>
Basic_unit<T,i1,i2,i3>
operator+(Basic_unit<T,i1,i2,i3> x, Basic_unit<T,i1,i2,i3> y)
{
   Basic_unit<T,i1,i2,i3> result;
   result.m_data = (x.m_data + y.m_data);
   return result;
}
//////////////////////////////////////////////////////////////////////////////////////
// x-y   x-y   x-y   x-y   x-y   x-y   x-y   x-y   x-y   x-y   x-y   x-y   x-y   x-y  

template<class T, int i1, int i2, int i3>
Basic_unit<T,i1,i2,i3>
operator-(Basic_unit<T,i1,i2,i3> x, Basic_unit<T,i1,i2,i3> y)
{
  Basic_unit<T,i1,i2,i3> result;
  result.m_data = (x.m_data - y.m_data);
  return result;
}
//////////////////////////////////////////////////////////////////////////////////////
// x*y   x*y   x*y   x*y   x*y   x*y   x*y   x*y   x*y   x*y   x*y   x*y   x*y   x*y  

template<class T,int i1, int i2, int i3, int j1, int j2, int j3>
Basic_unit<T,i1+j1,i2+j2,i3+j3>
operator*(Basic_unit<T,i1,i2,i3> x, Basic_unit<T,j1,j2,j3> y)
{
  Basic_unit<T,i1+j1,i2+j2,i3+j3> result;
  result.m_data = (x.m_data * y.m_data); 
  return result;
}

//////////////////////////////////////////////////////////////////////////////////////
// 2*y   2*y   2*y   2*y   2*y   2*y   2*y   2*y   2*y   2*y   2*y   2*y   2*y   2*y  

template<class T,int i1, int i2, int i3>
Basic_unit<T,i1,i2,i3>
operator*(double pure_number, Basic_unit<T,i1,i2,i3> y)
{
  Basic_unit<T,i1,i2,i3> result;
  result.m_data = pure_number * y.m_data;
  return result;
}
//////////////////////////////////////////////////////////////////////////////////////
// x*2   x*2   x*2   x*2   x*2   x*2   x*2   x*2   x*2   x*2   x*2   x*2   x*2   x*2  

template<class T,int i1, int i2, int i3>
Basic_unit<T,i1,i2,i3>
operator*(Basic_unit<T,i1,i2,i3> y, double pure_number)
{
  Basic_unit<T,i1,i2,i3> result;
  result.m_data = pure_number * y.m_data;
  return result;
}
//////////////////////////////////////////////////////////////////////////////////////
// x/y   x/y   x/y   x/y   x/y   x/y   x/y   x/y   x/y   x/y   x/y   x/y   x/y   x/y  

template<class T,int i1, int i2, int i3, int j1, int j2, int j3>
Basic_unit<T,i1-j1,i2-j2,i3-j3>
operator/(Basic_unit<T,i1,i2,i3> x, Basic_unit<T,j1,j2,j3> y)
{
  Basic_unit<T,i1-j1,i2-j2,i3-j3> result;
  result.m_data = (x.m_data / y.m_data); 
  return result;
}
//////////////////////////////////////////////////////////////////////////////////////
// x/2   x/2   x/2   x/2   x/2   x/2   x/2   x/2   x/2   x/2   x/2   x/2   x/2   x/2  

template<class T,int i1, int i2, int i3>
Basic_unit<T,i1,i2,i3>
operator/(Basic_unit<T,i1,i2,i3> x, double y)
{
  Basic_unit<T,i1,i2,i3> result;
  result.m_data = x.m_data / y; 
  return result;
}
//////////////////////////////////////////////////////////////////////////////////////
// 2/y   2/y   2/y   2/y   2/y   2/y   2/y   2/y   2/y   2/y   2/y   2/y   2/y   2/y  

template<class T,int i1, int i2, int i3>
Basic_unit<T,i1,i2,i3>
operator/(double x, Basic_unit<T,i1,i2,i3> y)
{
  Basic_unit<T,i1,i2,i3> result;
  result.m_data = x / y.m_data; 
  return result;
}

#endif


