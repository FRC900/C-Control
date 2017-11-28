#include "Swerve.h"
#include <iostream>
#include <math.h>
#include <fstream>
#include <iomanip>	
#include <functional>
#include <cmath>
using namespace std;
using namespace Eigen;

swerve::swerve(array<Vector2d, WHEELCOUNT> _wheelCoordinates, double _maxSpeed, string _fileAddress, double _ratioEncodertoRotations, double _ratioEncodertoSteering, double _ratioMotortoRotations, double _ratioMotortoSteering, double _steeringEncoderGetUnits, double _steeringEncoderSetUnits, double _rotationEncoderGetVelocityUnits, double _rotationEncoderGetPositionUnits, double _rotationEncoderSetVelocityUnits, double _rotationEncoderSetPositionUnits, double _wheelRadius, double _robotMass, double _motorQuantity, double _motorFreeSpeed, double encoderPosition(int, int), double _motorStallTorque, double _speedLossConstant)
{
	wheelCoordinates = _wheelCoordinates;
	maxSpeed = _maxSpeed;
	fileAddress = _fileAddress;
	ratioEncodertoRotations = _ratioEncodertoRotations;
	ratioMotortoRotations = _ratioMotortoRotations; //This data is here just for physics/modeling
        steeringEncoderGetUnits = _steeringEncoderGetUnits;
	steeringEncoderSetUnits = _steeringEncoderSetUnits;
	rotationEncoderGetVelocityUnits = _rotationEncoderGetVelocityUnits;
	rotationEncoderGetPositionUnits = _rotationEncoderGetPositionUnits;
	rotationEncoderSetVelocityUnits = _rotationEncoderSetVelocityUnits;
	rotationEncoderSetPositionUnits = _rotationEncoderSetPositionUnits;
	for(int i =0; i < WHEELCOUNT; i++)
	{
		getWheelAngle(i);
	}
	wheelRadius = _wheelRadius;
	wheelAngleInvert = _wheelAngleInvert ? -1 : 1;
	ifstream offsetRead;
	offsetRead.open(fileAddress);
	if(!offsetRead)
	{
		cout<< "No Offset File!!!" << endl;
		saveNewOffsets();
	}
	double offset;
	int i = 0;
	while(offsetRead >> offset)
	{
		offsets[i] = offset;
		i++;
	}
	encoderPosition = _encoderPosition;
	robotMass = _robotMass;
	motorQuantity = _motorQuantity;
	motorFreeSpeed = _motorFreeSpeed;
	motorStallTorque = _motorStallTorque;
	speedLossConstant = _speedLossConstant;
}
array<Vector2d, WHEELCOUNT> motorOutputs(Vector2d velocityVector, double rotation, double angle, bool forceRead, array<bool, WHEELCOUNT> &reverses, bool park, int rotationCenterID, bool overrideID, Vector2d centerOfRotation)
{
	array<Vector2d, WHEELCOUNT> speedsAndAngles;
	if(!park)
	{
		velocityVector/=maxSpeed;

		if(overrideID)
		{
			multiplierSet newSet;
			newSet.multipliers = swerveMath.wheelMultipliersXY(centerOfRotation);
			newSet.maxRotRate = furthestWheel(centerOfRotation)/maxSpeed;	
			multiplierSets[rotationCenterID] = newSet;
		}
		rotation/=multiplierSets[rotationCenterID].maxRotRate;
		speedsAndAngles = swerveMath.wheelSpeedsAngles(multiplierSets[rotationCenterID].multipliers, velocityVector, rotation, angle);
		for(int i = 0; i < WHEELCOUNT; i++)
		{
			double nearestAngle;
			bool reverse;
			if(forceRead)
			{
				getWheelAngle[i];
				nearestAngle = leastDistantAngleWithinHalfPi(savedEncoderVals[i], speedsAndAngles[i][1], reverse);
			}
			else
			{
				nearestAngle = leastDistantAngleWithinHalfPi(savedEncoderVals[i], speedsAndAngles[i][1], reverse);
				if(abs(savedEncoderVals[i] - nearestAngle) > M_PI/4)
				{
					getWheelAngle[i];
					nearestAngle = leastDistantAngleWithinHalfPi(savedEncoderVals[i], speedsAndAngles[i][1], reverse);
				}
			}
			reverses[i] = reverse;
			speedsAndAngles[i][0]*=((maxSpeed/(wheelRadius*2*M_PI))/ratioEncodertoRotation)*rotationEncoderSetVelocityUnits* (reverse ? -1 : 1);
			speedsAndAngles[i][1] = (nearestAngle/(2*M_PI))*steeringEncoderSetUnits - offsets[i];
		}
	}
	else
	{	
		for(int i = 0; i < WHEELCOUNT; i++)
		{
			speedsAndAngles[i][1] = swerveMath.parkingAngle[i];
			speedsAndAngles[i][0] = 0;
		}

	}
	return speedsAndAngles;
}
void saveNewOffsets(bool useVals, array<double, WHEELCOUNT> newOffsets);
{
	if(!useVals)
	{
		for(int i = 0; i < WHEELCOUNT; i++)
		{
			newOffsets[i] = encoderPosition(i, 1);
		}
	}
	offsets = newOffsets;
	ofstream offsetFile;
	offsetFile.open(fileAddress);
	if(offsetFile)
	{
		offsetFile.close();
		offsetFile.open(fileAddress, ios::out | ios::trunc);

	}
	for(int i = 0; i < WHEELCOUNT; i++)
	{
		offsetFile << offsets[i] << endl;
	}
	offsetFile.close();
}
/*
Vector2d calculateOdom()
{

//Steal code from steered wheel base

}
*/

double getWheelAngle(int index)
{
	savedEncoderVals[index] = (encoderPosition(index, 1)+offsets[index])*steeringEncoderGetUnits*2*M_PI*wheelAngleInvert;
	return savedEncoderVals[index];
}

double furthestWheel(Vector2d centerOfRotation)
{
	double maxD = 0;
	for(int i = 0; i < WHEELCOUNT; i++)
	{
		double dist = sqrt(pow(wheelCoordinates[i][0] - centerOfRotation[0], 2) + pow(wheelCoordinates[i][1] - centerOfRotation[1], 2));
		if(dist>maxD){maxD=dist;}
	}
	return maxD;
}
