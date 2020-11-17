#include "operator.h"

// Convert bipolar [-1,1] to unipolar [0,1], or vice versa.
double convertB2U(double _in) {
	return (_in+1)*0.5;
}

double convertU2B(double _in) {
	return _in*2-1;
}

// Scale input [_min,_max] to unipolar [0,1], or vice versa.
double scaleX2U(double _in, double _min, double _max) {
	return div(_in-_min, _max-_min);
}

double scaleU2X(double _in, double _min, double _max) {
	return _in*(_max-_min)+_min;
}

// Flip to a symmetric value. 
double flip4U(double _in) {
	return _in*-1 + 1;
}

double flip4B(double _in) {
	return _in*-1;
}

// Clip input to [_min,_max].
double clipCC(double _in, double _min, double _max) {
	return (_min<=_in&&_in<=_max) ? _in : ((_in<_min) ? _min : _max);
}

double clipOO(double _in, double _min, double _max) {
	double output = 0;

	if(PD_FLOATSIZE==32)		output = (_min<_in&&_in<_max) ? _in : ((_in<=_min) ? nextafterf(_min, _max) : nextafterf(_max, _min));
	else if(PD_FLOATSIZE==64)	output = (_min<_in&&_in<_max) ? _in : ((_in<=_min) ? nextafter(_min, _max) : nextafter(_max, _min));

	return output;
}

double clipOC(double _in, double _min, double _max) {
	double output = 0;

	if(PD_FLOATSIZE==32)		output = (_min<_in&&_in<=_max) ? _in : ((_in<=_min) ? nextafterf(_min, _max) : _max);
	else if(PD_FLOATSIZE==64)	output = (_min<_in&&_in<=_max) ? _in : ((_in<=_min) ? nextafter(_min, _max) : _max);

	return output;
}

double clipCO(double _in, double _min, double _max) {
	double output = 0;

	if(PD_FLOATSIZE==32)		output = (_min<=_in&&_in<_max) ? _in : ((_in<_min) ? _min : nextafterf(_max, _min));
	else if(PD_FLOATSIZE==64)	output = (_min<=_in&&_in<_max) ? _in : ((_in<_min) ? _min: nextafter(_max, _min));

	return output;
}

// easing function
double easeInExponent4U(double _in, double _curve) {
	return (0<_curve && _curve<1) ? pow(_in, reciprocal(1-_curve)) : ((_curve<=0) ? _in : (_in==1));
}

double easeOutExponent4U(double _in, double _curve) {
	return (0<_curve && _curve<1) ? pow(_in, 1-_curve) : ((_curve<=0) ? _in : (_in!=0));
}

double easeInOutExponent4U(double _in, double _curve) {
	double output = _in;

	if(0<_curve&&_curve<1)
	{
		if(0<=_in && _in<=0.5)		output = scaleU2X(pow(scaleX2U(_in, 0, 0.5), reciprocal(1-_curve)), 0, 0.5);
		else if(0.5<=_in && _in<=1)	output = scaleU2X(pow(scaleX2U(_in, 0.5, 1), 1-_curve), 0.5, 1);
	}
	else
	{
		output = (_curve<=0) ? _in : 0.5 + ((_in<0.5)*-0.5) + ((0.5<_in)*0.5);
	}

	return output;
}

double easeOutInExponent4U(double _in, double _curve) {
	double output = _in;

	if(0<_curve&&_curve<1)
	{
		if(0<=_in && _in<0.5)		output = scaleU2X(pow(scaleX2U(_in, 0, 0.5), 1-_curve), 0, 0.5);
		else if(0.5<_in && _in<=1)	output = scaleU2X(pow(scaleX2U(_in, 0.5, 1), reciprocal(1-_curve)), 0.5, 1);
	}
	else
	{
		output = (_curve<=0) ? _in :  0.5 + ((_in==0)*-0.5) + ((_in==1)*0.5);
	}

	return output;
}

double shiftHalf4U(double _in, double _ratio) {
	double output = _in;

	if(0<_ratio&&_ratio<1)	output = (_in<_ratio) ? scaleU2X(scaleX2U(_in, 0, _ratio), 0, 0.5) : scaleU2X(scaleX2U(_in, _ratio, 1), 0.5, 1);
	else if(_ratio<=0)		output = (_in==0) ? 0 : scaleU2X(_in, 0.5, 1);
	else					output = (_in==1) ? 1 : scaleU2X(_in, 0, 0.5);

	return output;
}

double shiftQuarter4U(double _in, double _ratio) {
	double output = _in;

	if(0<_ratio&&_ratio<1)
	{
		if(_in<0.5)		output = (_in<_ratio*0.5) ? scaleU2X(scaleX2U(_in, 0, _ratio*0.5), 0, 0.25) : scaleU2X(scaleX2U(_in, _ratio*0.5, 0.5), 0.25, 0.5);
		else			output = (_in<1-_ratio*0.5) ? scaleU2X(scaleX2U(_in, 0.5, 1-_ratio*0.5), 0.5, 0.75) : scaleU2X(scaleX2U(_in, 1-_ratio*0.5, 1), 0.75, 1);
	}
	else if(_ratio<=0)
	{
		if(_in<0.5)		output = (_in==0) ? 0 : scaleU2X(scaleX2U(_in, 0, 0.5), 0.25, 0.5);
		else			output = (_in==1) ? 1 : scaleU2X(scaleX2U(_in, 0.5, 1), 0.5, 0.75);
	}
	else
	{
		if(_in<0.5)			output = (_in==0) ? 0 : scaleU2X(_in, 0, 0.25);
		else if(0.5<_in)	output = (_in==1) ? 1 : scaleU2X(_in, 0.55, 1);
		else				output = 0.5;
	}
	
	return output;	
}

double compHalf4U(double _in, double _amount) {
	double output = 0;

	if(0<_amount&&_amount<1)
	{
		if(_in<0.5) output = (_in<0.5-(_amount*0.5)) ? scaleU2X(scaleX2U(_in, 0, 0.5-_amount*0.5), 0, 0.5) : 0.5;
		else		output = (_in<0.5+(_amount*0.5)) ? 0.5 : scaleU2X(scaleX2U(_in, 0.5+_amount*0.5, 1), 0.5, 1);
	}
	else
	{
		output = (_amount<=0) ? _in :  0.5 + ((_in==0)*-0.5) + ((_in==1)*0.5);
	}

	return output;
}

double compQuarter4U(double _in, double _amount) {
	double output = 0;

	if(0<_amount&&_amount<1)
	{
		if(_in<0.5)
		{
			if(_in<0.25-_amount*0.25)		output = scaleU2X(scaleX2U(_in, 0, 0.25-_amount*0.25), 0, 0.25);
			else if(0.25+_amount*0.25<_in)	output = scaleU2X(scaleX2U(_in, 0.25+_amount*0.25, 0.5), 0.25, 0.5);
			else							output = 0.25;
		}
		else
		{
			if(_in<0.75-_amount*0.25)		output = scaleU2X(scaleX2U(_in, 0.5, 0.75-_amount*0.25), 0.5, 0.75);
			else if(0.75+_amount*0.25<_in)	output = scaleU2X(scaleX2U(_in, 0.75+_amount*0.25, 1), 0.75, 1);
			else							output = 0.75;

		}
	}
	else
	{
		output = (_amount<=0) ? _in : (0<_in)*0.25 + (0.5<=_in)*0.5 + (1==_in)*0.25;
	}

	return output;
}

