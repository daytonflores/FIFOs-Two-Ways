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

	size_t bytes_enqueued = 0;
	size_t i;

	// Ensure buf is a valid buffer to read from
	if (buf == NULL) {
		return EXIT_FAILURE_N;
	}

	// Return error if trying to enqueue non-zero number of bytes into a full FIFO
	if (cbfifo.is_full == true && nbyte > 0) {
		return EXIT_FAILURE_N;
	}

	// Return 0 immediately if trying to enqueue zero bytes into FIFO
	if (nbyte == 0) {
		return bytes_enqueued;
	}

	// Begin enqueueing byte-by-byte
	for (i = 0; i < nbyte; i++) {

		// Case of FIFO not being full
		if (cbfifo.is_full == false) {

			// Enqueue byte from buffer into FIFO
			cbfifo.buf[cbfifo.head] = *((char*)(buf) + i);

			// Increment FIFO head for circular buffer without modulus operation. This assumes FIFO capacity is a power of 2
			cbfifo.head = (cbfifo.head + 1) & (cbfifo.capacity - 1);

			// Check if FIFO is full after enqueueing byte
			if (cbfifo.head == cbfifo.tail) {
				cbfifo.is_full = true;
			}

			// Successfully enqueued byte
			(cbfifo.length)++;
			bytes_enqueued++;
		}

		// Case of FIFO being full
		else {

			// Do not enqueue anymore bytes into FIFO
			break;
		}
	}

	return (bytes_enqueued);
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

	size_t bytes_dequeued = 0;
	size_t i;

	// Ensure buf is a valid buffer to write to
	if (buf == NULL) {
		return EXIT_FAILURE_N;
	}

	// Return 0 immediately if trying to dequeue from empty FIFO
	if (cbfifo.length == 0) {
		return bytes_dequeued;
	}

	// Return 0 immediately if trying to dequeue zero bytes into FIFO
	if (nbyte == 0) {
		return bytes_dequeued;
	}

	// Begin dequeueing byte-by-byte
	for (i = 0; i < nbyte; i++) {

		// Case of FIFO having bytes available to dequeue
		if (cbfifo.length > 0) {

			// Dequeue byte from FIFO into buffer
			*((char*)(buf) + i) = cbfifo.buf[cbfifo.tail];

			// Increment FIFO tail for circular buffer without modulus operation. This assumes FIFO capacity is a power of 2
			cbfifo.tail = (cbfifo.tail + 1) & (cbfifo.capacity - 1);

			// Check if byte was just dequeued from a full FIFO
			if (cbfifo.is_full == true) {
				cbfifo.is_full = false;
			}

			// Successfully dequeued byte from FIFO
			(cbfifo.length)--;
			bytes_dequeued++;
		}

		// Case of FIFO being empty
		else {

			// Do not dequeue anymore bytes from FIFO
			break;
		}
	}

	return (bytes_dequeued);
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

	return cbfifo.length;
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

	return cbfifo.capacity;
}