/**
 * \file cbfifo.c
 * \author Dayton Flores, dayton.flores@colorado.edu
 */

#include <stdint.h>
#include <stdlib.h>
#include "cbfifo.h"

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