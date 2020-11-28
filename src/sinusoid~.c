// Copyright (c) 2020 xin.

#include "common/table.h"

/***** class declaration *********************************************************/

static t_class *sinusoid_tilde_class;
static t_sample *table;
static t_sample twopi;

typedef struct _sinusoid_tilde {
    t_object    x_obj;
    t_outlet    *outlet;
    t_float     dummy;
} t_sinusoid_tilde;

/***** DSP ***********************************************************************/

t_int* sinusoid_tilde_perform(t_int *_w) {
    t_sinusoid_tilde *x = (t_sinusoid_tilde*)(_w[1]);
    t_sample *in1       = (t_sample*)(_w[2]);
    t_sample *out1      = (t_sample*)(_w[3]);
    int vecsize         = (int)(_w[4]);

    while(vecsize--)    *out1++ = readTableLinear(table, *in1++);

    return (_w+5);
}

void sinusoid_tilde_dsp(t_sinusoid_tilde *_x, t_signal **_sp) {
  dsp_add(sinusoid_tilde_perform, 4, _x, _sp[0]->s_vec, _sp[1]->s_vec, _sp[0]->s_n);
}

/***** constructor & destructor **************************************************/

void *sinusoid_tilde_new(void) {
    t_sinusoid_tilde *x = (t_sinusoid_tilde*)pd_new(sinusoid_tilde_class);
    x->outlet           = outlet_new(&x->x_obj, gensym("signal"));

    return (void*)x;
}

void sinusoid_tilde_free(t_sinusoid_tilde *_x) {
    outlet_free(_x->outlet);
}

/***** class setup ***************************************************************/

void freefn() {
    freeTable(&table);
}

void sinusoid_tilde_setup(void) {
    sinusoid_tilde_class = class_new(gensym("sinusoid~"), (t_newmethod)sinusoid_tilde_new, (t_method)sinusoid_tilde_free, sizeof(t_sinusoid_tilde), CLASS_DEFAULT, 0);
    table                = NULL;
    twopi                = getTWOPI();

    class_addmethod(sinusoid_tilde_class, (t_method)sinusoid_tilde_dsp, gensym("dsp"), A_CANT, 0);
    class_sethelpsymbol(sinusoid_tilde_class, gensym("sinusoid~"));
    CLASS_MAINSIGNALIN(sinusoid_tilde_class, t_sinusoid_tilde, dummy);
    class_setfreefn(sinusoid_tilde_class, freefn);
    callocTableSinusoid(&table, twopi);
}