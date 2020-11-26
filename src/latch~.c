// Copyright (c) 2020 xin.

#include "common/heart.h"

/***** class declaration *********************************************************/

static t_class *latch_tilde_class;

typedef struct _latch_tilde {
    t_object    x_obj;
    t_inlet     *secondInlet;
    t_outlet    *outlet;
    t_float     dummy;

    t_sample    last;
} t_latch_tilde;

/***** DSP ***********************************************************************/

t_int* latch_tilde_perform(t_int *_w) {
    t_latch_tilde *x = (t_latch_tilde*)(_w[1]);
    t_sample *in1    = (t_sample*)(_w[2]);
    t_sample *in2    = (t_sample*)(_w[3]);
    t_sample *out1   = (t_sample*)(_w[4]);
    int vecsize      = (int)(_w[5]);

    while(vecsize--) *out1++ = latch(*in1++, &x->last, *in2++);

    return (_w+6);
}

void latch_tilde_dsp(t_latch_tilde *_x, t_signal **_sp) {
  dsp_add(latch_tilde_perform, 5, _x, _sp[0]->s_vec, _sp[1]->s_vec, _sp[2]->s_vec, _sp[0]->s_n);
}

/***** constructor & destructor **************************************************/

void* latch_tilde_new(void) {
    t_latch_tilde *x = (t_latch_tilde*)pd_new(latch_tilde_class);
    x->secondInlet   = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
    x->outlet        = outlet_new(&x->x_obj, &s_signal);
    x->last          = 0;

    return (void*)x;
}

void latch_tilde_free(t_latch_tilde *_x) {
    inlet_free(_x->secondInlet);
    outlet_free(_x->outlet);
}

/***** class setup ***************************************************************/

void latch_tilde_setup(void) {
    latch_tilde_class = class_new(gensym("latch~"), (t_newmethod)latch_tilde_new, (t_method)latch_tilde_free, sizeof(t_latch_tilde), CLASS_DEFAULT, 0);

    class_addmethod(latch_tilde_class, (t_method)latch_tilde_dsp, gensym("dsp"), A_CANT, 0);
    class_sethelpsymbol(latch_tilde_class, gensym("latch~"));
    CLASS_MAINSIGNALIN(latch_tilde_class, t_latch_tilde, dummy);
}
