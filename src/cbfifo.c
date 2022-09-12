/**
 * \file cbfifo.c
 * \author Dayton Flores, dayton.flores@colorado.edu
 */

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "cbfifo.h"

#define BUF_SIZE ((size_t)(128))
#define EXIT_FAILURE_N ((size_t)(-1))

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
 * \fn cbfifo_enqueue(void* buf, size_t nbyte)
 * \brief Enqueues data onto the FIFO, up to the limit of the available FIFO capacity.
 *
 * \param buf Pointer to the data
 * \param nbyte Max number of bytes to enqueue
 *
 * \return If successful, returns the number of bytes actually enqueued, which could be 0. In case of an error, returns (size_t)(-1).
 */
size_t cbfifo_enqueue(void* buf, size_t nbyte) {

	size_t i;

	// Ensure buf is a valid buffer
	if (buf == NULL) {
		return EXIT_FAILURE_N;
	}

	// Return error if trying to enqueue non-zero number of bytes into a full buffer
	if (cbfifo.is_full == true && nbyte > 0) {
		return EXIT_FAILURE_N;
	}

	// Return success immediately if trying to enqueue zero bytes into buffer
	if (nbyte == 0) {
		return 0;
	}

	// Begin enqueueing byte-by-byte
	for (i = 0; i < nbyte; i++) {

		// Case of cbfifo not being full
		if (cbfifo.is_full == false) {

			// Enqueue the new byte into the buffer
			cbfifo.buf[cbfifo.head] = *((char*)(buf) + i);

			// Increment cbfifo.head without modulus operation. This assumes cbfifo.capacity is a power of 2
			cbfifo.head = (cbfifo.head + 1) & (cbfifo.capacity - 1);

			// Check if buffer is full after enqueueing this new byte
			if (cbfifo.head == cbfifo.tail) {
				cbfifo.is_full = true;
			}

			// Successfully enqueued new byte
			(cbfifo.length)++;
		}

		// Case of cbfifo being full
		else {

			// Do not enqueue anymore bytes into the buffer
			break;
		}
	}

	return (++i);
}

/**
 * \fn cbfifo_dequeue(void* buf, size_t nbyte)
 * \brief Attempts to remove ("dequeue") up to nbyte bytes of data from the FIFO. Removed data will be copied into the buffer pointed to by buf.
 *
 * \param buf Destination for the dequeued data
 * \param nbyte Bytes of data requested
 *
 * \return Returns the number of bytes actually copied, which will be between 0 and nbyte. 
 * 
 * \details To further explain the behavior: If the FIFO's current length is 24
 * bytes, and the caller requests 30 bytes, cbfifo_dequeue should
 * return the 24 bytes it has, and the new FIFO length will be 0. If
 * the FIFO is empty (current length is 0 bytes), a request to dequeue
 * any number of bytes will result in a return of 0 from
 * cbfifo_dequeue.
 */
size_t cbfifo_dequeue(void* buf, size_t nbyte) {

}

/**
 * \fn cbfifo_length()
 * \brief Returns the number of bytes currently on the FIFO.
 *
 * \param N/A
 *
 * \return Returns the number of bytes currently available to be dequeued from the FIFO
 */
size_t cbfifo_length() {

}

/**
 * \fn cbfifo_capacity()
 * \brief Returns the FIFO's capacity
 *
 * \param N/A
 *
 * \return The capacity, in bytes, for the FIFO
 */
size_t cbfifo_capacity() {

}