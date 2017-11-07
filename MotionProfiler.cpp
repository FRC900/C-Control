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
	double effMaxA = min(maxA, min(pow(abs(travelDist)*.5*maxJ*maxJ, 1.0 / 3), sqrt(maxJ*maxV)));
//cout << "effMaxA: " << effMaxA << endl;
	double effMaxV = min(maxV, (effMaxA*effMaxA*(-1) + sqrt(pow(effMaxA, 4) + 4 * effMaxA*abs(travelDist)*maxJ*maxJ)) / (2 * maxJ));	
	//cout << "effMaxV: " << effMaxV << endl;
	int v1 = ceil(effMaxA * 1000 / (maxJ*controlRateMS));	
	//cout << "v1: " << v1 << endl;
	int v2 = ceil(effMaxV * 1000 / (effMaxA*controlRateMS));
	//cout << "v2: " << v2 << endl;
	double v3 = abs(travelDist) * 1000 / (effMaxV*controlRateMS) + 2;
	//cout << "v3: " << v3 << endl;
	int maxSize = floor(1000 * abs(travelDist) * 2 / (controlRateMS*effMaxV)) + 10;
	//cout << "maxSize: " << maxSize << endl;
	double f1sum[maxSize];
	f1sum[0] = 0;
	double f2sum;
	velocities.reserve(maxSize); //Effeciency YAY
	velocities.reserve(maxSize);	

	velocities.push_back(0);
	positions.push_back(0);
	double prevP = 0;
	int i = 0;
	double lv1;
	double lv2;
	double f1;
	
	int min1;
	int start;
	//cout << "Starting Looping:" << endl;
	do
	{
		min1 = min(i, v1);
		
		//cout << "min1: " << min1 << endl;
		start = i - (min1 - 1);
		f2sum = 0;	
		//cout << "start: " << start << endl;
		for (int j = 0; j < min1; j++) //May have off by one error here
		{
			f2sum = f1sum[start + j] + f2sum;
		}
		
		//cout << "f2sum: " << f2sum << endl;
		lv1 = f1sum[i] + ((i + 2 < v3) ? 1.0 : -1.0)/v2;
		
		//cout << "lv1: " << lv1 << endl;
		f1 = coerce(lv1, 0, 1); 
		
		//cout << "f1: " << f1 << endl;
		f1sum[i + 1] = f1;
		
		////cout << velocities.size() << endl;
		velocities.push_back((f1 + f2sum) * effMaxV / (v1 + 1));
		
		//cout << "velocity: " << velocities.at(i+1) << endl;
		positions.push_back(((velocities.at(i) + velocities.at(i + 1))*controlRateMS / 2000) + positions.at(i));
		
		//cout << "position: " << positions.at(i+1) << endl;
		i++;
		//cout << velocities.size() << endl;
	} while ((i == 0 || velocities.at(i) != 0) && i<= maxSize);
	//cout << velocities.size() << endl;
	velocities.erase(velocities.begin());
	positions.erase(positions.begin());
	if(travelDist < 0)
	{
		//TODO: FIX THIS TRANSFORM
		transform(velocities.begin(), velocities.end(), velocities.begin(),bind1st(multiplies<T>(),-1));		
		transform(positions.begin(), positions.end(), positions.begin(),bind1st(multiplies<T>(),-1));
	}
	return true;
}

