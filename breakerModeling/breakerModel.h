#ifndef INC_BREAKER_MODEL
#define INC_BREAKER_MODEL

#include <vector>
#include <math.h>

class breakerModel
{
	public:
		double propPopped;
		double iterModel(double current, double dt, double temp = 25);
	private:
		double ratedAmp;
		double n1;
		double n2;
		double n3;
		bool useTemp;
		double t1;
		double t2;
		double t3;
		double tempF(double temp);
		double popTime(currentF); //Takes current as a multiple of rated current1




























}
#endif
