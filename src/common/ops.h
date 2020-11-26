// Copyright (c) 2020 xin.

#ifndef _OPS_H_
#define _OPS_H_

/***** include ********************************************************************************************************/

#include <math.h>
#include <float.h>
#include <limits.h>
#include <m_pd.h>

/***** type ***********************************************************************************************************/

#if PDFLAG==0
#   define FTYPE    t_float
#else
#   define FTYPE    t_sample
#endif

/***** 32/64 **********************************************************************************************************/

#if PD_FLOATSIZE == 32
#   define FMAX        FLT_MAX
#   define FMIN        FlT_MIN
#   define SIN         sinf
#   define COS         cosf
#   define TAN         tanf
#   define ASIN        asinf
#   define ACOS        acosf
#   define ATAN        atanf
#   define ATAN2       atan2f
#   define SINH        sinhf
#   define COSH        coshf
#   define TANH        tanhf
#   define ASINH       asinhf
#   define ACOSH       acoshf
#   define ATANH       atanhf
#   define LOG         logf
#   define LOG10       log10f
#   define LOG2        log2f
#   define EXP         expf
#   define POW         powf
#   define SQRT        sqrtf
#   define FABS        fabsf
#   define CEIL        ceilf
#   define FLOOR       floorf
#   define ROUND       roundf
#   define TRUNC       truncf
#   define FMOD        fmodf
#   define NEXTAFTER   nextafterf
#elif PD_FLOATSIZE == 64
#   define FMAX        DBL_MAX
#   define FMIN        DBL_MIN
#   define SIN         sin
#   define COS         cos
#   define TAN         tan
#   define ASIN        asin
#   define ACOS        acos
#   define ATAN        atan
#   define ATAN2       atan2
#   define SINH        sinh
#   define COSH        cosh
#   define TANH        tanh
#   define ASINH       asinh
#   define ACOSH       acosh
#   define ATANH       atanh
#   define LOG         log
#   define LOG10       log10
#   define LOG2        log2
#   define EXP         exp
#   define POW         pow
#   define SQRT        sqrt
#   define FABS        fabs
#   define CEIL        ceil
#   define FLOOR       floor
#   define ROUND       round
#   define TRUNC       trunc
#   define FMOD        fmod
#   define NEXTAFTER   nextafter
#endif

/***** function prototype *********************************************************************************************/

// constant getter
FTYPE getPI(void);
FTYPE getTWOPI(void);
FTYPE getHALFPI(void);
FTYPE getINVPI(void);
FTYPE getE(void);
FTYPE getLN10(void);
FTYPE getLN2(void);
FTYPE getLOG10E(void);
FTYPE getLOG2E(void);
FTYPE getSQRT2(void);
FTYPE getINVSQRT2(void);
FTYPE getGRATIO(void);
FTYPE getSRATIO(void);
FTYPE getBRATIO(void);

// basic
FTYPE divide(FTYPE _v1, FTYPE _v2);
FTYPE modulo(FTYPE _v1, FTYPE _v2);
int sign(FTYPE _in);
FTYPE reciprocal(FTYPE _in);

// trigonometric
FTYPE sinNormed(FTYPE _x, FTYPE _twopi);
FTYPE cosNormed(FTYPE _x, FTYPE _twopi);
FTYPE tanNormed(FTYPE _x, FTYPE _twopi);
FTYPE cscNormed(FTYPE _x, FTYPE _twopi);
FTYPE secNormed(FTYPE _x, FTYPE _twopi);
FTYPE cotNormed(FTYPE _x, FTYPE _twopi);

// conversion
FTYPE deg2rad(FTYPE _deg, FTYPE _pi);
FTYPE rad2deg(FTYPE _rad, FTYPE _pi);

// rounding and clipping
FTYPE roundOff(FTYPE _x);
FTYPE roundUp(FTYPE _x);
FTYPE roundDown(FTYPE _x);
FTYPE roundT0(FTYPE _x);
FTYPE roundDownWithBase(FTYPE _x, FTYPE _base);
FTYPE clipCC(FTYPE _in, FTYPE _min, FTYPE _max);
FTYPE clipOO(FTYPE _in, FTYPE _min, FTYPE _max);
FTYPE clipOC(FTYPE _in, FTYPE _min, FTYPE _max);
FTYPE clipCO(FTYPE _in, FTYPE _min, FTYPE _max);

// mean
FTYPE meanArithmetic(FTYPE *_x, int _len);
FTYPE meanGeometric(FTYPE *_x, int _len);
FTYPE meanHarmonic(FTYPE *_x, int _len);

// interpolation
FTYPE interpLinear(FTYPE _in1, FTYPE _in2, FTYPE _weight);

// ops for unipolar & bipolar
FTYPE b2u(FTYPE _in);
FTYPE u2b(FTYPE _in);
FTYPE scaleX2U(FTYPE _in, FTYPE _min, FTYPE _max);
FTYPE scaleU2X(FTYPE _in, FTYPE _min, FTYPE _max);
FTYPE scaleX2X(FTYPE _in, FTYPE _inMin, FTYPE _inMax, FTYPE _outMin, FTYPE _outMax);

// shaping bipolar
FTYPE flipB(FTYPE _in);

// shaping unipolar
FTYPE flipU(FTYPE _in);
FTYPE reduceQuantumU(FTYPE _in, int _quantum);
FTYPE foldU(FTYPE _in);
FTYPE shiftHalfU(FTYPE _in, FTYPE _ratio);
FTYPE shiftQuarterU(FTYPE _in, FTYPE _ratio);
FTYPE compHalfU(FTYPE _in, FTYPE _amount);
FTYPE compQuarterU(FTYPE _in, FTYPE _amount);

// easing unipolar
FTYPE easeIExponentU(FTYPE _in, FTYPE _curve);
FTYPE easeOExponentU(FTYPE _in, FTYPE _curve);
FTYPE easeIOExponentU(FTYPE _in, FTYPE _curve);
FTYPE easeOIExponentU(FTYPE _in, FTYPE _curve);
FTYPE easeIIExponentU(FTYPE _in, FTYPE _curve);
FTYPE easeOOExponentU(FTYPE _in, FTYPE _curve);
FTYPE easeIOIOExponentU(FTYPE _in, FTYPE _curve);
FTYPE easeOIOIExponentU(FTYPE _in, FTYPE _curve);
FTYPE easeIOIIExponentU(FTYPE _in, FTYPE _curve);
FTYPE easeIOOIExponentU(FTYPE _in, FTYPE _curve);
FTYPE easeIOOOExponentU(FTYPE _in, FTYPE _curve);
FTYPE easeIIIOExponentU(FTYPE _in, FTYPE _curve);
FTYPE easeIIOIExponentU(FTYPE _in, FTYPE _curve);
FTYPE easeIIOOExponentU(FTYPE _in, FTYPE _curve);
FTYPE easeIIIIExponentU(FTYPE _in, FTYPE _curve);
FTYPE easeOIOOExponentU(FTYPE _in, FTYPE _curve);
FTYPE easeOIIOExponentU(FTYPE _in, FTYPE _curve);
FTYPE easeOIIIExponentU(FTYPE _in, FTYPE _curve);
FTYPE easeOOOIExponentU(FTYPE _in, FTYPE _curve);
FTYPE easeOOIOExponentU(FTYPE _in, FTYPE _curve);
FTYPE easeOOIIExponentU(FTYPE _in, FTYPE _curve);
FTYPE easeOOOOExponentU(FTYPE _in, FTYPE _curve);

/***** function *******************************************************************************************************/

// constant getter
inline FTYPE getPI(void)        { return ACOS(-1); }
inline FTYPE getTWOPI(void)     { return getPI()*2; }
inline FTYPE getHALFPI(void)    { return divide(getPI(), 2); }
inline FTYPE getINVPI(void)     { return reciprocal(getPI()); }
inline FTYPE getE(void)         { return EXP(1); }
inline FTYPE getLN10(void)      { return LOG(10); }
inline FTYPE getLN2(void)       { return LOG(2); }
inline FTYPE getLOG10E(void)    { return LOG10(getE()); }
inline FTYPE getLOG2E(void)     { return LOG2(getE()); }
inline FTYPE getSQRT2(void)     { return SQRT(2); }
inline FTYPE getINVSQRT2(void)  { return reciprocal(SQRT(2)); }
inline FTYPE getGRATIO(void)    { return divide(1+SQRT(5), 2); }
inline FTYPE getSRATIO(void)    { return 1+SQRT(2); }
inline FTYPE getBRATIO(void)    { return divide(3+SQRT(13), 2); }

// basic
inline FTYPE divide(FTYPE _v1, FTYPE _v2)               { return (_v2!=0) ? _v1/_v2          : FMAX; }
inline FTYPE modulo(FTYPE _v1, FTYPE _v2)               { return (_v2!=0) ? FMOD(_v1, _v2)   : 0; }
inline int sign(FTYPE _in)                              { return (_in==0) ? 0 : ((_in>0) ? 1 : -1); }
inline FTYPE reciprocal(FTYPE _in)                      { return divide(1, _in); }

// trigonometric
inline FTYPE sinNormed(FTYPE _x, FTYPE _twopi)          { return (_x==0.5||_x==1)     ? 0    : SIN(_x*_twopi); }
inline FTYPE cosNormed(FTYPE _x, FTYPE _twopi)          { return (_x==0.25||_x==0.75) ? 0    : COS(_x*_twopi); }
inline FTYPE tanNormed(FTYPE _x, FTYPE _twopi)          { return (_x==0.25||_x==0.75) ? FMAX : ((_x==0.5||_x==1) ? 0 : TAN(_x*_twopi)); }
inline FTYPE cscNormed(FTYPE _x, FTYPE _twopi)          { return reciprocal(sinNormed(_x, _twopi)); }
inline FTYPE secNormed(FTYPE _x, FTYPE _twopi)          { return reciprocal(cosNormed(_x, _twopi)); }
inline FTYPE cotNormed(FTYPE _x, FTYPE _twopi)          { return reciprocal(tanNormed(_x, _twopi)); }

// conversion
inline FTYPE deg2rad(FTYPE _deg, FTYPE _pi)             { return _deg*divide(_pi, 180); }
inline FTYPE rad2deg(FTYPE _rad, FTYPE _pi)             { return _rad*divide(180, _pi); }

// rounding and clipping
inline FTYPE roundOff(FTYPE _x)                         { return ROUND(_x); }
inline FTYPE roundUp(FTYPE _x)                          { return CEIL(_x); }
inline FTYPE roundDown(FTYPE _x)                        { return FLOOR(_x); }
inline FTYPE roundT0(FTYPE _x)                          { return TRUNC(_x); }
inline FTYPE roundDownWithBase(FTYPE _x, FTYPE _base)   { return roundDown(_x*reciprocal(_base)) * _base; }
inline FTYPE clipCC(FTYPE _in, FTYPE _min, FTYPE _max)  { return (_min<=_in&&_in<=_max) ? _in : ((_in<_min) ? _min : _max); }
inline FTYPE clipOO(FTYPE _in, FTYPE _min, FTYPE _max)  { return (_min<_in&&_in<_max)   ? _in : ((_in<=_min) ? NEXTAFTER(_min, _max) : NEXTAFTER(_max, _min)); }
inline FTYPE clipOC(FTYPE _in, FTYPE _min, FTYPE _max)  { return (_min<_in&&_in<=_max)  ? _in : ((_in<=_min) ? NEXTAFTER(_min, _max) : _max); }
inline FTYPE clipCO(FTYPE _in, FTYPE _min, FTYPE _max)  { return (_min<=_in&&_in<_max)  ? _in : ((_in<_min) ? _min : NEXTAFTER(_max, _min)); }

// mean
inline FTYPE meanArithmetic(FTYPE *_x, int _len) {
    FTYPE value = *_x;
    for(int i=1; i<_len; i++) value += *(_x+i);
    return value / _len;
}

inline FTYPE meanGeometric(FTYPE *_x, int _len) {
    FTYPE value = *_x;
    for(int i=1; i<_len; i++) value *= *(_x+i);
    return POW(value, 1/_len);
}

inline FTYPE meanHarmonic(FTYPE *_x, int _len) {
    FTYPE value = reciprocal(*_x);
    for(int i=1; i<_len; i++) value += reciprocal(*(_x+1));
    return reciprocal(value/_len);
}

// interpolation
inline FTYPE interpLinear(FTYPE _in1, FTYPE _in2, FTYPE _weight)    { return _in1*(1-_weight) + _in2*_weight; }

// ops for unipolar & bipolar
inline FTYPE b2u(FTYPE _in)                                                                { return (_in+1)*0.5; }
inline FTYPE u2b(FTYPE _in)                                                                { return _in*2-1; }
inline FTYPE scaleX2U(FTYPE _in, FTYPE _inMin, FTYPE _inMax)                               { return (_inMin==0 && _inMax==1) ? _in : ((_inMin==-1 && _inMax==1) ? b2u(_in) : divide(_in-_inMin, _inMax-_inMin)); }
inline FTYPE scaleU2X(FTYPE _in, FTYPE _outMin, FTYPE _outMax)                             { return (_outMin==0 && _outMax==1) ? _in : ((_outMin==-1 && _outMax==1) ? u2b(_in) : _in*(_outMax-_outMin)+_outMin); }
inline FTYPE scaleX2X(FTYPE _in, FTYPE _inMin, FTYPE _inMax, FTYPE _outMin, FTYPE _outMax) { return scaleU2X(scaleX2U(_in, _inMin, _inMax), _outMin, _outMax);  }

// shaping bipolar
inline FTYPE flipB(FTYPE _in)                           { return -_in; }

// shaping unipolar
inline FTYPE flipU(FTYPE _in)                           { return 1-_in; }
inline FTYPE foldU(FTYPE _in)                           { return (_in*2<=1) ? _in*2 : flipU(_in*2-1); }
inline FTYPE reduceQuantumU(FTYPE _in, int _quantum)    { return roundDownWithBase(_in, reciprocal(_quantum)) * reciprocal(flipU(reciprocal(_quantum))); }
inline FTYPE shiftQuarterU(FTYPE _in, FTYPE _ratio)     { return (_in<0.5) ? scaleU2X(shiftHalfU(scaleX2U(_in, 0, 0.5), _ratio), 0, 0.5) : scaleU2X(shiftHalfU(scaleX2U(_in, 0.5, 1), 1-_ratio), 0.5, 1); }
inline FTYPE compQuarterU(FTYPE _in, FTYPE _ratio)      { return (_in<0.5) ? scaleU2X(compHalfU(scaleX2U(_in, 0, 0.5), _ratio), 0, 0.5)  : scaleU2X(compHalfU(scaleX2U(_in, 0.5, 1), _ratio), 0.5, 1); }

inline FTYPE shiftHalfU(FTYPE _in, FTYPE _ratio) {
    if(0<_ratio&&_ratio<1)  return (_in<_ratio) ? scaleX2X(_in, 0, _ratio, 0, 0.5) : scaleX2X(_in, _ratio, 1, 0.5, 1);
    else if(_ratio<=0)      return (_in==0)     ? 0 : scaleU2X(_in, 0.5, 1);
    else                    return (_in==1)     ? 1 : scaleU2X(_in, 0, 0.5);
}

inline FTYPE compHalfU(FTYPE _in, FTYPE _amount) {
    if(0<_amount&&_amount<1) {
        if(_in<0.5)         return (_in<0.5-(_amount*0.5)) ? scaleX2X(_in, 0, 0.5-_amount*0.5, 0, 0.5) : 0.5;
        else                return (_in<0.5+(_amount*0.5)) ? 0.5 : scaleX2X(_in, 0.5+_amount*0.5, 1, 0.5, 1);
    } else {
        if(_amount<=0)      return _in;
        else                return 0.5 + ((_in==0)*-0.5) + ((_in==1)*0.5);
    }
}

// easing unipolar
inline FTYPE easeIExponentU(FTYPE _in, FTYPE _curve)    { return (0<_curve && _curve<1) ? POW(_in, reciprocal(flipU(_curve))) : ((_curve<=0) ? _in : (_in==1)); }
inline FTYPE easeOExponentU(FTYPE _in, FTYPE _curve)    { return (0<_curve && _curve<1) ? POW(_in, flipU(_curve)) : ((_curve<=0) ? _in : (_in!=0)); }
inline FTYPE easeIOExponentU(FTYPE _in, FTYPE _curve)   { return (_in<0.5) ? scaleU2X(easeIExponentU(scaleX2U(_in, 0, 0.5), _curve), 0, 0.5) : scaleU2X(easeOExponentU(scaleX2U(_in, 0.5, 1), _curve), 0.5, 1); }
inline FTYPE easeOIExponentU(FTYPE _in, FTYPE _curve)   { return (_in<0.5) ? scaleU2X(easeOExponentU(scaleX2U(_in, 0, 0.5), _curve), 0, 0.5) : scaleU2X(easeIExponentU(scaleX2U(_in, 0.5, 1), _curve), 0.5, 1); }
inline FTYPE easeIIExponentU(FTYPE _in, FTYPE _curve)   { return (_in<0.5) ? scaleU2X(easeIExponentU(scaleX2U(_in, 0, 0.5), _curve), 0, 0.5) : scaleU2X(easeIExponentU(scaleX2U(_in, 0.5, 1), _curve), 0.5, 1); }
inline FTYPE easeOOExponentU(FTYPE _in, FTYPE _curve)   { return (_in<0.5) ? scaleU2X(easeOExponentU(scaleX2U(_in, 0, 0.5), _curve), 0, 0.5) : scaleU2X(easeOExponentU(scaleX2U(_in, 0.5, 1), _curve), 0.5, 1); }
inline FTYPE easeIOIOExponentU(FTYPE _in, FTYPE _curve) { return (_in<0.5) ? scaleU2X(easeIOExponentU(scaleX2U(_in, 0, 0.5), _curve), 0, 0.5) : scaleU2X(easeIOExponentU(scaleX2U(_in, 0.5, 1), _curve), 0.5, 1); }
inline FTYPE easeOIOIExponentU(FTYPE _in, FTYPE _curve) { return (_in<0.5) ? scaleU2X(easeOIExponentU(scaleX2U(_in, 0, 0.5), _curve), 0, 0.5) : scaleU2X(easeOIExponentU(scaleX2U(_in, 0.5, 1), _curve), 0.5, 1); }
inline FTYPE easeIOIIExponentU(FTYPE _in, FTYPE _curve) { return (_in<0.5) ? scaleU2X(easeIOExponentU(scaleX2U(_in, 0, 0.5), _curve), 0, 0.5) : scaleU2X(easeIIExponentU(scaleX2U(_in, 0.5, 1), _curve), 0.5, 1); }
inline FTYPE easeIOOIExponentU(FTYPE _in, FTYPE _curve) { return (_in<0.5) ? scaleU2X(easeIOExponentU(scaleX2U(_in, 0, 0.5), _curve), 0, 0.5) : scaleU2X(easeOIExponentU(scaleX2U(_in, 0.5, 1), _curve), 0.5, 1); }
inline FTYPE easeIOOOExponentU(FTYPE _in, FTYPE _curve) { return (_in<0.5) ? scaleU2X(easeIOExponentU(scaleX2U(_in, 0, 0.5), _curve), 0, 0.5) : scaleU2X(easeOOExponentU(scaleX2U(_in, 0.5, 1), _curve), 0.5, 1); }
inline FTYPE easeIIIOExponentU(FTYPE _in, FTYPE _curve) { return (_in<0.5) ? scaleU2X(easeIIExponentU(scaleX2U(_in, 0, 0.5), _curve), 0, 0.5) : scaleU2X(easeIOExponentU(scaleX2U(_in, 0.5, 1), _curve), 0.5, 1); }
inline FTYPE easeIIOIExponentU(FTYPE _in, FTYPE _curve) { return (_in<0.5) ? scaleU2X(easeIIExponentU(scaleX2U(_in, 0, 0.5), _curve), 0, 0.5) : scaleU2X(easeOIExponentU(scaleX2U(_in, 0.5, 1), _curve), 0.5, 1); }
inline FTYPE easeIIOOExponentU(FTYPE _in, FTYPE _curve) { return (_in<0.5) ? scaleU2X(easeIIExponentU(scaleX2U(_in, 0, 0.5), _curve), 0, 0.5) : scaleU2X(easeOOExponentU(scaleX2U(_in, 0.5, 1), _curve), 0.5, 1); }
inline FTYPE easeIIIIExponentU(FTYPE _in, FTYPE _curve) { return (_in<0.5) ? scaleU2X(easeIIExponentU(scaleX2U(_in, 0, 0.5), _curve), 0, 0.5) : scaleU2X(easeIIExponentU(scaleX2U(_in, 0.5, 1), _curve), 0.5, 1); }
inline FTYPE easeOIOOExponentU(FTYPE _in, FTYPE _curve) { return (_in<0.5) ? scaleU2X(easeOIExponentU(scaleX2U(_in, 0, 0.5), _curve), 0, 0.5) : scaleU2X(easeOOExponentU(scaleX2U(_in, 0.5, 1), _curve), 0.5, 1); }
inline FTYPE easeOIIOExponentU(FTYPE _in, FTYPE _curve) { return (_in<0.5) ? scaleU2X(easeOIExponentU(scaleX2U(_in, 0, 0.5), _curve), 0, 0.5) : scaleU2X(easeIOExponentU(scaleX2U(_in, 0.5, 1), _curve), 0.5, 1); }
inline FTYPE easeOIIIExponentU(FTYPE _in, FTYPE _curve) { return (_in<0.5) ? scaleU2X(easeOIExponentU(scaleX2U(_in, 0, 0.5), _curve), 0, 0.5) : scaleU2X(easeIIExponentU(scaleX2U(_in, 0.5, 1), _curve), 0.5, 1); }
inline FTYPE easeOOOIExponentU(FTYPE _in, FTYPE _curve) { return (_in<0.5) ? scaleU2X(easeOOExponentU(scaleX2U(_in, 0, 0.5), _curve), 0, 0.5) : scaleU2X(easeOIExponentU(scaleX2U(_in, 0.5, 1), _curve), 0.5, 1); }
inline FTYPE easeOOIOExponentU(FTYPE _in, FTYPE _curve) { return (_in<0.5) ? scaleU2X(easeOOExponentU(scaleX2U(_in, 0, 0.5), _curve), 0, 0.5) : scaleU2X(easeIOExponentU(scaleX2U(_in, 0.5, 1), _curve), 0.5, 1); }
inline FTYPE easeOOIIExponentU(FTYPE _in, FTYPE _curve) { return (_in<0.5) ? scaleU2X(easeOOExponentU(scaleX2U(_in, 0, 0.5), _curve), 0, 0.5) : scaleU2X(easeIIExponentU(scaleX2U(_in, 0.5, 1), _curve), 0.5, 1); }
inline FTYPE easeOOOOExponentU(FTYPE _in, FTYPE _curve) { return (_in<0.5) ? scaleU2X(easeOOExponentU(scaleX2U(_in, 0, 0.5), _curve), 0, 0.5) : scaleU2X(easeOOExponentU(scaleX2U(_in, 0.5, 1), _curve), 0.5, 1); }

/***** end of definition **********************************************************************************************/

#endif