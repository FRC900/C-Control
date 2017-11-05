//#include "SwerveMath.h"

#include <iostream>
#include "900Math.h"
#include "SwerveMath.h"

using namespace std;
int main()
{
	double val;
	cout << "val" << endl;
	cin >> val;
	
	double lowerBound;
	cout << "lower" << endl;
	cin >> lowerBound;

	double upperBound;	
	cout << "upper" << endl;
	cin >> upperBound;
	
	bool reverse;
	//cout << normalizeAngle(angle) << endl;
	cout << coerce(val, lowerBound, upperBound) << endl;
	//string rev;
	//if(reverse){rev = "True";} else{rev = "False";}
	//cout << rev  << endl;
	return 0;	
								
}
