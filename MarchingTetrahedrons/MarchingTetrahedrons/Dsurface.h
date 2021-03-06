#ifndef DSURFACE_H
#define DSURFACE_H

#include "Isosurface.h"
#include "math3D.h"

class Dsurface : public Isosurface
{

public:
	virtual float valueAt(float x, float y, float z) const
	{
		return 1.5*(cosf(2 * PI*x)*cosf(2 * PI*y)*cosf(2 * PI*z) - sinf(2 * PI*x)*sinf(2 * PI*y)*sinf(2 * PI*z));
	};
	virtual Vector3D gradientAt(float x, float y, float z) const
	{
		float gx = -sinf(2 * PI*x)*cosf(2 * PI*y)*cosf(2 * PI*z) - cosf(2 * PI*x)*sinf(2 * PI*y)*sinf(2 * PI*z);
		float gy = -sinf(2 * PI*y)*cosf(2 * PI*x)*cosf(2 * PI*z) - cosf(2 * PI*y)*sinf(2 * PI*x)*sinf(2 * PI*z);
		float gz = -sinf(2 * PI*z)*cosf(2 * PI*x)*cosf(2 * PI*y) - cosf(2 * PI*z)*sinf(2 * PI*x)*sinf(2 * PI*y);

		Vector3D result = { gx, gy, gz };
		normalize(result);

		return result;
	};

};

#endif