// $Id: unit.h 219 2000-03-04 03:43:30Z foster $ -*- c++ -*-

#ifndef INCLUDED_UNIT
#define INCLUDED_UNIT

#ifndef INCLUDED_BASIC_UNIT
#include "basic_unit.h"
#endif

#ifndef INCLUDED_SYSTEM
#include "system.h"
#endif

class ostream;

// NOTE: m_data is in local units.  To convert it to the base of
// the same dimension use:
// 
//          m_data*s_conversion_factor;
//
// Obviously, divide by s_conversion_factor to converte a basic unit
// to the local version.
//
// In toher words, if the Basic_unit is feet, and the Unit under
// consideration is miles, then s_conversion_factor = 5280.
// 

template<class T_system,class T_unit,int i1, int i2 = 0, int i3 = 0>
class Unit
{
  typedef Unit      <T_system,T_unit,i1,i2,i3> unit_name;
  typedef Basic_unit<T_system,       i1,i2,i3> basic_unit_name;
  typedef System                               naming_source;
  
public:
  // CONSTRUCTORS
  ~Unit(){};
  Unit():
    m_data(1)
    {};
  Unit(double data):
    m_data(data)
    {
    };

  Unit(const T_unit & other):
    m_data(other.m_data)
    {
    }

  operator basic_unit_name() const
    {
      basic_unit_name result;
      result.m_data = s_conversion_factor.m_data * m_data;
      return result;
    }
  
  operator T_unit() const
    {
      T_unit result;
      result.m_data = m_data;
      return result;
    }
  
  Unit(const basic_unit_name & other):
    m_data(other.m_data/s_conversion_factor.m_data)
    {
    }
  
  // MANIPULATORS
  void assign(const unit_name & other)
    {
      m_data = other.m_data;
    }

  void assign(const basic_unit_name & other)
    {
      m_data = other.m_data/s_conversion_factor.m_data;
    }

  // ACCESSORS

  bool operator==(const unit_name & other) const
    {
      return m_data == other.m_data;
    }
  
  bool operator!=(const unit_name & other) const
    {
      return m_data != other.m_data;
    }
  
  bool operator<(const unit_name & other) const
    {
      return m_data < other.m_data;
    }
  bool operator>(const unit_name & other) const
    {
      return m_data > other.m_data;
    }
  
  bool operator<=(const unit_name & other) const
    {
      return m_data <= other.m_data;
    }
  
  bool operator>=(const unit_name & other) const
    {
      return m_data >= other.m_data;
    }
  

  double m_data; // shouldn't be public--but too many friends at the moment
  static Basic_unit<T_system,0,0,0> s_conversion_factor;
  
protected:

private:
  Unit& operator=(const Unit<T_system,T_unit,i1,i2,i3> &); // Don't delete this.
};


template<class T, class T_unit, int i1, int i2, int i3>
void
trait_print_unit(ostream& ostrm, const System&, Unit<T,T_unit,i1,i2,i3> obj)
{
  T printer;
  vector<int> dim;
  dim.push_back(i1);
  dim.push_back(i2);
  dim.push_back(i3);
  printer.print_unit(ostrm,dim,T_unit::s_conversion_factor.m_data * obj.m_data);
}

template<class T, class T_unit, int i1, int i2, int i3>
void
trait_print_unit(ostream& ostrm, const string&, Unit<T,T_unit,i1,i2,i3> obj)
{
  ostrm << obj.m_data << " " << T_unit::s_name;
}

template<class T, class T_unit, int i1, int i2, int i3>
ostream&
operator<<(ostream& ostrm, Unit<T,T_unit,i1,i2,i3> obj)
{
  typename T_unit::naming_source trait;
  
  trait_print_unit(ostrm, trait, obj);
  return ostrm;
}
//////////////////////////////////////////////////////////////////////////////////////
// x+y   x+y   x+y   x+y   x+y   x+y   x+y   x+y   x+y   x+y   x+y   x+y   x+y   x+y  

template<class T_sys,class T_unit,int i1, int i2, int i3>
Unit<T_sys,T_unit,i1,i2,i3>
operator+(Unit<T_sys,T_unit,i1,i2,i3> x, Unit<T_sys,T_unit,i1,i2,i3> y)
{
  return Unit<T_sys,T_unit,i1,i2,i3>(x.m_data + y.m_data);
}

//////////////////////////////////////////////////////////////////////////////////////
// x+y   x+y   x+y   x+y   x+y   x+y   x+y   x+y   x+y   x+y   x+y   x+y   x+y   x+y  

template<class T_sys,class T_unit,int i1, int i2, int i3>
Basic_unit<T_sys,i1,i2,i3>
operator+(Unit<T_sys,T_unit,i1,i2,i3> x, Basic_unit<T_sys,i1,i2,i3> y)
{
  double x_value = Unit<T_sys,T_unit,i1,i2,i3>::s_conversion_factor.m_data * x.m_data;
  double y_value =y.m_data;
  Basic_unit<T_sys,i1,i2,i3> result;
  result.m_data = x_value + y_value;
  return result;
}
//////////////////////////////////////////////////////////////////////////////////////
// x+y   x+y   x+y   x+y   x+y   x+y   x+y   x+y   x+y   x+y   x+y   x+y   x+y   x+y  

template<class T_sys,class T_unit,int i1, int i2, int i3>
Basic_unit<T_sys,i1,i2,i3>
operator+(Basic_unit<T_sys,i1,i2,i3> y,Unit<T_sys,T_unit,i1,i2,i3> x)
{
  double x_value = Unit<T_sys,T_unit,i1,i2,i3>::s_conversion_factor.m_data * x.m_data;
  double y_value =y.m_data;
  Basic_unit<T_sys,i1,i2,i3> result;
  result.m_data = x_value + y_value;
  return result;
}
//////////////////////////////////////////////////////////////////////////////////////
// x-y   x-y   x-y   x-y   x-y   x-y   x-y   x-y   x-y   x-y   x-y   x-y   x-y   x-y  

template<class T_sys,class T_unit,int i1, int i2, int i3>
Unit<T_sys,T_unit,i1,i2,i3>
operator-(Unit<T_sys,T_unit,i1,i2,i3> x, Unit<T_sys,T_unit,i1,i2,i3> y)
{
  return Unit<T_sys,T_unit,i1,i2,i3>(x.m_data - y.m_data);
}
//////////////////////////////////////////////////////////////////////////////////////
// x-y   x-y   x-y   x-y   x-y   x-y   x-y   x-y   x-y   x-y   x-y   x-y   x-y   x-y  

template<class T_sys,class T_unit,int i1, int i2, int i3>
Basic_unit<T_sys,i1,i2,i3>
operator-(Unit<T_sys,T_unit,i1,i2,i3> x, Basic_unit<T_sys,i1,i2,i3> y)
{
  double x_value = Unit<T_sys,T_unit,i1,i2,i3>::s_conversion_factor.m_data * x.m_data;
  double y_value =y.m_data;
  Basic_unit<T_sys,i1,i2,i3> result;
  result.m_data = x_value - y_value;
  return result;
}
//////////////////////////////////////////////////////////////////////////////////////
// x-y   x-y   x-y   x-y   x-y   x-y   x-y   x-y   x-y   x-y   x-y   x-y   x-y   x-y  

template<class T_sys,class T_unit,int i1, int i2, int i3>
Basic_unit<T_sys,i1,i2,i3>
operator-(Basic_unit<T_sys,i1,i2,i3> y,Unit<T_sys,T_unit,i1,i2,i3> x)
{
  double x_value = Unit<T_sys,T_unit,i1,i2,i3>::s_conversion_factor.m_data * x.m_data;
  double y_value =y.m_data;
  Basic_unit<T_sys,i1,i2,i3> result;
  result.m_data = y_value - x_value;
  return result;
}
//////////////////////////////////////////////////////////////////////////////////////
// x*y   x*y   x*y   x*y   x*y   x*y   x*y   x*y   x*y   x*y   x*y   x*y   x*y   x*y  

template<class T,class T_unit_x,class T_unit_y,int i1, int i2, int i3, int j1, int j2, int j3>
Basic_unit<T,i1+j1,i2+j2,i3+j3>
operator*(Unit<T,T_unit_x,i1,i2,i3> x, Unit<T,T_unit_y,j1,j2,j3> y)
{
  double x_value = Unit<T,T_unit_x,i1,i2,i3>::s_conversion_factor.m_data * x.m_data;
  double y_value = Unit<T,T_unit_y,j1,j2,j3>::s_conversion_factor.m_data * y.m_data;
  Basic_unit<T,i1+j1,i2+j2,i3+j3> result;
  result.m_data = x_value * y_value;
  return result;
}
//////////////////////////////////////////////////////////////////////////////////////
// x*y   x*y   x*y   x*y   x*y   x*y   x*y   x*y   x*y   x*y   x*y   x*y   x*y   x*y  

template<class T,class T_unit_x,int i1, int i2, int i3, int j1, int j2, int j3>
Basic_unit<T,i1+j1,i2+j2,i3+j3>
operator*(Unit<T,T_unit_x,i1,i2,i3> x, Basic_unit<T,j1,j2,j3> y)
{
  double x_value = Unit<T,T_unit_x,i1,i2,i3>::s_conversion_factor.m_data * x.m_data;
  double y_value = y.m_data;
  Basic_unit<T,i1+j1,i2+j2,i3+j3> result;
  result.m_data = x_value * y_value;
  return result;
}

//////////////////////////////////////////////////////////////////////////////////////
// x*y   x*y   x*y   x*y   x*y   x*y   x*y   x*y   x*y   x*y   x*y   x*y   x*y   x*y  

template<class T,class T_unit_x,int i1, int i2, int i3, int j1, int j2, int j3>
Basic_unit<T,i1+j1,i2+j2,i3+j3>
operator*(Basic_unit<T,j1,j2,j3> y, Unit<T,T_unit_x,i1,i2,i3> x)
{
  double x_value = Unit<T,T_unit_x,i1,i2,i3>::s_conversion_factor.m_data * x.m_data;
  double y_value = y.m_data;
  Basic_unit<T,i1+j1,i2+j2,i3+j3> result;
  result.m_data = x_value * y_value;
  return result;
}
//////////////////////////////////////////////////////////////////////////////////////
// 2*y   2*y   2*y   2*y   2*y   2*y   2*y   2*y   2*y   2*y   2*y   2*y   2*y   2*y  

template<class T,class T_unit_x,int i1, int i2, int i3>
Unit<T,T_unit_x,i1,i2,i3>
operator*(double x, Unit<T,T_unit_x,i1,i2,i3> y)
{
  // Note: this is all done in local units, not Basic_unit's
  double x_value = x;
  double y_value = y.m_data;
  Unit<T,T_unit_x,i1,i2,i3> result;
  result.m_data = x_value * y_value;
  return result;  
}
//////////////////////////////////////////////////////////////////////////////////////
// x*2   x*2   x*2   x*2   x*2   x*2   x*2   x*2   x*2   x*2   x*2   x*2   x*2   x*2  

template<class T,class T_unit_x,int i1, int i2, int i3>
Unit<T,T_unit_x,i1,i2,i3>
operator*(Unit<T,T_unit_x,i1,i2,i3> y, double x)
{
  double x_value = x;
  double y_value = y.m_data;
  Unit<T,T_unit_x,i1,i2,i3> result;
  result.m_data = x_value * y_value;
  return result;
}
//////////////////////////////////////////////////////////////////////////////////////
// x/y   x/y   x/y   x/y   x/y   x/y   x/y   x/y   x/y   x/y   x/y   x/y   x/y   x/y  

template<class T,class T_unit_x,class T_unit_y,int i1, int i2, int i3, int j1, int j2, int j3>
Basic_unit<T,i1-j1,i2-j2,i3-j3>
operator/(Unit<T,T_unit_x,i1,i2,i3> x, Unit<T,T_unit_y,j1,j2,j3> y)
{
  double x_value = Unit<T,T_unit_x,i1,i2,i3>::s_conversion_factor.m_data * x.m_data;
  double y_value = Unit<T,T_unit_y,j1,j2,j3>::s_conversion_factor.m_data * y.m_data;
  Basic_unit<T,i1-j1,i2-j2,i3-j3> result;
  result.m_data = x_value / y_value;
  return result;
}

//////////////////////////////////////////////////////////////////////////////////////
// x/y   x/y   x/y   x/y   x/y   x/y   x/y   x/y   x/y   x/y   x/y   x/y   x/y   x/y  

template<class T,class T_unit_x, int i1, int i2, int i3, int j1, int j2, int j3>
Basic_unit<T,i1-j1,i2-j2,i3-j3>
operator/(Unit<T,T_unit_x,i1,i2,i3> x, Basic_unit<T,j1,j2,j3> y)
{
  double x_value = Unit<T,T_unit_x,i1,i2,i3>::s_conversion_factor.m_data * x.m_data;
  double y_value = y.m_data;
  Basic_unit<T,i1-j1,i2-j2,i3-j3> result;
  result.m_data = x_value / y_value;
  return result;
}

//////////////////////////////////////////////////////////////////////////////////////
// x/y   x/y   x/y   x/y   x/y   x/y   x/y   x/y   x/y   x/y   x/y   x/y   x/y   x/y  

template<class T,class T_unit_y, int i1, int i2, int i3, int j1, int j2, int j3>
Basic_unit<T,i1-j1,i2-j2,i3-j3>
operator/(Basic_unit<T,i1,i2,i3> x, Unit<T,T_unit_y,j1,j2,j3> y)
{
  double x_value = x.m_data;
  double y_value = Unit<T,T_unit_y,i1,i2,i3>::s_conversion_factor.m_data * y.m_data;
  Basic_unit<T,i1-j1,i2-j2,i3-j3> result;
  result.m_data = x_value / y_value;
  return result;
}
//////////////////////////////////////////////////////////////////////////////////////
// x/2   x/2   x/2   x/2   x/2   x/2   x/2   x/2   x/2   x/2   x/2   x/2   x/2   x/2  

template<class T,class T_unit_x, int i1, int i2, int i3>
Unit<T,T_unit_x,i1,i2,i3>
operator/(Unit<T,T_unit_x,i1,i2,i3> x, double y)
{
  double x_value = x.m_data;
  Unit<T,T_unit_x,i1,i2,i3> result;
  result.m_data = x_value / y;
  return result;
}
// 2/y   2/y   2/y   2/y   2/y   2/y   2/y   2/y   2/y   2/y   2/y   2/y   2/y   2/y  

template<class T,class T_unit_y, int j1, int j2, int j3>
Basic_unit<T,-j1,-j2,-j3>
operator/(double x, Unit<T,T_unit_y,j1,j2,j3> y)
{
  double y_value = Unit<T,T_unit_y,j1,j2,j3>::s_conversion_factor.m_data * y.m_data;
  Basic_unit<T,-j1,-j2,-j3> result;
  result.m_data = x / y_value;
  return result;
}
#endif
