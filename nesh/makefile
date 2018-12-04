IDIR=../include
ODIR=obj
CC=gcc
CFLAGS=-Wall -I$(IDIR)

_DEPS = nesh.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o nesh.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

Portal : $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~