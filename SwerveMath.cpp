#include <math.h>
#include <array>
#include "SwerveMath.h"
#include <Eigen/Dense>

static const double pi = M_PI;
using namespace std;

swerveDriveMath::swerveDriveMath( array<Eigen::Vector2d, WHEELCOUNT> _wheelCoordinates)
{
	wheelCoordinates = _wheelCoordinates;
	parkingAngle = parkingAngles(wheelCoordinates);
	//The below numbers can potentially change, it is relative to the wheel coordinates
	Eigen::Vector2d baseRotationCenter = {0, 0};
	baseWheelMultipliersXY = wheelMultipliersXY(wheelCoordinates, baseRotationCenter);

}



//used for varying center of rotation and must be run once for initialization
 array<Eigen::Vector2d, WHEELCOUNT> swerveDriveMath::wheelMultipliersXY( array<Eigen::Vector2d, WHEELCOUNT> wheelCoordinates, Eigen::Vector2d rotationCenter)
{
	 array<double, WHEELCOUNT> wheelAngles;
	 array<double, WHEELCOUNT> wheelMultipliers;
	//int size =  wheelCoordinates::size;
	for (int i = 0; i < WHEELCOUNT; i++) //increment for each wheel
	{
		double x = wheelCoordinates[i][0] - rotationCenter[0];
		double y = wheelCoordinates[i][1] - rotationCenter[1];
		wheelMultipliers[i] = sqrt(x*x + y*y);
		wheelAngles[i] = (atan2(x, y) + .5*pi);
	}
	 array<Eigen::Vector2d, WHEELCOUNT> multipliersXY;
	wheelMultipliers = normalize(wheelMultipliers); //TODO: Fix, add normalize function that works to 900Math.cpp
	for (int i = 0; i < WHEELCOUNT; i++)
	{
		multipliersXY[i][0] = wheelMultipliers[i] * cos(wheelAngles[i]);
		multipliersXY[i][1] = wheelMultipliers[i] * sin(wheelAngles[i]);
	}
	return multipliersXY; //change to array
}

 array<Eigen::Vector2d, WHEELCOUNT> swerveDriveMath::wheelSpeedsAngles( array<Eigen::Vector2d, WHEELCOUNT> wheelMultipliersXY,
	Eigen::Vector2d velocityVector, double rotation, double angle) //for non field centric set angle to pi/2
{
	/*if (rotation == 0 && velocityVector[0] == 0 && velocityVector[1] == 0)
	{
	return
	}
	*/
	
	//parking config isn't handled here (the code commented out above was the outline of how it could be handled here). Only call function if movement exists.
	
	//Rotate the target velocity by the robots angle to make it field centric
	Eigen::Rotation2Dd r(angle);	
	Eigen::Vector2d rotatedVelocity = r.toRotationMatrix()*velocityVector; //Should this instead be a function in 900Math of the form: rotate(vector, angle) rather than 2 lines of eigen stuff?
	 array<double, WHEELCOUNT> speeds;
	 array<double, WHEELCOUNT> angles;
	for (int i = 0; i < WHEELCOUNT; i++)
	{
		double x = wheelMultipliersXY[i][0]*rotation + rotatedVelocity[0];
		double y = wheelMultipliersXY[i][1]*rotation + rotatedVelocity[1];
		angles[i] = (atan2(x, y));
		speeds[i] = sqrt(x*x + y*y);
	}
	speeds = normalize(speeds); 
	array<Eigen::Vector2d, WHEELCOUNT> speedsAngles;
	for (int i = 0; i < WHEELCOUNT; i++)
	{

		speedsAngles[i][0] = speeds[i];
		speedsAngles[i][1] = angles[i];
	}

	return speedsAngles;
}
 array<double, WHEELCOUNT> swerveDriveMath::parkingAngles( array<Eigen::Vector2d, WHEELCOUNT> wheelCoordinates) //only must be run once to determine the angles of the wheels in parking config
{
	 array<double, WHEELCOUNT> angles;
	for (int i = 0; i < wheelCoordinates.size(); i++)
	{
		angles[i] = (atan2(wheelCoordinates[i][0], wheelCoordinates[i][1]));
	}
	return angles;
}


 array<double, WHEELCOUNT> swerveDriveMath::normalize( array<double, WHEELCOUNT> input)
{
	
	double maxi =  *max_element(input.begin(), input.end());
	double mini =  *min_element(input.begin(), input.end());
	double absoluteMax;
	if ( abs(maxi)>abs(mini) )
	{
		absoluteMax = abs(maxi);
	}
	else
	{
		absoluteMax = abs(mini);
	}
	array<double, WHEELCOUNT> normalized;
	for (int i = 0; i < input.size(); i++)
	{
		normalized[i] = (input[i] / absoluteMax);
	}
	return normalized;


}


///*vector of some variety*/ wheelAverage( array</*vector of some variety*/, WHEELCOUNT>, double angle)
//{
	//you know what goes here
//}
///*vector of some variety*/ threeWheelAvg( array</*vector of some variety*/, WHEELCOUNT>, double angle)
//{
	//use horizontally adjacent wheels somehow?, needs to be generalized
	//Is this needed?
//}

