/**
 * \file test_llfifo.c
 * \author Dayton Flores, dayton.flores@colorado.edu
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "llfifo.h"
#include "test_llfifo.h"

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
 * \fn void llfifo_dump_state(llfifo_t* fifo)
 * \brief Dumps info about each node in the FIFO
 *
 * \param fifo Points to the FIFO for which to dump node info about
 *
 * \return N/A
 */
void llfifo_dump_state(llfifo_t* fifo) {

	int i;
	llnode_t* node;

	assert(fifo != NULL);

	// Print state of FIFO
	printf("\tllfifo at %p\n", (void*)fifo);

	if (fifo->head_free == NULL) {
		printf("\tllfifo->head_free at NULL\n");
	}
	else {
		printf("\tllfifo->head_free at %p\n", (void*)(fifo->head_free));
	}

	if (fifo->tail_free == NULL) {
		printf("\tllfifo->tail_free at NULL\n");
	}
	else {
		printf("\tllfifo->tail_free at %p\n", (void*)(fifo->tail_free));
	}

	if (fifo->head_used == NULL) {
		printf("\tllfifo->head_used at NULL\n");
	}
	else {
		printf("\tllfifo->head_used at %p\n", (void*)(fifo->head_used));
	}

	if (fifo->tail_used == NULL) {
		printf("\tllfifo->tail_used at NULL\n");
	}
	else {
		printf("\tllfifo->tail_used at %p\n", (void*)(fifo->tail_used));
	}

	printf("\tllfifo->capacity is %d\n", fifo->capacity);
	printf("\tllfifo->length is %d\n", fifo->length);

	// Print list of free nodes
	if ((fifo->capacity - fifo->length) == 0) {
		printf("\t\tFREE : Empty list");
	}
	else {
		for (i = 0; i < (fifo->capacity - fifo->length); i++) {

			if (i == 0) {
				node = (fifo->tail_free);
			}
			else {
				node = node->next;
			}

			if (node->previous == NULL) {
				printf("\t\tFREE[%d] at %p : previous = NULL\n", i, (void*)(node));
			}
			else {
				printf("\t\tFREE[%d] at %p : previous = %p\n", i, (void*)(node), (void*)(node->previous));
			}

			if (node->data == NULL) {
				printf("\t\tFREE[%d] at %p : data = NULL\n", i, (void*)(node));
			}
			else {
				printf("\t\tFREE[%d] at %p : data = %p\n", i, (void*)(node), (void*)(node->data));
			}

			if (node->next == NULL) {
				printf("\t\tFREE[%d] at %p : next = NULL\n", i, (void*)(node));
			}
			else {
				printf("\t\tFREE[%d] at %p : next = %p\n", i, (void*)(node), (void*)(node->next));
			}
		}
	}

	// Print list of used nodes
	if ((fifo->length) == 0) {
		printf("\t\tUSED : Empty list");
	}
	else {
		for (i = 0; i < (fifo->length); i++) {

			if (i == 0) {
				node = (fifo->tail_used);
			}
			else {
				node = node->next;
			}

			if (node->previous == NULL) {
				printf("\t\tUSED[%d] at %p : previous = NULL\n", i, (void*)(node));
			}
			else {
				printf("\t\tUSED[%d] at %p : previous = %p\n", i, (void*)(node), (void*)(node->previous));
			}

			if (node->data == NULL) {
				printf("\t\tUSED[%d] at %p : data = NULL\n", i, (void*)(node));
			}
			else {
				printf("\t\tUSED[%d] at %p : data = %p\n", i, (void*)(node), (void*)(node->data));
			}

			if (node->next == NULL) {
				printf("\t\tUSED[%d] at %p : next = NULL\n", i, (void*)(node));
			}
			else {
				printf("\t\tUSED[%d] at %p : next = %p\n", i, (void*)(node), (void*)(node->next));
			}
		}
	}
}

/**
 * \fn int test_llfifo_create(int capacity)
 * \brief Creates and initializes the FIFO
 *
 * \param capacity Initial size of the FIFO, in number of elements. Valid values are in the range of 0 to the limits of memory
 *
 * \return If successful, returns EXIT_SUCCESS (0). In the case of an error, the function prints the failure and returns EXIT_FAILURE (1)
 */
//int test_llfifo_create(int capacity) {
//
//}

/**
 * \fn int test_llfifo_enqueue(llfifo_t* fifo, void* element)
 * \brief Enqueues an element onto the FIFO, growing the FIFO by adding additional elements, if necessary. It is an error to attempt to enqueue the NULL pointer.
 *
 * \param fifo The fifo in question
 * \param element The element to enqueue, which cannot be NULL
 *
 * \return If successful, returns EXIT_SUCCESS (0). In the case of an error, the function prints the failure and returns EXIT_FAILURE (1)
 */
//int test_llfifo_enqueue(llfifo_t* fifo, void* element) {
//
//}

/**
 * \fn int test_llfifo_dequeue(llfifo_t* fifo)
 * \brief Removes ("dequeues") an element from the FIFO, and returns it
 *
 * \param fifo The fifo in question
 *
 * \return If successful, returns EXIT_SUCCESS (0). In the case of an error, the function prints the failure and returns EXIT_FAILURE (1)
 */
//int test_llfifo_dequeue(llfifo_t* fifo) {
//
//}

/**
 * \fn int test_llfifo_length(llfifo_t* fifo)
 * \brief Returns the number of elements currently on the FIFO.
 *
 * \param fifo The fifo in question
 *
 * \return If successful, returns EXIT_SUCCESS (0). In the case of an error, the function prints the failure and returns EXIT_FAILURE (1)
 */
//int test_llfifo_length(llfifo_t* fifo) {
//
//}

/**
 * \fn int test_llfifo_capacity(llfifo_t* fifo)
 * \brief Returns the FIFO's current capacity
 *
 * \param fifo The fifo in question
 *
 * \return If successful, returns EXIT_SUCCESS (0). In the case of an error, the function prints the failure and returns EXIT_FAILURE (1)
 */
//int test_llfifo_capacity(llfifo_t* fifo) {
//
//}

/**
 * \fn int test_llfifo_capacity(llfifo_t* fifo)
 * \brief Teardown function: Frees all dynamically allocated memory. After calling this function, the fifo should not be used again!
 *
 * \param fifo The fifo in question
 *
 * \return If successful, returns EXIT_SUCCESS (0). In the case of an error, the function prints the failure and returns EXIT_FAILURE (1)
 */
//int test_llfifo_destroy(llfifo_t* fifo) {
//
//}