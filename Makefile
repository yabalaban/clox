CC=cc
CFLAGS=-Wall
DEPS = common.h
ODIR = obj
BDIR = bin

_OBJ = chunk.o debug.o main.o memory.o value.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	@ mkdir -p $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) 

$(BDIR)/clox: $(OBJ)
	@ mkdir -p $(BDIR)
	$(CC) -o $@ $^ $(CFLAGS) 

.PHONY: clean

clean:
	rm -rf $(ODIR)
	rm -rf $(BDIR)