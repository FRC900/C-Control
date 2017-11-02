#include "SwerveMath.h"
#include "900Math.h"
#include <iostream>

using namespace std;
int _tmain(int argc, _TCHAR* argv[])
{
	while (true){
		double angle;
		cout << "angle" << endl;
		cin >> angle;
		cout << normalizeAngle(angle);
	}
										}
