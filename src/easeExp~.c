// Copyright (c) 2020 xin.

#include "common/DSPheart.h"

/***** class declaration *********************************************************/

static t_class *easeExp_tilde_class;

typedef struct _easeExp_tilde {
    t_object    x_obj;
    t_inlet     *secondInlets[4];
    t_outlet    *outlet;
    t_float     dummy;

    t_sample    curve;
    t_sample    width;
    int         easeType;
    int         flip;

} t_easeExp_tilde;

/***** DSP ***********************************************************************/

t_int* easeExp_tilde_perform(t_int *_w) {
    t_easeExp_tilde *x = (t_easeExp_tilde*)(_w[1]);
    t_sample *in1      = (t_sample*)(_w[2]);
    t_sample *in2      = (t_sample*)(_w[3]);
    t_sample *in3      = (t_sample*)(_w[4]);
    t_sample *in4      = (t_sample*)(_w[5]);
    t_sample *in5      = (t_sample*)(_w[6]);
    t_sample *out1     = (t_sample*)(_w[7]);
    int vecsize        = (int)(_w[8]);

    while(vecsize--) {
        x->width       = *in2++;
        x->curve       = *in3++;
        x->easeType    = (int)*in4++;
        x->flip        = ((*in5++)!=0);
        
        *out1++        = easeExp(*in1++, x->width, x->curve, x->flip, x->easeType);
    }

    return (_w+9);
}

void easeExp_tilde_dsp(t_easeExp_tilde *_x, t_signal **_sp) {
  dsp_add(easeExp_tilde_perform, 8, _x, _sp[0]->s_vec, _sp[1]->s_vec, _sp[2]->s_vec, _sp[3]->s_vec, _sp[4]->s_vec, _sp[5]->s_vec, _sp[0]->s_n);
}

/***** constructor & destructor **************************************************/

void* easeExp_tilde_new(t_symbol *_s, int _argc, t_atom *_argv) {
    t_easeExp_tilde *x = (t_easeExp_tilde*)pd_new(easeExp_tilde_class);
    x->secondInlets[0] = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
    x->secondInlets[1] = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
    x->secondInlets[2] = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
    x->secondInlets[3] = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
    x->outlet          = outlet_new(&x->x_obj, &s_signal);

    switch(_argc)
    {
        default:
        case 4: x->flip = atom_getfloat(_argv+3);
                pd_float((t_pd*)x->secondInlets[3], atom_getfloat(_argv+3));
        case 3: x->easeType = atom_getfloat(_argv+2);
                pd_float((t_pd*)x->secondInlets[2], atom_getfloat(_argv+2));
        case 2: x->curve = atom_getfloat(_argv+1);
                pd_float((t_pd*)x->secondInlets[1], atom_getfloat(_argv+1));
        case 1: x->width = atom_getfloat(_argv);
                pd_float((t_pd*)x->secondInlets[0], atom_getfloat(_argv));
                break;
        case 0: x->flip = 0;
                x->easeType = 0;
                x->curve = 0;
                x->width = 0.5;
                pd_float((t_pd*)x->secondInlets[3], 0);
                pd_float((t_pd*)x->secondInlets[2], 0);
                pd_float((t_pd*)x->secondInlets[1], 0);
                pd_float((t_pd*)x->secondInlets[0], 0.5);
                break;
    }

    return (void*)x;
}

void easeExp_tilde_free(t_easeExp_tilde *_x) {
    inlet_free(_x->secondInlets[0]);
    inlet_free(_x->secondInlets[1]);
    inlet_free(_x->secondInlets[2]);
    inlet_free(_x->secondInlets[3]);
    outlet_free(_x->outlet);
}

/***** class setup ***************************************************************/

void easeExp_tilde_setup(void) {
    easeExp_tilde_class = class_new(gensym("easeExp~"), (t_newmethod)easeExp_tilde_new, (t_method)easeExp_tilde_free, sizeof(t_easeExp_tilde), CLASS_DEFAULT, A_GIMME, 0);

    class_addmethod(easeExp_tilde_class, (t_method)easeExp_tilde_dsp, gensym("dsp"), A_CANT, 0);
    class_sethelpsymbol(easeExp_tilde_class, gensym("easeExp~"));
    CLASS_MAINSIGNALIN(easeExp_tilde_class, t_easeExp_tilde, dummy);
}
