// Copyright (c) 2020 xin.

#include <m_pd.h>
#include "common/operator.h"

/***** class declaration *********************************************************/

static t_class *psFlip_class;

typedef struct  _psFlip {
    t_object    x_obj;
    t_float     input;
    t_outlet    *out;

    int         flip;
} t_psFlip;

/***** method ********************************************************************/

void onBangMsg(t_psFlip *_x) {
    (_x->flip==0) ? outlet_float(_x->out, _x->input) : outlet_float(_x->out, flip4U(_x->input));
}

void onFloatMsg(t_psFlip *_x, t_floatarg _in) {
    _x->input = _in;
    onBangMsg(_x);
}

void setFlip(t_psFlip *_x, t_floatarg _flip) {
    _x->flip = (_flip!=0);
}

/***** constructor & destructor **************************************************/

void* psFlip_new(t_symbol *_s, t_floatarg _flip) {
    t_psFlip *x = (t_psFlip*)pd_new(psFlip_class);
    x->out      = outlet_new(&x->x_obj, &s_float);
    
    setFlip(x, _flip);

    return (void*)x;
}

void psFlip_free(t_psFlip *_x) {
    outlet_free(_x->out);
}

/***** class setup ***************************************************************/

void psFlip_setup(void) {
    psFlip_class = class_new(gensym("psFlip"), (t_newmethod)psFlip_new, (t_method)psFlip_free, sizeof(t_psFlip), CLASS_DEFAULT, A_DEFFLOAT, 0);

    class_addbang(psFlip_class, (t_method)onBangMsg);
    class_addfloat(psFlip_class, (t_method)onFloatMsg);
    class_addmethod(psFlip_class, (t_method)setFlip, gensym("flip"), A_DEFFLOAT, 0);

    class_sethelpsymbol(psFlip_class, gensym("psFlip"));
}
