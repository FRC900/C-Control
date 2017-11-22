#include <iostream>
#include "breakerModel.h"
#include <math.h>
#include <array>
#include <vector>
using namespace std;
//All temps in C
breakerModel::breakerModel(double _ratedCurrent, double _tempThresh, double _elecResis, double _initialTemp, vector<array<double, 2>> _targetData)
{

	bTemp = _initialTemp;
	elecResis = _elecResis;
	thermCond = (_ratedCurrent*_ratedCurrent*_elecResis)/(_tempThresh - ROOMTEMP); //complicated 
	tempThresh = _tempThresh;	
	//heatCapacity = _heatCapacity;
	//consider switching below to LSE
	//For below calculations initial temp is assumed to be equal to ambient temp
	double totalForAvg = 0;
	for(int i = 0; i < _targetData.size(); i++)
	{
		double I = _targetData[i][0];
		double t = _targetData[i][1];
		totalForAvg+=-log(1 - (_tempThresh - ROOMTEMP)/(I*I*elecResis/thermCond))/(thermCond*t); 
	}
	heatCapacity =  totalForAvg / _targetData.size();
	//cout<<heatCapacity<<endl;
	//cout<<thermCond<<endl;
}

bool breakerModel::iterModel(double current, double dt, double temp)
{
	//std::cout<<"elecR:"<<elecResis<<std::endl;	
	//std::cout<<"thermCond:"<<thermCond<<std::endl;
	//std::cout<<"heat capacity:"<<heatCapacity<<std::endl;
	bTemp += dt*heatCapacity*(current*current*elecResis-thermCond*(bTemp - temp));
	//std::cout<<"temp:"<<bTemp<<std::endl;
	if(bTemp>=tempThresh){return true;}
	else{return false;}
}

