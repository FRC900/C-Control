template <class T>
T normalize(const T& input);
std::array<double, 2> rotate(double angle, std::array<double, 2> vector);
double normalizeAngle(double angle);
double leastDistantAngleWithinHalfPi(double currentAngle, double targetAngle, bool &reverse);
double leastDistantAngleWithinPi(double currentAngle, double targetAngle);