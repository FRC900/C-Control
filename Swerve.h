#ifndef INC_SWERVE
#define INC_SWERVE

#include <vector>
#include <array>
#include <string>
#include <Eigen/Dense>
#include "SwerveMath.h"

using namespace std;
using namespace eigen;
//meters, radians, newtons, kg
//This class will need access to the swerve drive talons
//Gets should be rotations/encoder unit
//Sets should be encoder unit/rotation (or rotations/second)
class swerve
{
	public:
		swerve(array<Vector2d, WHEELCOUNT> _wheelCoordinates, double _maxSpeed, string _fileAddress, double _ratioEncodertoRotations, double _ratioEncodertoSteering, double _ratioMotortoRotations, double _ratioMotortoSteering, double _steeringEncoderGetUnits, double _steeringEncoderSetUnits, double _rotationEncoderGetVelocityUnits, double _rotationEncoderGetPositionUnits, double _rotationEncoderSetVelocityUnits, double _rotationEncoderSetPositionUnits, double _wheelRadius, double _robotMass, double _motorQuantity, double _motorFreeSpeed, double _motorStallTorque, bool _wheelAngleInvert, double encoderSteeringVal(int), double _speedLossConstant = .81);


		
		array<Vector2d, WHEELCOUNT> motorOutputs(Vector2d velocityVector, double rotation, int rotationCenterID = 0, bool overrideID = false, Vector2d centerOfRotation = {0, 0}, double angle, bool forceRead, array<bool, WHEELCOUNT> &reverses);
		//for non field centric drive set angle = pi/2
		//if rotationCenterID == 0 we will use the base center of rotation
		void saveNewOffsets(bool useVals = false, array<double, WHEELCOUNT> newOffsets = darray); //should these be doubles? 
		//Note that unless you pass vals in and set useVals to true, it will use the current wheel positions, wheels should be pointing to the right.
		array<double, WHEELCOUNT> getWheelAngle(int index); 
		//should we get them together instead?
		//the angle it passes out isn't normalized
		Vector2d currentOdom;
		Vector2d calculateOdom(); //might be some associated private variables
		//Probably should be called every 
		array <Vector2d, WHEELCOUNT> wheelCoordinates; //this should be private
		swerveDriveMath swerveMath(wheelCoordinates); //this should be public
	
	private:
		
		array<double, WHEELCOUNT> offsets; //Should these be doubles?
		double darray[WHEELCOUNT] = {[0 ... WHEELCOUNT] = 0};
		double maxSpeed;
		string fileAddress;
		double ratioEncodertoRotations, ratioMotortoRotations; 
		//Second piece of data is here just for physics/modeling
		
		double steeringEncoderGetUnits, steeringEncoderSetUnits, rotationEncoderGetVelocityUnits, rotationEncoderGetPositionUnits, rotationEncoderSetVelocityUnits, rotationEncoderSetPositionUnits;

		array<double, WHEELCOUNT> savedEncoderVals;
		double wheelRadius;
		int8_t wheelAngleInvert;
		
		double furthestWheel(Vector2d centerOfRotation); 	
		struct multiplierSet
		{
			array<Vector2d, WHEELCOUNT> multipliers;
			double maxRotRate;
		}
		array<multiplierSet, 63> multiplierSets;

		double robotMass, motorQuantity, motorFreeSpeed, motorStallTorque, speedLossConstant;

};
#endif
