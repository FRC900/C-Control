#ifndef INC_BREAKER_MODEL
#define INC_BREAKER_MODEL

#include <vector>
#include <math.h>
#include <array>
#define ROOMTEMP 25

using namespace std;
class breakerModel
{
	public:
		
		breakerModel(double _ratedCurrent, double _tempThresh, double _elecResis, double _initialTemp, vector<array<double, 2>> _targetData);
		double bTemp;
		double tempThresh;
		bool iterModel(double current, double dt, double temp = 25);
	private:
		double heatCapacity;
		double elecResis;
		double thermCond;




























};
#endif
