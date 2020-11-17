// Copyright (c) 2020 xin.

#include <m_pd.h>
#include "common/operator.h"

/***** class declaration *********************************************************/

static t_class *psEaseExp_class;

typedef struct _psEaseExp {
	t_object	x_obj;
	t_float		input;
	t_outlet	*out;

	double		curve;
	int			mode;
} t_psEaseExp;

/***** method ********************************************************************/

void onBangMsg(t_psEaseExp *_x) {
	switch(_x->mode)
	{
		default:
		case 0: outlet_float(_x->out, (t_float)easeInExponent4U(_x->input, _x->curve));
				break;
		case 1: outlet_float(_x->out, (t_float)easeOutExponent4U(_x->input, _x->curve));
				break;
		case 2: outlet_float(_x->out, (t_float)easeInOutExponent4U(_x->input, _x->curve));
				break;
		case 3: outlet_float(_x->out, (t_float)easeOutInExponent4U(_x->input, _x->curve));
				break;
	}
}

void onFloatMsg(t_psEaseExp *_x, t_floatarg _in) {
	_x->input = _in;
	onBangMsg(_x);
}

void setCurve(t_psEaseExp *_x, t_floatarg _curve) {
	_x->curve = _curve;
}

void setMode(t_psEaseExp *_x, t_floatarg _mode) {
	_x->mode = _mode;
}

/***** constructor & destructor **************************************************/

void* psEaseExp_new(t_symbol *_s, int _argc, t_atom  *_argv) {
	t_psEaseExp *x	= (t_psEaseExp*)pd_new(psEaseExp_class);
	x->out				= outlet_new(&x->x_obj, &s_float);
	
	switch(_argc)
	{
		default:
		case 2: setMode(x, atom_getfloat(_argv+1));
		case 1: setCurve(x, atom_getfloat(_argv));
				break;
		case 0: setMode(x, 0);
				setCurve(x, 0);
				break;
	}

	return (void*)x;
}

void psEaseExp_free(t_psEaseExp *_x) {
	outlet_free(_x->out);
}

/***** class setup ***************************************************************/

void psEaseExp_setup(void) {
	psEaseExp_class = class_new(gensym("psEaseExp"), (t_newmethod)psEaseExp_new, (t_method)psEaseExp_free, sizeof(t_psEaseExp), CLASS_DEFAULT, A_GIMME, 0);

	class_addbang(psEaseExp_class, (t_method)onBangMsg);
	class_addfloat(psEaseExp_class, (t_method)onFloatMsg);
	class_addmethod(psEaseExp_class, (t_method)setCurve, gensym("curve"), A_DEFFLOAT, 0);
	class_addmethod(psEaseExp_class, (t_method)setMode, gensym("mode"), A_DEFFLOAT, 0);

	class_sethelpsymbol(psEaseExp_class, gensym("psEaseExp"));
}
