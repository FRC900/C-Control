#include math.c


double nextVelocity(double v, double vt, double a, double am, double jm) 
{
	double diffv = vt - v;
	double z = sign(diffv);
	double nV;
	if(a^2/jm > diffv*sign(a))
	{
		//overshoot
		nV = v + (a - z * jm)
		return nv

	}
	
	else
	{
		if(sqrt((a^2+2*jm*abs(diffv))/2)>am)
		{	
			//flat
	

		}	
		else
		{

			//triangle

		}
	} 
}
double simpleNextVelocity	
	if(sqrt((a^2+2*jm*abs(diffv))/2)>am)
	{
		//flat
	}
	else
	{
		//triangle
	}
