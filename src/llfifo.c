/**
 * \file llfifo.c
 * \author Dayton Flores, dayton.flores@colorado.edu
 */

#include <stdint.h>
#include <stdlib.h>
#include "llfifo.h"

#define EXIT_FAILURE_N (-1)

 /**
  * The llnode's main data structure.
  * 
  * Defined here as an incomplete type.
  * Struct defined right below
  */
typedef struct llnode_s llnode_t;

struct llnode_s {
	void* data;
	llnode_t* previous;
	llnode_t* next;
};

struct llfifo_s {
	llnode_t* head_free;
	llnode_t* tail_free;
	llnode_t* head_used;
	llnode_t* tail_used;
	int capacity;
	int length;
};

 /**
  * \fn llfifo_create(int capacity)
  * \brief Creates and initializes the FIFO
  *
  * \param capacity Initial size of the FIFO, in number of elements. Valid values are in the range of 0 to the limits of memory
  *
  * \return If successful, returns pointer to a newly-created llfifo_t instance. In the case of an error, the function returns NULL
  */
llfifo_t* llfifo_create(int capacity) {

	int i;
	llfifo_t* fifo;
	llnode_t* new_node;

	// Ensure amount of free nodes to allocate space for is valid
	if (capacity < 0) {
		return NULL;
	}

	// Initialize FIFO for size 0
	fifo->head_free = NULL;
	fifo->tail_free = NULL;
	fifo->head_used = NULL;
	fifo->tail_used = NULL;
	fifo->capacity = 0;
	fifo->length = 0;

	// Begin allocating memory for capacity number of free nodes
	for (i = 0; i < capacity; i++) {

		// Ensure malloc is successful for a new free node
		new_node = (llnode_t*)malloc(sizeof(llnode_t));
		if (new_node == NULL) {
			return NULL;
		}

		// During 1st iteration
		if (i == 0) {

			// Special case of inserting into empty free list
			new_node->data = NULL;
			new_node->previous = NULL;
			new_node->next = NULL;

			// Set new free node as both free head & free tail
			fifo->head_free = new_node;
			fifo->tail_free = new_node;
		}

		// During all other iterations
		else {

			// Generic case of insert into free list containing at least 1 node
			new_node->data = NULL;
			new_node->previous = fifo->head_free;
			new_node->next = NULL;

			// Link old free head to new free node
			fifo->head_free->next = new_node;

			// Set new free node as free head only (do not touch free tail since there would be other nodes)
			fifo->head_free = new_node;
		}

		// FIFO has gotten a new free node so capacity has increased
		fifo->capacity++;
	}

	return fifo;
}

/**
 * \fn llfifo_enqueue(llfifo_t* fifo, void* element)
 * \brief Enqueues an element onto the FIFO, growing the FIFO by adding additional elements, if necessary. It is an error to attempt to enqueue the NULL pointer.
 *
 * \param fifo The fifo in question
 * \param element The element to enqueue, which cannot be NULL
 *
 * \return If successful, returns the new length of the FIFO on success. In the case of an error, the function returns -1
 */
int llfifo_enqueue(llfifo_t* fifo, void* element) {

}

/**
 * \fn llfifo_dequeue(llfifo_t* fifo)
 * \brief Removes ("dequeues") an element from the FIFO, and returns it
 *
 * \param fifo The fifo in question
 *
 * \return If successful, returns the dequeued element, or NULL if the FIFO was empty.
 */
void* llfifo_dequeue(llfifo_t* fifo) {

}

/**
 * \fn llfifo_length(llfifo_t* fifo)
 * \brief Returns the number of elements currently on the FIFO.
 *
 * \param fifo The fifo in question
 *
 * \return Returns the number of elements currently on the FIFO
 */
int llfifo_length(llfifo_t* fifo) {

}

/**
 * \fn llfifo_capacity(llfifo_t* fifo)
 * \brief Returns the FIFO's current capacity
 *
 * \param fifo The fifo in question
 *
 * \return Returns the current capacity, in number of elements, for the FIFO
 */
int llfifo_capacity(llfifo_t* fifo) {

}

/**
 * \fn llfifo_destroy(llfifo_t* fifo)
 * \brief Teardown function: Frees all dynamically allocated memory. After calling this function, the fifo should not be used again!
 *
 * \param fifo The fifo in question
 *
 * \return N/A
 */
void llfifo_destroy(llfifo_t* fifo) {

}