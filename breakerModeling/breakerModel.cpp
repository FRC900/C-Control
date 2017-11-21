#include <iostream>
#include "breakerModel.h"

breakerModel::breakerModel(double _ratedAmp, double _n1, double _n2, double _n3, bool _useTemp = false, double _t1 = 0, double _t2 = 0, double _t3 = 0)
{
	ratedAmp= _ratedAmp;
	n1 	= _n1;
	n2	= _n2;
	n3	= _n3;
	useTemp = _useTemp;
	t1	= _t1;
	t2	= _t2;
	t3	= _t3;
	propPopped = 0;
}

iterModel(double current, double dt, double temp = 25)
{
	current/=ratedAmp;
	if(useTemp){current/=tempF(temp);}
	if(current < 1)
	{
		//TODO: make this actually work
		propPopped -= (1-current);
	}
	else
	{
		propPopped += dt/popTime(current);
	}
	return propPopped;
}

double tempF(double temp)
{
	return t1*temp*temp + t2*temp + t3;
}

double popTime(double currentF)
{
	return n1*currentF*currentF + n2*currentF + n3;
}














