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
    
    double currentSpacing = 10;
	double maxCurrent = 1000;
	double minCurrent = 120;
	double tempThresh = 149; 
	double elecResis = .0005;
	double initialTemp = 25;
	double thermCond = .08;
	double specificHeat = .2716001267;
	cout<<"running"<<endl;
	vector<double> times, currents; 	
	// write data to the file	
        breakerModel test(120, tempThresh, elecResis, initialTemp, {{360, 4.8}, {240, 10}, {480, 2.4}});
	double time = 0;
	bool fin = false;
	test.bTemp = initialTemp;
	double i = 400;
	double limited;
	for(int t = 0; t<100; t++)
	{
		if(test.bTemp>100)
		{
			limited = 600*(tempThresh - 5 - test.bTemp)/(tempThresh - 5 - 120);
			cout<<"temp"<<test.bTemp<<"time"<<endl;
			if(limited>i){limited = i;}
			
        		fs << time << "," << i << endl;
			times.push_back(t*.1);
			
			currents.push_back(test.bTemp);
		}
		else
		{
			limited = i;
		}	
		//cout<<"time:"<<t*.1<<endl;
		if(test.iterModel(limited, .1, initialTemp))
		{
			fin = true;
			time = t*.1;
			cout<<"popped"<<endl;
			break;		
		}
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

