/**
 * \file test_cbfifo.c
 * \author Dayton Flores, dayton.flores@colorado.edu
 */

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "cbfifo.h"
#include "test_cbfifo.h"

#define BUF_SIZE ((size_t)(8))

 /**
  * \typedef cbfifo_t
  * \brief Allows struct cbfifo_s to be instantiated as cbfifo_t
  */
typedef struct cbfifo_s cbfifo_t;

/**
 * \struct cbfifo_s
 * \brief Circular buffer of fixed size
 *
 * \detail uint8_t buf[BUF_SIZE] - Buffer of fixed size. It is BUF_SIZE number of bytes large
 * \detail size_t head - Current head. This increments just after elements are added to buf
 * \detail size_t tail - Current tail. This increments just after elements are removed from buf
 * \detail size_t capacity - The amount of bytes the buffer can store at a time
 * \detail size_t length - The amount of bytes currently stored in the buffer
 * \detail bool is_full - Flag to keep track of status of the buf
 */
struct cbfifo_s {
	uint8_t buf[BUF_SIZE];
	size_t head;
	size_t tail;
	size_t capacity;
	size_t length;
	bool is_full;
};

/**
 * \var extern cbfifo_t cbfifo
 * \brief A single global instance of circular buffer. Defined in main.c
 */
extern cbfifo_t cbfifo;

 /**
  * \fn void cbfifo_dump_state(llfifo_t* fifo)
  * \brief Dumps info about each element in the FIFO
  *
  * \param fifo Points to the FIFO for which to dump element info about
  *
  * \return N/A
  */
void cbfifo_dump_state() {

	int i;
	size_t index;

	assert(&cbfifo != NULL);

	// Print state of FIFO
	printf("\tcbfifo at %p\n", (void*)(&cbfifo));
	printf("\tcbfifo->head is %d\n", cbfifo.head);
	printf("\tcbfifo->tail is %d\n", cbfifo.tail);
	printf("\tcbfifo->capacity is %d\n", cbfifo.capacity);
	printf("\tcbfifo->length is %d\n", cbfifo.length);

	// Print list of free elements
	if ((cbfifo.capacity - cbfifo.length) == 0) {
		printf("\t\tFREE : Empty list");
	}
	else {
		for (i = 0; i < (cbfifo.capacity - cbfifo.length); i++) {

			if (i == 0) {
				index = cbfifo.head;
			}
			else {
				index = (index + 1) & (cbfifo.capacity - 1);
			}

			printf("\t\tFREE[%d] : %u\n", index, cbfifo.buf[index]);

		}
	}

	// Print list of used elements
	if (cbfifo.length == 0) {
		printf("\t\tUSED : Empty list");
	}
	else {
		for (i = 0; i < (cbfifo.length); i++) {

			if (i == 0) {
				index = cbfifo.tail;
			}
			else {
				index = (index + 1) & (cbfifo.capacity - 1);
			}

			printf("\t\tUSED[%d] : %u\n", index, cbfifo.buf[index]);

		}
	}
}

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