// Copyright (c) 2020 xin.

#include "common/heart.h"
#include <stdlib.h>

/***** class declaration *********************************************************/

static t_class *clicker_tilde_class;

typedef struct _clicker_tilde {
    t_object    x_obj;
    t_outlet    **outlets;
    t_float     dummy;

    int         outNum;
    int         last;


} t_clicker_tilde;

/***** DSP ***********************************************************************/

t_int* clicker_tilde_perform(t_int *_w) {
    t_clicker_tilde *x                    = (t_clicker_tilde*)(_w[1]);
    t_sample *in1                         = (t_sample*)(_w[2]);
    t_sample *out[x->outNum];

    for(int i=0; i<x->outNum; i++) out[i] = (t_sample*)(_w[i+3]);

    int vecsize                           = (int)(_w[(x->outNum)+3]);
    t_sample input;

    while(vecsize--) {
        // for(int i=0; i<x->outNum; i++) *out[i]++ = 0;
        input = *in1++;

        for(int i=0; i<x->outNum; i++) *(out[i]) = 0;

        if((input) != 0) {
            *(out[x->last]) = 1;
            x->last++;
            if(x->last >= x->outNum) x->last = 0;
            // x->last = modulo(x->last, x->outNum);
            // x->last += 1;
            // post("hoge");
        }

        for(int i=0; i<x->outNum; i++) (out[i])++;
    }

    return (_w+4+(x->outNum));
}

void clicker_tilde_dsp(t_clicker_tilde *_x, t_signal **_sp) {
    if(!_sp[0]->s_sr) return;

    int ptrNum                           = _x->outNum + 3; // 1 object, 1 inlet, 1vecsize
    t_int **tmp                          = (t_int**)calloc(ptrNum, sizeof(t_int*));
    for(long i=0; i<ptrNum; i++) tmp[i]  = (t_int*)calloc(sizeof(t_int), 1);

    tmp[0]                               = (t_int*)_x;
    for(int i=1; i<ptrNum-1; i++) tmp[i] = (t_int*)_sp[i-1]->s_vec;
    tmp[ptrNum-1]                        = (t_int*)_sp[0]->s_n;

    dsp_addv(clicker_tilde_perform, ptrNum, (t_int*)tmp);
    free(tmp);
}

/***** constructor & destructor **************************************************/

void* clicker_tilde_new(t_symbol *_s, int _argc, t_atom  *_argv) {
    t_clicker_tilde *x = (t_clicker_tilde*) pd_new(clicker_tilde_class);

    switch(_argc) {
        default :
        case 1 : x->outNum  = (int) atom_getfloat(_argv);                           break;
        case 0 : error("Write the Argument indicating the number of outlets.");     return 0;
    }

    x->outlets                                   = (t_outlet**)calloc(x->outNum, sizeof(t_outlet*));
    x->last                                      = 0;

    for(int i=0; i<x->outNum; i++) x->outlets[i] = outlet_new(&x->x_obj, &s_signal);

    return (void*)x;
}

void clicker_tilde_free(t_clicker_tilde *_x) {
    if (_x->outlets) freebytes(_x->outlets, _x->outNum * sizeof(*_x->outlets));
}

/***** class setup ***************************************************************/

void clicker_tilde_setup(void) {
    clicker_tilde_class = class_new(gensym("clicker~"), (t_newmethod)clicker_tilde_new, (t_method)clicker_tilde_free, sizeof(t_clicker_tilde), CLASS_DEFAULT, A_GIMME, 0);

    class_addmethod(clicker_tilde_class, (t_method)clicker_tilde_dsp, gensym("dsp"), A_CANT, 0);
    class_sethelpsymbol(clicker_tilde_class, gensym("clicker~"));
    CLASS_MAINSIGNALIN(clicker_tilde_class, t_clicker_tilde, dummy);
}
