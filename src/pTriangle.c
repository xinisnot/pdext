// Copyright (c) 2020 xin.

#include <m_pd.h>
#include "common/operator.h"

/***** class declaration *********************************************************/

static t_class *pTriangle_class;

typedef struct _pTriangle {
    t_object    x_obj;
    t_float     input;
    t_outlet    *out;

    // double      ratio;
    // int         mode;
} t_pTriangle;

/***** method ********************************************************************/

void onBangMsg(t_pTriangle *_x) {
    outlet_float(_x->out, phaseTriangle(_x->input));
    // (_x->mode==0) ? outlet_float(_x->out, phaseTriangle(_x->input, _x->ratio)) : outlet_float(_x->out, shiftQuarter4Phasor(_x->input, _x->ratio));
}

void onFloatMsg(t_pTriangle *_x, t_floatarg _in) {
    _x->input = _in;
    onBangMsg(_x);
}

// void setRatio(t_pTriangle *_x, t_floatarg _ratio) {
//     _x->ratio = _ratio;
// }

// void setMode(t_pTriangle *_x, t_floatarg _mode) {
//     _x->mode = (_mode!=0);
// }

/***** constructor & destructor **************************************************/

void* pTriangle_new(void) {
    t_pTriangle *x    = (t_pTriangle*)pd_new(pTriangle_class);
    x->out          = outlet_new(&x->x_obj, &s_float);

    // switch(_argc)
    // {
    //     default:
    //     case 2: setMode(x, atom_getfloat(_argv+1));
    //     case 1: setRatio(x, atom_getfloat(_argv));
    //             break;
    //     case 0: setMode(x, 0);
    //             setRatio(x, 0.5);
    //             break;
    // }

    return (void*)x;
}

void pTriangle_free(t_pTriangle *_x) {
    outlet_free(_x->out);
}

/***** class setup ***************************************************************/

void pTriangle_setup(void) {
    pTriangle_class = class_new(gensym("pTriangle"), (t_newmethod)pTriangle_new, (t_method)pTriangle_free, sizeof(t_pTriangle), CLASS_DEFAULT, 0);

    class_addbang(pTriangle_class, (t_method)onBangMsg);
    class_addfloat(pTriangle_class, (t_method)onFloatMsg);
    // class_addmethod(pTriangle_class, (t_method)setRatio, gensym("ratio"), A_DEFFLOAT, 0);
    // class_addmethod(pTriangle_class, (t_method)setMode, gensym("mode"), A_DEFFLOAT, 0);

    class_sethelpsymbol(pTriangle_class, gensym("pTriangle"));
}
