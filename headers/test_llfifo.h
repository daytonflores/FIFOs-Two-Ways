/**
 * \file test_llfifo.h
 * \author Dayton Flores, dayton.flores@colorado.edu
 */

#ifndef _TEST_LLFIFO_H_
#define _TEST_LLFIFO_H_

#include "llfifo.h"

void llfifo_dump_state(llfifo_t* fifo);
int test_llfifo_create(int capacity);
int test_llfifo_enqueue(llfifo_t* fifo, void* element);
int test_llfifo_dequeue(llfifo_t* fifo);
int test_llfifo_length(llfifo_t* fifo);
int test_llfifo_capacity(llfifo_t* fifo);
int test_llfifo_destroy(llfifo_t* fifo);

#endif // _TEST_LLFIFO_H_