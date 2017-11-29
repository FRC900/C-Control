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

#define WHEELCOUNT 4

using namespace std;
using namespace Eigen;
//meters, radians, newtons, kg
//This class will need access to the swerve drive talons
//Gets should be rotations/encoder unit
//Sets should be encoder unit/rotation (or rotations/second)




namespace swerveVar
{
struct ratios
{
double encodertoRotations;
double motortoRotations;
double motortoSteering;
};

struct encoderUnits
{
double steeringGet;
double steeringSet;
double rotationGetV;
double rotationGetP;
double rotationSetV;
double rotationSetP;
};
struct driveModel
{
double maxSpeed;
double wheelRadius;
double mass;
double motorFreeSpeed;
double motorStallTorque;
int motorQuantity;
double speedLossConstant = .81;
}; //more info should be added to this struct
}
using namespace swerveVar;
class swerve
{
	public:
		swerve(array<Vector2d, WHEELCOUNT> _wheelCoordinates, string _fileAddress, bool _wheelAngleInvert, std::function<double(int, int)> _encoderPosition, std::function<double(int, int)> _encoderVelocity, ratios _ratio, encoderUnits _units, driveModel _drive);
		
		array<Vector2d, WHEELCOUNT> motorOutputs(Vector2d velocityVector, double rotation, double angle, bool forceRead, array<bool, WHEELCOUNT> &reverses, bool park, int rotationCenterID = 0, bool overrideID = false, Vector2d centerOfRotation = {0, 0});
		//for non field centric drive set angle = pi/2
		//if rotationCenterID == 0 we will use the base center of rotation
		void saveNewOffsets(bool useVals, array<double, WHEELCOUNT> newOffsets); //should these be doubles? 
		//Note that unless you pass vals in and set useVals to true, it will use the current wheel positions, wheels should be pointing to the right.
		double getWheelAngle(int index); 
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
		swerveDriveMath swerveMath; //this should be public
	
	private:
		
		array<double, WHEELCOUNT> offsets; //Should these be doubles?
		string fileAddress;
		//Second piece of data is here just for physics/modeling
		
		array<double, WHEELCOUNT> savedEncoderVals;
		int8_t wheelAngleInvert;
		
		double furthestWheel(Vector2d centerOfRotation); 	
		struct multiplierSet
		{
			array<Vector2d, WHEELCOUNT> multipliers;
			double maxRotRate;
		};
		array<multiplierSet, 63> multiplierSets;
		std::function<double(int, int)> encoderPosition;	
		std::function<double(int, int)> encoderVelocity;
		ratios ratio;
		encoderUnits units;
		driveModel drive;
};
#endif
