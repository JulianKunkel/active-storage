#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <stdbool.h>
#include <float.h>
#include <time.h>
#include <errno.h>


/*
 * Generate test data
 */


// generate float number between 0 and 99 with at most 2 decimal
float gen_float(void){
	u_int32_t my_int = rand() % 10000;
	float my_float = (float) my_int / 100;
	return my_float;
  }


// generate some data such that we can reduce it later
void prepare_data(int size){
  float * data = malloc(size * sizeof(float));
  for(int i=0; i < size; i++){
    data[i] = (float) gen_float();
  }

  FILE * file = fopen("data.bin", "wb");
  fwrite(data, size*sizeof(float), 1, file);

  fclose(file);
  free(data);
}

// parse generated data
void parse_data(int size){
  float data ;

  FILE * file = fopen("data.bin", "r");

  for(int i=0; i < size; i++){
  	int res = fread(&data, sizeof(float), 1, file);
	if (res != 1){
		res = errno;
		fprintf(stderr, "fread failed to read the right amount of float: %s\n",strerror(res));
		exit(EXIT_FAILURE);
	}
   	fprintf(stdout, "%.2f  ", data);
  }
	  
  fclose(file);
}

int main(){
  int size = 40;
  srand(time(NULL));
  prepare_data(size);
  return 0;
}
