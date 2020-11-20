// Copyright (c) 2020 xin.

#include <m_pd.h>
#include "common/operator.h"

/***** class declaration *********************************************************/

static t_class *biscuitInv_tilde_class;

typedef struct _biscuitInv_tilde {
    t_object    x_obj;
    t_inlet     *inlet2active;
    t_inlet     *inlet3digit8;
    t_inlet     *inlet4digit7;
    t_inlet     *inlet5digit6;
    t_inlet     *inlet6digit5;
    t_inlet     *inlet7digit4;
    t_inlet     *inlet8digit3;
    t_inlet     *inlet9digit2;
    t_inlet     *inlet10digit1;
    t_outlet    *outlet1;
    t_float     dummy;

    int         active;
    int         digits[8];

} t_biscuitInv_tilde;

/***** internal method ***********************************************************/

void setDigits(t_biscuitInv_tilde *_x, int _index, t_floatarg _v) {
    int value = (_v==0);
    
    _x->digits[_index] = value<<_index;
}

// int getDigits(t_biscuitInv_tilde *_x, int _index) {
//     return _x->digits[_index];
// }

int getMask(t_biscuitInv_tilde *_x) {
    int value = 0;
    for(int i=0; i<8; i++)  value += _x->digits[i];

    return value;
}

void setActive(t_biscuitInv_tilde *_x, t_floatarg _v) {
    _x->active = _v;
}

int getActive(t_biscuitInv_tilde *_x) {
   return  _x->active;
}




t_sample signalOut(t_biscuitInv_tilde *_x, t_sample _current) {
    int input = (int)roundf(scaleU2X(convertB2U(_current), 0, 255));

    return (getActive(_x)==0) ? _current : (t_sample)convertU2B(scaleX2U(input^getMask(_x), 0, 255));
}

/***** DSP ***********************************************************************/

t_int* biscuitInv_tilde_perform(t_int *_w) {
    t_biscuitInv_tilde *x = (t_biscuitInv_tilde*)(_w[1]);
    t_sample *in1        = (t_sample*)(_w[2]);
    t_sample *in2        = (t_sample*)(_w[3]);
    t_sample *in3        = (t_sample*)(_w[4]);
    t_sample *in4        = (t_sample*)(_w[5]);
    t_sample *in5        = (t_sample*)(_w[6]);
    t_sample *in6        = (t_sample*)(_w[7]);
    t_sample *in7        = (t_sample*)(_w[8]);
    t_sample *in8        = (t_sample*)(_w[9]);
    t_sample *in9        = (t_sample*)(_w[10]);
    t_sample *in10       = (t_sample*)(_w[11]);
    t_sample *out1       = (t_sample*)(_w[12]);
    int vecsize          = (int)(_w[13]);

    while(vecsize--) {
        setActive(x, *in2++);
        setDigits(x, 7, *in3++);
        setDigits(x, 6, *in4++);
        setDigits(x, 5, *in5++);
        setDigits(x, 4, *in6++);
        setDigits(x, 3, *in7++);
        setDigits(x, 2, *in8++);
        setDigits(x, 1, *in9++);
        setDigits(x, 0, *in10++);
        
        *out1++ = signalOut(x, *in1++);
    }

    return (_w+14);
}

void biscuitInv_tilde_dsp(t_biscuitInv_tilde *_x, t_signal **_sp) {
  dsp_add(biscuitInv_tilde_perform, 13, _x, _sp[0]->s_vec, _sp[1]->s_vec, _sp[2]->s_vec, _sp[3]->s_vec, _sp[4]->s_vec, _sp[5]->s_vec, _sp[6]->s_vec, _sp[7]->s_vec, _sp[8]->s_vec, _sp[9]->s_vec, _sp[10]->s_vec, _sp[0]->s_n);
}

/***** constructor & destructor **************************************************/

void* biscuitInv_tilde_new(t_symbol *_s, int _argc, t_atom  *_argv) {
    t_biscuitInv_tilde *x = (t_biscuitInv_tilde*)pd_new(biscuitInv_tilde_class);

    x->inlet2active     = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
    x->inlet3digit8     = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
    x->inlet4digit7     = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
    x->inlet5digit6     = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
    x->inlet6digit5     = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
    x->inlet7digit4     = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
    x->inlet8digit3     = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
    x->inlet9digit2     = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
    x->inlet10digit1    = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
    x->outlet1          = outlet_new(&x->x_obj, &s_signal);

    switch(_argc)
    {
        default:
        case 9: setDigits(x, 0, atom_getfloat(_argv+8));
                pd_float((t_pd*)x->inlet10digit1, atom_getfloat(_argv+8));
        case 8: setDigits(x, 1, atom_getfloat(_argv+7));
                pd_float((t_pd*)x->inlet9digit2, atom_getfloat(_argv+7));
        case 7: setDigits(x, 2, atom_getfloat(_argv+6));
                pd_float((t_pd*)x->inlet8digit3, atom_getfloat(_argv+6));
        case 6: setDigits(x, 3, atom_getfloat(_argv+5));
                pd_float((t_pd*)x->inlet7digit4, atom_getfloat(_argv+5));
        case 5: setDigits(x, 4, atom_getfloat(_argv+4));
                pd_float((t_pd*)x->inlet6digit5, atom_getfloat(_argv+4));
        case 4: setDigits(x, 5, atom_getfloat(_argv+3));
                pd_float((t_pd*)x->inlet5digit6, atom_getfloat(_argv+3));
        case 3: setDigits(x, 6, atom_getfloat(_argv+2));
                pd_float((t_pd*)x->inlet4digit7, atom_getfloat(_argv+2));
        case 2: setDigits(x, 7, atom_getfloat(_argv+1));
                pd_float((t_pd*)x->inlet3digit8, atom_getfloat(_argv+1));
        case 1: setActive(x, atom_getfloat(_argv));
                pd_float((t_pd*)x->inlet2active, atom_getfloat(_argv));
                break;
        case 0: setDigits(x, 0, 0);
                setDigits(x, 1, 0);
                setDigits(x, 2, 0);
                setDigits(x, 3, 0);
                setDigits(x, 4, 0);
                setDigits(x, 5, 0);
                setDigits(x, 6, 0);
                setDigits(x, 7, 0);
                setActive(x, 0);
                pd_float((t_pd*)x->inlet10digit1, 0);
                pd_float((t_pd*)x->inlet9digit2, 0);
                pd_float((t_pd*)x->inlet8digit3, 0);
                pd_float((t_pd*)x->inlet7digit4, 0);
                pd_float((t_pd*)x->inlet6digit5, 0);
                pd_float((t_pd*)x->inlet5digit6, 0);
                pd_float((t_pd*)x->inlet4digit7, 0);
                pd_float((t_pd*)x->inlet3digit8, 0);
                pd_float((t_pd*)x->inlet2active, 0);
                break;
    }

    return (void*)x;
}

void biscuitInv_tilde_free(t_biscuitInv_tilde *_x) {
    inlet_free(_x->inlet2active);
    inlet_free(_x->inlet3digit8);
    inlet_free(_x->inlet4digit7);
    inlet_free(_x->inlet5digit6);
    inlet_free(_x->inlet6digit5);
    inlet_free(_x->inlet7digit4);
    inlet_free(_x->inlet8digit3);
    inlet_free(_x->inlet9digit2);
    inlet_free(_x->inlet10digit1);
    outlet_free(_x->outlet1);
}

/***** class setup ***************************************************************/

void biscuitInv_tilde_setup(void) {
    biscuitInv_tilde_class = class_new(gensym("biscuitInv~"), (t_newmethod)biscuitInv_tilde_new, (t_method)biscuitInv_tilde_free, sizeof(t_biscuitInv_tilde), CLASS_DEFAULT, A_GIMME, 0);

    class_addmethod(biscuitInv_tilde_class, (t_method)biscuitInv_tilde_dsp, gensym("dsp"), A_CANT, 0);
    class_sethelpsymbol(biscuitInv_tilde_class, gensym("biscuitInv~"));
    CLASS_MAINSIGNALIN(biscuitInv_tilde_class, t_biscuitInv_tilde, dummy);
}
