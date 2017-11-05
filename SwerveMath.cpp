#include <math.h>
#include <array>
#include "SwerveMath.h"
#include <Eigen/Dense>

static const double pi = M_PI;
//TODO: switch std::array<double, 2> to a vector class of some kind


swerveDriveMath::swerveDriveMath(std::array<std::array<double, 2>, WHEELCOUNT> _wheelCoordinates)
{
	wheelCoordinates = _wheelCoordinates;
	parkingAngle = parkingAngles(wheelCoordinates);
	//The below numbers can potentially change, it is relative to the wheel coordinates
	std::array<double, 2> baseRotationCenter = {0, 0};
	baseWheelMultipliersXY = wheelMultipliersXY(wheelCoordinates, baseRotationCenter);

}



//used for varying center of rotation and must be run once for initialization
std::array<std::array<double, 2>, WHEELCOUNT> swerveDriveMath::wheelMultipliersXY(std::array<std::array<double, 2>, WHEELCOUNT> wheelCoordinates, std::array<double, 2> rotationCenter)
{
	std::array<double, WHEELCOUNT> wheelAngles;
	std::array<double, WHEELCOUNT> wheelMultipliers;
	//int size = std::wheelCoordinates::size;
	for (int i = 0; i < WHEELCOUNT; i++) //increment for each wheel
	{
		double x = wheelCoordinates.at(i).at(0) - rotationCenter.at(0);
		double y = wheelCoordinates.at(i).at(1) - rotationCenter.at(1);
		wheelMultipliers[i] = sqrt(x*x + y*y);
		wheelAngles[i] = (atan2(x, y) + .5*pi);
	}
	std::array<std::array<double, 2>, WHEELCOUNT> multipliersXY;
	wheelMultipliers = normalize(wheelMultipliers); //Fix
	for (int i = 0; i < WHEELCOUNT; i++)
	{
		multipliersXY[i][0] = wheelMultipliers[i] * cos(wheelAngles.at(i));
		multipliersXY[i][1] = wheelMultipliers[i] * sin(wheelAngles.at(i));
	}
	return multipliersXY; //change to array
}

std::array<std::array<double, 2>, WHEELCOUNT> swerveDriveMath::wheelSpeedsAngles(std::array<std::array<double, 2>, WHEELCOUNT> wheelMultipliersXY,
	std::array<double, 2> velocityVector, double rotation, double angle) //for non field centric set angle to pi/2
{
	/*if (rotation == 0 && velocityVector.at(0) == 0 && velocityVector.at(1) == 0)
	{
	return
	}
	*/
	
	//parking config isn't handled here (the code commented out above was the outline of how it could be handled here). Only call function if movement exists.
	
	std::array<double, 2> rotatedVelocity = rotate(angle, velocityVector); //Change to vectors
	std::array<double, WHEELCOUNT> speeds;
	std::array<double, WHEELCOUNT> angles;
	for (int i = 0; i < WHEELCOUNT; i++)
	{
		double x = wheelMultipliersXY.at(i).at(0)*rotation + rotatedVelocity.at(0);
		double y = wheelMultipliersXY.at(i).at(1)*rotation + rotatedVelocity.at(1);
		angles[i] = (atan2(x, y));
		speeds[i] = sqrt(x*x + y*y);
	}
	speeds = normalize(speeds);
	std::array<std::array<double, 2>, WHEELCOUNT> speedsAngles;
	for (int i = 0; i < WHEELCOUNT; i++)
	{

		speedsAngles[i][0] = speeds.at(i);
		speedsAngles[i][0] = angles.at(i);
	}

	return speedsAngles;
}
std::array<double, WHEELCOUNT> swerveDriveMath::parkingAngles(std::array<std::array<double, 2>, WHEELCOUNT> wheelCoordinates) //only must be run once to determine the angles of the wheels in parking config
{
	std::array<double, WHEELCOUNT> angles;
	for (int i = 0; i < wheelCoordinates.size(); i++)
	{
		angles[i] = (atan2(wheelCoordinates.at(i).at(0), wheelCoordinates.at(i).at(1)));
	}
	return angles;
}


///*vector of some variety*/ wheelAverage(std::array</*vector of some variety*/, WHEELCOUNT>, double angle)
//{
	//you know what goes here
//}
///*vector of some variety*/ threeWheelAvg(std::array</*vector of some variety*/, WHEELCOUNT>, double angle)
//{
	//use horizontally adjacent wheels somehow?, needs to be generalized
	//Is this needed?
//}

