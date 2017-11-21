#ifndef INC_THERMAL_MODEL
#define INC_THERMAL_MODEL
#include <vector>
#include <array>
#include <math.h>
#include <stdlib.h>
#include "900Math.h"
#include <Eigen/Dense>
#include "spline-master/src/spline.h"



using namespace std;

//All temp is in Kelvin


class thermalModel
{
	struct connection //Characteristics of a given heat flow from one node to another (should this include fan stuff?)
	{
		int ID;
		double viewFactor;
		//TODO, add all needed info here for heat transfer between motors
		
	};
	struct node //Characterisitics of a node of the thermal model
	{
		double thermalCapacity;
		vector<connection> connections;
		double emissivity;
		double lossAbsorb;
		double exposure;
		double fanExposure;
	}
	public:	
		vector<double> temps;
		void iterModel(double dt, double current, double voltage, double rotationRate);
	private:
		//void adjustTemp(double heat, int ID); //Not needed I think.
		vector<node> nodes;
		double gearboxEfficiency;
		void distributeHeat(vector<double> heats);
		tk::spline efficiencyCurve;
		vector<double> diffuseHeat(double dt);					
		vector<double> dissipateHeat(double dt);					
}; 
#endif
