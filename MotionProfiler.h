#ifndef INC_MOTION_PROFILER
#define INC_MOTION_PROFILER
#include <array> 
#include <math.h> 
#include <stdlib.h> 
#include <vector>

class motionProfile{
        public:
                double maxV;   //Maybe make these private and accessable through helper function
                double maxA;
                double maxJ;
                double controlRateMS;
                motionProfile(double _maxV, double _maxA, double _maxJ, double _controlRateMS = 10);
                bool genMotionProfile(double travelDist, std::vector<double> &velocities, std::vector<double> &positions);
};
#endif
