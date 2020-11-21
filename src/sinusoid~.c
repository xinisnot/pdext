// Copyright (c) 2020 xin.

#include "common/DSPheart.h"

#define TABLE_INDEX_MAX 65536

/***** class declaration *********************************************************/

static t_class *sinusoid_tilde_class;
static t_sample *sinTable;

typedef struct _sinusoid_tilde {
    t_object    x_obj;
    t_outlet    *outlet;
    t_float     dummy;

    int         size;
} t_sinusoid_tilde;

/***** DSP ***********************************************************************/

t_int* sinusoid_tilde_perform(t_int *_w) {
    t_sinusoid_tilde *x = (t_sinusoid_tilde*)(_w[1]);
    t_sample *in1       = (t_sample*)(_w[2]);
    t_sample *out1      = (t_sample*)(_w[3]);
    int vecsize         = (int)(_w[4]);

    t_sample value;
    int idx0;
    int idx1;
    t_sample weight;

    while(vecsize--) {
        value   = *in1++ * x->size;
        idx0    = (int)FLOOR(value);
        idx1    = (idx0!=TABLE_INDEX_MAX) ? idx0+1 : 0;
        weight  = value - idx0;
        *out1++ = linearInterpolation(sinTable[idx0], sinTable[idx1], weight);
    }

    return (_w+5);
}

void sinusoid_tilde_dsp(t_sinusoid_tilde *_x, t_signal **_sp) {
  dsp_add(sinusoid_tilde_perform, 4, _x, _sp[0]->s_vec, _sp[1]->s_vec, _sp[0]->s_n);
}

/***** constructor & destructor **************************************************/

void *sinusoid_tilde_new(void) {
    t_sinusoid_tilde *x = (t_sinusoid_tilde*)pd_new(sinusoid_tilde_class);
    x->outlet           = outlet_new(&x->x_obj, gensym("signal"));
    x->size             = TABLE_INDEX_MAX + 1;

    return (void*)x;
}

void sinusoid_tilde_free(t_sinusoid_tilde *_x) {
    outlet_free(_x->outlet);
}

/***** generate & free table *****************************************************/

void makeTableSinusoid(void) {
    if(sinTable) return;

    int size          = TABLE_INDEX_MAX + 1;
    int quarterOfSize = TABLE_INDEX_MAX / 4;
    sinTable          = (t_sample*)getbytes(size * sizeof(t_sample));
    t_sample *pTable  = sinTable;

    if(sinTable) {
        for(int i=0; i<quarterOfSize; i++)  *pTable++ = sine(scaleU2X(scaleX2U(i, 0, quarterOfSize), 0, 0.25));
        for(int i=0; i<quarterOfSize; i++)  *pTable++ = cosine(scaleU2X(scaleX2U(i, 0, quarterOfSize), 0, 0.25));
        for(int i=0; i<quarterOfSize; i++)  *pTable++ = -sine(scaleU2X(scaleX2U(i, 0, quarterOfSize), 0, 0.25));
        for(int i=0; i<quarterOfSize; i++)  *pTable++ = -cosine(scaleU2X(scaleX2U(i, 0, quarterOfSize), 0, 0.25));
        *pTable++ = 0;
    } else {
        error("could not make table.");
    }
}

void freeTable(t_class *_class) {
    freebytes(sinTable, sizeof(float) * (TABLE_INDEX_MAX+1));
    sinTable = 0;
}

/***** class setup ***************************************************************/

void sinusoid_tilde_setup(void) {
    sinusoid_tilde_class = class_new(gensym("sinusoid~"), (t_newmethod)sinusoid_tilde_new, (t_method)sinusoid_tilde_free, sizeof(t_sinusoid_tilde), CLASS_DEFAULT, 0);

    class_addmethod(sinusoid_tilde_class, (t_method)sinusoid_tilde_dsp, gensym("dsp"), A_CANT, 0);
    class_sethelpsymbol(sinusoid_tilde_class, gensym("sinusoid~"));
    CLASS_MAINSIGNALIN(sinusoid_tilde_class, t_sinusoid_tilde, dummy);
    class_setfreefn(sinusoid_tilde_class, freeTable);
    makeTableSinusoid();
}
