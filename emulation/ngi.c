#include <ngi.h>
#include <ngi_log.h>
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

/*
 * this function should be called by IME client on the compute node 
 */
int ngi_client_side_reduce(FILE * file, ngi_op_t op, ngi_type_t type, void * out_buff, size_t off, size_t size){
  ngi_dbg("Starting offset %lu size %lu Byte\n",off, size);
  assert(size <= NGI_EXT_SZ);
  fseek(file, off, SEEK_SET);

  assert(type == NGI_TYPE_FLOAT);
  assert(op == NGI_OP_MAX);
  int res = ngi_server_side_reduce(file, op, type, out_buff, off, size);
  assert(res == 0);
  exit(0);
  return res;
}

/*
 * this function should be called by IME server on the storage appliance
 */

int ngi_server_side_reduce(FILE * file, ngi_op_t op, ngi_type_t type, void * out_buff, size_t off, size_t ext_sz){

  ngi_dbg("Starting offset %lu size %lu Byte\n",off, ext_sz);
  assert(type == NGI_TYPE_FLOAT);
  assert(op == NGI_OP_MAX);
  assert(ext_sz  <= NGI_EXT_SZ);

  float * data = malloc(ext_sz);
  fseek(file, off, 0);
  fread(data, ext_sz, 1, file);

  float mx = -INFINITY;
  for(size_t i=0; i < ext_sz/sizeof(float); i++){
    mx = data[i] > mx ? data[i]: mx;
  }
  ngi_dbg("Result: %f \n", mx);
  *(float*) out_buff = mx;

  free(data);
  return 0;
}

/*
 * this function split the reduction in a set of client server transaction
 */
int ngi_reduce_stub(FILE * file, ngi_op_t op, ngi_type_t type, void * out_buff, size_t off, size_t size){
  fseek(file, off, SEEK_SET);

  assert(type == NGI_TYPE_FLOAT);
  assert(op == NGI_OP_MAX);
  u_int32_t nb_tx = size / NGI_EXT_SZ;
  // handle remainder in extend computation
  if (size % NGI_EXT_SZ != 0)
	  nb_tx += 1;

  float *tmp_red = (float*) malloc(sizeof(float*) * nb_tx); 

  /* will be executed in parallel withint the client */
  ngi_dbg("Reduction from %lu to %lu Byte in %u transactions\n", off, size, nb_tx);
  for(u_int32_t i = 0; i < nb_tx ; i++){
	  size_t ext_off =  off + NGI_EXT_SZ * i;
	  int res = ngi_client_side_reduce(file, op, type, &tmp_red[i], ext_off, NGI_EXT_SZ);
	  assert(res == 0);

  }
  float mx = -INFINITY;
  for(u_int32_t i = 0; i < nb_tx ; i++){
    mx = tmp_red[i] > mx ? tmp_red[i]: mx;
  }

  *(float*) out_buff = mx;
  free(tmp_red);
  return 0;
}

int ngi_reduce(FILE * file, ngi_op_t op, ngi_type_t type, void * out_buff, size_t off, size_t size){
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
