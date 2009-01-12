// $Id: market.test.cc 242 2000-03-10 16:12:15Z foster $-*- c++ -*-


#include <iostream.h>
#include <assert.h>
#include <fstream.h>

#include "market.h"

int
main()
{
  cout << "\n\n\n\t\t\t MARKET  MARKET  MARKET\n\n\n"<<endl;
  {
    Market m;  // testing construction
    Shares thick;
    thick = 10000. * Shares();
    
    cout << "constructed!" << endl;
    m.add(Order(100*Price(), -40*Shares(),1000*Shares()));
    m.add(Order( 50*Price(), -50*Shares(),1000*Shares()));
    m.add(Order( 49*Price(),  -1*Shares(),1000*Shares()));
    m.add(Order( 51*Price(),  -1*Shares(),1000*Shares()));
    m.add(Order(50*Price(),    1*Shares(),1000*Shares()));
    m.add(Order(51*Price(),    1*Shares(),1000*Shares()));
    m.add(Order(200*Price(),  50*Shares(),1000*Shares()));
    m.add(Order(30*Price(),   49*Shares(),1000*Shares()));

    cout << m << endl;
    cout << " Cross at: " << m.cross(thick).first << endl;
    cout << "volumn of: " << m.cross(thick).second << endl;
    
    vector<Shares> x;
    x.push_back(0*Shares());
    x.push_back(500*Shares());
    x.push_back(1100*Shares());
    x.push_back(2000*Shares());
    
    cout << "Some price calculations:\n\t";
    copy(x.begin(),x.end(),ostream_iterator<Shares>(cout,"\t"));
    cout << "\n\t";
    vector<Price> y = m.price(x);
    copy(y.begin(),y.end(),ostream_iterator<Price>(cout,"\t"));
    cout << "\n\t";
    y = m.price(x,10*Shares());
    copy(y.begin(),y.end(),ostream_iterator<Price>(cout,"\t"));
    cout << "\n\t";
    y = m.price(x,-1000*Shares());
    copy(y.begin(),y.end(),ostream_iterator<Price>(cout,"\t"));
    cout << "\n\t";
     y = m.price(x);
    copy(y.begin(),y.end(),ostream_iterator<Price>(cout,"\t"));
    cout << "\n\t\n";
    vector<Shares> offset;
    offset.push_back(0*Shares());
    offset.push_back(+500*Shares());
    m.add(Order(61*Price(), 100000*Shares(),0 * Shares()));  // market maker buyer
    m.add(Order(49*Price(),-100000*Shares(),0 * Shares()));  // market maker selle
    m.add(Order(50*Price(),      1*Shares(),0 * Shares()));  // market buy
    m.add(Order(60*Price(),     -1*Shares(),0 * Shares()));  // market sell
    //    ofstream o("gp");
    m.gnuplot_price_header(offset,cout);
    m.gnuplot_price(x,offset,cout);
    m.gnuplot_firing_header(cout);
    m.gnuplot_firing(x,cout);
    m.fire_market(thick, m.cross(thick).first);
    cout << "After firing the market:" << endl;
    cout << m << endl;

    cout << "Maximal firing at a volumn of: " << m.maximal_trading(10000 * Shares()).second << endl;
    {
      cout << "********** new market  --  protected firing *************" << endl;
      Market n;
      n.buffer(50*Price(),60*Price());
      n.add(Order(50*Price() ,     -1*Shares(), 0 * Shares()));  // market sell  
      n.add(Order(60*Price() ,      1*Shares(), 0 * Shares()));  // market buy

      //    ofstream o("gp");
      cout << n<< endl;
      n.gnuplot_price_header(offset,cout);
      n.gnuplot_price(x,offset,cout);
      n.gnuplot_firing_header(cout);
      n.gnuplot_firing(x,cout);
      n.maximal_trading(2000* Shares());
      n.gnuplot_firing_header(cout);
      n.gnuplot_firing(x,cout);
    }
  }
  

  cout << "\n\nDONE." << endl;  
};
