#ifndef INC_SWERVE
#define INC_SWERVE

#include <vector>
#include <array>
#include <string>
#include <Eigen/Dense>
#include "SwerveMath.h"
#include <functional>
#include <vector>
#include <math.h>

using namespace std;
using namespace Eigen;
//meters, radians, newtons, kg
//This class will need access to the swerve drive talons
//Gets should be rotations/encoder unit
//Sets should be encoder unit/rotation (or rotations/second)
class swerve
{
	public:
		swerve(array<Vector2d, WHEELCOUNT> _wheelCoordinates, double _maxSpeed, string _fileAddress, double _ratioEncodertoRotations, double _ratioEncodertoSteering, double _ratioMotortoRotations, double _ratioMotortoSteering, double _steeringEncoderGetUnits, double _steeringEncoderSetUnits, double _rotationEncoderGetVelocityUnits, double _rotationEncoderGetPositionUnits, double _rotationEncoderSetVelocityUnits, double _rotationEncoderSetPositionUnits, double _wheelRadius, double _robotMass, double _motorQuantity, double _motorFreeSpeed, double _motorStallTorque, bool _wheelAngleInvert, std::function<double(int, int)> _encoderPosition, double _speedLossConstant = .81);


		
		array<Vector2d, WHEELCOUNT> motorOutputs(Vector2d velocityVector, double rotation, double angle, bool forceRead, array<bool, WHEELCOUNT> &reverses, int rotationCenterID = 0, bool overrideID = false, Vector2d centerOfRotation = {0, 0});
		//for non field centric drive set angle = pi/2
		//if rotationCenterID == 0 we will use the base center of rotation
		void saveNewOffsets(bool useVals = false, array<double, WHEELCOUNT> newOffsets = {[0 ... WHEELCOUNT] = 0}); //should these be doubles? 
		//Note that unless you pass vals in and set useVals to true, it will use the current wheel positions, wheels should be pointing to the right.
		array<double, WHEELCOUNT> getWheelAngle(int index); 
		//should we get them together instead?
		//the angle it passes out isn't normalized
		//Vector2d currentOdom;
		//Vector2d calculateOdom(); //might be some associated private variables
		//Probably should be called every 
		//Vector2d wheel1(-4, 4);
		//Vector2d wheel3(4, 4);
		//Vector2d wheel2(-4, -4);
		//Vector2d wheel4(4, -4);
		
		array<Vector2d, WHEELCOUNT> wheelCoordinates; //= {wheel1, wheel2, wheel3, wheel4};
		swerveDriveMath swerveMath(wheelCoordinates); //this should be public
	
	private:
		
		array<double, WHEELCOUNT> offsets; //Should these be doubles?
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
		};
		array<multiplierSet, 63> multiplierSets;
		std::function<double(int, int)> encoderPosition;
		double robotMass, motorQuantity, motorFreeSpeed, motorStallTorque, speedLossConstant;

};
#endif
