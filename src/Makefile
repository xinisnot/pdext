CC = clang

cflags_for_obj	= -c -fPIC -arch x86_64 -I /Applications/Pd-0.51-1.app/Contents/Resources/src
cflags_for_bin	= -dynamic -bundle -undefined dynamic_lookup -arch x86_64

cmd_for_bin = $(CC) $^ $(cflags_for_bin) -o $@
cmd_for_obj = $(CC) $(cflags_for_obj)



.PHONY: all
all:	clear \
		psEaseExp.pd_darwin \
		psShift.pd_darwin \
		psFlip.pd_darwin \
		psComp.pd_darwin \
		clean

## build .pd_darwin

# FUNCTIONTEST.pd_darwin: FUNCTIONTEST.o operator.o arithmetic.o
# 	@$(cmd_for_bin)

# FUNCTIONTEST.o:
# 	@$(cmd_for_obj) FUNCTIONTEST.c

# b2u.pd_darwin: b2u.o calc.o
# 	@$(cmd_for_bin)

# b2u.o:
# 	@$(cmd_for_obj) b2u.c

# scale2u.pd_darwin: scale2u.o calc.o
# 	@$(cmd_for_bin)

# scale2u.o:
# 	@$(cmd_for_obj) scale2u.c

# flip.pd_darwin: flip.o calc.o
# 	@$(cmd_for_bin)

# flip.o:
# 	@$(cmd_for_obj) flip.c

# reciprocal.pd_darwin: reciprocal.o calc.o
# 	@$(cmd_for_bin)

# reciprocal.o:
# 	@$(cmd_for_obj) reciprocal.c

# sign.pd_darwin: sign.o calc.o
# 	@$(cmd_for_bin)

# sign.o:
# 	@$(cmd_for_obj) sign.c

psEaseExp.pd_darwin: psEaseExp.o operator.o arithmetic.o
	@$(cmd_for_bin)

psEaseExp.o:
	@$(cmd_for_obj) psEaseExp.c

psShift.pd_darwin: psShift.o operator.o arithmetic.o
	@$(cmd_for_bin)

psShift.o:
	@$(cmd_for_obj) psShift.c

psComp.pd_darwin: psComp.o operator.o arithmetic.o
	@$(cmd_for_bin)

psComp.o:
	@$(cmd_for_obj) psComp.c

psFlip.pd_darwin: psFlip.o operator.o arithmetic.o
	@$(cmd_for_bin)

psFlip.o:
	@$(cmd_for_obj) psFlip.c

# easeOutExponent.pd_darwin: easeOutExponent.o calc.o
# 	@$(cmd_for_bin)

# easeOutExponent.o:
# 	@$(cmd_for_obj) easeOutExponent.c

# easeInOutExponent.pd_darwin: easeInOutExponent.o calc.o
# 	@$(cmd_for_bin)
# easeInOutExponent.o:

# 	@$(cmd_for_obj) easeInOutExponent.c

# easeOutInExponent.pd_darwin: easeOutInExponent.o calc.o
# 	@$(cmd_for_bin)
	
# easeOutInExponent.o:
# 	@$(cmd_for_obj) easeOutInExponent.c

# add.pd_darwin: add.o
# 	@$(cmd_for_bin)

# add.o:
# 	@$(cmd_for_obj) add.c

# sub.pd_darwin: sub.o
# 	@$(cmd_for_bin)

# sub.o:
# 	@$(cmd_for_obj) sub.c

# mul.pd_darwin: mul.o
# 	@$(cmd_for_bin)

# mul.o:
# 	@$(cmd_for_obj) mul.c

# div.pd_darwin: div.o
# 	@$(cmd_for_bin)

# div.o:
# 	@$(cmd_for_obj) div.c

# sin.pd_darwin: sin.o arithmetic.o
# 	@$(cmd_for_bin)

# sin.o:
# 	@$(cmd_for_obj) sin.c

# cos.pd_darwin: cos.o arithmetic.o
# 	@$(cmd_for_bin)

# cos.o:
# 	@$(cmd_for_obj) cos.c

# tan.pd_darwin: tan.o arithmetic.o
# 	@$(cmd_for_bin)

# tan.o:
# 	@$(cmd_for_obj) tan.c

# meanA.pd_darwin: meanA.o arithmetic.o
# 	@$(cmd_for_bin)

# meanA.o:
# 	@$(cmd_for_obj) meanA.c

## build common library

operator.o:
	@$(cmd_for_obj) ./common/operator.c

arithmetic.o:
	@$(cmd_for_obj) ./common/arithmetic.c

## preparation and cleanup

.PHONY: clean
clean:
	@$(RM) *.o && mv *.pd_darwin ../

.PHONY: clear
clear:
	@$(RM) ../*.pd_darwin