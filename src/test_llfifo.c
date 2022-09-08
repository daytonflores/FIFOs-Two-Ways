/**
 * \file test_llfifo.c
 * \author Dayton Flores, dayton.flores@colorado.edu
 */

#include "test_llfifo.h"

/**
 * \fn test_llfifo_create(int capacity)
 * \brief Creates and initializes the FIFO
 *
 * \param capacity Initial size of the FIFO, in number of elements. Valid values are in the range of 0 to the limits of memory
 *
 * \return If successful, returns pointer to a newly-created llfifo_t instance. In the case of an error, the function returns NULL
 */
//llfifo_t* test_llfifo_create(int capacity) {
//
//}

/**
 * \fn test_llfifo_enqueue(llfifo_t* fifo, void* element)
 * \brief Enqueues an element onto the FIFO, growing the FIFO by adding additional elements, if necessary. It is an error to attempt to enqueue the NULL pointer.
 *
 * \param fifo The fifo in question
 * \param element The element to enqueue, which cannot be NULL
 *
 * \return If successful, returns the new length of the FIFO on success. In the case of an error, the function returns -1
 */
//int test_llfifo_enqueue(llfifo_t* fifo, void* element) {
//
//}

/**
 * \fn test_llfifo_dequeue(llfifo_t* fifo)
 * \brief Removes ("dequeues") an element from the FIFO, and returns it
 *
 * \param fifo The fifo in question
 *
 * \return If successful, returns the dequeued element, or NULL if the FIFO was empty.
 */
//void* test_llfifo_dequeue(llfifo_t* fifo) {
//
//}

/**
 * \fn test_llfifo_length(llfifo_t* fifo)
 * \brief Returns the number of elements currently on the FIFO.
 *
 * \param fifo The fifo in question
 *
 * \return Returns the number of elements currently on the FIFO
 */
//int test_llfifo_length(llfifo_t* fifo) {
//
//}

/**
 * \fn test_llfifo_capacity(llfifo_t* fifo)
 * \brief Returns the FIFO's current capacity
 *
 * \param fifo The fifo in question
 *
 * \return Returns the current capacity, in number of elements, for the FIFO
 */
//int test_llfifo_capacity(llfifo_t* fifo) {
//
//}

/**
 * \fn test_llfifo_capacity(llfifo_t* fifo)
 * \brief Teardown function: Frees all dynamically allocated memory. After calling this function, the fifo should not be used again!
 *
 * \param fifo The fifo in question
 *
 * \return N/A
 */
//void test_llfifo_destroy(llfifo_t* fifo) {
//
//}