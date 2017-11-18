#include <cmath>
#include <math.h>
#include "900Math.h"
#include "nextVelocity.h"
#include <iostream>

using namespace std;
double nextVelocity(double v, double vt, double &a, double am, double jm, double cr) 
{
	double diffv = vt - v;
	double signDiffV = sign(diffv);
	double signA = sign(a);
	double nV;
	bool finish;
	if(pow(a, 2)/jm >= diffv*signA) //Fix tendency to overshoot?
	{
		//overshoot
		if(abs((diffv/cr) -(a))  < jm*cr) //verify and fix
		{
			//cout<<"finish"<<endl;
			a = (diffv/cr); //if we can get to target now, do it
			finish = true;	
		}
		else
		{
			a = (a -  signA * jm * cr);
			finish = false;
			//cout<<"return from peak accel"<<endl;
		}										 
	}
	else
	{
		//upswing or flat	
		a = (a + signDiffV * jm * cr);
		if(abs(a) > am)
		{
			a = signDiffV*am;
			finish = false;
		}
		if(abs(a*cr) > abs(diffv)) //verify and fix
		{
			a = (diffv/cr); //if we can get to target now, do it
			finish = true;
		}	
	}
	nV = v + a * cr;
	if(finish) {a=0;} //TODO fix
	return nV;
}
