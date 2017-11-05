#ifndef INC_SWERVE_MATH
#define INC_SWERVE_MATH
#include <vector>
#include <array>
#include <math.h>
#include <stdlib.h>
#include "900Math.h"
#include <Eigen/Dense>

class swerveDriveMath
{
	public: 		
				
		#define WHEELCOUNT 4
		
		swerveDriveMath::swerveDriveMath(std::array<std::array<double, 2>, WHEELCOUNT> _wheelCoordinates);
		std::array<std::array<double, 2>, WHEELCOUNT> swerveDriveMath::wheelMultipliersXY(std::array<std::array<double, 2>, WHEELCOUNT> wheelCoordinates, std::array<double, 2> rotationCenter);
				
		
		std::array<std::array<double, 2>, WHEELCOUNT> swerveDriveMath::wheelSpeedsAngles(std::array<std::array<double, 2>, WHEELCOUNT> wheelMultipliersXY,
		std::array<double, 2> velocityVector, double rotation, double angle); //for non field centric set angle to pi/2	
		std::array<double, WHEELCOUNT> swerveDriveMath::parkingAngles(std::array<std::array<double, 2>, WHEELCOUNT> wheelCoordinates); //only must be run once to determine the angles of the wheels in parking config	
		
		//Variables which need to be used externally
		std::array<double, WHEELCOUNT> parkingAngle;		
		std::array<std::array<double, 2>, WHEELCOUNT> baseWheelMultipliersXY; //Wheel multipliers would need to be rerun if wheels somehow get moved around	
		double maximumSpeed; //M / s should this be here?
	
	private:
		//All variables here which don't need to be accessed externally
		std::array<std::array<double, 2>, _WHEELCOUNT> wheelCoordinates; 
}; //Why is a semicolon required here...
#endif
