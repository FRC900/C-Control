#include <cmath>
#include <math.h>
#include "900Math.h"
#include "nextVelocity.h"
#include <iostream>

using namespace std;
double nextVelocity(double v, double vt, double &a, double am, double jm, double cr) 
{
	double diffv = vt - v;
	double z = sign(diffv);
	double g = sign(a);
	double nV;
	if(pow(a, 2)/jm >= diffv*g) //Fix tendency to overshoot?
	{
		//overshoot
		if(abs((diffv/cr) -(a))  < jm*cr) //verify and fix
		{
			//cout<<"finish"<<endl;
			a = (diffv/cr); //if we can get to target now, do it
		}
		else
		{
			a = (a -  g * jm * cr);
			//cout<<"return from peak accel"<<endl;
		}										 
	}
	else
	{
		//upswing or flat	
		a = (a + z * jm * cr);
		if(abs(a) > am)
		{
			a = z*am;
		}
		if(abs(a*cr) > abs(diffv)) //verify and fix
		{
			a = (diffv/cr); //if we can get to target now, do it
		}	
	}
	nV = v + a * cr;
	return nV;
}
