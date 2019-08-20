#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <stdbool.h>
#include <float.h>


/*
 * Generate test data
 */

// generate some data such that we can reduce it later
void prepare_data(int size){
  float * data = malloc(size * sizeof(float));
  for(int i=0; i < size; i++){
    data[i] = (float) i;
  }

  FILE * file = fopen("data.bin", "wb");
  fwrite(data, size*sizeof(float), 1, file);

  fclose(file);
  free(data);
}

int main(){
  int size = 100;
  prepare_data(size);
  return 0;
}
