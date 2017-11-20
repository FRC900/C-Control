#include <cmath>
#include <iostream>
#include "nextVelocity.h"
#include <Eigen/Dense>
#include <cmath>
#include <math.h>
#include "nextPositions.h"
#include "900Math.h"

using namespace std;
using namespace Eigen;

//Takes in current position and target position, both in the same units as the other values passed in
//So the units depend on the differential gear ratio
//If m1 and m2 have velocities of (1, -1), difV is 1
//Maximum velocity, acceleration, and jerk are different for the differential and the spin of the wheel. The differential is assumed to have infinite possible jerk (for simplification) 
array<double, 2> nextDifV(double pos, double targetPos, double maxDV, double maxDA, double maxDJ, double &DV, double maxThreshHold, double minThreshHold, double targetV, double maxV,  double maxA, double maxJ, array<double, 2> &mV, double &A)
{
	double difV = (mV[0] - mv[1])/2;
	double V = (mV[0] + mv[1])/2;
	double nextV;
	if(abs(pos - targetPos) > maxThreshHold)
	{
		//note that next velocity is being used here to calculate a position
		nextPosition(pos, targetPos, DV, DA, maxDV, maxDA, maxDJ, cr);
		nextV = 0;
	}
	else
	{
	if(abs(pos - targetPos) < minThreshHold)
	{	
		 nextV = nextVelocity(V, targetV, A, maxA, maxJ, cr);
	}
	else
	{
		double divider = (pos - targetPos - minThreshHold)/(maxThreshHold - minThreshHold)
		double newMaxDJ = divider*maxDJ;
		double newMaxJ = (1-divider)*maxJ;
		nextPosition(pos, targetPos, DV, DA, maxDV, maxDA, newMaxDJ, cr);
		nextV = nextVelocity(V, targetV, A, maxA, newMaxJ, cr);
	}
	}

	correcter = abs(nextV/maxV)+abs(DV/maxDV)	
	if(correcter>1)
	{
		if(abs(DV)<maxDV)
		{
			nextV = (1 - abs(DV/maxDV))*sign(nextV); //TODO, fix this, should change acceleration etc.
								 //also forces more acceleration than is possible on the motor with lower speed.

		} 		
		else
		{
			nextV = 0;
			DV = maxDV*sign(DV);
		}
	}
	mV[0] = nextV + DV;
	mV[1] = nextV - DV;

}
	
	




















































