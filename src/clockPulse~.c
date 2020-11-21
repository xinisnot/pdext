// Copyright (c) 2020 xin.

#include "common/DSPheart.h"

/***** class declaration *********************************************************/

static t_class *clockPulse_tilde_class;

typedef struct _clockPulse_tilde {
    t_object    x_obj;
    t_outlet    *outlet;
    t_float     dummy;

    t_sample    n1;
} t_clockPulse_tilde;

/***** DSP ***********************************************************************/

t_int* clockPulse_tilde_perform(t_int *_w) {
    t_clockPulse_tilde *x = (t_clockPulse_tilde*)(_w[1]);
    t_sample *in1      = (t_sample*)(_w[2]);
    t_sample *out1     = (t_sample*)(_w[3]);
    int vecsize        = (int)(_w[4]);

    t_sample n0;

    while(vecsize--) {        
        n0      = *in1++;
        *out1++ = clockPulse(n0, x->n1);
        x->n1   = n0;
    }

    return (_w+5);
}

void clockPulse_tilde_dsp(t_clockPulse_tilde *_x, t_signal **_sp) {
  dsp_add(clockPulse_tilde_perform, 4, _x, _sp[0]->s_vec, _sp[1]->s_vec, _sp[0]->s_n);
}

/***** constructor & destructor **************************************************/

void* clockPulse_tilde_new(void) {
    t_clockPulse_tilde *x = (t_clockPulse_tilde*)pd_new(clockPulse_tilde_class);
    x->outlet             = outlet_new(&x->x_obj, &s_signal);
    x->n1                 = 0;

    return (void*)x;
}

void clockPulse_tilde_free(t_clockPulse_tilde *_x) {
    outlet_free(_x->outlet);
}

/***** class setup ***************************************************************/

void clockPulse_tilde_setup(void) {
    clockPulse_tilde_class = class_new(gensym("clockPulse~"), (t_newmethod)clockPulse_tilde_new, (t_method)clockPulse_tilde_free, sizeof(t_clockPulse_tilde), CLASS_DEFAULT, 0);

    class_addmethod(clockPulse_tilde_class, (t_method)clockPulse_tilde_dsp, gensym("dsp"), A_CANT, 0);
    class_sethelpsymbol(clockPulse_tilde_class, gensym("clockPulse~"));
    CLASS_MAINSIGNALIN(clockPulse_tilde_class, t_clockPulse_tilde, dummy);
}
