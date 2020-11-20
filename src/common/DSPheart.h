// Copyright (c) 2020 xin.

#ifndef _DSPHEART_H_
#define _DSPHEART_H_

/***** start of definition *******************************************************/

#include "operator.h"

/***** function prototype ********************************************************/

FTYPE biscuitInv(FTYPE _in, int* _digits);
FTYPE biscuitMute(FTYPE _in, int* _digits);

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

/***** end of definition *********************************************************/

#endif