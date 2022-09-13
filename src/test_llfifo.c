/**
 * \file test_llfifo.c
 * \author Dayton Flores, dayton.flores@colorado.edu
 */

#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "llfifo.h"
#include "test_llfifo.h"

#define GREEN "\x1B[32m"
#define RESET "\x1B[0m"
#define EXIT_FAILURE_N ((int)(-1))
#define LL_SIZE ((int)(3))

#define TEST_LLFIFO_CREATE
#define TEST_LLFIFO_ENQUEUE
#define TEST_LLFIFO_DEQUEUE
#define TEST_LLFIFO_CAPACITY
#define TEST_LLFIFO_LENGTH
#define TEST_LLFIFO_DESTROY

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
 * \fn void test_llfifo()
 * \brief Runs unit tests for happy cases + failure cases + boundary cases for each llfifo function
 *
 * \return N/A
 */
void test_llfifo() {
#ifdef TEST_LLFIFO_CREATE
	// Set first parameter to capacity to test
	// Set second parameter to how many nodes you want to dump free list + used list

	// ------------------- //
	// Happy Test Cases    //
	// ------------------- //
	//		Create llfifo and attempt to initialize 2 nodes in free list + 0 nodes in used list. Display max 2 nodes from free list + 2 nodes from used list
	assert(test_llfifo_create(2, 2) == EXIT_SUCCESS);
	//		Create llfifo and attempt to initialize 9 nodes in free list + 0 nodes in used list. Display max 8 nodes from free list + 8 nodes from used list
	assert(test_llfifo_create(9, 8) == EXIT_SUCCESS);
	//		Create llfifo and attempt to initialize 100 nodes in free list + 0 nodes in used list. Display max 4 nodes from free list + 4 nodes from used list
	assert(test_llfifo_create(100, 4) == EXIT_SUCCESS);

	// ------------------- //
	// Failure Test Cases  //
	// ------------------- //
	//		Create llfifo and attempt to initialize -5 nodes in free list
	assert(test_llfifo_create(-5, 0) == EXIT_FAILURE);

	// ------------------- //
	// Boundary Test Cases //
	// ------------------- //
	//		Create llfifo and attempt to initialize -5 nodes in free list
	assert(test_llfifo_create(-1, 1) == EXIT_FAILURE);
	//		Create llfifo and attempt to initialize 0 nodes in free list + 0 nodes in used list. Display max 1 nodes from free list + 1 nodes from used list
	assert(test_llfifo_create(0, 1) == EXIT_SUCCESS);
	//		Create llfifo and attempt to initialize 1 nodes in free list + 0 nodes in used list. Display max 1 nodes from free list + 1 nodes from used list
	assert(test_llfifo_create(1, 1) == EXIT_SUCCESS);
	//		Create llfifo and attempt to initialize INT_MIN nodes in free list + 0 nodes in used list. Display max 1 nodes from free list + 1 nodes from used list
	assert(test_llfifo_create(INT_MIN, 1) == EXIT_FAILURE);
#endif

#ifdef TEST_LLFIFO_ENQUEUE
	// Set first parameter to llfifo to test with
	// Set second parameter to char* pointer (technically this can be any pointer but the dump function only prints %s in printf so for nice input stick with char*)
	// Set third parameter to how many nodes you want to dump from each of free list + used list

	char element1_enqueue[17] = "element1_enqueue";
	char element2_enqueue[17] = "element2_enqueue";
	char element3_enqueue[17] = "element3_enqueue";
	char element4_enqueue[17] = "element4_enqueue";

	llfifo_t* llfifo_enqueue;
	llfifo_enqueue = llfifo_create(LL_SIZE);

	// ------------------- //
	// Happy Test Cases    //
	// ------------------- //
	//		Enqueue element1 to llfifo capacity 3, length 0. Resulting length will be 1
	assert(test_llfifo_enqueue(llfifo_enqueue, (void*)element1_enqueue, LL_SIZE) == EXIT_SUCCESS);
	//		Enqueue element2 to llfifo capacity 3, length 1. Resulting length will be 2
	assert(test_llfifo_enqueue(llfifo_enqueue, (void*)element2_enqueue, LL_SIZE) == EXIT_SUCCESS);
	//		Enqueue element3 to llfifo capacity 3, length 2. Resulting length will be 3
	assert(test_llfifo_enqueue(llfifo_enqueue, (void*)element3_enqueue, LL_SIZE) == EXIT_SUCCESS);

	// ------------------- //
	// Failure Test Cases  //
	// ------------------- //
	//		Attempt to enqueue element1 to NULL llfifo
	assert(test_llfifo_enqueue(NULL, (void*)element1_enqueue, LL_SIZE) == EXIT_FAILURE);
	//		Attempt to enqueue NULL element to llfifo
	assert(test_llfifo_enqueue(llfifo_enqueue, NULL, LL_SIZE) == EXIT_FAILURE);

	// ------------------- //
	// Boundary Test Cases //
	// ------------------- //
	//		Enqueue element4 to llfifo capacity 3, length 3. Resulting capacity will be 4. Resulting length will be 4
	assert(test_llfifo_enqueue(llfifo_enqueue, (void*)element4_enqueue, LL_SIZE + 1) == EXIT_SUCCESS);

	llfifo_destroy(llfifo_enqueue);
#endif

#ifdef TEST_LLFIFO_DEQUEUE
	// Set first parameter to llfifo to test with
	// Set second parameter to char* pointer (technically this can be any pointer but the dump function only prints %s in printf so for nice input stick with char*)
	// Set third parameter to how many nodes you want to dump from each of free list + used list

	char element1_dequeue[17] = "element1_dequeue";
	char element2_dequeue[17] = "element2_dequeue";
	char element3_dequeue[17] = "element3_dequeue";
	char element4_dequeue[17] = "element4_dequeue";

	llfifo_t* llfifo_dequeue;
	llfifo_dequeue = llfifo_create(LL_SIZE);

	// ------------------- //
	// Happy Test Cases    //
	// ------------------- //
	//		Enqueue element1 to llfifo capacity 3, length 0. Resulting length will be 1
	assert(test_llfifo_enqueue(llfifo_dequeue, (void*)element1_dequeue, LL_SIZE) == EXIT_SUCCESS);
	//		Enqueue element2 to llfifo capacity 3, length 1. Resulting length will be 2
	assert(test_llfifo_enqueue(llfifo_dequeue, (void*)element2_dequeue, LL_SIZE) == EXIT_SUCCESS);
	//		Enqueue element3 to llfifo capacity 3, length 2. Resulting length will be 3
	assert(test_llfifo_enqueue(llfifo_dequeue, (void*)element3_dequeue, LL_SIZE) == EXIT_SUCCESS);
	//		Dequeue element1 from llfifo capacity 3, length 3. Resulting length will be 2
	assert(test_llfifo_dequeue(llfifo_dequeue, LL_SIZE) == EXIT_SUCCESS);
	//		Dequeue element2 from llfifo capacity 3, length 2. Resulting length will be 1
	assert(test_llfifo_dequeue(llfifo_dequeue, LL_SIZE) == EXIT_SUCCESS);
	//		Dequeue element3 from llfifo capacity 3, length 1. Resulting length will be 0
	assert(test_llfifo_dequeue(llfifo_dequeue, LL_SIZE) == EXIT_SUCCESS);
	//		Enqueue element3 to llfifo capacity 3, length 0. Resulting length will be 1
	assert(test_llfifo_enqueue(llfifo_dequeue, (void*)element3_dequeue, LL_SIZE) == EXIT_SUCCESS);
	//		Enqueue element2 to llfifo capacity 3, length 1. Resulting length will be 2
	assert(test_llfifo_enqueue(llfifo_dequeue, (void*)element2_dequeue, LL_SIZE) == EXIT_SUCCESS);
	//		Dequeue element3 from llfifo capacity 3, length 2. Resulting length will be 1
	assert(test_llfifo_dequeue(llfifo_dequeue, LL_SIZE) == EXIT_SUCCESS);
	//		Enqueue element1 to llfifo capacity 3, length 1. Resulting length will be 2
	assert(test_llfifo_enqueue(llfifo_dequeue, (void*)element1_dequeue, LL_SIZE) == EXIT_SUCCESS);
	//		Dequeue element2 from llfifo capacity 3, length 2. Resulting length will be 1
	assert(test_llfifo_dequeue(llfifo_dequeue, LL_SIZE) == EXIT_SUCCESS);
	//		Dequeue element1 from llfifo capacity 3, length 1. Resulting length will be 0
	assert(test_llfifo_dequeue(llfifo_dequeue, LL_SIZE) == EXIT_SUCCESS);

	// ------------------- //
	// Failure Test Cases  //
	// ------------------- //
	//		Attempt to dequeue element from NULL llfifo
	assert(test_llfifo_dequeue(NULL, LL_SIZE) == EXIT_FAILURE);

	// ------------------- //
	// Boundary Test Cases //
	// ------------------- //
	//		Attempt to dequeue NULL element from llfifo
	assert(test_llfifo_dequeue(llfifo_dequeue, LL_SIZE) == EXIT_FAILURE);
	//		Enqueue element1 to llfifo capacity 3, length 0. Resulting length will be 1
	assert(test_llfifo_enqueue(llfifo_dequeue, (void*)element1_dequeue, LL_SIZE) == EXIT_SUCCESS);
	//		Enqueue element2 to llfifo capacity 3, length 1. Resulting length will be 2
	assert(test_llfifo_enqueue(llfifo_dequeue, (void*)element2_dequeue, LL_SIZE) == EXIT_SUCCESS);
	//		Enqueue element3 to llfifo capacity 3, length 2. Resulting length will be 3
	assert(test_llfifo_enqueue(llfifo_dequeue, (void*)element3_dequeue, LL_SIZE) == EXIT_SUCCESS);
	//		Enqueue element4 to llfifo capacity 3, length 3. Resulting capacity will be 4. Resulting length will be 4
	assert(test_llfifo_enqueue(llfifo_dequeue, (void*)element4_dequeue, LL_SIZE + 1) == EXIT_SUCCESS);
	//		Dequeue element1 from llfifo capacity 4, length 4. Resulting length will be 3
	assert(test_llfifo_dequeue(llfifo_dequeue, LL_SIZE + 1) == EXIT_SUCCESS);
	//		Enqueue element1 to llfifo capacity 4, length 3. Resulting length will be 4
	assert(test_llfifo_enqueue(llfifo_dequeue, (void*)element1_dequeue, LL_SIZE + 1) == EXIT_SUCCESS);
	//		Dequeue element2 from llfifo capacity 4, length 4. Resulting length will be 3
	assert(test_llfifo_dequeue(llfifo_dequeue, LL_SIZE + 1) == EXIT_SUCCESS);
	//		Dequeue element3 from llfifo capacity 4, length 3. Resulting length will be 2
	assert(test_llfifo_dequeue(llfifo_dequeue, LL_SIZE + 1) == EXIT_SUCCESS);
	//		Dequeue element4 from llfifo capacity 4, length 2. Resulting length will be 1
	assert(test_llfifo_dequeue(llfifo_dequeue, LL_SIZE + 1) == EXIT_SUCCESS);
	//		Dequeue element1 from llfifo capacity 4, length 1. Resulting length will be 0
	assert(test_llfifo_dequeue(llfifo_dequeue, LL_SIZE + 1) == EXIT_SUCCESS);
	//		Attempt to dequeue NULL element from llfifo
	assert(test_llfifo_dequeue(llfifo_dequeue, LL_SIZE + 1) == EXIT_FAILURE);

	llfifo_destroy(llfifo_dequeue);

#endif

#ifdef TEST_LLFIFO_CAPACITY
	// Set first parameter to llfifo to test with
	// Set second parameter to how many nodes you want to dump from each of free list + used list

	char element1_capacity[18] = "element1_capacity";
	char element2_capacity[18] = "element2_capacity";
	char element3_capacity[18] = "element3_capacity";
	char element4_capacity[18] = "element4_capacity";

	llfifo_t* llfifo_capacity;
	llfifo_capacity = llfifo_create(LL_SIZE);

	// ------------------- //
	// Happy Test Cases    //
	// ------------------- //
	//		Grab capacity of llfifo capacity 3, length 0. Answer should be 3
	assert(test_llfifo_capacity(llfifo_capacity, LL_SIZE) == EXIT_SUCCESS);
	//		Enqueue element1 to llfifo capacity 3, length 0. Resulting length will be 1
	assert(test_llfifo_enqueue(llfifo_capacity, (void*)element1_capacity, LL_SIZE) == EXIT_SUCCESS);
	//		Grab capacity of llfifo capacity 3, length 1. Answer should be 3
	assert(test_llfifo_capacity(llfifo_capacity, LL_SIZE) == EXIT_SUCCESS);
	//		Enqueue element2 to llfifo capacity 3, length 1. Resulting length will be 2
	assert(test_llfifo_enqueue(llfifo_capacity, (void*)element2_capacity, LL_SIZE) == EXIT_SUCCESS);
	//		Grab capacity of llfifo capacity 3, length 2. Answer should be 3
	assert(test_llfifo_capacity(llfifo_capacity, LL_SIZE) == EXIT_SUCCESS);
	//		Enqueue element3 to llfifo capacity 3, length 2. Resulting length will be 3
	assert(test_llfifo_enqueue(llfifo_capacity, (void*)element3_capacity, LL_SIZE) == EXIT_SUCCESS);
	//		Grab capacity of llfifo capacity 3, length 3. Answer should be 3
	assert(test_llfifo_capacity(llfifo_capacity, LL_SIZE) == EXIT_SUCCESS);
	//		Dequeue element1 from llfifo capacity 3, length 3. Resulting length will be 2
	assert(test_llfifo_dequeue(llfifo_capacity, LL_SIZE) == EXIT_SUCCESS);
	//		Grab capacity of llfifo capacity 3, length 2. Answer should be 3
	assert(test_llfifo_capacity(llfifo_capacity, LL_SIZE) == EXIT_SUCCESS);
	//		Dequeue element2 from llfifo capacity 3, length 2. Resulting length will be 1
	assert(test_llfifo_dequeue(llfifo_capacity, LL_SIZE) == EXIT_SUCCESS);
	//		Grab capacity of llfifo capacity 3, length 1. Answer should be 3
	assert(test_llfifo_capacity(llfifo_capacity, LL_SIZE) == EXIT_SUCCESS);
	//		Dequeue element3 from llfifo capacity 3, length 1. Resulting length will be 0
	assert(test_llfifo_dequeue(llfifo_capacity, LL_SIZE) == EXIT_SUCCESS);
	//		Grab capacity of llfifo capacity 3, length 0. Answer should be 3
	assert(test_llfifo_capacity(llfifo_capacity, LL_SIZE) == EXIT_SUCCESS);
	//		Attempt to dequeue NULL element from llfifo
	assert(test_llfifo_dequeue(llfifo_capacity, LL_SIZE) == EXIT_FAILURE);
	//		Grab capacity of llfifo capacity 3, length 0. Answer should be 3
	assert(test_llfifo_capacity(llfifo_capacity, LL_SIZE) == EXIT_SUCCESS);
	//		Enqueue element1 to llfifo capacity 3, length 0. Resulting length will be 1
	assert(test_llfifo_enqueue(llfifo_capacity, (void*)element1_capacity, LL_SIZE) == EXIT_SUCCESS);
	//		Grab capacity of llfifo capacity 3, length 1. Answer should be 3
	assert(test_llfifo_capacity(llfifo_capacity, LL_SIZE) == EXIT_SUCCESS);
	//		Enqueue element2 to llfifo capacity 3, length 1. Resulting length will be 2
	assert(test_llfifo_enqueue(llfifo_capacity, (void*)element2_capacity, LL_SIZE) == EXIT_SUCCESS);
	//		Grab capacity of llfifo capacity 3, length 2. Answer should be 3
	assert(test_llfifo_capacity(llfifo_capacity, LL_SIZE) == EXIT_SUCCESS);
	//		Enqueue element3 to llfifo capacity 3, length 2. Resulting length will be 3
	assert(test_llfifo_enqueue(llfifo_capacity, (void*)element3_capacity, LL_SIZE) == EXIT_SUCCESS);
	//		Grab capacity of llfifo capacity 3, length 3. Answer should be 3
	assert(test_llfifo_capacity(llfifo_capacity, LL_SIZE) == EXIT_SUCCESS);
	//		Enqueue element4 to llfifo capacity 3, length 3. Resulting capacity will be 4. Resulting length will be 4
	assert(test_llfifo_enqueue(llfifo_capacity, (void*)element4_capacity, LL_SIZE + 1) == EXIT_SUCCESS);
	//		Grab capacity of llfifo capacity 4, length 4. Answer should be 4
	assert(test_llfifo_capacity(llfifo_capacity, LL_SIZE + 1) == EXIT_SUCCESS);
	//		Dequeue element1 from llfifo capacity 4, length 4. Resulting length will be 3
	assert(test_llfifo_dequeue(llfifo_capacity, LL_SIZE + 1) == EXIT_SUCCESS);
	//		Grab capacity of llfifo capacity 4, length 3. Answer should be 4
	assert(test_llfifo_capacity(llfifo_capacity, LL_SIZE + 1) == EXIT_SUCCESS);
	//		Dequeue element2 from llfifo capacity 4, length 3. Resulting length will be 2
	assert(test_llfifo_dequeue(llfifo_capacity, LL_SIZE + 1) == EXIT_SUCCESS);
	//		Grab capacity of llfifo capacity 4, length 2. Answer should be 4
	assert(test_llfifo_capacity(llfifo_capacity, LL_SIZE + 1) == EXIT_SUCCESS);
	//		Dequeue element3 from llfifo capacity 4, length 2. Resulting length will be 1
	assert(test_llfifo_dequeue(llfifo_capacity, LL_SIZE + 1) == EXIT_SUCCESS);
	//		Grab capacity of llfifo capacity 4, length 1. Answer should be 4
	assert(test_llfifo_capacity(llfifo_capacity, LL_SIZE + 1) == EXIT_SUCCESS);
	//		Dequeue element4 from llfifo capacity 4, length 1. Resulting length will be 0
	assert(test_llfifo_dequeue(llfifo_capacity, LL_SIZE + 1) == EXIT_SUCCESS);
	//		Grab capacity of llfifo capacity 4, length 0. Answer should be 4
	assert(test_llfifo_capacity(llfifo_capacity, LL_SIZE + 1) == EXIT_SUCCESS);
	//		Attempt to dequeue NULL element from llfifo
	assert(test_llfifo_dequeue(llfifo_capacity, LL_SIZE + 1) == EXIT_FAILURE);
	//		Grab capacity of llfifo capacity 4, length 0. Answer should be 4
	assert(test_llfifo_capacity(llfifo_capacity, LL_SIZE + 1) == EXIT_SUCCESS);

	// ------------------- //
	// Failure Test Cases  //
	// ------------------- //
	//		Attempt to grab capacity from NULL llfifo
	assert(test_llfifo_capacity(NULL, LL_SIZE) == EXIT_FAILURE);

	// ------------------- //
	// Boundary Test Cases //
	// ------------------- //


	llfifo_destroy(llfifo_capacity);
#endif

#ifdef TEST_LLFIFO_LENGTH
	// Set first parameter to llfifo to test with
	// Set second parameter to how many nodes you want to dump from each of free list + used list

	char element1_length[16] = "element1_length";
	char element2_length[16] = "element2_length";
	char element3_length[16] = "element3_length";
	char element4_length[16] = "element4_length";

	llfifo_t* llfifo_length;
	llfifo_length = llfifo_create(LL_SIZE);

	// ------------------- //
	// Happy Test Cases    //
	// ------------------- //
	//		Grab length of llfifo capacity 3, length 0. Answer should be 0
	assert(test_llfifo_length(llfifo_length, LL_SIZE) == EXIT_SUCCESS);
	//		Enqueue element1 to llfifo capacity 3, length 0. Resulting length will be 1
	assert(test_llfifo_enqueue(llfifo_length, (void*)element1_length, LL_SIZE) == EXIT_SUCCESS);
	//		Grab length of llfifo capacity 3, length 1. Answer should be 1
	assert(test_llfifo_length(llfifo_length, LL_SIZE) == EXIT_SUCCESS);
	//		Enqueue element2 to llfifo capacity 3, length 1. Resulting length will be 2
	assert(test_llfifo_enqueue(llfifo_length, (void*)element2_length, LL_SIZE) == EXIT_SUCCESS);
	//		Grab length of llfifo capacity 3, length 2. Answer should be 2
	assert(test_llfifo_length(llfifo_length, LL_SIZE) == EXIT_SUCCESS);
	//		Enqueue element3 to llfifo capacity 3, length 2. Resulting length will be 3
	assert(test_llfifo_enqueue(llfifo_length, (void*)element3_length, LL_SIZE) == EXIT_SUCCESS);
	//		Grab length of llfifo capacity 3, length 3. Answer should be 3
	assert(test_llfifo_length(llfifo_length, LL_SIZE) == EXIT_SUCCESS);
	//		Dequeue element1 from llfifo capacity 3, length 3. Resulting length will be 2
	assert(test_llfifo_dequeue(llfifo_length, LL_SIZE) == EXIT_SUCCESS);
	//		Grab length of llfifo capacity 3, length 2. Answer should be 2
	assert(test_llfifo_length(llfifo_length, LL_SIZE) == EXIT_SUCCESS);
	//		Dequeue element2 from llfifo capacity 3, length 2. Resulting length will be 1
	assert(test_llfifo_dequeue(llfifo_length, LL_SIZE) == EXIT_SUCCESS);
	//		Grab length of llfifo capacity 3, length 1. Answer should be 1
	assert(test_llfifo_length(llfifo_length, LL_SIZE) == EXIT_SUCCESS);
	//		Dequeue element3 from llfifo capacity 3, length 1. Resulting length will be 0
	assert(test_llfifo_dequeue(llfifo_length, LL_SIZE) == EXIT_SUCCESS);
	//		Grab length of llfifo capacity 3, length 0. Answer should be 0
	assert(test_llfifo_length(llfifo_length, LL_SIZE) == EXIT_SUCCESS);
	//		Attempt to dequeue NULL element from llfifo
	assert(test_llfifo_dequeue(llfifo_length, LL_SIZE) == EXIT_FAILURE);
	//		Grab length of llfifo capacity 3, length 0. Answer should be 0
	assert(test_llfifo_length(llfifo_length, LL_SIZE) == EXIT_SUCCESS);
	//		Enqueue element1 to llfifo capacity 3, length 0. Resulting length will be 1
	assert(test_llfifo_enqueue(llfifo_length, (void*)element1_length, LL_SIZE) == EXIT_SUCCESS);
	//		Grab length of llfifo capacity 3, length 1. Answer should be 1
	assert(test_llfifo_length(llfifo_length, LL_SIZE) == EXIT_SUCCESS);
	//		Enqueue element2 to llfifo capacity 3, length 1. Resulting length will be 2
	assert(test_llfifo_enqueue(llfifo_length, (void*)element2_length, LL_SIZE) == EXIT_SUCCESS);
	//		Grab length of llfifo capacity 3, length 2. Answer should be 2
	assert(test_llfifo_length(llfifo_length, LL_SIZE) == EXIT_SUCCESS);
	//		Enqueue element3 to llfifo capacity 3, length 2. Resulting length will be 3
	assert(test_llfifo_enqueue(llfifo_length, (void*)element3_length, LL_SIZE) == EXIT_SUCCESS);
	//		Grab length of llfifo capacity 3, length 3. Answer should be 3
	assert(test_llfifo_length(llfifo_length, LL_SIZE) == EXIT_SUCCESS);
	//		Enqueue element4 to llfifo capacity 3, length 3. Resulting length will be 4
	assert(test_llfifo_enqueue(llfifo_length, (void*)element4_length, LL_SIZE) == EXIT_SUCCESS);
	//		Grab length of llfifo capacity 4, length 4. Answer should be 4
	assert(test_llfifo_length(llfifo_length, LL_SIZE) == EXIT_SUCCESS);
	//		Dequeue element1 from llfifo capacity 4, length 4. Resulting length will be 3
	assert(test_llfifo_dequeue(llfifo_length, LL_SIZE) == EXIT_SUCCESS);
	//		Grab length of llfifo capacity 4, length 3. Answer should be 3
	assert(test_llfifo_length(llfifo_length, LL_SIZE) == EXIT_SUCCESS);
	//		Dequeue element2 from llfifo capacity 4, length 3. Resulting length will be 2
	assert(test_llfifo_dequeue(llfifo_length, LL_SIZE) == EXIT_SUCCESS);
	//		Grab length of llfifo capacity 4, length 2. Answer should be 2
	assert(test_llfifo_length(llfifo_length, LL_SIZE) == EXIT_SUCCESS);
	//		Dequeue element3 from llfifo capacity 4, length 2. Resulting length will be 1
	assert(test_llfifo_dequeue(llfifo_length, LL_SIZE) == EXIT_SUCCESS);
	//		Grab length of llfifo capacity 4, length 1. Answer should be 1
	assert(test_llfifo_length(llfifo_length, LL_SIZE) == EXIT_SUCCESS);
	//		Dequeue element4 from llfifo capacity 4, length 1. Resulting length will be 0
	assert(test_llfifo_dequeue(llfifo_length, LL_SIZE) == EXIT_SUCCESS);
	//		Grab length of llfifo capacity 4, length 0. Answer should be 0
	assert(test_llfifo_length(llfifo_length, LL_SIZE) == EXIT_SUCCESS);
	//		Attempt to dequeue NULL element from llfifo
	assert(test_llfifo_dequeue(llfifo_length, LL_SIZE) == EXIT_FAILURE);
	//		Grab length of llfifo capacity 4, length 0. Answer should be 0
	assert(test_llfifo_length(llfifo_length, LL_SIZE) == EXIT_SUCCESS);

	// ------------------- //
	// Failure Test Cases  //
	// ------------------- //
	//		Attempt to grab length from NULL llfifo
	assert(test_llfifo_length(NULL, LL_SIZE) == EXIT_FAILURE);

	// ------------------- //
	// Boundary Test Cases //
	// ------------------- //


	llfifo_destroy(llfifo_length);
#endif

#ifdef TEST_LLFIFO_DESTROY
	// Set first parameter to llfifo to test with
	char element1_destroy[17] = "element1_destroy";
	char element2_destroy[17] = "element2_destroy";
	char element3_destroy[17] = "element3_destroy";
	char element4_destroy[17] = "element4_destroy";

	llfifo_t* llfifo_destroy;
	llfifo_destroy = llfifo_create(LL_SIZE);

	// ------------------- //
	// Happy Test Cases    //
	// ------------------- //
	//		Destroy llfifo with capacity 3, length 0
	assert((test_llfifo_destroy(llfifo_destroy)) == EXIT_SUCCESS);
	//		Create llfifo with capacity 3, length 0
	llfifo_destroy = llfifo_create(LL_SIZE);
	//		Enqueue element1 to llfifo capacity 3, length 0. Resulting length will be 1
	assert(test_llfifo_enqueue(llfifo_destroy, (void*)element1_destroy, LL_SIZE) == EXIT_SUCCESS);
	//		Destroy llfifo with capacity 3, length 1
	assert((test_llfifo_destroy(llfifo_destroy)) == EXIT_SUCCESS);
	//		Create llfifo with capacity 3, length 0
	llfifo_destroy = llfifo_create(LL_SIZE);
	//		Enqueue element1 to llfifo capacity 3, length 0. Resulting length will be 1
	assert(test_llfifo_enqueue(llfifo_destroy, (void*)element1_destroy, LL_SIZE) == EXIT_SUCCESS);
	//		Enqueue element2 to llfifo capacity 3, length 1. Resulting length will be 2
	assert(test_llfifo_enqueue(llfifo_destroy, (void*)element2_destroy, LL_SIZE) == EXIT_SUCCESS);
	//		Destroy llfifo with capacity 3, length 2
	assert((test_llfifo_destroy(llfifo_destroy)) == EXIT_SUCCESS);
	//		Create llfifo with capacity 3, length 0
	llfifo_destroy = llfifo_create(LL_SIZE);
	//		Enqueue element1 to llfifo capacity 3, length 0. Resulting length will be 1
	assert(test_llfifo_enqueue(llfifo_destroy, (void*)element1_destroy, LL_SIZE) == EXIT_SUCCESS);
	//		Enqueue element2 to llfifo capacity 3, length 1. Resulting length will be 2
	assert(test_llfifo_enqueue(llfifo_destroy, (void*)element2_destroy, LL_SIZE) == EXIT_SUCCESS);
	//		Enqueue element3 to llfifo capacity 3, length 2. Resulting length will be 3
	assert(test_llfifo_enqueue(llfifo_destroy, (void*)element3_destroy, LL_SIZE) == EXIT_SUCCESS);
	//		Destroy llfifo with capacity 3, length 3
	assert((test_llfifo_destroy(llfifo_destroy)) == EXIT_SUCCESS);
	//		Create llfifo with capacity 3, length 0
	llfifo_destroy = llfifo_create(LL_SIZE);
	//		Enqueue element1 to llfifo capacity 3, length 0. Resulting length will be 1
	assert(test_llfifo_enqueue(llfifo_destroy, (void*)element1_destroy, LL_SIZE) == EXIT_SUCCESS);
	//		Enqueue element2 to llfifo capacity 3, length 1. Resulting length will be 2
	assert(test_llfifo_enqueue(llfifo_destroy, (void*)element2_destroy, LL_SIZE) == EXIT_SUCCESS);
	//		Enqueue element3 to llfifo capacity 3, length 2. Resulting length will be 3
	assert(test_llfifo_enqueue(llfifo_destroy, (void*)element3_destroy, LL_SIZE) == EXIT_SUCCESS);
	//		Enqueue element4 to llfifo capacity 3, length 3. Resulting capacity will be 4. Resulting length will be 4
	assert(test_llfifo_enqueue(llfifo_destroy, (void*)element4_destroy, LL_SIZE) == EXIT_SUCCESS);
	//		Destroy llfifo with capacity 4, length 4
	assert((test_llfifo_destroy(llfifo_destroy)) == EXIT_SUCCESS);
	//		Create llfifo with capacity 3, length 0
	llfifo_destroy = llfifo_create(LL_SIZE);
	//		Enqueue element1 to llfifo capacity 3, length 0. Resulting length will be 1
	assert(test_llfifo_enqueue(llfifo_destroy, (void*)element1_destroy, LL_SIZE) == EXIT_SUCCESS);
	//		Dequeue element1 from llfifo capacity 3, length 1. Resulting length will be 0
	assert(test_llfifo_enqueue(llfifo_destroy, (void*)element2_destroy, LL_SIZE) == EXIT_SUCCESS);
	//		Destroy llfifo with capacity 3, length 0
	assert((test_llfifo_destroy(llfifo_destroy)) == EXIT_SUCCESS);

	// ------------------- //
	// Failure Test Cases  //
	// ------------------- //
	//		Attempt to destroy NULL llfifo
	assert(test_llfifo_destroy(NULL) == EXIT_SUCCESS);

	// ------------------- //
	// Boundary Test Cases //
	// ------------------- //


#endif
	
	printf("\n");

#ifdef TEST_LLFIFO_CREATE
	printf(GREEN "Asserts for all test cases against llfifo_create have passed\n" RESET);
#endif
#ifdef TEST_LLFIFO_ENQUEUE
	printf(GREEN "Asserts for all test cases against llfifo_enqueue have passed\n" RESET);
#endif
#ifdef TEST_LLFIFO_DEQUEUE
	printf(GREEN "Asserts for all test cases against llfifo_dequeue have passed\n" RESET);
#endif
#ifdef TEST_LLFIFO_CAPACITY
	printf(GREEN "Asserts for all test cases against llfifo_capacity have passed\n" RESET);
#endif
#ifdef TEST_LLFIFO_LENGTH
	printf(GREEN "Asserts for all test cases against llfifo_length have passed\n" RESET);
#endif
#ifdef TEST_LLFIFO_DESTROY
	printf(GREEN "Asserts for all test cases against llfifo_destroy have passed\n" RESET);
#endif
}

/**
 * \fn int test_llfifo_create(int capacity)
 * \brief Creates and initializes the FIFO
 *
 * \param capacity Initial size of the FIFO, in number of elements. Valid values are in the range of 0 to the limits of memory
 * \param max_nodes The number of nodes to dump from each of free list + used list. If max_node is less than the total nodes in either list, it will dump (max_node - 1) nodes from the tail and then dump the head
 *
 * \return If successful, returns EXIT_SUCCESS (0). In the case of an error, the function prints the failure and returns EXIT_FAILURE (1)
 */
int test_llfifo_create(int capacity, int max_nodes) {

	llfifo_t* fifo;

	fifo = llfifo_create(capacity);
	llfifo_dump_state(fifo, max_nodes);
	free(fifo);

	if (fifo != NULL) {
		return EXIT_SUCCESS;
	}
	else {
		return EXIT_FAILURE;
	}
}

/**
 * \fn int test_llfifo_enqueue(llfifo_t* fifo, void* element)
 * \brief Enqueues an element onto the FIFO, growing the FIFO by adding additional elements, if necessary. It is an error to attempt to enqueue the NULL pointer.
 *
 * \param fifo The fifo in question
 * \param element The element to enqueue, which cannot be NULL
 * \param max_nodes The number of nodes to dump from each of free list + used list. If max_node is less than the total nodes in either list, it will dump (max_node - 1) nodes from the tail and then dump the head
 *
 * \return If successful, returns EXIT_SUCCESS (0). In the case of an error, the function prints the failure and returns EXIT_FAILURE (1)
 */
int test_llfifo_enqueue(llfifo_t* fifo, void* element, int max_nodes) {

	int length;

	length = llfifo_enqueue(fifo, element);
	llfifo_dump_state(fifo, max_nodes);

	if (length != EXIT_FAILURE_N) {
		return EXIT_SUCCESS;
	}
	else {
		return EXIT_FAILURE;
	}
}

/**
 * \fn int test_llfifo_dequeue(llfifo_t* fifo)
 * \brief Removes ("dequeues") an element from the FIFO, and returns it
 *
 * \param fifo The fifo in question
 * \param max_nodes The number of nodes to dump from each of free list + used list. If max_node is less than the total nodes in either list, it will dump (max_node - 1) nodes from the tail and then dump the head
 *
 * \return If successful, returns EXIT_SUCCESS (0). In the case of an error, the function prints the failure and returns EXIT_FAILURE (1)
 */
int test_llfifo_dequeue(llfifo_t* fifo, int max_nodes) {

	void* data;

	data = llfifo_dequeue(fifo);
	llfifo_dump_state(fifo, max_nodes);

	if (data != NULL) {
		return EXIT_SUCCESS;
	}
	else {
		return EXIT_FAILURE;
	}
}

/**
 * \fn int test_llfifo_length(llfifo_t* fifo)
 * \brief Returns the number of elements currently on the FIFO.
 *
 * \param fifo The fifo in question
 * \param max_nodes The number of nodes to dump from each of free list + used list. If max_node is less than the total nodes in either list, it will dump (max_node - 1) nodes from the tail and then dump the head
 *
 * \return If successful, returns EXIT_SUCCESS (0). In the case of an error, the function prints the failure and returns EXIT_FAILURE (1)
 */
int test_llfifo_length(llfifo_t* fifo, int max_nodes) {

	int length;

	length = llfifo_length(fifo);
	llfifo_dump_state(fifo, max_nodes);

	if (length != EXIT_FAILURE_N) {
		return EXIT_SUCCESS;
	}
	else {
		return EXIT_FAILURE;
	}
}

/**
 * \fn int test_llfifo_capacity(llfifo_t* fifo)
 * \brief Returns the FIFO's current capacity
 *
 * \param fifo The fifo in question
 * \param max_nodes The number of nodes to dump from each of free list + used list. If max_node is less than the total nodes in either list, it will dump (max_node - 1) nodes from the tail and then dump the head
 *
 * \return If successful, returns EXIT_SUCCESS (0). In the case of an error, the function prints the failure and returns EXIT_FAILURE (1)
 */
int test_llfifo_capacity(llfifo_t* fifo, int max_nodes) {

	int capacity;

	capacity = llfifo_capacity(fifo);
	llfifo_dump_state(fifo, max_nodes);

	if (capacity != EXIT_FAILURE_N) {
		return EXIT_SUCCESS;
	}
	else {
		return EXIT_FAILURE;
	}
}

/**
 * \fn int test_llfifo_capacity(llfifo_t* fifo)
 * \brief Teardown function: Frees all dynamically allocated memory. After calling this function, the fifo should not be used again!
 *
 * \param fifo The fifo in question
 *
 * \return If successful, returns EXIT_SUCCESS (0). In the case of an error, the function prints the failure and returns EXIT_FAILURE (1)
 */
int test_llfifo_destroy(llfifo_t* fifo) {

	llfifo_destroy(fifo);

	return EXIT_SUCCESS;
}

/**
 * \fn void llfifo_dump_state(llfifo_t* fifo)
 * \brief Dumps info about each node in the FIFO
 *
 * \param fifo Points to the FIFO for which to dump node info about
 * \param max_nodes The number of nodes to dump from each of free list + used list. If max_node is less than the total nodes in either list, it will dump (max_node - 1) nodes from the tail and then dump the head
 *
 * \return N/A
 */
void llfifo_dump_state(llfifo_t* fifo, int max_nodes) {

	bool skip_to_head;
	int i;
	llnode_t* node;

	printf("\n***************************NEW LLFIFO****************************\n");

	if (fifo == NULL) {
		printf("\tllfifo at NULL\n");
		return;
	}

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

	printf("\t\t-----------------------------------------\n");

	// Print list of free nodes
	if ((fifo->capacity - fifo->length) == 0) {
		printf("\t\tFREE : Empty list\n");
	}
	else if (max_nodes == 0) {
		printf("\t\tDisplaying %d out of %d free nodes\n", (max_nodes > (fifo->capacity - fifo->length)) ? (fifo->capacity - fifo->length) : (max_nodes), (fifo->capacity - fifo->length));
	}
	else if (max_nodes == 1) {
		printf("\t\tDisplaying %d out of %d free nodes\n", (max_nodes > (fifo->capacity - fifo->length)) ? (fifo->capacity - fifo->length) : (max_nodes), (fifo->capacity - fifo->length));

		node = (fifo->tail_free);

		if (node->previous == NULL) {
			printf("\t\tFREE[%d] at %p : previous = NULL\n", 0, (void*)(node));
		}
		else {
			printf("\t\tFREE[%d] at %p : previous = %p\n", 0, (void*)(node), (void*)(node->previous));
		}

		if (node->data == NULL) {
			printf("\t\tFREE[%d] at %p : data = NULL\n", 0, (void*)(node));
			printf("\t\tFREE[%d] at %p : *data = NULL\n", 0, (void*)(node));
		}
		else {
			printf("\t\tFREE[%d] at %p : data = %p\n", 0, (void*)(node), (void*)(node->data));
			printf("\t\tFREE[%d] at %p : *data = %s\n", 0, (void*)(node), (char*)(node->data));
		}

		if (node->next == NULL) {
			printf("\t\tFREE[%d] at %p : next = NULL\n", 0, (void*)(node));
		}
		else {
			printf("\t\tFREE[%d] at %p : next = %p\n", 0, (void*)(node), (void*)(node->next));
		}

		printf("\t\t...\n");
	}
	else {

		skip_to_head = false;

		printf("\t\tDisplaying %d out of %d free nodes\n\n", (max_nodes > (fifo->capacity - fifo->length)) ? (fifo->capacity - fifo->length) : (max_nodes), (fifo->capacity - fifo->length));

		for (i = 0; i < (fifo->capacity - fifo->length); i++) {

			if (i == 0) {
				node = (fifo->tail_free);
			}
			else {
				if (((i + 1) >= max_nodes) && (skip_to_head == true)) {
					node = (fifo->head_free);
					i = (fifo->capacity - fifo->length) - 1;
					printf("\t\t...\n");
					printf("\t\t|\n");
					printf("\t\tV\n");
				}
				else {
					node = node->next;
					printf("\t\t|\n");
					printf("\t\tV\n");
				}
			}

			if (node->previous == NULL) {
				printf("\t\tFREE[%d] at %p : previous = NULL\n", i, (void*)(node));
			}
			else {
				printf("\t\tFREE[%d] at %p : previous = %p\n", i, (void*)(node), (void*)(node->previous));
			}

			if (node->data == NULL) {
				printf("\t\tFREE[%d] at %p : data = NULL\n", i, (void*)(node));
				printf("\t\tFREE[%d] at %p : *data = NULL\n", i, (void*)(node));
			}
			else {
				printf("\t\tFREE[%d] at %p : data = %p\n", i, (void*)(node), (void*)(node->data));
				printf("\t\tFREE[%d] at %p : *data = %s\n", i, (void*)(node), (char*)(node->data));
			}

			if (node->next == NULL) {
				printf("\t\tFREE[%d] at %p : next = NULL\n", i, (void*)(node));
			}
			else {
				printf("\t\tFREE[%d] at %p : next = %p\n", i, (void*)(node), (void*)(node->next));
			}

			if (skip_to_head == true) {
				break;
			}

			if (((i + 1) + 1) >= max_nodes) {
				skip_to_head = true;
			}
		}
	}


	printf("\t\t-----------------------------------------\n");

	// Print list of used nodes
	if ((fifo->length) == 0) {
		printf("\t\tUSED : Empty list\n");
	}
	else if (max_nodes == 0) {
		printf("\t\tDisplaying %d out of %d used nodes\n", (max_nodes > (fifo->length)) ? (fifo->length) : (max_nodes), (fifo->length));
	}
	else if (max_nodes == 1) {
		printf("\t\tDisplaying %d out of %d used nodes\n", (max_nodes > (fifo->length)) ? (fifo->length) : (max_nodes), (fifo->length));

		node = (fifo->tail_used);

		if (node->previous == NULL) {
			printf("\t\tUSED[%d] at %p : previous = NULL\n", 0, (void*)(node));
		}
		else {
			printf("\t\tUSED[%d] at %p : previous = %p\n", 0, (void*)(node), (void*)(node->previous));
		}

		if (node->data == NULL) {
			printf("\t\tUSED[%d] at %p : data = NULL\n", 0, (void*)(node));
			printf("\t\tUSED[%d] at %p : *data = NULL\n", 0, (void*)(node));
		}
		else {
			printf("\t\tUSED[%d] at %p : data = %p\n", 0, (void*)(node), (void*)(node->data));
			printf("\t\tUSED[%d] at %p : data = %s\n", 0, (void*)(node), (char*)(node->data));
		}

		if (node->next == NULL) {
			printf("\t\tUSED[%d] at %p : next = NULL\n", 0, (void*)(node));
		}
		else {
			printf("\t\tUSED[%d] at %p : next = %p\n", 0, (void*)(node), (void*)(node->next));
		}

		printf("\t\t...\n");
	}
	else {

		skip_to_head = false;

		printf("\t\tDisplaying %d out of %d used nodes\n\n", (max_nodes > (fifo->length)) ? (fifo->length) : (max_nodes), (fifo->length));

		for (i = 0; i < (fifo->length); i++) {

			if (i == 0) {
				node = (fifo->tail_used);
			}
			else {
				if ((i + 1) >= max_nodes) {
					skip_to_head = true;
					node = (fifo->head_used);
					i = (fifo->length) - 1;
					printf("\t\t...\n");
					printf("\t\t|\n");
					printf("\t\tV\n");
				}
				else {
					node = node->next;
					printf("\t\t|\n");
					printf("\t\tV\n");
				}
			}

			if (node->previous == NULL) {
				printf("\t\tUSED[%d] at %p : previous = NULL\n", i, (void*)(node));
			}
			else {
				printf("\t\tUSED[%d] at %p : previous = %p\n", i, (void*)(node), (void*)(node->previous));
			}

			if (node->data == NULL) {
				printf("\t\tUSED[%d] at %p : data = NULL\n", i, (void*)(node));
				printf("\t\tUSED[%d] at %p : *data = NULL\n", i, (void*)(node));
			}
			else {
				printf("\t\tUSED[%d] at %p : data = %p\n", i, (void*)(node), (void*)(node->data));
				printf("\t\tUSED[%d] at %p : *data = %s\n", i, (void*)(node), (char*)(node->data));
			}

			if (node->next == NULL) {
				printf("\t\tUSED[%d] at %p : next = NULL\n", i, (void*)(node));
			}
			else {
				printf("\t\tUSED[%d] at %p : next = %p\n", i, (void*)(node), (void*)(node->next));
			}

			if (skip_to_head == true) {
				break;
			}
		}
	}
}