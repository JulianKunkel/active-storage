
ROOT=../../server-side-compute

CC=gcc
CFLAGS=-Wall -Wextra -g3
INCLUDES=-I$(ROOT)/emulation/
RM = rm -rf
SRC=reduce-traditionnal.c data_gen.c
BIN=reduce-traditional data-gen reduce-ngi
OBJ=libngi.so libreduce-ngi-userlib.so

all: clean build test

build: $(BIN) $(OBJ)

clean:
	$(RM) $(BIN) $(OBJ)

reduce-traditional: reduce-traditional.c
	$(CC) $(CFLAGS) $< -o $@ -g3

data-gen: data-gen.c
	$(CC) $(CFLAGS) $< -o $@ 

# Build NGI Emulation lib
libngi.so: $(ROOT)/emulation/ngi.c
	@echo 'Building ngi shared library: $@'
	$(CC) $(CLFAGS) $(INCLUDES) $< -shared -fpic -o $@

libreduce-ngi-userlib.so: reduce-ngi-userlib.c
	@echo 'Building ngi user shared library: $@'
	gcc  $(CFLAGS) -Wall -Wextra  $< -shared -fpic -o $@

reduce-ngi: reduce-ngi.c libngi.so
	$(CC) $(CFLAGS) $< -o $@ $(INCLUDES)  -L. -l ngi -Wl,-rpath=$(PWD) -ldl

test:
	@echo "Data generation"
	@./data-gen
	@echo "Executing traditional"
	@./reduce-traditional
	@echo "Executing NGI"
	@./reduce-ngi
