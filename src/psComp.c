// Copyright (c) 2020 xin.

#include <m_pd.h>
#include "common/operator.h"

/***** class declaamountn *********************************************************/

static t_class *psComp_class;

typedef struct _psComp {
	t_object	x_obj;
	t_float		input;
	t_outlet	*out;

	double		amount;
	int			mode;
} t_psComp;

/***** method ********************************************************************/

void onBangMsg(t_psComp *_x) {
	(_x->mode==0) ? outlet_float(_x->out, (t_float)compHalf4U(_x->input, _x->amount)) : outlet_float(_x->out, (t_float)compQuarter4U(_x->input, _x->amount));
}

void onFloatMsg(t_psComp *_x, t_floatarg _in) {
	_x->input = _in;
	onBangMsg(_x);
}

void setAmount(t_psComp *_x, t_floatarg _amount) {
	_x->amount = _amount;
}

void setMode(t_psComp *_x, t_floatarg _mode) {
	_x->mode = (_mode!=0);
}

/***** constructor & destructor **************************************************/

void* psComp_new(t_symbol *_s, int _argc, t_atom  *_argv) {
	t_psComp *x	= (t_psComp*)pd_new(psComp_class);
	x->out		= outlet_new(&x->x_obj, &s_float);

	switch(_argc)
	{
		default:
		case 2: setMode(x, atom_getfloat(_argv+1));
		case 1: setAmount(x, atom_getfloat(_argv));
				break;
		case 0: setMode(x, 0);
				setAmount(x, 0);
				break;
	}

	return (void*)x;
}

void psComp_free(t_psComp *_x) {
	outlet_free(_x->out);
}

/***** class setup ***************************************************************/

void psComp_setup(void) {
	psComp_class = class_new(gensym("psComp"), (t_newmethod)psComp_new, (t_method)psComp_free, sizeof(t_psComp), CLASS_DEFAULT, A_GIMME, 0);

	class_addbang(psComp_class, (t_method)onBangMsg);
	class_addfloat(psComp_class, (t_method)onFloatMsg);
	class_addmethod(psComp_class, (t_method)setAmount, gensym("amount"), A_DEFFLOAT, 0);
	class_addmethod(psComp_class, (t_method)setMode, gensym("mode"), A_DEFFLOAT, 0);

	class_sethelpsymbol(psComp_class, gensym("psComp"));
}
