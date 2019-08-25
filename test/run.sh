#!/bin/bash -e

gcc -Wall -Wextra data-gen.c -o data-gen -g3

gcc -Wall -Wextra reduce-traditional.c -o reduce-traditional -g3



# Build NGI lib
gcc -Wall -Wextra ../emulation/ngi.c -shared -fpic -o libngi.so -g3 -I../emulation/ -ldl
# Build client application
gcc -Wall -Wextra reduce-ngi.c -o reduce-ngi -g3 -I../emulation/ -L. -l ngi -Wl,-rpath=$PWD
# Build extra user library
gcc -Wall -Wextra  reduce-ngi-userlib.c  -shared -fpic -o libreduce-ngi-userlib.so -g3

echo "Data generation"
./data-gen
echo "Executing traditional"
./reduce-traditional
echo "Executing NGI"
./reduce-ngi
