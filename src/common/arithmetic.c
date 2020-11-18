#include "arithmetic.h"

// basic

double add(double _v1, double _v2) {
	return _v1 + _v2;
}

double sub(double _v1, double _v2) {
	return _v1 - _v2;
}

double mul(double _v1, double _v2) {
	return _v1 * _v2;
}

double div(double _v1, double _v2) {
	return (_v2!=0) ? _v1/_v2 : FMAX;
}

double modulo(double _v1, double _v2) {
	return (_v2!=0) ? fmod(_v1, _v2) : 0;
}

int sign(double _in) {
	return (_in==0) ? 0 : ((_in>0) ? 1 : -1);
}

double reciprocal(double _in) {
	return div(1, _in);
}

// average

double meanA(double *_x, int _len) {
	double value = *_x;
	for(int i=1; i<_len; i++)	value += *(_x+i);
	return value / _len;
}

double meanG(double *_x, int _len) {
	double value = *_x;
	for(int i=1; i<_len; i++)	value *= *(_x+i);
	return pow(value, 1/_len);
}

double meanH(double *_x, int _len) {
	double value = reciprocal(*_x);
	for(int i=1; i<_len; i++)	value += reciprocal(*(_x+1));
	return reciprocal(value/_len);
}

// trigonometric

double sine(double _x) {
	return (_x==0.5||_x==1) ? 0 :  sin(_x*TWOPI);
}

double cosine(double _x) {
	return (_x==0.25||_x==0.75) ? 0 : cos(_x*TWOPI);
}

double tangent(double _x) {
	return (_x==0.25||_x==0.75) ? FMAX : ((_x==0.5||_x==1) ? 0 : tan(_x*TWOPI));
}

double cosecant(double _x) {
	return reciprocal(sine(_x));
}

double secant(double _x) {
	return reciprocal(cosine(_x));
}

double cotangent(double _x) {
	return reciprocal(tangent(_x));
}

