// $Id: simulation.test.cc 242 2000-03-10 16:12:15Z foster $-*- c++ -*-


#include <iostream.h>
#include <assert.h>
#include <strstream.h>
#include <fstream.h>
#include <vector.h>
#include "simulation.h"
#include "market.h"

int
main()
{
  cout << "\n\n\n\t\t\t SIMULATION  SIMULATION  SIMULATION\n\n\n"<<endl;
  {
    cout << "Doing a regression testing run." << endl;
    vector<Shares> offset;
    offset.push_back(  2000*Shares());
    offset.push_back(  1000*Shares());
    offset.push_back(   400*Shares());
    offset.push_back(   200*Shares());
    offset.push_back(     0*Shares());

    vector<Shares> x;
    x.push_back(0*Shares());
    for(double i = 100; i < 1000; i = i*2)
      x.push_back(i*Shares());
	
    strstream out;
    Order_generator gen;
    Simulation sim(.1,gen,out);
    sim.do_sloppy_rounds(20,10);
    cout << sim << endl;
    cout << "OUT OUT OUT OUT OUT OUT OUT OUT OUT OUT OUT OUT OUT OUT OUT OUT OUT OUT" << endl;
    cout << string(out.str(),out.pcount());
    cout << "PRICE PRICE PRICE PRICE PRICE PRICE PRICE PRICE PRICE PRICE PRICE PRICE" << endl;
    sim.market().gnuplot_price_header(offset,cout,"[0:60000] [45:65] ");
    sim.market().gnuplot_price(x,offset,cout);
    cout << "VOLUME VOLUME VOLUME VOLUME VOLUME VOLUME VOLUME VOLUME VOLUME VOLUME" << endl;
    sim.market().gnuplot_firing_header(cout,"[0:60000] [0:1.5] ");
    sim.market().gnuplot_firing(x,cout);
  };
  cout << "\n\nDONE." << endl;  
};
