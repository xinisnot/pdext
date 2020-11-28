// Copyright (c) 2020 xin.

#include "common/table.h"

/***** class declaration *********************************************************/

static t_class *triangle_tilde_class;
static t_sample *table;

typedef struct _triangle_tilde {
    t_object    x_obj;
    t_outlet    *outlet;
    t_float     dummy;
} t_triangle_tilde;

/***** DSP ***********************************************************************/

t_int* triangle_tilde_perform(t_int *_w) {
    t_triangle_tilde *x = (t_triangle_tilde*)(_w[1]);
    t_sample *in1       = (t_sample*)(_w[2]);
    t_sample *out1      = (t_sample*)(_w[3]);
    int vecsize         = (int)(_w[4]);

    while(vecsize--)    *out1++ = readTableLinear(table, *in1++);

    return (_w+5);
}

void triangle_tilde_dsp(t_triangle_tilde *_x, t_signal **_sp) {
  dsp_add(triangle_tilde_perform, 4, _x, _sp[0]->s_vec, _sp[1]->s_vec, _sp[0]->s_n);
}

/***** constructor & destructor **************************************************/

void *triangle_tilde_new(void) {
    t_triangle_tilde *x = (t_triangle_tilde*)pd_new(triangle_tilde_class);
    x->outlet           = outlet_new(&x->x_obj, gensym("signal"));

    return (void*)x;
}

void triangle_tilde_free(t_triangle_tilde *_x) {
    outlet_free(_x->outlet);
}

/***** class setup ***************************************************************/

void freefn() {
    freeTable(&table);
}

void triangle_tilde_setup(void) {
    triangle_tilde_class = class_new(gensym("triangle~"), (t_newmethod)triangle_tilde_new, (t_method)triangle_tilde_free, sizeof(t_triangle_tilde), CLASS_DEFAULT, 0);
    table                = NULL;

    class_addmethod(triangle_tilde_class, (t_method)triangle_tilde_dsp, gensym("dsp"), A_CANT, 0);
    class_sethelpsymbol(triangle_tilde_class, gensym("triangle~"));
    CLASS_MAINSIGNALIN(triangle_tilde_class, t_triangle_tilde, dummy);
    class_setfreefn(triangle_tilde_class, freefn);
    callocTableTriangle(&table);
}