
ROOT=../../server-side-compute

CC=gcc
CFLAGS=-Wall -Wextra -g3
INCLUDES=-I$(ROOT)/emulation/
RM = rm -rf
SRC=reduce-traditionnal.c data_gen.c
BIN=reduce-traditional data-gen reduce-ngi
OBJ=libngi.so

all: clean build test

build: data-gen reduce-ngi reduce-traditional

clean:
	$(RM) $(BIN) $(OBJ)

reduce-traditional: reduce-traditional.c
	$(CC) $(CFLAGS) $< -o $@ -g3

data-gen: data-gen.c
	$(CC) $(CFLAGS) $< -o $@ 

# Build NGI Emulation lib
libngi.so: $(ROOT)/emulation/ngi.c
	@echo 'Building ngi shared library: $@'
	@echo $(ROOT)
	$(CC) $(CLFAFS) $(INCLUDES) $< -shared -fpic -o $@

reduce-ngi: reduce-ngi.c libngi.so
	$(CC) $(CFLAGS) $< -o $@ $(INCLUDES)  -L. -l ngi -Wl,-rpath=$(PWD)

test:
	@echo "Data generation"
	@./data-gen
	@echo "Executing traditional"
	@./reduce-traditional
	@echo "Executing NGI"
	@./reduce-ngi
