// Copyright (c) 2020 xin.

#include "common/heart.h"

/***** class declaration *********************************************************/

static t_class *clock_tilde_class;
static t_sample SR;

typedef struct _clock_tilde {
    t_object    x_obj;
    t_inlet     *secondInlets[4];
    t_outlet    *outlets[2];
    t_float     dummy;

    t_sample    bpm;
    t_sample    base;
    t_sample    dot;
    t_sample    active;

    t_sample    current;
    t_sample    last;
} t_clock_tilde;

/***** DSP ***********************************************************************/

t_int* clock_tilde_perform(t_int *_w) {
    t_clock_tilde *x = (t_clock_tilde*)(_w[1]);
    t_sample *in1    = (t_sample*)(_w[2]);
    t_sample *in2    = (t_sample*)(_w[3]);
    t_sample *in3    = (t_sample*)(_w[4]);
    t_sample *in4    = (t_sample*)(_w[5]);
    t_sample *in5    = (t_sample*)(_w[6]);
    t_sample *out1   = (t_sample*)(_w[7]);
    t_sample *out2   = (t_sample*)(_w[8]);
    int vecsize      = (int)(_w[9]);

    while(vecsize--) {
        x->active = (*in1++)!=0;
        x->bpm    = *in2++;
        x->base   = *in3++; 
        x->dot    = *in4++;

        if((*in5++)==1) {
            x->current = 1;
            x->last    = 1;
        }

        if(x->active!=0) {
            x->current = x->last + divide(x->bpm, 15*SR*(x->base + x->base*(x->dot!=0)*0.5));
            x->current = (1 < x->current) ? 1 - x->current : x->current;
        }

        *out1++    = x->current;
        *out2++    = (x->current - x->last)<0;
        x->last    = x->current;
    }

    return (_w+10);
}

void clock_tilde_dsp(t_clock_tilde *_x, t_signal **_sp) {
  dsp_add(clock_tilde_perform, 9, _x, _sp[0]->s_vec, _sp[1]->s_vec, _sp[2]->s_vec, _sp[3]->s_vec, _sp[4]->s_vec, _sp[5]->s_vec, _sp[6]->s_vec, _sp[0]->s_n);
}

/***** constructor & destructor **************************************************/

void* clock_tilde_new(t_symbol *_s, int _argc, t_atom  *_argv) {
    t_clock_tilde *x = (t_clock_tilde*)pd_new(clock_tilde_class);
    x->secondInlets[0] = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
    x->secondInlets[1] = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
    x->secondInlets[2] = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
    x->secondInlets[3] = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
    x->outlets[0]      = outlet_new(&x->x_obj, &s_signal);
    x->outlets[1]      = outlet_new(&x->x_obj, &s_signal);

    x->active          = 0;
    x->bpm             = 0;
    x->base            = 4;
    x->dot             = 0;
    x->current         = 1;
    x->last            = 1;

    pd_float((t_pd*)x->secondInlets[0], x->bpm);
    pd_float((t_pd*)x->secondInlets[1], x->base);
    pd_float((t_pd*)x->secondInlets[2], x->dot);
    pd_float((t_pd*)x->secondInlets[3], 0);

    switch(_argc) {
        default:
        case 3: x->dot  = atom_getfloat(_argv+2);
                pd_float((t_pd*)x->secondInlets[2], atom_getfloat(_argv+2));
        case 2: x->base = atom_getfloat(_argv+1);
                pd_float((t_pd*)x->secondInlets[1], atom_getfloat(_argv+1));
        case 1: x->bpm  = atom_getfloat(_argv);
                pd_float((t_pd*)x->secondInlets[0], atom_getfloat(_argv));
                break;
        case 0: break;
    }

    return (void*)x;
}

void clock_tilde_free(t_clock_tilde *_x) {
    inlet_free(_x->secondInlets[0]);
    inlet_free(_x->secondInlets[1]);
    inlet_free(_x->secondInlets[2]);
    outlet_free(_x->outlets[0]);
    outlet_free(_x->outlets[1]);
}

/***** class setup ***************************************************************/

void clock_tilde_setup(void) {
    clock_tilde_class = class_new(gensym("clock~"), (t_newmethod)clock_tilde_new, (t_method)clock_tilde_free, sizeof(t_clock_tilde), CLASS_DEFAULT, A_GIMME, 0);
    SR                = sys_getsr();

    class_addmethod(clock_tilde_class, (t_method)clock_tilde_dsp, gensym("dsp"), A_CANT, 0);
    class_sethelpsymbol(clock_tilde_class, gensym("clock~"));
    CLASS_MAINSIGNALIN(clock_tilde_class, t_clock_tilde, dummy);
}
