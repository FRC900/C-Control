#include <iostream>
#include <fstream>
#include <string>
#include "nextVelocity.h"

using namespace std;



int main( int argc, char** argv)
{
    
    ofstream fs;
    std::string filename = "MotionProfile.csv";
    fs.open(filename);
    
    // write the file headers
    fs << "Time" << "," << "Velocity" << "," << "Acceleration" << "," << "Jerk" << std::endl;
    
    double v = 2;
    double vt = 4;
    double a = 5;
    double am = 5;
    double jm = 5;
    double cr = .01;
    double tempA;
    // write data to the file
    for (int i = 0; i <  400; i++)
    {
        tempA = a;
        v = nextVelocity(v, vt, a, am, jm, cr);
        // write the data to the output file
        fs << i*cr << "," << v << "," << a << "," <<(a - tempA)/cr<< std::endl;
        
    }
    
    // close the output file
    fs.close();
    return 0;   
}
