//#include "SwerveMath.h"

#include <iostream>
//#include "900Math.h"
//#include "SwerveMath.h"
#include "nextVelocity.h"

using namespace std;
int main()
{
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
	//bool reverse;
	//cout << normalizeAngle(angle) << endl;
	cout << nextVelocity(v, vt, a, am, jm, cr) << endl;
	//string rev;
	//if(reverse){rev = "True";} else{rev = "False";}
	//cout << rev  << endl;
	return 0;	
								
}
