/**
 * \file test_cbfifo.c
 * \author Dayton Flores, dayton.flores@colorado.edu
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "cbfifo.h"
#include "test_cbfifo.h"

/**
 * \fn int test_cbfifo_enqueue(void* buf, size_t nbyte)
 * \brief Enqueues data onto the FIFO, up to the limit of the available FIFO capacity.
 *
 * \param buf Pointer to the data
 * \param nbyte Max number of bytes to enqueue
 *
 * \return If successful, returns EXIT_SUCCESS (0). In the case of an error, the function prints the failure and returns EXIT_FAILURE (1)
 */
//int test_cbfifo_enqueue(void* buf, size_t nbyte) {
//
//}

/**
 * \fn int test_cbfifo_dequeue(void* buf, size_t nbyte)
 * \brief Attempts to remove ("dequeue") up to nbyte bytes of data from the FIFO. Removed data will be copied into the buffer pointed to by buf.
 *
 * \param buf Destination for the dequeued data
 * \param nbyte Bytes of data requested
 *
 * \return If successful, returns EXIT_SUCCESS (0). In the case of an error, the function prints the failure and returns EXIT_FAILURE (1)
 *
 * \details To further explain the behavior: If the FIFO's current length is 24
 * bytes, and the caller requests 30 bytes, cbfifo_dequeue should
 * return the 24 bytes it has, and the new FIFO length will be 0. If
 * the FIFO is empty (current length is 0 bytes), a request to dequeue
 * any number of bytes will result in a return of 0 from
 * cbfifo_dequeue.
 */
//int test_cbfifo_dequeue(void* buf, size_t nbyte) {
//
//}

/**
 * \fn int test_cbfifo_length()
 * \brief Returns the number of bytes currently on the FIFO.
 *
 * \param N/A
 *
 * \return If successful, returns EXIT_SUCCESS (0). In the case of an error, the function prints the failure and returns EXIT_FAILURE (1)
 */
//int test_cbfifo_length() {
//
//}

/**
 * \fn int test_cbfifo_capacity()
 * \brief Returns the FIFO's capacity
 *
 * \param N/A
 *
 * \return If successful, returns EXIT_SUCCESS (0). In the case of an error, the function prints the failure and returns EXIT_FAILURE (1)
 */
//int test_cbfifo_capacity() {
//
//}