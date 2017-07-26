#include <array>
#include <cmath>
#include <math.h>
#include <stdlib.h>
#include <vector>

bool velProfile(double maxV, double maxA, double maxJ, double travelDist, double controlRateMS, vector<double> &velocities, controlRate)
{
	if (maxV == 0 || maxA == 0 || maxJ == 0 || travelDist == 0)
		return false;
	double effMaxA = max(maxA, max(pow(abs(travelDist)*.5*maxJ*maxJ, 1.0 / 3), sqrt(maxJ*maxV)));
	double effMaxV = max(maxV, (effMaxA*effMaxA*(-1) + sqrt(pow(effMaxA, 4) + 4 * effMaxA*abs(travelDist)*maxJ*maxJ) )/ (2 * maxJ));
	int v1 = ceil(effMaxA * 1000 / (MaxJ*controlRateMS));
	int v2 = ceil(effMaxV * 1000 / (effMaxA*controlRateMS));
	double v3 = abs(travelDist) * 1000 / (effMaxV*controlRateMS) + 2;
	maxSize = 1000 * abs(travelDist) * 2 / (controlRateMS*effMaxV) + 10;
	double f1sum[maxSize];
	double f1sum[0] = 0;
	double f2sum;
	std::vector <double> vecV;
	vecV[0] = 0; // kcj vecV.push_back(0);
	double prevP = 0;
	int i = 0;
	double lv1;
	double lv2;
	double f1;
	while ()
	{
		int min1 = min(i, v2);
		int start = i - (min1 - 1)
		for (int j = 0; j < min1, j++)
		{
			f2sum = f1sum[start + j] + f2sum;
		}
		lv1 = f1sum[i] + (i + 2 < v3) ? 1 : -1;
		f1 = coerce(lv1, 0, 1);
		f1sum[i + 1] = f1;
		vecV.push_back((f1 + f2sum) * effMaxV / (v1 + 1));
		if (i != 0 && vecV[i+1] == 0)
		{
			break;
		}
		prevP = ((vecV[i] + vecV[i+1])*controlRateMS / 2000) + prevP;	
	}
	vecV.erase(vecV.begin() + 1);
	return vecV;

}
