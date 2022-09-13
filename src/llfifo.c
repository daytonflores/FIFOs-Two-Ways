/**
 * \file llfifo.c
 * \author Dayton Flores, dayton.flores@colorado.edu
 */

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include "llfifo.h"

#define EXIT_FAILURE_N ((int)(-1))

/**
 * \typedef llnode_t
 * \brief Allows struct llnode_s to be instantiated as llnode_t
 */
typedef struct llnode_s llnode_t;

/**
 * \struct llnode_s
 * \brief Any linked list is comprised of these llnode_t (nodes)
 *
 * \detail void* data - Points to data
 * \detail llnode_t* - previous Points to node before in the linked list (towards the tail). If NULL then the node is the tail
 * \detail llnode_t* - next Points to node next in the linked list (towards the head). If NULL then the node is the head
 */
struct llnode_s {
	void* data;
	llnode_t* previous;
	llnode_t* next;
};

/**
  * \struct llfifo_s
  * \brief Keeps track of 2 separate lists of nodes, free + used. Free nodes are available to be enqueued with data while used nodes are available to be dequeued
  *
  * \detail llnode_t* head_free - Points to head node of free list. If NULL then the list of free nodes is empty
  * \detail llnode_t* tail_free - Points to tail node of free list. If NULL then the list of free nodes is empty
  * \detail llnode_t* head_used - Points to head node of used list. If NULL then the list of used nodes is empty
  * \detail llnode_t* tail_used - Points to tail node of used list. If NULL then the list of used nodes is empty
  * \detail int capacity - The total number of nodes between both free list + used list that memory has been allocated for
  * \detail int length - The number of nodes currently in the used list
 */
struct llfifo_s {
	llnode_t* head_free;
	llnode_t* tail_free;
	llnode_t* head_used;
	llnode_t* tail_used;
	int capacity;
	int length;
};

 /**
  * \fn llfifo_t* llfifo_create(int capacity)
  * \brief Creates and initializes the FIFO
  *
  * \param capacity Initial size of the FIFO, in number of elements. Valid values are in the range of 0 to the limits of memory
  *
  * \return If successful, returns pointer to a newly-created llfifo_t instance. In the case of an error, the function returns NULL
  */
llfifo_t* llfifo_create(int capacity) {

	int i;
	llfifo_t* fifo;
	llnode_t* new_free_node;

	// Ensure amount of free nodes to allocate space for is valid
	if (capacity < 0) {
		return NULL;
	}

	// Ensure malloc is successful for a new FIFO list
	fifo = (llfifo_t*)malloc(sizeof(llfifo_t));
	if (fifo == NULL) {
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
		new_free_node = (llnode_t*)malloc(sizeof(llnode_t));
		if (new_free_node == NULL) {
			return NULL;
		}

		// Special case of inserting free node into empty free list
		if (i == 0) {
			new_free_node->data = NULL;
			new_free_node->previous = NULL;
			new_free_node->next = NULL;

			// Set new free node as both free head & free tail
			fifo->head_free = new_free_node;
			fifo->tail_free = new_free_node;
		}

		// Generic case of insert into free list containing at least 1 free node
		else {
			new_free_node->data = NULL;
			new_free_node->previous = fifo->head_free;
			new_free_node->next = NULL;

			// Link old free head to new free node
			fifo->head_free->next = new_free_node;

			// Set new free node as free head only (do not touch free tail since there would be other nodes)
			fifo->head_free = new_free_node;
		}

		// FIFO has gotten a new free node so capacity has increased
		fifo->capacity++;
	}

	return fifo;
}

/**
 * \fn int llfifo_enqueue(llfifo_t* fifo, void* element)
 * \brief Enqueues an element onto the FIFO, growing the FIFO by adding additional elements, if necessary. It is an error to attempt to enqueue the NULL pointer.
 *
 * \param fifo The fifo in question
 * \param element The element to enqueue, which cannot be NULL
 *
 * \return If successful, returns the new length of the FIFO on success. In the case of an error, the function returns -1
 */
int llfifo_enqueue(llfifo_t* fifo, void* element) {

	llnode_t* new_used_node;

	// Ensure the element to enqueue is valid
	if (element == NULL) {
		return EXIT_FAILURE_N;
	}

	// Allocate memory for an extra free node if no free nodes are available
	if (fifo->length == fifo->capacity) {
		new_used_node = (llnode_t*)malloc(sizeof(llnode_t));
		if (new_used_node == NULL) {
			return EXIT_FAILURE_N;
		}

		// Special case of inserting into empty free list
		new_used_node->data = NULL;
		new_used_node->previous = NULL;
		new_used_node->next = NULL;

		// Set new free node as both free head & free tail
		fifo->head_free = new_used_node;
		fifo->tail_free = new_used_node;

		// Free node has been added to fifo
		fifo->capacity++;
	}

	// Grab the free tail to enqueue into used list
	new_used_node = fifo->tail_free;

	// Special case of inserting used node into empty used list
	if (fifo->length == 0) {

		// Special case of free list becoming empty after grabbing this free node
		if (fifo->capacity - fifo->length == 1) {
			fifo->head_free = NULL;
			fifo->tail_free = NULL;
		}

		// Generic case of free list having at least 1 free node left after grabbing this free node
		else
		{
			// Unlink new used node from free list
			fifo->tail_free->next->previous = NULL;

			// Set new free node as free head only (do not touch free tail since there would be other nodes)
			fifo->tail_free = fifo->tail_free->next;
		}

		// Special case of inserting into empty used list
		new_used_node->data = element;
		new_used_node->previous = NULL;
		new_used_node->next = NULL;

		// Set new used node as both used head & used tail in this special case
		fifo->head_used = new_used_node;
		fifo->tail_used = new_used_node;
	}

	// Generic case of inserting into used list containing at least 1 used node
	else {

		// Special case of free list becoming empty after grabbing this free node
		if (fifo->capacity - fifo->length == 1) {
			fifo->head_free = NULL;
			fifo->tail_free = NULL;
		}

		// Generic case of free list having at least 1 free node left after grabbing this free node
		else
		{
			// Set new used tail node
			fifo->tail_free->next->previous = NULL;

			// Set new free node as free head only (do not touch free tail since there would be other nodes)
			fifo->tail_free = fifo->tail_free->next;
		}

		// Generic case of inserting into used list containing at least 1 node
		new_used_node->data = element;
		new_used_node->previous = fifo->head_used;
		new_used_node->next = NULL;

		// Link old used head to new used node
		fifo->head_used->next = new_used_node;

		// Set new used node as used head only (do not touch used tail since there would be other nodes)
		fifo->head_used = new_used_node;
	}

	// Used node has been added to fifo
	fifo->length++;

	return fifo->length;
}

/**
 * \fn void* llfifo_dequeue(llfifo_t* fifo)
 * \brief Removes ("dequeues") an element from the FIFO, and returns it
 *
 * \param fifo The fifo in question
 *
 * \return If successful, returns the dequeued element, or NULL if the FIFO was empty.
 */
void* llfifo_dequeue(llfifo_t* fifo) {

	llnode_t* new_free_node;

	// Ensure at least 1 used note exists in FIFO to dequeue
	if (fifo->length == 0) {
		return NULL;
	}

	// Grab the used tail to dequeue
	new_free_node = fifo->tail_used;

	// Special case of used list becoming empty after grabbing this used node
	if (fifo->length == 1) {
		fifo->head_used = NULL;
		fifo->tail_used = NULL;
	}

	// Generic case of used list having at least 1 used node left after grabbing this used node
	else
	{
		// Unlink new free node from used list
		fifo->tail_used->next->previous = NULL;

		// Set new used tail node
		fifo->tail_used = fifo->tail_used->next;

	}

	// Special case of inserting used node into empty free list
	if (fifo->capacity == fifo->length) {
		new_free_node->previous = NULL;
		new_free_node->next = NULL;

		// Set new free node as both free head & free tail in this special case
		fifo->head_free = new_free_node;
		fifo->tail_free = new_free_node;
	}

	// Generic case of inserting into used list containing at least 1 node
	else {
		new_free_node->previous = fifo->head_free;
		new_free_node->previous->next = new_free_node;

		// Unlink new free node from used list
		new_free_node->next = NULL;

		// Set new free node as free head only (do not touch free tail since there would be other nodes)
		fifo->head_free = new_free_node;
	}

	// Used node has been dequeued from FIFO
	fifo->length--;

	return new_free_node;
}

/**
 * \fn int llfifo_length(llfifo_t* fifo)
 * \brief Returns the number of elements currently on the FIFO.
 *
 * \param fifo The fifo in question
 *
 * \return Returns the number of elements currently on the FIFO
 */
int llfifo_length(llfifo_t* fifo) {

	return fifo->length;
}

/**
 * \fn int llfifo_capacity(llfifo_t* fifo)
 * \brief Returns the FIFO's current capacity
 *
 * \param fifo The fifo in question
 *
 * \return Returns the current capacity, in number of elements, for the FIFO
 */
int llfifo_capacity(llfifo_t* fifo) {

	return fifo->capacity;
}

/**
 * \fn void llfifo_destroy(llfifo_t* fifo)
 * \brief Teardown function: Frees all dynamically allocated memory. After calling this function, the fifo should not be used again!
 *
 * \param fifo The fifo in question
 *
 * \return N/A
 */
void llfifo_destroy(llfifo_t* fifo) {

	int i;
	llnode_t* node_to_destroy;

	// Check if there are any nodes to destroy
	if (fifo->capacity > 0) {
		
		// Destroy all used nodes
		if (fifo->length > 0) {

			for (i = 1; i <= fifo->length; i++) {

				node_to_destroy = fifo->tail_used;

				// Save next node to destroy
				fifo->tail_used = fifo->tail_used->next;

				free(node_to_destroy);
			}

			// Ensure all used nodes have been destroyed
			assert(fifo->length == i);

			// Update FIFO to reflect destroying all used nodes
			fifo->capacity = (fifo->capacity - i);
			fifo->length = (fifo->length - i);
		}

		// Destroy all free nodes
		if (fifo->capacity > 0) {

			for (i = 1; i <= fifo->capacity; i++) {

				node_to_destroy = fifo->tail_free;

				// Save next node to destroy
				fifo->tail_free = fifo->tail_free->next;

				free(node_to_destroy);
			}

			// Ensure all free nodes have been destroyed
			assert(fifo->capacity == i);

			// Update FIFO to reflect destroying all free nodes
			fifo->capacity = (fifo->capacity - i);
		}

	}

	// Ensure all nodes have been destroyed
	assert(fifo->capacity == 0);

	// Destroy FIFO only after all nodes have been destroyed
	free(fifo);
}