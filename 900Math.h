#ifndef INC_900_MATH
#define INC_900_MATH
#include <array>

//template <class T>
//T normalize(const T& input);
//std::array<double, 2> rotate(double angle, std::array<double, 2> vector);
double leastDistantAngleWithinHalfPi(double currentAngle, double targetAngle, bool &reverse);
double normalizeAngle(double angle);
double leastDistantAngleWithinPi(double currentAngle, double targetAngle);
double coerce(double value, double lowerBound, double upperBound);
/*
template <class T>
T normalize(const T& input)
{

	// KCJ
	// - there are functions named min and max so naming variables min and max
	//   might cause conflicts
	double maxV = *std::max_element(input.begin(), input.end());
	double minV = *std::min_element(input.begin(), input.end());
	double absoluteMax;

	// KCJ - use max(abs(max), abs(min) here?
	absoluteMax = std::max(abs(maxV), abs(minV));

	T normalized;
	for (size_t i = 0; i < input.size(); i++)
	{
		normalized[i] = input[i] / absoluteMax;
	}

	return normalized;

}
*/



#endif
