#include math.c


double nextVelocity(double v, double vt, double &a, double am, double jm, double cr) 
{
	double diffv = vt - v;
	double z = sign(diffv);
	double g = sign(a);
	double nV;
	if(a^2/jm => diffv*g) //Fix tendency to overshoot?
	{
		//overshoot
		if(abs(diffv/cr) - abs(a) < jm*cr) //verify and fix
		{
			a = (diffv/cr); //if we can get to target now, do it
		}
		else
		{
			a = (a - z * jm * cr);
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
		if(abs(tempA*cr) > abs(diffv)) //verify and fix
		{
			a = (diffv/cr); //if we can get to target now, do it
		}	
	}
	nV = v + a * cr;
	return nV;
}
//double simpleNextVelocity	
//	if(sqrt((a^2+2*jm*abs(diffv))/2)>am)
//	{
		//flat
//	}
//	else
//	{
		//triangle
//	}
