#ifndef _ARITHMETIC_H_
#define _ARITHMETIC_H_

#include <m_pd.h>
#include <math.h>
#include <float.h>

#define PI			3.141592653589793
#define TWOPI		6.283185307179586
#define HALFPI		1.570796326794897
#define INVPI		0.318309886183791
#define DEGTORAD	0.017453292519943
#define RADTODEG	57.29577951308232
#define E			2.718281828459045
#define LN10		2.302585092994046
#define LN2			0.693147180559945
#define LOG10E		0.434294481903252
#define LOG2E		1.442695040888963
#define SQRT2		1.414213562373095
#define INVSQRT2	0.707106781186548

#if PD_FLOATSIZE == 32
# define FMAX		FLT_MAX
# define FMIN		FlT_MIN
#elif PD_FLOATSIZE == 64
# define FMAX		DBL_MAX
# define FMIN		DBL_MIN
#endif

double add(double _v1, double _v2);
double sub(double _v1, double _v2);
double mul(double _v1, double _v2);
double div(double _v1, double _v2);
double mod(double _v1, double _v2);
double meanA(double *_x, int _len);
double meanG(double *_x, int _len);
double meanH(double *_x, int _len);
int sign(double _in);
double reciprocal(double _in);
double sine(double _x);
double cosine(double _x);
double tangent(double _x);
double cosecant(double _x);
double secant(double _x);
double cotangent(double _x);

#endif