// Copyright (c) 2020 xin.

#ifndef _HEART_H_
#define _HEART_H_

/***** include ********************************************************************************************************/

#include "ops.h"

/***** function prototype *********************************************************************************************/

FTYPE shapeU(FTYPE _in, FTYPE _ratioSH, FTYPE _ratioSQ, FTYPE _ratioCH, FTYPE _ratioCQ, int _flagFlip, int _flagFold, int _flagStep, int _numStep);
FTYPE easeExpU(FTYPE _in, FTYPE _curve, int _type);
FTYPE scale(FTYPE _in, FTYPE _inMin, FTYPE _inMax, FTYPE _outMin, FTYPE _outMax);
FTYPE latch(FTYPE _current, FTYPE *_last, FTYPE _trigger);

FTYPE biscuitInv(FTYPE _in, int *_digits);
FTYPE biscuitMask(FTYPE _in, int *_digits);

/***** function prototype *********************************************************************************************/

inline FTYPE shapeU(FTYPE _in, FTYPE _ratioSH, FTYPE _ratioSQ, FTYPE _ratioCH, FTYPE _ratioCQ, int _flagFlip, int _flagFold, int _flagStep, int _numStep) {
    FTYPE value = (_flagFlip==0) ? _in   : flipU(_in);
    value = (_flagFold==0)       ? value : foldU(value);
    value = (_flagStep==0)       ? value : (reduceQuantumU(value, _numStep));

    return compQuarterU(compHalfU(shiftQuarterU(shiftHalfU(value, _ratioSH), _ratioSQ), _ratioCH), _ratioCQ);
}

inline FTYPE easeExpU(FTYPE _in, FTYPE _curve, int _type) {
    switch(_type) {
        default:
        case 0:  return easeIExponentU(_in, _curve);    break;
        case 1:  return easeOExponentU(_in, _curve);    break;
        case 2:  return easeIOExponentU(_in, _curve);   break;
        case 3:  return easeOIExponentU(_in, _curve);   break;
        case 4:  return easeIIExponentU(_in, _curve);   break;
        case 5:  return easeOOExponentU(_in, _curve);   break;
        case 6:  return easeIOIOExponentU(_in, _curve); break;
        case 7:  return easeOIOIExponentU(_in, _curve); break;
        case 8:  return easeIOIIExponentU(_in, _curve); break;
        case 9:  return easeIOOIExponentU(_in, _curve); break;
        case 10: return easeIOOOExponentU(_in, _curve); break;
        case 11: return easeIIIOExponentU(_in, _curve); break;
        case 12: return easeIIOIExponentU(_in, _curve); break;
        case 13: return easeIIOOExponentU(_in, _curve); break;
        case 14: return easeIIIIExponentU(_in, _curve); break;
        case 15: return easeOIOOExponentU(_in, _curve); break;
        case 16: return easeOIIOExponentU(_in, _curve); break;
        case 17: return easeOIIIExponentU(_in, _curve); break;
        case 18: return easeOOOIExponentU(_in, _curve); break;
        case 19: return easeOOIOExponentU(_in, _curve); break;
        case 20: return easeOOIIExponentU(_in, _curve); break;
        case 21: return easeOOOOExponentU(_in, _curve); break;
    }
}

inline FTYPE scale(FTYPE _in, FTYPE _inMin, FTYPE _inMax, FTYPE _outMin, FTYPE _outMax) {
    return scaleX2X(_in, _inMin, _inMax, _outMin, _outMax);
}

inline FTYPE latch(FTYPE _current, FTYPE *_last, FTYPE _trigger) {
    if(_trigger!=0) {
        *_last = _current;
        return _current;
    } else {
        return *_last;
    }
}

inline FTYPE biscuitInv(FTYPE _in, int *_digits) {
    int input = (int)roundOff(scaleU2X(b2u(_in), 0, 255));
    int mask  = _digits[0] + (_digits[1]<<1) + (_digits[2]<<2) + (_digits[3]<<3) + (_digits[4]<<4) + (_digits[5]<<5) + (_digits[6]<<6) + (_digits[7]<<7);

    return (FTYPE)u2b(scaleX2U(input^mask, 0, 255));
}

inline FTYPE biscuitMask(FTYPE _in, int *_digits) {
    int input = (int)roundOff(scaleU2X(b2u(_in), 0, 255));
    int mask  = _digits[0] + (_digits[1]<<1) + (_digits[2]<<2) + (_digits[3]<<3) + (_digits[4]<<4) + (_digits[5]<<5) + (_digits[6]<<6) + (_digits[7]<<7);

    return (FTYPE)u2b(scaleX2U(input&mask, 0, 255));
}

/***** end of definition **********************************************************************************************/

#endif