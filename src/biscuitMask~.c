// Copyright (c) 2020 xin.

#include "common/heart.h"

/***** class declaration *********************************************************/

static t_class *biscuitMask_tilde_class;

typedef struct _biscuitMask_tilde {
    t_object    x_obj;
    t_inlet     *secondInlets[9];
    t_outlet    *outlet;
    t_float     dummy;
    
    int         active;
    int         digits[8];
} t_biscuitMask_tilde;

/***** DSP ***********************************************************************/

t_int* biscuitMask_tilde_perform(t_int *_w) {
    t_biscuitMask_tilde *x = (t_biscuitMask_tilde*)(_w[1]);
    t_sample *in1          = (t_sample*)(_w[2]);
    t_sample *in2          = (t_sample*)(_w[3]);
    t_sample *in3          = (t_sample*)(_w[4]);
    t_sample *in4          = (t_sample*)(_w[5]);
    t_sample *in5          = (t_sample*)(_w[6]);
    t_sample *in6          = (t_sample*)(_w[7]);
    t_sample *in7          = (t_sample*)(_w[8]);
    t_sample *in8          = (t_sample*)(_w[9]);
    t_sample *in9          = (t_sample*)(_w[10]);
    t_sample *in10         = (t_sample*)(_w[11]);
    t_sample *out1         = (t_sample*)(_w[12]);
    int vecsize            = (int)(_w[13]);

    while(vecsize--) {
        x->active          = *in2++;
        x->digits[7]       = ((*in3++)==0);
        x->digits[6]       = ((*in4++)==0);
        x->digits[5]       = ((*in5++)==0);
        x->digits[4]       = ((*in6++)==0);
        x->digits[3]       = ((*in7++)==0);
        x->digits[2]       = ((*in8++)==0);
        x->digits[1]       = ((*in9++)==0);
        x->digits[0]       = ((*in10++)==0);
        *out1++            = (x->active==0) ? *in1++ : biscuitMask(*in1++, x->digits);
    }

    return (_w+14);
}

void biscuitMask_tilde_dsp(t_biscuitMask_tilde *_x, t_signal **_sp) {
  dsp_add(biscuitMask_tilde_perform, 13, _x, _sp[0]->s_vec, _sp[1]->s_vec, _sp[2]->s_vec, _sp[3]->s_vec, _sp[4]->s_vec, _sp[5]->s_vec, _sp[6]->s_vec, _sp[7]->s_vec, _sp[8]->s_vec, _sp[9]->s_vec, _sp[10]->s_vec, _sp[0]->s_n);
}

/***** constructor & destructor **************************************************/

void* biscuitMask_tilde_new(t_symbol *_s, int _argc, t_atom  *_argv) {
    t_biscuitMask_tilde *x = (t_biscuitMask_tilde*)pd_new(biscuitMask_tilde_class);

    x->secondInlets[0] = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
    x->secondInlets[1] = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
    x->secondInlets[2] = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
    x->secondInlets[3] = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
    x->secondInlets[4] = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
    x->secondInlets[5] = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
    x->secondInlets[6] = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
    x->secondInlets[7] = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
    x->secondInlets[8] = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
    x->outlet          = outlet_new(&x->x_obj, &s_signal);

    x->active = 0;
    x->digits[7] = 0;
    x->digits[6] = 0;
    x->digits[5] = 0;
    x->digits[4] = 0;
    x->digits[3] = 0;
    x->digits[2] = 0;
    x->digits[1] = 0;
    x->digits[0] = 0;
    pd_float((t_pd*)x->secondInlets[0], 0);
    pd_float((t_pd*)x->secondInlets[1], 0);
    pd_float((t_pd*)x->secondInlets[2], 0);
    pd_float((t_pd*)x->secondInlets[3], 0);
    pd_float((t_pd*)x->secondInlets[4], 0);
    pd_float((t_pd*)x->secondInlets[5], 0);
    pd_float((t_pd*)x->secondInlets[6], 0);
    pd_float((t_pd*)x->secondInlets[7], 0);
    pd_float((t_pd*)x->secondInlets[8], 0);

    switch(_argc) {
        default:
        case 9: x->digits[0] = (atom_getfloat(_argv+8)==0);
                pd_float((t_pd*)x->secondInlets[8], atom_getfloat(_argv+8));
        case 8: x->digits[1] = (atom_getfloat(_argv+7)==0);
                pd_float((t_pd*)x->secondInlets[7], atom_getfloat(_argv+7));
        case 7: x->digits[2] = (atom_getfloat(_argv+6)==0);
                pd_float((t_pd*)x->secondInlets[6], atom_getfloat(_argv+6));
        case 6: x->digits[3] = (atom_getfloat(_argv+5)==0);
                pd_float((t_pd*)x->secondInlets[5], atom_getfloat(_argv+5));
        case 5: x->digits[4] = (atom_getfloat(_argv+4)==0);
                pd_float((t_pd*)x->secondInlets[4], atom_getfloat(_argv+4));
        case 4: x->digits[5] = (atom_getfloat(_argv+3)==0);
                pd_float((t_pd*)x->secondInlets[3], atom_getfloat(_argv+3));
        case 3: x->digits[6] = (atom_getfloat(_argv+2)==0);
                pd_float((t_pd*)x->secondInlets[2], atom_getfloat(_argv+2));
        case 2: x->digits[7] = (atom_getfloat(_argv+1)==0);
                pd_float((t_pd*)x->secondInlets[1], atom_getfloat(_argv+1));
        case 1: x->active = atom_getfloat(_argv);
                pd_float((t_pd*)x->secondInlets[0], atom_getfloat(_argv));
                break;
        case 0: break;
    }

    return (void*)x;
}

void biscuitMask_tilde_free(t_biscuitMask_tilde *_x) {
    inlet_free(_x->secondInlets[0]);
    inlet_free(_x->secondInlets[1]);
    inlet_free(_x->secondInlets[2]);
    inlet_free(_x->secondInlets[3]);
    inlet_free(_x->secondInlets[4]);
    inlet_free(_x->secondInlets[5]);
    inlet_free(_x->secondInlets[6]);
    inlet_free(_x->secondInlets[7]);
    inlet_free(_x->secondInlets[8]);
    outlet_free(_x->outlet);
}

/***** class setup ***************************************************************/

void biscuitMask_tilde_setup(void) {
    biscuitMask_tilde_class = class_new(gensym("biscuitMask~"), (t_newmethod)biscuitMask_tilde_new, (t_method)biscuitMask_tilde_free, sizeof(t_biscuitMask_tilde), CLASS_DEFAULT, A_GIMME, 0);

    class_addmethod(biscuitMask_tilde_class, (t_method)biscuitMask_tilde_dsp, gensym("dsp"), A_CANT, 0);
    class_sethelpsymbol(biscuitMask_tilde_class, gensym("biscuitMask~"));
    CLASS_MAINSIGNALIN(biscuitMask_tilde_class, t_biscuitMask_tilde, dummy);
}
