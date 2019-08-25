#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <stdbool.h>
#include <float.h>
#include <math.h>

#include <ngi.h>

/*
 * This application applies the reduce operation using the server-side compute using NGI
 */

// read the data and reduce it
void reduce_data(int size){
  FILE * file = fopen("data.bin", "rb");
  float mx;
  server_reduce(file, NGI_OP_MAX, NGI_TYPE_FLOAT, & mx, 0, size*sizeof(float));
  printf("Maximum: %f\n", mx);
  fclose(file);
}

void reduce_min_func(int8_t * data_i, void * out_buff, size_t off, size_t size){
  float * outf = (float*) out_buff;
  float mx = *outf;
  float * data = (float*) data_i;
  for(size_t i=0; i < size/sizeof(float); i++){
    mx = data[i] > mx ? data[i]: mx;
  }
  *outf = mx;
}

void reduce_minmax_func(int8_t * data_i, void * out_buff, size_t off, size_t size){
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

// alternative using an internal function
void reduce_data_func(int size){
  FILE * file = fopen("data.bin", "rb");
  float mx;
  mx = -INFINITY;
  server_reduce_any_func(file, reduce_min_func, &mx, sizeof(float), 0, size*sizeof(float));
  printf("Maximum: %f\n", mx);

  float minmax[2] = {INFINITY, -INFINITY};
  server_reduce_any_func(file, reduce_minmax_func, minmax, 2* sizeof(float), 0, size*sizeof(float));
  printf("Min/Max: %f - %f\n", minmax[0], minmax[1]);
  fclose(file);
}

// alternative using an external library function shipped a s lib
void reduce_data_func_lib(int size){
  FILE * file = fopen("data.bin", "rb");
  float minmax[2] = {INFINITY, -INFINITY};
  server_reduce_any_func_lib(file, "./libreduce-ngi-userlib.so", "reduce_minmax_func_external", minmax, 2* sizeof(float), 0, size*sizeof(float));
  printf("Using the external library libreduce-ngi-userlib.so provided by the user: Min/Max: %f - %f\n", minmax[0], minmax[1]);
  fclose(file);
}


int main(){
  int size = 100;
  reduce_data(size);
  reduce_data_func(size);
  reduce_data_func_lib(size);
  return 0;
}
