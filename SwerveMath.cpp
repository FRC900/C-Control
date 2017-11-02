#include "stdafx.h"
#include "SwerveMath.h"
static const double pi = 3.1415926535897;

	swerveDriveMath::swerveDriveMath(std::array<std::array<double, 2>, wheelCount> _wheelCoordinates)
	{
		wheelCoordinates = _wheelCoordinates;
	}

	//used for varying center of rotation and must be run once for initialization
	std::array<std::array<double, 2>, wheelCount> swerveDriveMath::wheelMultipliersXY(std::array<std::array<double, 2>, wheelCount> wheelCoordinates, std::array<double, 2> rotationCenter)
	{
		std::array<double, wheelCount> wheelAngles;
		std::array<double, wheelCount> wheelMultipliers;
		//int size = std::wheelCoordinates::size;
		for (int i = 0; i < wheelCount; i++) //increment for each wheel
		{
			double x = wheelCoordinates.at(i).at(0) - rotationCenter.at(0);
			double y = wheelCoordinates.at(i).at(1) - rotationCenter.at(1);
			wheelMultipliers[i] = sqrt(x*x + y*y);
			wheelAngles[i] = (atan2(x, y) + .5*pi);
		}
		std::array<std::array<double, 2>, wheelCount> multipliersXY;
		wheelMultipliers = normalize(wheelMultipliers); //Fix
		for (int i = 0; i < wheelCount; i++)
		{
			multipliersXY[i][0] = wheelMultipliers[i] * cos(wheelAngles.at(i));
			multipliersXY[i][1] = wheelMultipliers[i] * sin(wheelAngles.at(i));
		}
		return multipliersXY; //change to array
	}

	/*
	std::vector<std::array<double, 2>> wheelSpeedsAngles(std::vector<std::array<double, 2>> wheelMultipliersXY,
	std::array<double, 2> velocityVector, double rotation, double angle) //for non field centric set angle to pi/2
	{
	/*if (rotation == 0 && velocityVector.at(0) == 0 && velocityVector.at(1) == 0)
	{
	return
	}
	//parking config isn't handled here, some movement should be passed to this function
	add commenty but here
	std::array<double, 2> rotatedVelocity = rotate(velocityVector);
	std::vector<double> speeds;
	std::vector<double> angles;
	for (int i = 0; i < std::wheelMultipliersXY::size; i++)
	{
	double x = wheelMultipliersXY.at(i).at(0)*rotation + rotatedVelocity.at(0);
	double y = wheelMultipliersXY.at(i).at(1)*rotation + rotatedVelocity.at(1);
	angles.push_back(atan2(x, y));
	speeds.push_back(sqrt(pow(x, 2) + pow(y, 2)));
	}
	speeds = normalize(speeds);
	std::vector<std::array<double, 2>> speedsAngles;
	for (int i = 0; i < std::wheelMultipliersXY::size; i++)
	{
	speedsAngles.push_back({ speeds.at(i), angles.at(i) });
	}
	return speedsAngles;
	}
	*/
	std::array<std::array<double, 2>, wheelCount> wheelSpeedsAngles(std::array<std::array<double, 2>, wheelCount> wheelMultipliersXY,
		std::array<double, 2> velocityVector, double rotation, double angle) //for non field centric set angle to pi/2
	{
		/*if (rotation == 0 && velocityVector.at(0) == 0 && velocityVector.at(1) == 0)
		{
		return
		}
		//parking config isn't handled here, some movement should be passed to this function
		*/
		std::array<double, 2> rotatedVelocity = rotate(angle, velocityVector); //Change to vectors
		std::array<double, wheelCount> speeds;
		std::array<double, wheelCount> angles;
		for (int i = 0; i < wheelCount; i++)
		{
			double x = wheelMultipliersXY.at(i).at(0)*rotation + rotatedVelocity.at(0);
			double y = wheelMultipliersXY.at(i).at(1)*rotation + rotatedVelocity.at(1);
			angles[i] = (atan2(x, y));
			speeds[i] = sqrt(x*x + y*y);
		}
		speeds = normalize(speeds);
		std::array<std::array<double, 2>, wheelCount> speedsAngles;
		for (int i = 0; i < wheelCount; i++)
		{

			speedsAngles[i][0] = speeds.at(i);
			speedsAngles[i][0] = angles.at(i);
		}

		return speedsAngles;
	}
	std::array<double, wheelCount> parkingAngles(std::array<std::array<double, 2>, wheelCount> wheelCoordinates) //only must be run once to determine the angles of the wheels in parking config
	{
		std::array<double, wheelCount> angles;
		for (int i = 0; i < wheelCoordinates.size(); i++)
		{
			angles[i] = (atan2(wheelCoordinates.at(i).at(0), wheelCoordinates.at(i).at(1)));
		}
		return angles;
	}
	/*vector of some variety/// wheelAverage(std::array</*vector of some variety/, wheelCount>, double angle)
	{
		//you know what goes here
	}
	/*vector of some variety threeWheelAvg(std::array</*vector of some variety/, wheelCount>, double angle)
	{
		//use horizontally adjacent wheels somehow?, needs to be generalized
		//Is this needed?
	}
	*/

