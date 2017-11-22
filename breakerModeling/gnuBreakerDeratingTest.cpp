#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include "../GnuPlot/gnuplot_i.hpp"
#include <algorithm>
#include <iterator>
#include "breakerModel.h"
using namespace std;

void wait_for_key();

int main( int argc, char* argv[])
{
    
    ofstream fs;
    string filename = "Breaker.csv";
    fs.open(filename);
    
	Gnuplot g1("Current");
	g1.set_grid();
	//g1.set_xlogscale(8);
    // write the file headers
    fs << "Time to Pop" << "," << "Current"  << endl;
    
    double currentSpacing = 1;
	double maxCurrent = 50;
	double minCurrent = 0;
	double tempThresh = 149; 
	double elecResis = .0005;
	double thermCond = .08;
	double specificHeat = .2716001267;
	double initialTemp = 25;
	cout<<"running"<<endl;
	vector<double> times, currents; 	
	// write data to the file	
	for (float i = minCurrent; i <=  maxCurrent; i+=currentSpacing)
    	{
		//if(i==400){
		
        	breakerModel test(120, tempThresh, elecResis, i, {{360, 7.5}, {240, 20}, {480, 3.5}});
		double time = 0;
		bool fin = false;
		bool trueFin = false;
		for(int r = 160; r > 79; r-=1)
		{
		
		test.bTemp = i;
		fin = false;
		for(int t = 0; t<10000; t++)
		{
			//cout<<"time:"<<t*.1<<endl;
			if(test.iterModel(r, .1, i))
			{
				fin = true;
				time = t*.1;
				break;		
			}
		}
		
		if(fin){;}
		else
		{
			time = r;
			trueFin = true;
			break;
		}
		}
		if(trueFin)
		{
        		fs << time << "," << i << endl;
			times.push_back(i);
			currents.push_back(time);
		}//}
	}	
	g1.set_style("points").plot_xy(times, currents ,"Current"); 
	g1.reset_plot();

	g1.showonscreen();
    wait_for_key();
	
	fs.close();
	return 0;   
}
void wait_for_key()
{
	cout << endl << "Type Number to Continue" << endl;
    cin.clear();
    int f;
	cin>>f;
	cin.ignore(cin.rdbuf()->in_avail());
    cin.get();
	return;
}

