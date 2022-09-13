/**
 * \file test_cbfifo.h
 * \author Dayton Flores, dayton.flores@colorado.edu
 */

#ifndef _TEST_CBFIFO_H_
#define _TEST_CBFIFO_H_

#include "cbfifo.h"

void test_cbfifo();
int test_cbfifo_enqueue(void* buf, size_t nbyte, size_t max_bytes);
int test_cbfifo_dequeue(void* buf, size_t nbyte, size_t max_bytes);
int test_cbfifo_length(size_t max_bytes);
int test_cbfifo_capacity(size_t max_bytes);
void cbfifo_dump_state(size_t max_bytes);

#endif // _TEST_CBFIFO_H_