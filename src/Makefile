CC = clang

CFLAGS4OBJ = -c -fPIC -arch x86_64 -I /Applications/Pd-0.51-1.app/Contents/Resources/src -D
CFLAGS4BIN = -dynamic -bundle -undefined dynamic_lookup -arch x86_64

.PHONY: all
all:	clear \
		easeExp~ \
		biscuitMute~ \
		biscuitInv~ \
		clean

easeExp~:
	@$(CC) $(CFLAGS4OBJ) PDFLAG=2 $@.c && $(CC) $(CFLAGS4BIN) -o $@.pd_darwin $@.o

biscuitMute~:
	@$(CC) $(CFLAGS4OBJ) PDFLAG=2 $@.c && $(CC) $(CFLAGS4BIN) -o $@.pd_darwin $@.o

biscuitInv~:
	@$(CC) $(CFLAGS4OBJ) PDFLAG=2 $@.c && $(CC) $(CFLAGS4BIN) -o $@.pd_darwin $@.o

## preparation and cleanup

.PHONY: clear
clear:
	@$(RM) ../*.pd_darwin

.PHONY: clean
clean:
	@$(RM) *.o && mv *.pd_darwin ../