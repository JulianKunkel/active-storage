#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <stdbool.h>
#include <float.h>


/*
 * This application shows a traditional reduce operation
 */

// read the data and reduce it
void reduce_data(int size){
  float * data = malloc(size * sizeof(float));
  FILE * file = fopen("data.bin", "rb");
  fread(data, size*sizeof(float), 1, file);
  fclose(file);

  float mx = FLT_MIN;
  for(int i=0; i < size; i++){
    mx = data[i] > mx ? data[i]: mx;
  }
  free(data);

  printf("Maximum: %f\n", mx);
}



int main(){
  int size = 100;
  reduce_data(size);
  return 0;
}
