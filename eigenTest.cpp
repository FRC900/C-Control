#include <iostream>
#include <Eigen/Dense>
#include <math.h>
using namespace Eigen;
int main()
{
	Vector2d a(2, 3);
	double theta = M_PI/4;
	Rotation2Dd t(theta);
	std::cout << a << std::endl;
	Vector2d rotatedV = t.toRotationMatrix()*a;
	std::cout<< rotatedV << std::endl;
	
}

