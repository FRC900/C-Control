#include <vector>
#include <iostream>
#include "thermalModel.h"
#include "../spline-master/src/spline.h"
#include <cstdio>
#include <cstdlib>

using namespace std;
//TODO: RK4
//kelvin, joules, kg
//Maybe instead of having the heat interchanges set up like they are now, just a coeffecient * (t1 - t2)
//The above coeffecient would need to change substantially with rotor speed if there is a fan
thermalModel::thermalModel(vector<double> _thermalCapacities, vector<vector<int>> _connectionIDs, vector<vector<double>> _viewFactors, vector<double> _emissivities, double _initialKTemp, array<vector<double>, 2> _efficiencyCurve, vector<double> _percentLossAbsorbtion, vector<double> _outsideExposureCoefficient, vector<double> _fanExposureCoefficient)
{
	for(int i = 0; i < _thermalCapacities.size(); i++)
	{
		node newNode;
		newNode.thermalCapacity = _thermalCapacities.at(i);	
		newNode.emissivity	= _emissivities.at(i)
		newNode.lossAbsorb 	= _percentLossAbsorbtion.at(i);
		newNode.exposure        = _outsideExposureCoefficient.at(i);
		newNode.fanExposure     = _fanExposureCoefficient.at(i);
		
		
		for(int j = 0; j < _connectionIDs.at(i).size(); j++)
		{
			connection newConnec;
			newConnec.ID 		= _connectionIDs.at(i).at(j);
			newConnec.viewFactor    = _viewFactors.at(i).at(j);
			newNode.connections.push_back(newConnec);
		}
		nodes.push_back(newNode); 	//Add node	
		
		temps.push_back(intialKTemp);	//Set node temp
	}
	
	gearboxEfficiency = _gearboxEfficiency;
	efficiencyCurve.set_points(_efficiencyCurve[0], _efficiencyCurve[1]); //Not used right now
}
void thermalModel::iterModel(double dt, double current, double voltage, double rotationRate, double acceleration, double effMass, vector<valAndID> assignTemp)
{
	//this operation and every suboperation needs to be highly efficient, run time critical
	
	vector<double> heatAdd;
	heatAdd = diffuseTemp();
	double totalLoss = dt*(abs(voltage)*current - rotationRate*acceleration*effMass); //TODO: check this/improve
	//note that the above shouldn't be negative, if it was that would be >100% effeciency
	for(int i  = 0; i < nodes.size(); i++)
	{
		heatAdd.at(i) += node.at(i).lossAbsorb*totalLoss; //Add heat from power losses
		//Take into account inertia and store it as heat for bookkeeping? There is probably a better way but still.
	} 
	distributeHeat(dissipateHeat(dt, rotationRate));		
	distributeHeat(heatAdd(dt)); 
	//assign temp should only be used if there are temp sensors
	for(int i = 0; i < assignTemp.size(); i++)
	{
		temps.at(assignTemp.at(i).ID) = assignTemp.at(i).val;
	}
}
vector<double> thermalModel::diffuseHeat(double dt);
{
	//Uses temps and nodes.at(i).connections to diffuse. Returns delta heat.
	//Run time critical


}
//Should this even be a separate function from diffuse heat?
//for separate:
//pros: runtime (maybe), might be fundamentally different if only this function uses the fan stuff
//cons: more code, clarity
vector<double> thermalModel::dissipateHeat(double dt, double rotationRate)
{
	//Uses temps and nodes.at(i).exposure and nodes.at(i).fanExposure to dissipate heat. Returns delta heat.
	//Run time critical
}
void thermalModel::distributeHeat(vector<double> &heats)
{
	for(int i = 0; i < heats.size(); i++)
	{
		temps.at(i) += heats.at(i) / nodes.at(i).thermalCapacity	
	}
	//Run time critical
}
