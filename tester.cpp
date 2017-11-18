//#include "SwerveMath.h"
#include <math.h>
#include <iostream>
//#include "900Math.h"
#include "SwerveMath.h"
#include "nextVelocity.h"
#include <Eigen/Dense>

using namespace Eigen;
using namespace std;
int main()
{	
	Vector2d wheel1(-4, 4);
	Vector2d wheel3(4, 4);	
	Vector2d wheel2(-4, -4);	
	Vector2d wheel4(4, -4);
	
	array <Vector2d, WHEELCOUNT> wheelCoordinates = {wheel1, wheel2, wheel3, wheel4};
	swerveDriveMath testSwerve(wheelCoordinates);

	
	cout << "Parking Angles" << endl;

	cout << testSwerve.parkingAngle[0] << endl;			
	cout << testSwerve.parkingAngle[1] << endl;		
	cout << testSwerve.parkingAngle[2] << endl;		
	cout << testSwerve.parkingAngle[3] << endl;		
	
	cout << "Base Multipliers" << endl;

	cout << testSwerve.baseWheelMultipliersXY[0] << endl;
	cout << testSwerve.baseWheelMultipliersXY[1] << endl;
	cout << testSwerve.baseWheelMultipliersXY[2] << endl;
	cout << testSwerve.baseWheelMultipliersXY[3] << endl;

	Vector2d centerOfRot(-3, 5);
	array<Vector2d, WHEELCOUNT> testMult  = testSwerve.wheelMultipliersXY(wheelCoordinates, centerOfRot);
	
	
	cout << "Test Multipliers" << endl;
	
	cout << testMult[0] << endl;
	cout << testMult[1] << endl;
	cout << testMult[2] << endl;
	cout << testMult[3] << endl;
	
	//If you want to test normalization the function needs to be made public in SwerveMath.h
	/*
	cout << "Normalizing {1, 2, 3, 4}" << endl;
	
	array<double, WHEELCOUNT> input = {1, 2, 3, -4};
	array<double, WHEELCOUNT> normalized = testSwerve.normalize(input);


	cout << normalized[0] << endl;
	cout << normalized[1] << endl;
	cout << normalized[2] << endl;
	cout << normalized[3] << endl;
	
	*/
	
	cout << "Speeds and Angles" << endl;

	Vector2d velocity(.75, -.25);	
	double rotation = .3;
	double angle = M_PI/2;


	array<Vector2d, WHEELCOUNT> speedsAngles = testSwerve.wheelSpeedsAngles(testSwerve.baseWheelMultipliersXY, velocity, rotation, angle);
	
	cout << speedsAngles[0] << endl;
	cout << speedsAngles[1] << endl;
	cout << speedsAngles[2] << endl;
	cout << speedsAngles[3] << endl;
	/*
	double v;
	cout << "v" << endl;
	cin >> v;
	
	double vt;
	cout << "vt" << endl;
	cin >> vt;

	double a;	
	cout << "a" << endl;
	cin >> a;
	
	double am;	
	cout << "am" << endl;
	cin >> am;
	
	
	double jm;	
	cout << "jm" << endl;
	cin >> jm;

	
	double cr;	
	cout << "cr" << endl;
	cin >> cr;
	*/
	//bool reverse;
	//cout << normalizeAngle(angle) << endl;
	//cout << nextVelocity(v, vt, a, am, jm, cr) << endl;
	//string rev;
	//if(reverse){rev = "True";} else{rev = "False";}
	//cout << rev  << endl;
	return 0;	
								
}
