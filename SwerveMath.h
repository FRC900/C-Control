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
	
	#define WHEELCOUNT 4
	public: 		
				
		//TODO: Take another look at what is currently public, most of is could be made private or protected
		
		swerveDriveMath(std::array<Eigen::Vector2d, WHEELCOUNT> _wheelCoordinates);
		
		std::array<Eigen::Vector2d, WHEELCOUNT> wheelMultipliersXY(std::array<Eigen::Vector2d, WHEELCOUNT> wheelCoordinates, Eigen::Vector2d rotationCenter);
				
		
		std::array<Eigen::Vector2d, WHEELCOUNT> wheelSpeedsAngles(std::array<Eigen::Vector2d, WHEELCOUNT> wheelMultipliersXY, Eigen::Vector2d velocityVector, double rotation, double angle); //for non field centric set angle to pi/2	
		
		std::array<double, WHEELCOUNT> parkingAngles(std::array<Eigen::Vector2d, WHEELCOUNT> wheelCoordinates); //only must be run once to determine the angles of the wheels in parking config	
		
		//Variables which need to be used externally
		std::array<double, WHEELCOUNT> parkingAngle;		
		std::array<Eigen::Vector2d, WHEELCOUNT> baseWheelMultipliersXY; //Wheel multipliers would need to be rerun if wheels somehow get moved around	
		double maximumSpeed; //M / s should this be here?
	
	

	private:
		//All variables here which don't need to be accessed externally
		std::array<Eigen::Vector2d, WHEELCOUNT> wheelCoordinates;
		std::array<double, WHEELCOUNT> normalize(std::array<double, WHEELCOUNT> input);  
		struct movement
		{
			Eigen::Vector2d translation;
			double rotation;
		};
		
		movement wheelAverage(std::array<Eigen::Vector2d, WHEELCOUNT> wheelMove, double angle, bool rotation);
}; //Why is a semicolon required here...
#endif
