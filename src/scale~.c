// Copyright (c) 2020 xin.

#include "common/heart.h"

/***** class declaration **********************************************************************************************/

static t_class *scale_tilde_class;

typedef struct _scale_tilde {
    t_object    x_obj;
    t_inlet     *secondInlets[4];
    t_outlet    *outlet;
    t_float     dummy;

    t_sample    inMin;
    t_sample    inMax;
    t_sample    outMin;
    t_sample    outMax;
} t_scale_tilde;

/***** DSP ************************************************************************************************************/

t_int* scale_tilde_perform(t_int *_w) {
    t_scale_tilde *x = (t_scale_tilde*)(_w[1]);
    t_sample *in1      = (t_sample*)(_w[2]);
    t_sample *in2      = (t_sample*)(_w[3]);
    t_sample *in3      = (t_sample*)(_w[4]);
    t_sample *in4      = (t_sample*)(_w[5]);
    t_sample *in5      = (t_sample*)(_w[6]);
    t_sample *out1     = (t_sample*)(_w[7]);
    int vecsize        = (int)(_w[8]);

    while(vecsize--) {
        x->inMin       = *in2++;
        x->inMax       = *in3++;
        x->outMin      = *in4++;
        x->outMax      = *in5++;
        
        *out1++        = scale(*in1++, x->inMin, x->inMax, x->outMin, x->outMax);
    }

    return (_w+9);
}

void scale_tilde_dsp(t_scale_tilde *_x, t_signal **_sp) {
  dsp_add(scale_tilde_perform, 8, _x, _sp[0]->s_vec, _sp[1]->s_vec, _sp[2]->s_vec, _sp[3]->s_vec, _sp[4]->s_vec, _sp[5]->s_vec, _sp[0]->s_n);
}

/***** constructor & destructor ***************************************************************************************/

void* scale_tilde_new(t_symbol *_s, int _argc, t_atom *_argv) {
    t_scale_tilde *x = (t_scale_tilde*)pd_new(scale_tilde_class);
    x->secondInlets[0] = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
    x->secondInlets[1] = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
    x->secondInlets[2] = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
    x->secondInlets[3] = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
    x->outlet          = outlet_new(&x->x_obj, &s_signal);

    x->inMin = 0;
    x->inMax = 1;
    x->outMin = 0;
    x->outMax = 1;
    pd_float((t_pd*)x->secondInlets[0], 0);
    pd_float((t_pd*)x->secondInlets[1], 1);
    pd_float((t_pd*)x->secondInlets[2], 0);
    pd_float((t_pd*)x->secondInlets[3], 1);

    switch(_argc) {
        default:
        case 4: x->outMax = atom_getfloat(_argv+3);
                pd_float((t_pd*)x->secondInlets[3], atom_getfloat(_argv+3));
        case 3: x->outMin = atom_getfloat(_argv+2);
                pd_float((t_pd*)x->secondInlets[2], atom_getfloat(_argv+2));
        case 2: x->inMax = atom_getfloat(_argv+1);
                pd_float((t_pd*)x->secondInlets[1], atom_getfloat(_argv+1));
        case 1: x->inMin = atom_getfloat(_argv);
                pd_float((t_pd*)x->secondInlets[0], atom_getfloat(_argv));
                break;
        case 0: break;
    }

    return (void*)x;
}

void scale_tilde_free(t_scale_tilde *_x) {
    inlet_free(_x->secondInlets[0]);
    inlet_free(_x->secondInlets[1]);
    inlet_free(_x->secondInlets[2]);
    inlet_free(_x->secondInlets[3]);
    outlet_free(_x->outlet);
}

/***** class setup ****************************************************************************************************/

void scale_tilde_setup(void) {
    scale_tilde_class = class_new(gensym("scale~"), (t_newmethod)scale_tilde_new, (t_method)scale_tilde_free, sizeof(t_scale_tilde), CLASS_DEFAULT, A_GIMME, 0);

    class_addmethod(scale_tilde_class, (t_method)scale_tilde_dsp, gensym("dsp"), A_CANT, 0);
    class_sethelpsymbol(scale_tilde_class, gensym("scale~"));
    CLASS_MAINSIGNALIN(scale_tilde_class, t_scale_tilde, dummy);
}
