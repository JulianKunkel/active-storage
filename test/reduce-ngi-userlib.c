#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <stdbool.h>
#include <float.h>
#include <math.h>

/*
 Extra user library provided
 */

void reduce_minmax_func_external(int8_t * data_i, void * out_buff, size_t off, size_t size){
  float * outf = (float*) out_buff;
  float mi = outf[0];
  float mx = outf[1];
  float * data = (float*) data_i;
  for(size_t i=0; i < size/sizeof(float); i++){
    mx = data[i] > mx ? data[i]: mx;
    mi = data[i] < mi ? data[i]: mi;
  }
  outf[0] = mi;
  outf[1] = mx;
}
