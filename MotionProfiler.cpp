#include <array>
#include <algorithm>
#include <math.h>
#include <stdlib.h>
#include <vector>
#include "MotionProfiler.h"
#include "900Math.h"
#include <iostream>

motionProfile::motionProfile(double _maxV, double _maxA, double _maxJ, double _controlRateMS)
{
	maxV = _maxV;
	maxA = _maxA;
	maxJ = _maxJ;
	controlRateMS = _controlRateMS;
}
//This function below is very difficult to comment line by line
using namespace std;
bool motionProfile::genMotionProfile(double travelDist, std::vector<double> &velocities, std::vector<double> &positions)
{
	if (maxV == 0 || maxA == 0 || maxJ == 0 || travelDist == 0)
		return false;
	double effMaxA = min(maxA, max(pow(abs(travelDist)*.5*maxJ*maxJ, 1.0 / 3), sqrt(maxJ*maxV)));
	double effMaxV = min(maxV, (effMaxA*effMaxA*(-1) + sqrt(pow(effMaxA, 4) + 4 * effMaxA*abs(travelDist)*maxJ*maxJ)) / (2 * maxJ));
	int v1 = ceil(effMaxA * 1000 / (maxJ*controlRateMS));
	int v2 = ceil(effMaxV * 1000 / (effMaxA*controlRateMS));
	double v3 = abs(travelDist) * 1000 / (effMaxV*controlRateMS) + 2;
	int maxSize = floor(1000 * abs(travelDist) * 2 / (controlRateMS*effMaxV)) + 10;
	double f1sum[maxSize];
	cout << maxSize << endl;
	f1sum[0] = 0;
	double f2sum;
	velocities.push_back(0);
	positions.push_back(0);
	double prevP = 0;
	int i = 0;
	double lv1;
	double lv2;
	double f1;
	
	int min1;
	int start;
	
	do
	{
		min1 = min(i, v1);
		start = i - (min1 - 1);
		for (int j = 0; j < min1; j++) //May have off by one error here
		{
			f2sum = f1sum[start + j] + f2sum;
		}
		lv1 = f1sum[i] + (i + 2 < v3) ? 1 : -1;
		f1 = coerce(lv1, 0, 1);
		f1sum[i + 1] = f1;
		
		//cout << velocities.size() << endl;
		velocities.push_back((f1 + f2sum) * effMaxV / (v1 + 1));
		positions.push_back(((velocities.at(i) + velocities.at(i + 1))*controlRateMS / 2000) + positions.at(i));
		i++;
		cout << velocities.size() << endl;
	} while ((i == 0 || velocities.at(i) != 0) && i<= maxSize);
	cout << velocities.size() << endl;
	velocities.erase(velocities.begin());
	positions.erase(positions.begin());
	return true;
}

