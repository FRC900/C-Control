#include <vector>
#include <array>
#include <cmath>
#include <math.h>
#include <stdlib.h>
static const double pi = 3.1415926535897;

/* Run once somewhere
float lookup_table[2000];
for(int i = 0; i < sizeof(lookup_table)/sizeof(lookup_table[0]); i++) {
	float num = i/1000.0;
	float sqrt_num = sqrt(num);
	lookup_table[i] = sqrt_num;
}
*/
/*template <class T>
T maximum(const T& input)
{
	double maximum = *max_element(input.begin(), input.end());
}
*/
template <class T>
T normalize(const T& input)
{
	double max = *max_element(wheelMultipliers.begin(), wheelMultipliers.end());
	double min = *min_element(wheelMultipliers.begin(), wheelMultipliers.end());
	double absoluteMax;
	absoluteMax = (abs(max) > abs(min)) ? abs(max) : abs(min);
	T normalized;
	for (int i = 0; i < input.size(); i++)
	{
		normalized[i] = input.at(i) / absoluteMax;
	}
}
double pythaguptotwo(double a, double b)
{
	double c = lookup_table[(a*a + b*b)]; //sqrt lookup table
	return c;
}
double pythag(double a, double b)
{
	double c = sqrt(a*a + b*b);
	return c;
}
/*std::vector<double> normalize(const std::vector<double>& input) //vector version
{
double max = *max_element(wheelMultipliers.begin(), wheelMultipliers.end());
double min = *min_element(wheelMultipliers.begin(), wheelMultipliers.end());
double absoluteMax;
if (abs(max)>abs(min) )
{
absoluteMax = abs(max);
}
else
{
absoluteMax = abs(min);
}
std::vector<double> normalized;
for (int i = 0; i < input.size(); i++)
{
normalized.push_back(input.at(i) / absoluteMax);
}
return normalized
}
*/

std::array<double, 2> rotate(double angle, std::array<double, 2> vector)
{
	std::array<double, 2> rotated;
	rotated[0] = (vector.at(0)*cos(angle) - vector.at(1)*sin(angle));
	rotated[1] = (vector.at(0)*sin(angle) + vector.at(1)*cos(angle));
	return rotated;
}
double normalizeAngle(double angle) //normalizes between -pi and pi
{
	angle = angle - floor((angle + pi) / (2 * pi)) * 2 * pi;
	return angle;
}
double leastDistantAngleWithinHalfPi(double currentAngle, double targetAngle, bool &reverse)
{
	double normalizedDiff = normalizeAngle(targetAngle) - normalizeAngle(currentAngle);
	double withinPi = (abs(normalizedDiff) < pi) ? normalizedDiff : (normalizedDiff - (2 * pi*((normalizedDiff > 0) ? 1 : ((normalizedDiff < 0) ? -1 : 0))));
	double withinHalfPi;
	if (abs(withinPi) < (pi / 2))
	{
		withinHalfPi = currentAngle + withinPi;
		reverse = false;
	}
	else
	{
		withinHalfPi = currentAngle + ((pi - abs(withinPi)) * ((withinPi > 0) ? 1 : ((withinPi < 0) ? -1 : 0))*(-1));
		reverse = true;
	}
	double withinHalfPi = currentAngle + (abs(withinPi) < (pi / 2)) ? withinPi : ((pi - abs(withinPi)) * ((withinPi > 0) ? 1 : ((withinPi < 0) ? -1 : 0))*(-1));
	return withinHalfPi;
}
double leastDistantAngleWithinPi(double currentAngle, double targetAngle)
{
	double normalizedDiff = normalizeAngle(targetAngle) - normalizeAngle(currentAngle);
	double withinPi = (abs(normalizedDiff) < pi) ? normalizedDiff : (normalizedDiff - (2 * pi*((normalizedDiff > 0) ? 1 : ((normalizedDiff < 0) ? -1 : 0))));
	return withinPi;
}
double coerce(double value, double lowerBound, double upperBound)
{
	return (value<lowerBound) ? lowerBound : (value>upperBound) ? upperBound : value;
}