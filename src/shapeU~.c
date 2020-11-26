// Copyright (c) 2020 xin.

#include "common/heart.h"

/***** class declaration **********************************************************************************************/

static t_class *shapeU_tilde_class;

typedef struct _shapeU_tilde {
    t_object    x_obj;
    t_inlet     *secondInlets[8];
    t_outlet    *outlet;
    t_float     dummy;

    t_sample    ratioSH;
    t_sample    ratioSQ;
    t_sample    ratioCH;
    t_sample    ratioCQ;
    int         flagFlip;
    int         flagFold;
    int         flagStep;
    int         numStep;
} t_shapeU_tilde;

/***** DSP ************************************************************************************************************/

t_int* shapeU_tilde_perform(t_int *_w) {
    t_shapeU_tilde *x = (t_shapeU_tilde*)(_w[1]);
    t_sample *in1      = (t_sample*)(_w[2]);
    t_sample *in2      = (t_sample*)(_w[3]);
    t_sample *in3      = (t_sample*)(_w[4]);
    t_sample *in4      = (t_sample*)(_w[5]);
    t_sample *in5      = (t_sample*)(_w[6]);
    t_sample *in6      = (t_sample*)(_w[7]);
    t_sample *in7      = (t_sample*)(_w[8]);
    t_sample *in8      = (t_sample*)(_w[9]);
    t_sample *in9      = (t_sample*)(_w[10]);
    t_sample *out1     = (t_sample*)(_w[11]);
    int vecsize        = (int)(_w[12]);

    while(vecsize--) {
        x->ratioSH     = *in2++;
        x->ratioSQ     = *in3++;
        x->ratioCH     = *in4++;
        x->ratioCQ     = *in5++;
        x->flagFlip    = (*in6++)!=0;
        x->flagFold    = (*in7++)!=0;
        x->flagStep    = (*in8++)!=0;
        x->numStep     = (int)(*in9++);
        
        *out1++        = shapeU(*in1++, x->ratioSH, x->ratioSQ, x->ratioCH, x->ratioCQ, x->flagFlip, x->flagFold, x->flagStep, x->numStep);
    }

    return (_w+13);
}

void shapeU_tilde_dsp(t_shapeU_tilde *_x, t_signal **_sp) {
  dsp_add(shapeU_tilde_perform, 12, _x, _sp[0]->s_vec, _sp[1]->s_vec, _sp[2]->s_vec, _sp[3]->s_vec, _sp[4]->s_vec, _sp[5]->s_vec, _sp[6]->s_vec, _sp[7]->s_vec, _sp[8]->s_vec, _sp[9]->s_vec, _sp[0]->s_n);
}

/***** constructor & destructor ***************************************************************************************/

void* shapeU_tilde_new(t_symbol *_s, int _argc, t_atom *_argv) {
    t_shapeU_tilde *x = (t_shapeU_tilde*)pd_new(shapeU_tilde_class);
    x->secondInlets[0] = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
    x->secondInlets[1] = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
    x->secondInlets[2] = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
    x->secondInlets[3] = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
    x->secondInlets[4] = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
    x->secondInlets[5] = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
    x->secondInlets[6] = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
    x->secondInlets[7] = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
    x->outlet          = outlet_new(&x->x_obj, &s_signal);

    x->numStep = 16;
    x->flagStep = 0;
    x->flagFold = 0;
    x->flagFlip = 0;
    x->ratioCQ = 0;
    x->ratioCH = 0;
    x->ratioSQ = 0.5;
    x->ratioSH = 0.5;
    pd_float((t_pd*)x->secondInlets[0], 0.5);
    pd_float((t_pd*)x->secondInlets[1], 0.5);
    pd_float((t_pd*)x->secondInlets[2], 0);
    pd_float((t_pd*)x->secondInlets[3], 0);
    pd_float((t_pd*)x->secondInlets[4], 0);
    pd_float((t_pd*)x->secondInlets[5], 0);
    pd_float((t_pd*)x->secondInlets[6], 0);
    pd_float((t_pd*)x->secondInlets[7], 16);

    switch(_argc) {
        default:
        case 8: x->numStep = (int)atom_getfloat(_argv+7);
                pd_float((t_pd*)x->secondInlets[7], atom_getfloat(_argv+7));
        case 7: x->flagStep = (atom_getfloat(_argv+6)!=0);
                pd_float((t_pd*)x->secondInlets[6], atom_getfloat(_argv+6));
        case 6: x->flagFold = (atom_getfloat(_argv+5)!=0);
                pd_float((t_pd*)x->secondInlets[5], atom_getfloat(_argv+5));
        case 5: x->flagFlip = (atom_getfloat(_argv+4)!=0);
                pd_float((t_pd*)x->secondInlets[4], atom_getfloat(_argv+4));
        case 4: x->ratioCQ = atom_getfloat(_argv+3);
                pd_float((t_pd*)x->secondInlets[3], atom_getfloat(_argv+3));
        case 3: x->ratioCH = atom_getfloat(_argv+2);
                pd_float((t_pd*)x->secondInlets[2], atom_getfloat(_argv+2));
        case 2: x->ratioSQ = atom_getfloat(_argv+1);
                pd_float((t_pd*)x->secondInlets[1], atom_getfloat(_argv+1));
        case 1: x->ratioSH = atom_getfloat(_argv);
                pd_float((t_pd*)x->secondInlets[0], atom_getfloat(_argv));
                break;
        case 0: break;
    }

    return (void*)x;
}

void shapeU_tilde_free(t_shapeU_tilde *_x) {
    inlet_free(_x->secondInlets[0]);
    inlet_free(_x->secondInlets[1]);
    inlet_free(_x->secondInlets[2]);
    inlet_free(_x->secondInlets[3]);
    inlet_free(_x->secondInlets[4]);
    inlet_free(_x->secondInlets[5]);
    inlet_free(_x->secondInlets[6]);
    inlet_free(_x->secondInlets[7]);
    outlet_free(_x->outlet);
}

/***** class setup ****************************************************************************************************/

void shapeU_tilde_setup(void) {
    shapeU_tilde_class = class_new(gensym("shapeU~"), (t_newmethod)shapeU_tilde_new, (t_method)shapeU_tilde_free, sizeof(t_shapeU_tilde), CLASS_DEFAULT, A_GIMME, 0);

    class_addmethod(shapeU_tilde_class, (t_method)shapeU_tilde_dsp, gensym("dsp"), A_CANT, 0);
    class_sethelpsymbol(shapeU_tilde_class, gensym("shapeU~"));
    CLASS_MAINSIGNALIN(shapeU_tilde_class, t_shapeU_tilde, dummy);
}
