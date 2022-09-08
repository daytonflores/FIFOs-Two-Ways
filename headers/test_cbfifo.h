/**
 * \file test_cbfifo.h
 * \author Dayton Flores, dayton.flores@colorado.edu
 */

#ifndef _TEST_CBFIFO_H_
#define _TEST_CBFIFO_H_

#include "cbfifo.h"

size_t test_cbfifo_enqueue(void* buf, size_t nbyte);
size_t test_cbfifo_dequeue(void* buf, size_t nbyte);
size_t test_cbfifo_length();
size_t test_cbfifo_capacity();

#endif // _TEST_CBFIFO_H_