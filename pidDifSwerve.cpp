#include <cmath>
#include <iostream>
#include <Eigen/Dense>
#include <cmath>
#include <math.h>
#include "900Math.h"

using namespace std;
using namespace Eigen;

//Takes in current position and target position
//make sure directions are right
array<double, 2> pidDifV(double pos, double targetPos, double targetV/*, some pid struct or whatever*/)
{
	/* some pid stuff here that outputs difV, it should be coerced between 1 and -1*/
	
	array<double, 2> vels;
	vels[0] = targetV + difV;
	vels[1] = targetV - difV;
	over1 = abs(vels[0]) - 1;
	over2 = abs(vels[1]) - 1;
	//The code below puts prority on steering
	if(over1 > 0)
	{
		vels[0] = sign(vels[0])*1;
		vels[1] -= over1;
	}
	else
	{
	if(over2 > 0)
	{
		vels[1] = sign(vels[1])*1;
		vels[0] +=over2;
	}
	return vels;
}
	
	




















































