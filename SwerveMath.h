const int wheelCount;
std::array<std::array<double, 2>, wheelCount> wheelMultipliersXY(std::array<std::array<double, 2>, wheelCount> wheelCoordinates,
	std::array<double, 2> rotationCenter = { 0, 0 });
std::array<std::array<double, 2>, wheelCount> wheelSpeedsAngles(std::array<std::array<double, 2>, wheelCount> wheelMultipliersXY,
	std::array<double, 2> velocityVector, double rotation, double angle);
std::array<double> parkingAngles(std::array<std::array<double, 2>, wheelCount> wheelCoordinates);