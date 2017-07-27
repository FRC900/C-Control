#include <array>
#include <cmath>
#include <math.h>
#include <stdlib.h>
#include <vector>
class motionProfile{
	double maxV;
	double maxA;
	double maxJ;
	double controlRateMS = 10;
	
	motionProfile(double _maxV, double _maxA, double _maxJ, double _controlRateMS = 10)
	{
		maxV = _maxV;
		maxA = _maxA;
		maxJ = _maxJ;
		controlRateMS = _controlRateMS;
	}

	bool motionProfile(double travelDist, vector<double> &velocities, vector<double> &positions)
	{
		if (maxV == 0 || maxA == 0 || maxJ == 0 || travelDist == 0)
			return false;
		double effMaxA = max(maxA, max(pow(abs(travelDist)*.5*maxJ*maxJ, 1.0 / 3), sqrt(maxJ*maxV)));
		double effMaxV = max(maxV, (effMaxA*effMaxA*(-1) + sqrt(pow(effMaxA, 4) + 4 * effMaxA*abs(travelDist)*maxJ*maxJ)) / (2 * maxJ));
		int v1 = ceil(effMaxA * 1000 / (MaxJ*controlRateMS));
		int v2 = ceil(effMaxV * 1000 / (effMaxA*controlRateMS));
		double v3 = abs(travelDist) * 1000 / (effMaxV*controlRateMS) + 2;
		maxSize = 1000 * abs(travelDist) * 2 / (controlRateMS*effMaxV) + 10;
		double f1sum[maxSize];
		double f1sum[0] = 0;
		double f2sum;
		velocities[0] = 0;
		positions[0] = 0;
		double prevP = 0;
		int i = 0;
		double lv1;
		double lv2;
		double f1;
		do
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
			velocities.push_back((f1 + f2sum) * effMaxV / (v1 + 1));
			positions.push_back(((velocities[i] + velocities[i + 1])*controlRateMS / 2000) + positions[i]);
			i++;
		} while (i == 0 || velocities[i + 1] != 0);
		velocities.erase(velocities.begin());
		positions.erase(positions.begin());
		return true;
	}
}