//#include "SwerveMath.h"
#include <math.h>
#include <iostream>
//#include "900Math.h"
#include "Swerve.h"
#include <Eigen/Dense>
#include <functional>

using namespace Eigen;
using namespace std;
using namespace swerveVar;

double testIndexer1(int module, int which) //0 is rotation, 1 is steering
{	
array<array<double, 2>, WHEELCOUNT> fakeEncoderPositions;
	
fakeEncoderPositions[0] = {0, 0};
fakeEncoderPositions[1] = {0, 0};
fakeEncoderPositions[2] = {0, 0};
fakeEncoderPositions[3] = {0, 0};
	return fakeEncoderPositions[module][which];
}

double testIndexer2(int module, int which) //0 is rotation, 1 is steering
{	

array<array<double, 2>, WHEELCOUNT> fakeEncoderVelocities;
fakeEncoderVelocities[0] = {0, 0};
fakeEncoderVelocities[1] = {0, 0};
fakeEncoderVelocities[2] = {0, 0};
fakeEncoderVelocities[3] = {0, 0};
	return fakeEncoderVelocities[module][which];
}
int main()
{	
	Vector2d wheel1(-4, 4);
	Vector2d wheel3(4, 4);	
	Vector2d wheel2(-4, -4);	
	Vector2d wheel4(4, -4);
	
	array <Vector2d, WHEELCOUNT> wheelCoordinates = {wheel1, wheel2, wheel3, wheel4};
	function<double(int, int)> pos = testIndexer1;
	function<double(int, int)> vel = testIndexer2;

	cout<<pos(2, 3)<<endl;	
	ratios testRs;
	testRs.encodertoRotations = 1;
	testRs.motortoRotations = 7;
	testRs.motortoSteering  = 4;
	
	encoderUnits units;
	units.steeringGet = 1;
	units.steeringSet = 1;
	units.rotationGetV = 1;
	units.rotationGetP = 1;
	units.rotationSetV = 1;
	units.rotationSetP = 1;

	driveModel model;
	model.maxSpeed = 5;
	model.wheelRadius = .045;
	model.mass = 70;
	model.motorFreeSpeed = 5840;
	model.motorStallTorque = 1.41;
	model.motorQuantity = 4;

	

	swerve testSwerve(wheelCoordinates, "offsets.txt", false, pos, vel, testRs, units, model);

	
	cout << "Parking Config" << endl;
	
	Vector2d tVel = {3, 1};
	double rotation = .3;
	array<bool, WHEELCOUNT> holder;
	bool park = true;
	

	array<Vector2d, WHEELCOUNT> outputs1 = testSwerve.motorOutputs(tVel, rotation, M_PI/2, false, holder, park);  
	
	cout << outputs1[0][1] << endl;			
	cout << outputs1[1][1] << endl;			
	cout << outputs1[2][1] << endl;			
	cout << outputs1[3][1] << endl;				
	
	cout << outputs1[0][0] << endl;			
	cout << outputs1[1][0] << endl;			
	cout << outputs1[2][0] << endl;			
	cout << outputs1[3][0] << endl;			

	return 0;	
								
}
