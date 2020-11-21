// Copyright (c) 2020 xin.

#ifndef _OPERATOR_H_
#define _OPERATOR_H_

/***** start of definition *******************************************************/

#include <math.h>
#include <float.h>
#include <limits.h>

#if (PDFLAG==1) || (PDFLAG==2)
#   include <m_pd.h>
#   define FMAX         FLT_MAX
#   define FMIN         FlT_MIN
#   define SIN          sinf
#   define COS          cosf
#   define TAN          tanf
#   define FMOD         fmodf
#   define POW          powf
#   define FLOOR        floorf
#   define NEXTAFTER    nextafterf
#   if PDFLAG==1
#       define FTYPE    t_float
#   else
#       define FTYPE    t_sample
#   endif
#else
#   define FTYPE        double
#   define FMAX         DBL_MAX
#   define FMIN         DBL_MIN
#endif

/***** constant ******************************************************************/

#define PI          3.141592653589793
#define TWOPI       6.283185307179586
#define HALFPI      1.570796326794897
#define INVPI       0.318309886183791
#define DEGTORAD    0.017453292519943
#define RADTODEG    57.29577951308232
#define E           2.718281828459045
#define LN10        2.302585092994046
#define LN2         0.693147180559945
#define LOG10E      0.434294481903252
#define LOG2E       1.442695040888963
#define SQRT2       1.414213562373095
#define INVSQRT2    0.707106781186548
#define GRATIO      1.618033988749895
#define SRATIO      2.414213562373095
#define BRATIO      3.302775637731995

/***** function prototype ********************************************************/

FTYPE add(FTYPE _v1, FTYPE _v2);
FTYPE sub(FTYPE _v1, FTYPE _v2);
FTYPE mul(FTYPE _v1, FTYPE _v2);
FTYPE div(FTYPE _v1, FTYPE _v2);
FTYPE modulo(FTYPE _v1, FTYPE _v2);
FTYPE meanA(FTYPE *_x, int _len);
FTYPE meanG(FTYPE *_x, int _len);
FTYPE meanH(FTYPE *_x, int _len);
int sign(FTYPE _in);
FTYPE reciprocal(FTYPE _in);
FTYPE sine(FTYPE _x);
FTYPE cosine(FTYPE _x);
FTYPE tangent(FTYPE _x);
FTYPE cosecant(FTYPE _x);
FTYPE secant(FTYPE _x);
FTYPE cotangent(FTYPE _x);
FTYPE roundFloor(FTYPE _x, FTYPE _base);

FTYPE convertB2U(FTYPE _in);
FTYPE convertU2B(FTYPE _in);
FTYPE scaleX2U(FTYPE _in, FTYPE _min, FTYPE _max);
FTYPE scaleU2X(FTYPE _in, FTYPE _min, FTYPE _max);
FTYPE flip4U(FTYPE _in);
FTYPE flip4B(FTYPE _in);

FTYPE clipCC(FTYPE _in, FTYPE _min, FTYPE _max);
FTYPE clipOO(FTYPE _in, FTYPE _min, FTYPE _max);
FTYPE clipOC(FTYPE _in, FTYPE _min, FTYPE _max);
FTYPE clipCO(FTYPE _in, FTYPE _min, FTYPE _max);

FTYPE easeInExponent4U(FTYPE _in, FTYPE _curve);
FTYPE easeOutExponent4U(FTYPE _in, FTYPE _curve);
FTYPE easeInOutExponent4U(FTYPE _in, FTYPE _curve);
FTYPE easeOutInExponent4U(FTYPE _in, FTYPE _curve);
FTYPE easeInInExponent4U(FTYPE _in, FTYPE _curve);
FTYPE easeOutOutExponent4U(FTYPE _in, FTYPE _curve);

FTYPE shiftHalf4U(FTYPE _in, FTYPE _ratio);
FTYPE shiftQuarter4U(FTYPE _in, FTYPE _ratio);
FTYPE compHalf4U(FTYPE _in, FTYPE _amount);
FTYPE compQuarter4U(FTYPE _in, FTYPE _amount);
FTYPE phaseTriangle(FTYPE _in);
FTYPE reduceQuantum4U(FTYPE _in, int _quantum);

FTYPE linearInterpolation(FTYPE _in1, FTYPE _in2, FTYPE _weight);

/***** function - arithmetic *****************************************************/

inline FTYPE add(FTYPE _v1, FTYPE _v2) {
    return _v1 + _v2;
}

inline FTYPE sub(FTYPE _v1, FTYPE _v2) {
    return _v1 - _v2;
}

inline FTYPE mul(FTYPE _v1, FTYPE _v2) {
    return _v1 * _v2;
}

inline FTYPE div(FTYPE _v1, FTYPE _v2) {
    return (_v2!=0) ? _v1/_v2 : FMAX;
}

inline FTYPE modulo(FTYPE _v1, FTYPE _v2) {
    return (_v2!=0) ? FMOD(_v1, _v2) : 0;
}

inline int sign(FTYPE _in) {
    return (_in==0) ? 0 : ((_in>0) ? 1 : -1);
}

inline FTYPE reciprocal(FTYPE _in) {
    return div(1, _in);
}

inline FTYPE meanA(FTYPE *_x, int _len) {
    FTYPE value = *_x;
    for(int i=1; i<_len; i++) value += *(_x+i);
    return value / _len;
}

inline FTYPE meanG(FTYPE *_x, int _len) {
    FTYPE value = *_x;
    for(int i=1; i<_len; i++) value *= *(_x+i);
    return POW(value, 1/_len);
}

inline FTYPE meanH(FTYPE *_x, int _len) {
    FTYPE value = reciprocal(*_x);
    for(int i=1; i<_len; i++) value += reciprocal(*(_x+1));
    return reciprocal(value/_len);
}

inline FTYPE sine(FTYPE _x) {
    return (_x==0.5||_x==1) ? 0 : SIN(_x*TWOPI);
}

inline FTYPE cosine(FTYPE _x) {
    return (_x==0.25||_x==0.75) ? 0 : COS(_x*TWOPI);
}

inline FTYPE tangent(FTYPE _x) {
    return (_x==0.25||_x==0.75) ? FMAX : ((_x==0.5||_x==1) ? 0 : TAN(_x*TWOPI));
}

inline FTYPE cosecant(FTYPE _x) {
    return reciprocal(sine(_x));
}

inline FTYPE secant(FTYPE _x) {
    return reciprocal(cosine(_x));
}

inline FTYPE cotangent(FTYPE _x) {
    return reciprocal(tangent(_x));
}

inline FTYPE roundFloor(FTYPE _x, FTYPE _base) {
    return FLOOR(_x*reciprocal(_base)) * _base;
}

/***** function - bipolar and unipolar operation *********************************/

inline FTYPE convertB2U(FTYPE _in) {
    return (_in+1)*0.5;
}

inline FTYPE convertU2B(FTYPE _in) {
    return _in*2-1;
}

inline FTYPE scaleX2U(FTYPE _in, FTYPE _min, FTYPE _max) {
    return div(_in-_min, _max-_min);
}

inline FTYPE scaleU2X(FTYPE _in, FTYPE _min, FTYPE _max) {
    return _in*(_max-_min)+_min;
}

inline FTYPE flip4U(FTYPE _in) {
    return _in*-1 + 1;
}

inline FTYPE flip4B(FTYPE _in) {
    return _in*-1;
}

/***** function - clipper ********************************************************/

inline FTYPE clipCC(FTYPE _in, FTYPE _min, FTYPE _max) {
    return (_min<=_in&&_in<=_max) ? _in : ((_in<_min) ? _min : _max);
}

inline FTYPE clipOO(FTYPE _in, FTYPE _min, FTYPE _max) {
    return (_min<_in&&_in<_max) ? _in : ((_in<=_min) ? NEXTAFTER(_min, _max) : NEXTAFTER(_max, _min));
}

inline FTYPE clipOC(FTYPE _in, FTYPE _min, FTYPE _max) {
    return (_min<_in&&_in<=_max) ? _in : ((_in<=_min) ? NEXTAFTER(_min, _max) : _max);
}

inline FTYPE clipCO(FTYPE _in, FTYPE _min, FTYPE _max) {
    return (_min<=_in&&_in<_max) ? _in : ((_in<_min) ? _min : NEXTAFTER(_max, _min));
}

/***** function - shaping or easing functions for phasor *************************/

inline FTYPE easeInExponent4U(FTYPE _in, FTYPE _curve) {
    return (0<_curve && _curve<1) ? POW(_in, reciprocal(1-_curve)) : ((_curve<=0) ? _in : (_in==1));
}

inline FTYPE easeOutExponent4U(FTYPE _in, FTYPE _curve) {
    return (0<_curve && _curve<1) ? POW(_in, 1-_curve) : ((_curve<=0) ? _in : (_in!=0));
}

inline FTYPE easeInOutExponent4U(FTYPE _in, FTYPE _curve) {
    FTYPE output = _in;

    if(0<_curve&&_curve<1)
    {
        if(0<=_in && _in<=0.5)      output = scaleU2X(POW(scaleX2U(_in, 0, 0.5), reciprocal(1-_curve)), 0, 0.5);
        else if(0.5<=_in && _in<=1) output = scaleU2X(POW(scaleX2U(_in, 0.5, 1), 1-_curve), 0.5, 1);
    }
    else
    {
        output = (_curve<=0) ? _in : 0.5 + ((_in<0.5)*-0.5) + ((0.5<_in)*0.5);
    }

    return output;
}

inline FTYPE easeOutInExponent4U(FTYPE _in, FTYPE _curve) {
    FTYPE output = _in;

    if(0<_curve&&_curve<1)
    {
        if(0<=_in && _in<0.5)       output = scaleU2X(POW(scaleX2U(_in, 0, 0.5), 1-_curve), 0, 0.5);
        else if(0.5<_in && _in<=1)  output = scaleU2X(POW(scaleX2U(_in, 0.5, 1), reciprocal(1-_curve)), 0.5, 1);
    }
    else
    {
        output = (_curve<=0) ? _in :  0.5 + ((_in==0)*-0.5) + ((_in==1)*0.5);
    }

    return output;
}

inline FTYPE easeInInExponent4U(FTYPE _in, FTYPE _curve) {
    FTYPE output = _in;

    if(0<_curve&&_curve<1)
    {
        if(0<=_in && _in<=0.5)      output = scaleU2X(POW(scaleX2U(_in, 0, 0.5), reciprocal(1-_curve)), 0, 0.5);
        else if(0.5<=_in && _in<=1) output = scaleU2X(POW(scaleX2U(_in, 0.5, 1), reciprocal(1-_curve)), 0.5, 1);
    }
    else
    {
        output = (_curve<=0) ? _in : 0.5 + ((_in<0.5)*-0.5) + ((0.5<_in)*0.5);
    }

    return output;
}

inline FTYPE easeOutOutExponent4U(FTYPE _in, FTYPE _curve) {
    FTYPE output = _in;

    if(0<_curve&&_curve<1)
    {
        if(0<=_in && _in<0.5)       output = scaleU2X(POW(scaleX2U(_in, 0, 0.5), 1-_curve), 0, 0.5);
        else if(0.5<_in && _in<=1)  output = scaleU2X(POW(scaleX2U(_in, 0.5, 1), 1-_curve), 0.5, 1);
    }
    else
    {
        output = (_curve<=0) ? _in :  0.5 + ((_in==0)*-0.5) + ((_in==1)*0.5);
    }

    return output;
}

inline FTYPE shiftHalf4U(FTYPE _in, FTYPE _ratio) {
    FTYPE output = _in;

    if(0<_ratio&&_ratio<1)  output = (_in<_ratio) ? scaleU2X(scaleX2U(_in, 0, _ratio), 0, 0.5) : scaleU2X(scaleX2U(_in, _ratio, 1), 0.5, 1);
    else if(_ratio<=0)      output = (_in==0) ? 0 : scaleU2X(_in, 0.5, 1);
    else                    output = (_in==1) ? 1 : scaleU2X(_in, 0, 0.5);

    return output;
}

inline FTYPE shiftQuarter4U(FTYPE _in, FTYPE _ratio) {
    FTYPE output = _in;

    if(0<_ratio&&_ratio<1)
    {
        if(_in<0.5)         output = (_in<_ratio*0.5) ? scaleU2X(scaleX2U(_in, 0, _ratio*0.5), 0, 0.25) : scaleU2X(scaleX2U(_in, _ratio*0.5, 0.5), 0.25, 0.5);
        else                output = (_in<1-_ratio*0.5) ? scaleU2X(scaleX2U(_in, 0.5, 1-_ratio*0.5), 0.5, 0.75) : scaleU2X(scaleX2U(_in, 1-_ratio*0.5, 1), 0.75, 1);
    }
    else if(_ratio<=0)
    {
        if(_in<0.5)         output = (_in==0) ? 0 : scaleU2X(scaleX2U(_in, 0, 0.5), 0.25, 0.5);
        else                output = (_in==1) ? 1 : scaleU2X(scaleX2U(_in, 0.5, 1), 0.5, 0.75);
    }
    else
    {
        if(_in<0.5)         output = (_in==0) ? 0 : scaleU2X(_in, 0, 0.25);
        else if(0.5<_in)    output = (_in==1) ? 1 : scaleU2X(_in, 0.55, 1);
        else                output = 0.5;
    }
    
    return output;	
}

inline FTYPE compHalf4U(FTYPE _in, FTYPE _amount) {
    FTYPE output = 0;

    if(0<_amount&&_amount<1)
    {
        if(_in<0.5) output = (_in<0.5-(_amount*0.5)) ? scaleU2X(scaleX2U(_in, 0, 0.5-_amount*0.5), 0, 0.5) : 0.5;
        else        output = (_in<0.5+(_amount*0.5)) ? 0.5 : scaleU2X(scaleX2U(_in, 0.5+_amount*0.5, 1), 0.5, 1);
    }
    else
    {
        output = (_amount<=0) ? _in :  0.5 + ((_in==0)*-0.5) + ((_in==1)*0.5);
    }

    return output;
}

inline FTYPE compQuarter4U(FTYPE _in, FTYPE _amount) {
    FTYPE output = 0;

    if(0<_amount&&_amount<1)
    {
        if(_in<0.5)
        {
            if(_in<0.25-_amount*0.25)       output = scaleU2X(scaleX2U(_in, 0, 0.25-_amount*0.25), 0, 0.25);
            else if(0.25+_amount*0.25<_in)  output = scaleU2X(scaleX2U(_in, 0.25+_amount*0.25, 0.5), 0.25, 0.5);
            else                            output = 0.25;
        }
        else
        {
            if(_in<0.75-_amount*0.25)       output = scaleU2X(scaleX2U(_in, 0.5, 0.75-_amount*0.25), 0.5, 0.75);
            else if(0.75+_amount*0.25<_in)  output = scaleU2X(scaleX2U(_in, 0.75+_amount*0.25, 1), 0.75, 1);
            else                            output = 0.75;
        }
    }
    else
    {
        output = (_amount<=0) ? _in : (0<_in)*0.25 + (0.5<=_in)*0.5 + (1==_in)*0.25;
    }

    return output;
}

inline FTYPE phaseTriangle(FTYPE _in) {
    return (_in*2<=1) ? _in*2 : flip4U(_in*2-1);
}

inline FTYPE reduceQuantum4U(FTYPE _in, int _quantum) {
    return roundFloor(_in, reciprocal(_quantum)) * reciprocal(1-reciprocal(_quantum));
}


inline FTYPE linearInterpolation(FTYPE _in1, FTYPE _in2, FTYPE _weight) {
    return _in1*(1-_weight) + _in2*_weight;
}

/***** end of definition *********************************************************/

#endif