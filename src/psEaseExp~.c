// Copyright (c) 2020 xin.

#include <m_pd.h>
#include "common/operator.h"

/***** class declaration *********************************************************/

static t_class *psEaseExp_tilde_class;

typedef struct _psEaseExp_tilde {
    t_object    x_obj;
    t_inlet     *inlet2;
    t_inlet     *inlet3;
    t_inlet     *inlet4;
    t_outlet    *outlet1;
    t_float     dummy;

    t_sample    curve;
    int         easeMode;
    int         flip;

} t_psEaseExp_tilde;

/***** internal method ***********************************************************/

void setCurve(t_psEaseExp_tilde *_x, t_floatarg _curve) {
    _x->curve = _curve;
}

t_sample getCurve(t_psEaseExp_tilde *_x) {
    return _x->curve;
}

void setEaseMode(t_psEaseExp_tilde *_x, t_floatarg _mode) {
    _x->easeMode = _mode;
}

int getEaseMode(t_psEaseExp_tilde *_x) {
    return _x->easeMode;
}

void setFlip(t_psEaseExp_tilde *_x, t_floatarg _flip) {
    _x->flip = _flip;
}

int getFlip(t_psEaseExp_tilde *_x) {
    return _x->flip;
}

t_sample signalOut(t_psEaseExp_tilde *_x, t_sample _current) {
    t_sample value = (getFlip(_x)==0) ? _current : flip4U(_current);

    switch(getEaseMode(_x)) {
        default:
        case 0: value = easeInExponent4U(value, getCurve(_x));      break;
        case 1: value = easeOutExponent4U(value, getCurve(_x));     break;
        case 2: value = easeInOutExponent4U(value, getCurve(_x));   break;
        case 3: value = easeOutInExponent4U(value, getCurve(_x));   break;
        case 4: value = easeInInExponent4U(value, getCurve(_x));    break;
        case 5: value = easeOutOutExponent4U(value, getCurve(_x));  break;
    }
    return value;
}

/***** DSP ***********************************************************************/

t_int* psEaseExp_tilde_perform(t_int *_w) {
    t_psEaseExp_tilde *x = (t_psEaseExp_tilde*)(_w[1]);
    t_sample *in1        = (t_sample*)(_w[2]);
    t_sample *in2        = (t_sample*)(_w[3]);
    t_sample *in3        = (t_sample*)(_w[4]);
    t_sample *in4        = (t_sample*)(_w[5]);
    t_sample *out1       = (t_sample*)(_w[6]);
    int vecsize          = (int)(_w[7]);

    while(vecsize--) {
        setCurve(x, *in2++);
        setEaseMode(x, *in3++);
        setFlip(x, *in4++);
        
        *out1++ = signalOut(x, *in1++);
    }

    return (_w+8);
}

void psEaseExp_tilde_dsp(t_psEaseExp_tilde *_x, t_signal **_sp) {
  dsp_add(psEaseExp_tilde_perform, 7, _x, _sp[0]->s_vec, _sp[1]->s_vec, _sp[2]->s_vec, _sp[3]->s_vec, _sp[4]->s_vec, _sp[0]->s_n);
}

/***** constructor & destructor **************************************************/

void* psEaseExp_tilde_new(t_symbol *_s, int _argc, t_atom  *_argv) {
    t_psEaseExp_tilde *x = (t_psEaseExp_tilde*)pd_new(psEaseExp_tilde_class);
    x->inlet2            = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
    x->inlet3            = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
    x->inlet4            = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
    x->outlet1           = outlet_new(&x->x_obj, &s_signal);

    switch(_argc)
    {
        default:
        case 3: setFlip(x, atom_getfloat(_argv+2));
                pd_float((t_pd*)x->inlet4, atom_getfloat(_argv+2));
        case 2: setEaseMode(x, atom_getfloat(_argv+1));
                pd_float((t_pd*)x->inlet3, atom_getfloat(_argv+1));
        case 1: setCurve(x, atom_getfloat(_argv));
                pd_float((t_pd*)x->inlet2, atom_getfloat(_argv));
                break;
        case 0: setFlip(x, 0);
                setEaseMode(x, 0);
                setCurve(x, 0);
                pd_float((t_pd*)x->inlet4, 0);
                pd_float((t_pd*)x->inlet3, 0);
                pd_float((t_pd*)x->inlet2, 0);
                break;
    }

    return (void*)x;
}

void psEaseExp_tilde_free(t_psEaseExp_tilde *_x) {
    inlet_free(_x->inlet2);
    inlet_free(_x->inlet3);
    inlet_free(_x->inlet4);
    outlet_free(_x->outlet1);
}

/***** class setup ***************************************************************/

void psEaseExp_tilde_setup(void) {
    psEaseExp_tilde_class = class_new(gensym("psEaseExp~"), (t_newmethod)psEaseExp_tilde_new, (t_method)psEaseExp_tilde_free, sizeof(t_psEaseExp_tilde), CLASS_DEFAULT, A_GIMME, 0);

    class_addmethod(psEaseExp_tilde_class, (t_method)psEaseExp_tilde_dsp, gensym("dsp"), A_CANT, 0);
    class_sethelpsymbol(psEaseExp_tilde_class, gensym("psEaseExp~"));
    CLASS_MAINSIGNALIN(psEaseExp_tilde_class, t_psEaseExp_tilde, dummy);
}
