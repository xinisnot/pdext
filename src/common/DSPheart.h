// Copyright (c) 2020 xin.

#ifndef _DSPHEART_H_
#define _DSPHEART_H_

/***** start of definition *******************************************************/

#include "operator.h"

/***** function prototype ********************************************************/

FTYPE biscuitInv(FTYPE _in, int* _digits);
FTYPE biscuitMute(FTYPE _in, int* _digits);
FTYPE easeExp(FTYPE _in, FTYPE _width, FTYPE _curve, int _flip, int _easeType);

/***** function ******************************************************************/

inline FTYPE biscuitInv(FTYPE _in, int* _digits) {
    int input = (int)roundf(scaleU2X(convertB2U(_in), 0, 255));
    int mask  = _digits[0] + (_digits[1]<<1) +(_digits[2]<<2) + (_digits[3]<<3) + (_digits[4]<<4) + (_digits[5]<<5) + (_digits[6]<<6) +(_digits[7]<<7);

    return (FTYPE)convertU2B(scaleX2U(input^mask, 0, 255));
}

inline FTYPE biscuitMute(FTYPE _in, int* _digits) {
    int input = (int)roundf(scaleU2X(convertB2U(_in), 0, 255));
    int mask  = _digits[0] + (_digits[1]<<1) +(_digits[2]<<2) + (_digits[3]<<3) + (_digits[4]<<4) + (_digits[5]<<5) + (_digits[6]<<6) +(_digits[7]<<7);

    return (FTYPE)convertU2B(scaleX2U(input&mask, 0, 255));
}

inline FTYPE easeExp(FTYPE _in, FTYPE _width, FTYPE _curve, int _flip, int _easeType) {
    FTYPE value = (_flip==0) ? shiftHalf4U(_in, _width) : shiftHalf4U(flip4U(_in), 1-_width);

    switch(_easeType) {
        default:
        case 0: value = easeInExponent4U(value, _curve);      break;
        case 1: value = easeOutExponent4U(value, _curve);     break;
        case 2: value = easeInOutExponent4U(value, _curve);   break;
        case 3: value = easeOutInExponent4U(value, _curve);   break;
        case 4: value = easeInInExponent4U(value, _curve);    break;
        case 5: value = easeOutOutExponent4U(value, _curve);  break;
    }
    return value;
}
/***** end of definition *********************************************************/

#endif