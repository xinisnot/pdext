CC = clang

CFLAGS4OBJ = -c -fPIC -arch x86_64 -I /Applications/Pd-0.51-1.app/Contents/Resources/src -D
CFLAGS4BIN = -dynamic -bundle -undefined dynamic_lookup -arch x86_64

.PHONY: all
all:	clear \
		shapeU~ \
		easeExpU~ \
		scale~ \
		latch~ \
		biscuitInv~ \
		biscuitMask~ \
		sinusoid~ \
		triangle~ \
		clock~ \
		clean

shapeU~:
	@$(CC) $(CFLAGS4OBJ) PDFLAG=1 $@.c && $(CC) $(CFLAGS4BIN) -o $@.pd_darwin $@.o

easeExpU~:
	@$(CC) $(CFLAGS4OBJ) PDFLAG=1 $@.c && $(CC) $(CFLAGS4BIN) -o $@.pd_darwin $@.o

scale~:
	@$(CC) $(CFLAGS4OBJ) PDFLAG=1 $@.c && $(CC) $(CFLAGS4BIN) -o $@.pd_darwin $@.o

latch~:
	@$(CC) $(CFLAGS4OBJ) PDFLAG=1 $@.c && $(CC) $(CFLAGS4BIN) -o $@.pd_darwin $@.o

biscuitInv~:
	@$(CC) $(CFLAGS4OBJ) PDFLAG=1 $@.c && $(CC) $(CFLAGS4BIN) -o $@.pd_darwin $@.o

biscuitMask~:
	@$(CC) $(CFLAGS4OBJ) PDFLAG=1 $@.c && $(CC) $(CFLAGS4BIN) -o $@.pd_darwin $@.o

sinusoid~:
	@$(CC) $(CFLAGS4OBJ) PDFLAG=1 $@.c && $(CC) $(CFLAGS4BIN) -o $@.pd_darwin $@.o

triangle~:
	@$(CC) $(CFLAGS4OBJ) PDFLAG=1 $@.c && $(CC) $(CFLAGS4BIN) -o $@.pd_darwin $@.o

clock~:
	@$(CC) $(CFLAGS4OBJ) PDFLAG=1 $@.c && $(CC) $(CFLAGS4BIN) -o $@.pd_darwin $@.o

## preparation and cleanup

.PHONY: clear
clear:
	@$(RM) ../*.pd_darwin

.PHONY: clean
clean:
	@$(RM) *.o && mv *.pd_darwin ../