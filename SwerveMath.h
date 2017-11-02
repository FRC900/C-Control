#include "stdafx.h"
#include <vector>
#include <array>
#include <cmath>
#include <math.h>
#include <stdlib.h>
#include "900Math.h"

class swerveDriveMath
{
	#define wheelCount 4
	std::array<std::array<double, 2>, wheelCount> wheelCoordinates;
	double maximumSpeed; //M / s should this be here?

	swerveDriveMath(std::array<std::array<double, 2>, wheelCount> _wheelCoordinates);

	std::array<std::array<double, 2>, wheelCount> wheelMultipliersXY(std::array<std::array<double, 2>, wheelCount> wheelCoordinates,
		std::array<double, 2> rotationCenter);
	std::array<std::array<double, 2>, wheelCount> wheelSpeedsAngles(std::array<std::array<double, 2>, wheelCount> wheelMultipliersXY,
		std::array<double, 2> velocityVector, double rotation, double angle);
	std::array<double, wheelCount> parkingAngles(std::array<std::array<double, 2>, wheelCount> wheelCoordinates);
}
;