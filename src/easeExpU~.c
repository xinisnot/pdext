// Copyright (c) 2020 xin.

#include "common/heart.h"

/***** class declaration *********************************************************/

static t_class *easeExpU_tilde_class;

typedef struct _easeExpU_tilde {
    t_object    x_obj;
    t_inlet     *secondInlets[2];
    t_outlet    *outlet;
    t_float     dummy;

    t_sample    curve;
    int         type;
} t_easeExpU_tilde;

/***** DSP ***********************************************************************/

t_int* easeExpU_tilde_perform(t_int *_w) {
    t_easeExpU_tilde *x = (t_easeExpU_tilde*)(_w[1]);
    t_sample *in1       = (t_sample*)(_w[2]);
    t_sample *in2       = (t_sample*)(_w[3]);
    t_sample *in3       = (t_sample*)(_w[4]);
    t_sample *out1      = (t_sample*)(_w[5]);
    int vecsize         = (int)(_w[6]);

    while(vecsize--) {
        x->curve        = *in2++;
        x->type         = (int)*in3++;
        *out1++         = easeExpU(*in1++, x->curve, x->type);
    }

    return (_w+7);
}

void easeExpU_tilde_dsp(t_easeExpU_tilde *_x, t_signal **_sp) {
  dsp_add(easeExpU_tilde_perform, 6, _x, _sp[0]->s_vec, _sp[1]->s_vec, _sp[2]->s_vec, _sp[3]->s_vec, _sp[0]->s_n);
}

/***** constructor & destructor **************************************************/

void* easeExpU_tilde_new(t_symbol *_s, int _argc, t_atom *_argv) {
    t_easeExpU_tilde *x = (t_easeExpU_tilde*)pd_new(easeExpU_tilde_class);
    x->secondInlets[0] = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
    x->secondInlets[1] = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
    x->outlet          = outlet_new(&x->x_obj, &s_signal);

    x->curve = 0;
    x->type  = 0;
    pd_float((t_pd*)x->secondInlets[0], 0);
    pd_float((t_pd*)x->secondInlets[1], 0);

    switch(_argc) {
        default:
        case 2: x->type = (int)atom_getfloat(_argv+1);
                pd_float((t_pd*)x->secondInlets[1], atom_getfloat(_argv+1));
        case 1: x->curve = atom_getfloat(_argv);
                pd_float((t_pd*)x->secondInlets[0], atom_getfloat(_argv));
                break;
        case 0: break;
    }

    return (void*)x;
}

void easeExpU_tilde_free(t_easeExpU_tilde *_x) {
    inlet_free(_x->secondInlets[0]);
    inlet_free(_x->secondInlets[1]);
    outlet_free(_x->outlet);
}

/***** class setup ***************************************************************/

void easeExpU_tilde_setup(void) {
    easeExpU_tilde_class = class_new(gensym("easeExpU~"), (t_newmethod)easeExpU_tilde_new, (t_method)easeExpU_tilde_free, sizeof(t_easeExpU_tilde), CLASS_DEFAULT, A_GIMME, 0);

    class_addmethod(easeExpU_tilde_class, (t_method)easeExpU_tilde_dsp, gensym("dsp"), A_CANT, 0);
    class_sethelpsymbol(easeExpU_tilde_class, gensym("easeExpU~"));
    CLASS_MAINSIGNALIN(easeExpU_tilde_class, t_easeExpU_tilde, dummy);
}
