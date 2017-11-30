#ifndef INC_THERMAL_MODEL
#define INC_THERMAL_MODEL
#include <vector>
#include <array>
#include <math.h>
#include <stdlib.h>
#include "900Math.h"
#include <Eigen/Dense>
#include "../spline-master/src/spline.h"



using namespace std;

//All temp is in Kelvin
//kelvin, joules, kg
	

class thermalModel
{
	public: //TODO: should these structs be inside or outside the class definition?	
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
	};
	struct valAndID
	{
		double val;
		double ID;
	};
		thermalModel(vector<double> _thermalCapacities, vector<vector<int>> _connectionIDs, vector<vector<double>> _viewFactors, vector<double> _emissivities, double _initialKTemp, array<vector<double>, 2> _efficiencyCurve, vector<double> _percentLossAbsorbtion, vector<double> _outsideExposureCoefficient, vector<double> _fanExposureCoefficient);	
		vector<double> temps;
		void iterModel(double dt, double current, double voltage, double rotationRate, double acceleration, double effMass, vector<valAndID> assignTemp);
	private:
		//void adjustTemp(double heat, int ID); //Not needed I think.
		vector<node> nodes;
		void distributeHeat(vector<double> heats);
		tk::spline efficiencyCurve;
		vector<double> diffuseHeat(double dt, double rotationRate);					
		vector<double> dissipateHeat(double dt);					
}; 
#endif
