// Copyright (c) 2020 xin.

#include "common/DSPheart.h"
#include "common/tableGen.h"
#include <stdlib.h>

/***** class declaration *********************************************************/

static t_class *triangle_tilde_class;
static t_sample *triTable;

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

    t_sample value;
    int idx0;
    int idx1;
    t_sample weight;

    while(vecsize--) {
        value   = *in1++ * (TABLE_INDEX+1);
        idx0    = (int)FLOOR(value);
        idx1    = (idx0!=TABLE_INDEX) ? idx0+1 : 0;
        weight  = value - idx0;
        *out1++ = linearInterpolation(triTable[idx0], triTable[idx1], weight);
    }

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

void allocateTable() {
    if(triTable) return;
    triTable = (t_sample*)calloc(TABLE_INDEX+1, sizeof(t_sample));
}

void freeTable() {
    free(triTable);
}

void triangle_tilde_setup(void) {
    triangle_tilde_class = class_new(gensym("triangle~"), (t_newmethod)triangle_tilde_new, (t_method)triangle_tilde_free, sizeof(t_triangle_tilde), CLASS_DEFAULT, 0);

    class_addmethod(triangle_tilde_class, (t_method)triangle_tilde_dsp, gensym("dsp"), A_CANT, 0);
    class_sethelpsymbol(triangle_tilde_class, gensym("triangle~"));
    CLASS_MAINSIGNALIN(triangle_tilde_class, t_triangle_tilde, dummy);

    class_setfreefn(triangle_tilde_class, freeTable);
    allocateTable();
    generateTableTriangle(triTable);
}