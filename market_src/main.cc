// $Id: main.cc 245 2000-03-10 22:57:54Z foster $-*- c++ -*-


#include <iostream.h>
#include <assert.h>
#include <strstream.h>
#include <fstream.h>
#include <vector.h>
#include <math.h>
#include "simulation.h"
#include "market.h"

int
stoi(string s)
{
  // remove all non-numbers
  for(int i=0;i < s.length();++i)
        if(s[i] < '0' || s[i] > '9')
	  s[i] = ' ';

  int result = 0;
  strstream sm;
  sm << s;
  sm >> result;
  return result;
}



int
main()
{
  vector<Shares> offset;
  offset.push_back(     0*Shares());
  offset.push_back(  1000*Shares());

  vector<Shares> x;
  x.push_back(0*Shares());
  for(double i = 100; i < 60000; i = i*1.02)
    x.push_back(i*Shares());
	
  Order_generator gen;
  strstream out;
  ofstream gnu_price("gp");
  ofstream gnu_volume("gv");
  Simulation sim(.00001,gen,out);
  int interval = 10;
  bool done = false;
  cout << "\n\n\t\tMarket simulator\n\n" << endl;

  string last_command = "s";
  
  while(!done)
    {
      cout << "command (? for help) [" << last_command << "] : ";
      string response;
      getline(cin,response);
      if(response == "")
	response = last_command;
      last_command = response;
      int sim_steps = 0;
      if(response.at(0) == '?')
	{
	  cout << "\n\n" << endl;
	  cout << "\t ?     = This message." << endl;
	  cout << "\t s     = take one step, and check for firing the market." << endl;
	  cout << "\t 4     = simulate 2^4 rounds." << endl;
	  cout << "\t i 100 = check for market firing every 100 trades" << endl;
	  cout << "\t q     = quit" << endl;
	  cout << "\t p     = print market statistics" << endl;
	  cout << "\t f     = simulate until the market fires" << endl;
	  cout << "\t b     = simulate until just before the market fires" << endl;
	  cout << "\n\n" << endl;
	  last_command = "s";	  
	}
      if((response == "q") || (response == "quit"))
	done = true;

      if(('0' <= response.at(0)) && (response.at(0) <= '9'))
	sim_steps = (int)pow(2,stoi(response));
      
      if(response == "s")
	sim_steps = 1;
      
      if(response.at(0) == 'i')
	interval = stoi(response);
      
      if(interval < 1)
	interval = 1;

      if((response == "p") || (response == "print"))
	cout << "\n\n" << sim << "\n\n" << endl;

      if((response == "f") || (response == "fire"))
	 {
	   response = "f";
	   pair<Price,Shares> m = sim.do_until_fire(interval);	   
	   cout << "Market fired at " << m.second
		<< "with a price of " << m.first << endl;
	 }
	 
      if((response == "b") || (response == "before"))
	 {
	   response = "b";	   
	   sim.do_till_before_fire();	   
	 }
	 

      if(sim_steps > 0)
	{
	  cout << "simulating " << sim_steps
	       << " rounds, checking market firing every " << interval << " rounds." << endl;
      
	  if(sim_steps >= interval)
	    sim.do_sloppy_rounds((sim_steps/interval)*interval,interval);
	  if((sim_steps % interval) > 0)
	    sim.do_sloppy_rounds(sim_steps % interval,sim_steps % interval);
	}

      if((sim_steps > 0) || (response == "f") || (response == "b"))
	{
	  sim.market().gnuplot_price_header(offset,gnu_price,"[0:60000] [45:65] ");
	  sim.market().gnuplot_firing_header(gnu_volume,"[0:60000] [0:1.5] ");
	  sim.market().gnuplot_price(x,offset,gnu_price);
	  sim.market().gnuplot_firing(x,gnu_volume);
	}
    }
};
