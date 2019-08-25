#ifndef NGI_H_
#define NGI_H_

#include <stdlib.h>
#include <stdio.h>
//#include "ngi_log.h"

/*
 * Define the size in B of file extent exchanged between server and clint
 */
#define NGI_EXT_SZ 1048576

typedef enum NGI_OP{
  NGI_OP_MAX
} ngi_op_t;

typedef enum NGI_TYPE{
  NGI_TYPE_FLOAT
} ngi_type_t;

/*
 *
 */
int ngi_server_side_reduce(FILE * , ngi_op_t , ngi_type_t , void * , size_t , size_t );
int ngi_client_side_reduce(FILE * , ngi_op_t , ngi_type_t , void * , size_t , size_t );
int ngi_reduce_stub(FILE * , ngi_op_t , ngi_type_t , void * , size_t , size_t );
/*
 * This function invoces a well known reduction operation on data of a well known type
 * Return 0 upon success, any other code, if e.g., short read
 */
int server_reduce(FILE * file, ngi_op_t op, ngi_type_t type, void * out_buff, size_t off, size_t size);

/*
 * This function runs any type of function on the data
 * It assumes that the output buffer was initialized accordingly and that it is of max_out_data_size
 * func must be associative and needs to read/output the output buffer as intermediate storage
 * Return 0 upon success, any other code, if e.g., short read
 */
int server_reduce_any_func(FILE * file, void (*func)(int8_t * data, void * out_buff, size_t off, size_t size), void * out_buff, size_t max_out_data_size, size_t off, size_t size);

int server_reduce_any_func_lib(FILE * file, char const * libname, char const * funcname, void * out_buff, size_t max_out_data_size, size_t off, size_t size);


#endif
