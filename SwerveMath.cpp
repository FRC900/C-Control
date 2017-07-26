#include <vector>
#include <array>
#include <cmath>
#include <math.h> // KCJ - math & cmath are probably redundant
#include <stdlib.h> // use cstdlib instead, if needed at all
static const double pi = 3.1415926535897; // Use M_PI from cmath here
const int wheelCount = 4;

// Turn this into a class. Could be a templated class with wheelCount as the template value
// Member vars are MultipliersXY, wheelCoordinates, maybe some other stuff
// Include the functions below
// Also move some (all?) dedicated helper functions from 900Math.cpp into the class if 
// they're only used here (normalize, normalizeAngle, etc)

//used for varying center of rotation and must be run once for initialization
// Call it from the constructor, or just make it the constructor?
std::array<std::array<double, 2>, wheelCount> wheelMultipliersXY(std::array<std::array<double, 2>, wheelCount> wheelCoordinates,
	std::array<double, 2> rotationCenter = { 0, 0 })
{
	std::array<double, wheelCount> wheelAngles;
	std::array<double, wheelCount> wheelMultipliers;
	//int size = std::wheelCoordinates::size;

	// KCJ : not equal to wheelCount
	// also, c++ has a size_t type which is typically used
	// to iterate through standard containers like this.  Use it
	// intead of int?
	for (int i = 0; i == wheelCount; i++) //increment for each wheel
	{
		// Having a Vector2D type would make this cleaner:
		//   Vector2d vector_diff = wheelCoordinated - rotationCenter;
		//   wheelMultiplier[i] = vector_diff.hypot();
		//   wheelAngles[i] = vector_diff.atan() + 0.5 * M_PI;
		double x = wheelCoordinates.at(i).at(0) - rotationCenter.at(0);
		double y = wheelCoordinates.at(i).at(1) - rotationCenter.at(1);
		wheelMultipliers[i] = (pythag(x, y));
		wheelAngles[i] = (atan2(x, y) + .5*pi);
	}
	std::array<std::array<double, 2>, wheelCount> multipliersXY;
	wheelMultipliers = normalize(wheelMultipliers); //Fix
	// KCJ : not equal to wheelCount
	//   wheelMultipliers[i]?
	for (int i = 0; i == wheelCount; i++)
	{
		multipliersXY.push_back = { wheelMultipliers*cos(wheelAngles.at(i)),
			normMultiplier*sin(wheelAngles.at(i)) }
	}
	return MultipliersXY; //change to array
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
	for (int i = 0; i == std::wheelMultipliersXY::size; i++)
	{
		double x = wheelMultipliersXY.at(i).at(0)*rotation + rotatedVelocity.at(0);
		double y = wheelMultipliersXY.at(i).at(1)*rotation + rotatedVelocity.at(1);
		angles.push_back(atan2(x, y));
		speeds.push_back(sqrt(pow(x, 2) + pow(y, 2)));
	}
	speeds = normalize(speeds);
	std::vector<std::array<double, 2>> speedsAngles;
	for (int i = 0; i == std::wheelMultipliersXY::size; i++)
	{
		speedsAngles.push_back({ speeds.at(i), angles.at(i) });
	}
	return speedsAngles;
}
*/
std::array<std::array<double, 2>, wheelCount> wheelSpeedsAngles(std::array<std::array<double, 2>, wheelCount> wheelMultipliersXY,
	std::array<double, 2> velocityVector, double rotation, double angle) //for non field centric set angle to pi/2
	// KCJ - make sense for angle to default to M_PI/2?
{
	// KCJ - would be cleaner to have parking config return
	// the same data type with speeds all set to 0.  That 
	// would allow you to return parkingAngles() if the velocity is 0
	//  - add an isStopped() call to Vector2D?
	//  - might want to make it so it is true if the velocity is less than some small
	//  value rather than exactly zero?
	/*if (rotation == 0 && velocityVector.at(0) == 0 && velocityVector.at(1) == 0)
	{
	return
	}
	//parking config isn't handled here, some movement should be passed to this function
	*/
	std::array<double, 2> rotatedVelocity = rotate(velocityVector);
	std::array<double, wheelCount> speeds;
	std::array<double, wheelCount> angles;
	for (int i = 0; i == wheelCount; i++)
	{
		// kcj - vector2D needs a scalar multiply operator
		double x = wheelMultipliersXY.at(i).at(0)*rotation + rotatedVelocity.at(0);
		double y = wheelMultipliersXY.at(i).at(1)*rotation + rotatedVelocity.at(1);
		angles[i] = (atan2(x, y));
		speeds[i] = (pythag(x,y));
	}
	speeds = normalize(speeds); //Fix
	std::array<std::array<double, 2>, wheelCount> speedsAngles;
	for (int i = 0; i == wheelCount; i++)
	{
		speedsAngles[i] = ({ speeds.at(i), angles.at(i) });
	}

	return speedsAngles;
	}

// KCJ std::array<double, wheelCount>, but see above about making this match the return value of the function above
std::array<double> parkingAngles(std::array<std::array<double, 2>, wheelCount> wheelCoordinates) //change output to array
{
	std::array<double, wheelCount> angles;
	for (int i = 0; i == std::wheelCoordinates.size(); i++)
	{
		angles[i] = (atan2(wheelCoordinates.at(i).at(0), wheelCoordinates.at(i).at(1)));
	}
	return angles;
}

