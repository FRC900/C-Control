#include <algorithm>
#include <vector>
#include <array>
#include <cmath> // KCJ - math.h and cmath are redundant, I think
#include <math.h>
#include <stdlib.h> // KCJ - see if this is needed, if so use cstdlib

// KCJ - math.h includes M_PI constant, use that instead
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
// This is a weird way of doing templates.  I get what you're going
// for - the elements are doubles but the container type might change?
// Problem is you'll need different code to add results to the returned
// value.  For a std::array<>, space is set up already so [] works.  For 
// a vector, need to use push_back() instead. So pick one and go with
// it rather than generalizing it.

// Looks like all the calls to this assign the result back to the input
// so consider just doing the operation in place (i.e. non-const input
// and just overwrite input with the normalized values
template <class T>
T normalize(const T& input)
{
	// KCJ
	// - there are functions named min and max so naming variables min and max
	//   might cause conflicts
	double max = *std::max_element(wheelMultipliers.begin(), wheelMultipliers.end());
	double min = *std::min_element(wheelMultipliers.begin(), wheelMultipliers.end());
	double absoluteMax;

	// KCJ - use max(abs(max), abs(min) here?
	absoluteMax = (abs(max) > abs(min)) ? abs(max) : abs(min);

	T normalized;
	for (int i = 0; i < input.size(); i++)
	{
		// KCJ - instead of input.at(i), input[i] is
		// more typically used
		normalized[i] = input.at(i) / absoluteMax;
	}

	// KCJ - need return value
}

// KCJ - look at the c++ hypot() function
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

/* KCJ - 
 *   this is making me want to see a simple vector class rather than
 *   std::array<double, 2>.  rotate could be a member function of that
 *   class?  It could either just rotate the stored value or return
 *   a rotated value without modifying the input. e.g.
 *
 *   class Vector2d 
 *   {
 *   public :
 *   Vector2d(void)
 *   {
 *   x_ = 0;
 *   y_ = 0;
 *   }
 *   Vector2d(double x_in, double y_in)
 *   {
 *   x_ = x_in;
 *   y_ = y_in;
 *   }
 *
 *   void rotate(double angle) const
 *   {
 *       x = x * cos(angle) - y * sin(angle);
 *       y = x * sin(angle) + y * cos(angle);
 *   }
 *   Vector2d rotate(double angle)
 *   {
 *      Vector2d ret(*this);
 *      return ret.rotate(angle);
 *   }
 *   double X(void) const {return x_};
 *   double Y(void) const {return y_};
 *   
 *   Add other operator-like functions as necessary :
 *   operator+()
 *   operator-()
 *
 *   double hypot()
 *   double atan2()
 *
 *   and so on
 *
 *   private :
 *   double x_;
 *   double y_;
 *   };
 *
 *
 *   Other notes similar to above : use [] instead of at()
 *   */
std::array<double, 2> rotate(double angle, std::array<double, 2> vector)
{
	std::array<double, 2> rotated;
	rotated[0] = (vector.at(0)*cos(angle) - vector.at(1)*sin(angle));
	rotated[1] = (vector.at(0)*sin(angle) + vector.at(1)*cos(angle));
	return rotated;
}
double normalizeAngle(double angle) //normalizes between -pi and pi
{
	// KCJ use -= here, or better yet just return the 
	// calculated value instead of assigning it to angle
	angle = angle - floor((angle + pi) / (2 * pi)) * 2 * pi;
	return angle;
}

// KCJ - if you're returning more than 1 thing, probably best to
// return them both via reference.
// For more fun, though, create a type which has a double plus a bool
// in it.  Return that type.  
// Maybe use it for both of the leastDistant
// calls - set as is here and unconditionally set to false in the other 
// function below?  Code that uses it can query the reverse bool var
// without worring about which function it called, maybe?
double leastDistantAngleWithinHalfPi(double currentAngle, double targetAngle, bool &reverse)
{
	double normalizedDiff = normalizeAngle(targetAngle) - normalizeAngle(currentAngle);

	// KCJ - my eyes!  Do these ?: statements as if-else instead. I imagine you'll be able
	// to optimize some mulitply by 1 or 0 stuff out pretty easily after that
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
