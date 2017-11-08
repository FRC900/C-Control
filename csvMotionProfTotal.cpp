#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "MotionProfiler.h"

using namespace std;



int main( int argc, char** argv)
{
    
    ofstream fs;
    std::string filename = "MotionProfile.csv";
    fs.open(filename);
    
    // write the file headers
    fs << "Time" << "," << "Position" << "," << "Velocity" << "," << "Acceleration" << std::endl;
    
    double vMax = 3;
    double aMax = 4;
    double jMax = 5;
    double controlRate = 10;
    double tempV;
    motionProfile testProf(vMax, aMax, jMax, controlRate);
    double dist = -10;
    double v = 0;
    double p = 0;
    vector<double> velocities;
    vector<double> positions;
    bool worked = testProf.genMotionProfile(dist, velocities, positions);
    double cr = controlRate/1000; 
    
    string success;
    if(worked){success = "True";} else{success = "False";}
    cout << success  << endl;
    cout << velocities.size() << endl;
    // write data to the file
    for (int i = 0; i <  velocities.size() ; i++)
    {
        tempV = v;
        v = velocities.at(i);
	p = positions.at(i);
        // write the data to the output file
        fs << i*cr << "," << p << "," << v << "," <<v-tempV<< std::endl;
        
    }
    
    // close the output file
    fs.close();
    return 0;   
}
