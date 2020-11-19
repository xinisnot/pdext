// Copyright (c) 2020 xin.

#include <m_pd.h>
#include "common/operator.h"

/***** class declaration *********************************************************/

static t_class *psEaseExp_tilde_class;

typedef struct _psEaseExp_tilde {
    t_object    x_obj;
    t_inlet     *inlet2curve;
    t_inlet     *inlet3width;
    t_inlet     *inlet4easeMode;
    t_inlet     *inlet5flip;
    t_outlet    *outlet1;
    t_float     dummy;

    t_sample    curve;
    t_sample    width;
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

void setWidth(t_psEaseExp_tilde *_x, t_floatarg _width) {
    _x->width = _width;
}

t_sample getWidth(t_psEaseExp_tilde *_x) {
    return _x->width;
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

    value = (getFlip(_x)==0) ? shiftHalf4U(value, getWidth(_x)) : shiftHalf4U(value, 1-getWidth(_x));

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
    t_sample *in5        = (t_sample*)(_w[6]);
    t_sample *out1       = (t_sample*)(_w[7]);
    int vecsize          = (int)(_w[8]);

    while(vecsize--) {
        setCurve(x, *in2++);
        setWidth(x, *in3++);
        setEaseMode(x, *in4++);
        setFlip(x, *in5++);
        
        *out1++ = signalOut(x, *in1++);
    }

    return (_w+9);
}

void psEaseExp_tilde_dsp(t_psEaseExp_tilde *_x, t_signal **_sp) {
  dsp_add(psEaseExp_tilde_perform, 8, _x, _sp[0]->s_vec, _sp[1]->s_vec, _sp[2]->s_vec, _sp[3]->s_vec, _sp[4]->s_vec, _sp[5]->s_vec, _sp[0]->s_n);
}

/***** constructor & destructor **************************************************/

void* psEaseExp_tilde_new(t_symbol *_s, int _argc, t_atom  *_argv) {
    t_psEaseExp_tilde *x = (t_psEaseExp_tilde*)pd_new(psEaseExp_tilde_class);
    x->inlet2curve       = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
    x->inlet3width       = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
    x->inlet4easeMode    = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
    x->inlet5flip        = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
    x->outlet1           = outlet_new(&x->x_obj, &s_signal);

    switch(_argc)
    {
        default:
        case 4: setFlip(x, atom_getfloat(_argv+3));
                pd_float((t_pd*)x->inlet5flip, atom_getfloat(_argv+3));
        case 3: setEaseMode(x, atom_getfloat(_argv+2));
                pd_float((t_pd*)x->inlet4easeMode, atom_getfloat(_argv+2));
        case 2: setWidth(x, atom_getfloat(_argv+1));
                pd_float((t_pd*)x->inlet3width, atom_getfloat(_argv+1));
        case 1: setCurve(x, atom_getfloat(_argv));
                pd_float((t_pd*)x->inlet2curve, atom_getfloat(_argv));
                break;
        case 0: setFlip(x, 0);
                setEaseMode(x, 0);
                setWidth(x, 0.5);
                setCurve(x, 0);
                pd_float((t_pd*)x->inlet5flip, 0);
                pd_float((t_pd*)x->inlet4easeMode, 0);
                pd_float((t_pd*)x->inlet3width, 0.5);
                pd_float((t_pd*)x->inlet2curve, 0);
                break;
    }

    return (void*)x;
}

void psEaseExp_tilde_free(t_psEaseExp_tilde *_x) {
    inlet_free(_x->inlet2curve);
    inlet_free(_x->inlet3width);
    inlet_free(_x->inlet4easeMode);
    inlet_free(_x->inlet5flip);
    outlet_free(_x->outlet1);
}

/***** class setup ***************************************************************/

void psEaseExp_tilde_setup(void) {
    psEaseExp_tilde_class = class_new(gensym("psEaseExp~"), (t_newmethod)psEaseExp_tilde_new, (t_method)psEaseExp_tilde_free, sizeof(t_psEaseExp_tilde), CLASS_DEFAULT, A_GIMME, 0);

    class_addmethod(psEaseExp_tilde_class, (t_method)psEaseExp_tilde_dsp, gensym("dsp"), A_CANT, 0);
    class_sethelpsymbol(psEaseExp_tilde_class, gensym("psEaseExp~"));
    CLASS_MAINSIGNALIN(psEaseExp_tilde_class, t_psEaseExp_tilde, dummy);
}
