CC = clang

CFLAGS4OBJ = -c -fPIC -arch x86_64 -I /Applications/Pd-0.51-1.app/Contents/Resources/src -D
CFLAGS4BIN = -dynamic -bundle -undefined dynamic_lookup -arch x86_64

.PHONY: all
all:	clear \
		psEaseExp \
		psShift \
		psFlip \
		psComp \
		psStep \
		pTriangle \
		clean

psEaseExp:
	@$(CC) $(CFLAGS4OBJ) PDFLAG=1 $@.c && $(CC) $(CFLAGS4BIN) -o $@.pd_darwin $@.o

psShift:
	@$(CC) $(CFLAGS4OBJ) PDFLAG=1 $@.c && $(CC) $(CFLAGS4BIN) -o $@.pd_darwin $@.o

psFlip:
	@$(CC) $(CFLAGS4OBJ) PDFLAG=1 $@.c && $(CC) $(CFLAGS4BIN) -o $@.pd_darwin $@.o

psComp:
	@$(CC) $(CFLAGS4OBJ) PDFLAG=1 $@.c && $(CC) $(CFLAGS4BIN) -o $@.pd_darwin $@.o

psStep:
	@$(CC) $(CFLAGS4OBJ) PDFLAG=1 $@.c && $(CC) $(CFLAGS4BIN) -o $@.pd_darwin $@.o

pTriangle:
	@$(CC) $(CFLAGS4OBJ) PDFLAG=1 $@.c && $(CC) $(CFLAGS4BIN) -o $@.pd_darwin $@.o

## preparation and cleanup

.PHONY: clear
clear:
	@$(RM) ../*.pd_darwin

.PHONY: clean
clean:
	@$(RM) *.o && mv *.pd_darwin ../