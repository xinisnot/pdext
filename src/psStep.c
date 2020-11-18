// Copyright (c) 2020 xin.

#include <m_pd.h>
#include "common/operator.h"

/***** class declaration *********************************************************/

static t_class *psStep_class;

typedef struct _psStep {
    t_object    x_obj;
    t_float     input;
    t_outlet    *out;

    int         active;
    int         step;
} t_psStep;

/***** method ********************************************************************/

void onBangMsg(t_psStep *_x) {
    (_x->active==0) ? outlet_float(_x->out, _x->input) : outlet_float(_x->out, reduceQuantum4Phasor(_x->input, _x->step));
}

void onFloatMsg(t_psStep *_x, t_floatarg _in) {
    _x->input = _in;
    onBangMsg(_x);
}

void setActive(t_psStep *_x, t_floatarg _active) {
    _x->active = (_active!=0);
}

void setStep(t_psStep *_x, t_floatarg _step) {
    _x->step = (int)_step;
}

/***** constructor & destructor **************************************************/

void* psStep_new(t_symbol *_s, int _argc, t_atom  *_argv) {
    t_psStep *x    = (t_psStep*)pd_new(psStep_class);
    x->out          = outlet_new(&x->x_obj, &s_float);

    switch(_argc)
    {
        default:
        case 2: setActive(x, atom_getint(_argv+1));
        case 1: setStep(x, atom_getint(_argv));
                break;
        case 0: setActive(x, 0);
                setStep(x, 256);
                break;
    }

    return (void*)x;
}

void psStep_free(t_psStep *_x) {
    outlet_free(_x->out);
}

/***** class setup ***************************************************************/

void psStep_setup(void) {
    psStep_class = class_new(gensym("psStep"), (t_newmethod)psStep_new, (t_method)psStep_free, sizeof(t_psStep), CLASS_DEFAULT, A_GIMME, 0);

    class_addbang(psStep_class, (t_method)onBangMsg);
    class_addfloat(psStep_class, (t_method)onFloatMsg);
    class_addmethod(psStep_class, (t_method)setActive, gensym("active"), A_DEFFLOAT, 0);
    class_addmethod(psStep_class, (t_method)setStep, gensym("step"), A_DEFFLOAT, 0);

    class_sethelpsymbol(psStep_class, gensym("psStep"));
}
