//#include "SwerveMath.h"

#include <iostream>

#include "900Math.h"


using namespace std;
int main()
{
	double angle;
	cout << "angle" << endl;
	cin >> angle;
	
	double tarAngle;
	cout << "target angle" << endl;
	cin >> tarAngle;
	
	bool reverse;
	cout << normalizeAngle(angle) << endl;
	//cout << leastDistantAngleWithinHalfPi(angle, tarAngle, reverse) << endl;
	//string rev;
	//if(reverse){rev = "True";} else{rev = "False";}
	//cout << rev  << endl;
	return 0;	
								
}
