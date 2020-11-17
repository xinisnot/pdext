// Copyright (c) 2020 xin.

#include <m_pd.h>
#include "common/operator.h"

/***** class declaration *********************************************************/

static t_class *psShift_class;

typedef struct _psShift {
	t_object	x_obj;
	t_float		input;
	t_outlet	*out;

	double		ratio;
	int			mode;
} t_psShift;

/***** method ********************************************************************/

void onBangMsg(t_psShift *_x) {
	(_x->mode==0) ? outlet_float(_x->out, (t_float)shiftHalf4U(_x->input, _x->ratio)) : outlet_float(_x->out, (t_float)shiftQuarter4U(_x->input, _x->ratio));
}

void onFloatMsg(t_psShift *_x, t_floatarg _in) {
	_x->input = _in;
	onBangMsg(_x);
}

void setRatio(t_psShift *_x, t_floatarg _ratio) {
	_x->ratio = _ratio;
}

void setMode(t_psShift *_x, t_floatarg _mode) {
	_x->mode = (_mode!=0);
}

/***** constructor & destructor **************************************************/

void* psShift_new(t_symbol *_s, int _argc, t_atom  *_argv) {
	t_psShift *x	= (t_psShift*)pd_new(psShift_class);
	x->out		= outlet_new(&x->x_obj, &s_float);

	switch(_argc)
	{
		default:
		case 2: setMode(x, atom_getfloat(_argv+1));
		case 1: setRatio(x, atom_getfloat(_argv));
				break;
		case 0: setMode(x, 0);
				setRatio(x, 0.5);
				break;
	}

	return (void*)x;
}

void psShift_free(t_psShift *_x) {
	outlet_free(_x->out);
}

/***** class setup ***************************************************************/

void psShift_setup(void) {
	psShift_class = class_new(gensym("psShift"), (t_newmethod)psShift_new, (t_method)psShift_free, sizeof(t_psShift), CLASS_DEFAULT, A_GIMME, 0);

	class_addbang(psShift_class, (t_method)onBangMsg);
	class_addfloat(psShift_class, (t_method)onFloatMsg);
	class_addmethod(psShift_class, (t_method)setRatio, gensym("ratio"), A_DEFFLOAT, 0);
	class_addmethod(psShift_class, (t_method)setMode, gensym("mode"), A_DEFFLOAT, 0);

	class_sethelpsymbol(psShift_class, gensym("psShift"));
}
