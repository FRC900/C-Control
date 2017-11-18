#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include "GnuPlot/gnuplot_i.hpp"
#include "nextVelocity.h"
#include <algorithm>
#include <iterator>
using namespace std;

void wait_for_key();

int main( int argc, char* argv[])
{
    
    ofstream fs;
    std::string filename = "MotionProfile.csv";
    fs.open(filename);
    
	Gnuplot g1("velocities");
	g1.set_grid();

    // write the file headers
    fs << "Time" << "," << "Velocity" << "," << "Acceleration" << "," << "Jerk" << std::endl;
    
    double v = 2;
    double vt = 4;
    double a = 5;
    double am = 5;
    double jm = 5;
    double cr = .01;
    double tempA;
    int tT;
	double j;
	cout<<"am"<<endl;
	cin>>am;	
	cout<<"jm"<<endl;
	cin>>jm;	
	cout<<"v"<<endl;
	cin>>v;	
	cout<<"vt"<<endl;
	cin>>vt;	
	cout<<"a"<<endl;
	cin>>a;
	cout<<"run time"<< endl;
	cin>>tT;
	cout<<"running"<<endl;
	vector<double> times, velocities, accelerations, jerks, vj, aj; 	
	times.reserve(tT);	
	velocities.reserve(tT);
	accelerations.reserve(tT);
	// write data to the file	
	bool save = false;
	for (int i = 0; i <  tT; i++)
    	{
        	tempA = a;
        	v = nextVelocity(v, vt, a, am, jm, cr);
        	// write the data to the output file
		j=(a - tempA)/cr;
        	fs << i*cr << "," << v << "," << a << "," <<j<< std::endl;
        	velocities.push_back(v);
		times.push_back(i*cr);
		accelerations.push_back(a);
		double aJ = fabs(j);
		if(save or fabs(aJ - jm)>.002)
		{
			save = true;
			jerks.push_back(j);
			vj.push_back(v);
			aj.push_back(a);
		}
    	
	}
	
	g1.set_style("points").plot_xy(times, velocities,"velocity"); 
	g1.reset_plot();

	g1.showonscreen();
    wait_for_key();
	g1.set_style("points").plot_xy(times, accelerations,"acceleration"); 
	g1.showonscreen(); 
	 
    wait_for_key();
  	cout<<"jerks"<<endl;
	copy(jerks.begin(), jerks.end(),  ostream_iterator<double>( cout, " "));
  	cout<<"velocities"<<endl;
  	copy(vj.begin(), vj.end(),  ostream_iterator<double>( cout, " "));
  	cout<<"accelerations"<<endl;
  	copy(aj.begin(), aj.end(),  ostream_iterator<double>( cout, " "));
	// close the output file
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

