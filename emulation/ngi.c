#include <ngi.h>
#include <assert.h>
#include <float.h>
#include <math.h>

int server_reduce(FILE * file, ngi_op_t op, ngi_type_t type, void * out_buff, size_t off, size_t size){
  fseek(file, off, SEEK_SET);

  assert(type == NGI_TYPE_FLOAT);
  assert(op == NGI_OP_MAX);

  float * data = malloc(size);
  fread(data, size, 1, file);

  float mx = -INFINITY;
  for(size_t i=0; i < size/sizeof(float); i++){
    mx = data[i] > mx ? data[i]: mx;
  }
  *(float*) out_buff = mx;

  free(data);
  return 0;
}

int server_reduce_any_func(FILE * file, void (*func)(int8_t * data, void * out_buff, size_t off, size_t size), void * out_buff, size_t max_out_data_size, size_t off, size_t size){
  fseek(file, off, SEEK_SET);

  int8_t * data = malloc(size);
  fread(data, size, 1, file);
  func(data, out_buff, off, size);
  free(data);
  return 0;
}
