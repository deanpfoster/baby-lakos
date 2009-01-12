// $Id: foo.cc 2013 2000-09-01 21:13:45Z foster $-*- c++ -*-


#include "foo.h"

// put other includes here
#include "assert.h"
#include <iostream.h>

////////////////////////////////////////////////////////////////////////////////////////////
//                          U S I N G   D I R E C T I V E S                            using

// using two::foo;       // fine to use two
// using namespace two;  // generally avoid using the whole namespace

////////////////////////////////////////////////////////////////////////////////////////////
//                              C O N S T R U C T O R S                         constructors

two::Foo::~Foo()
{
};
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
two::Foo::Foo()
{
};
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
two::Foo::Foo(const Foo & rhs)
  :
  Bar(rhs)
{
};
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
////////////////////////////////////////////////////////////////////////////////////////////
//                             M A N I P U L A T O R S                          manipulators
 

two::Foo&
two::Foo::operator=(const Foo & )
{
  // add code here
  return *this; 
};
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


////////////////////////////////////////////////////////////////////////////////////////////
//                               A C C E S S O R S                                 accessors
void
two::Foo::print_on(ostream & ostrm) const
{
  ostrm << "This is a two::Foo.";
};
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

////////////////////////////////////////////////////////////////////////////////////////////
//                           P R O T E C T E D                                     protected

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

////////////////////////////////////////////////////////////////////////////////////////////
//                           P R I V A T E                                           private


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
////////////////////////////////////////////////////////////////////////////////////////////
//                     F R E E   F U N C T I O N S                            free functions

ostream & operator<<(ostream & ostrm, const two::Foo & object)
{
  object.print_on(ostrm);
  return ostrm;
};

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
