#ifndef _OPERATOR_H_
#define _OPERATOR_H_

#include <m_pd.h>
#include <math.h>
#include "arithmetic.h"

double convertB2U(double _in);
double convertU2B(double _in);
double scaleX2U(double _in, double _min, double _max);
double scaleU2X(double _in, double _min, double _max);

double flip4U(double _in);
double flip4B(double _in);

double clipCC(double _in, double _min, double _max);
double clipOO(double _in, double _min, double _max);
double clipOC(double _in, double _min, double _max);
double clipCO(double _in, double _min, double _max);

double easeInExponent4U(double _in, double _curve);
double easeOutExponent4U(double _in, double _curve);
double easeInOutExponent4U(double _in, double _curve);
double easeOutInExponent4U(double _in, double _curve);

double shiftHalf4U(double _in, double _ratio);
double shiftQuarter4U(double _in, double _ratio);
double compHalf4U(double _in, double _amount);
double compQuarter4U(double _in, double _amount);

#endif