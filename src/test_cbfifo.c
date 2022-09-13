/**
 * \file test_cbfifo.c
 * \author Dayton Flores, dayton.flores@colorado.edu
 */

#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "cbfifo.h"
#include "test_cbfifo.h"

#define CB_SIZE ((size_t)(128))

#define GREEN "\x1B[32m"
#define RESET "\x1B[0m"

#define EXIT_FAILURE_N ((int)(-1))

#define TEST_CBFIFO_ENQUEUE
//#define TEST_CBFIFO_DEQUEUE
//#define TEST_CBFIFO_CAPACITY
//#define TEST_CBFIFO_LENGTH

 /**
  * \typedef cbfifo_t
  * \brief Allows struct cbfifo_s to be instantiated as cbfifo_t
  */
typedef struct cbfifo_s cbfifo_t;

/**
 * \struct cbfifo_s
 * \brief Circular buffer of fixed size
 *
 * \detail uint8_t buf[CB_SIZE] - Buffer of fixed size. It is CB_SIZE number of bytes large
 * \detail size_t head - Current head. This increments just after elements are added to buf
 * \detail size_t tail - Current tail. This increments just after elements are removed from buf
 * \detail size_t capacity - The amount of bytes the buffer can store at a time
 * \detail size_t length - The amount of bytes currently stored in the buffer
 * \detail bool is_full - Flag to keep track of status of the buf
 */
struct cbfifo_s {
	uint8_t buf[CB_SIZE];
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
 * \fn void test_cbfifo()
 * \brief Runs unit tests for happy cases + failure cases + boundary cases for each cbfifo function
 *
 * \return N/A
 */
void test_cbfifo() {

#ifdef TEST_CBFIFO_ENQUEUE
	// Set first parameter to the buffer to read from and store into cbfifo
	// Set second parameter to the amount of bytes to read from buffer and store into cbfifo
	// Set third parameter to how many bytes you want to dump from cbfifo

	char element1_enqueue[17] = "element1_enqueue";
	char element2_enqueue[17] = "element2_enqueue";
	char element3_enqueue[17] = "element3_enqueue";
	char element4_enqueue[128] = "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";

	// ------------------- //
	// Happy Test Cases    //
	// ------------------- //
	//		Enqueue element1 to cbfifo capacity 128, length 0. Resulting length will be 17
	assert(test_cbfifo_enqueue((void*)element1_enqueue, 17, CB_SIZE) == EXIT_SUCCESS);
	//		Enqueue element2 to cbfifo capacity 128, length 17. Resulting length will be 34
	assert(test_cbfifo_enqueue((void*)element2_enqueue, 17, CB_SIZE) == EXIT_SUCCESS);
	//		Enqueue element3 to cbfifo capacity 128, length 34. Resulting length will be 51
	assert(test_cbfifo_enqueue((void*)element3_enqueue, 17, CB_SIZE) == EXIT_SUCCESS);

	// ------------------- //
	// Failure Test Cases  //
	// ------------------- //
	//		Attempt to enqueue data from NULL pointer to cbfifo
	assert(test_cbfifo_enqueue(NULL, 17, CB_SIZE) == EXIT_FAILURE);

	// ------------------- //
	// Boundary Test Cases //
	// ------------------- //
	//		Enqueue over the available space to cbfifo capacity 128, length 68. Resulting length will be 128
	assert(test_cbfifo_enqueue((void*)element4_enqueue, (size_t)(-1), CB_SIZE) == EXIT_SUCCESS);

#endif

#ifdef TEST_CBFIFO_DEQUEUE
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

#ifdef TEST_CBFIFO_CAPACITY
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

#ifdef TEST_CBFIFO_LENGTH
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

#ifdef TEST_CBFIFO_ENQUEUE
	printf(GREEN "Asserts for all test cases against cbfifo_enqueue have passed\n" RESET);
#endif
#ifdef TEST_CBFIFO_DEQUEUE
	printf(GREEN "Asserts for all test cases against cbfifo_dequeue have passed\n" RESET);
#endif
#ifdef TEST_CBFIFO_CAPACITY
	printf(GREEN "Asserts for all test cases against cbfifo_capacity have passed\n" RESET);
#endif
#ifdef TEST_CBFIFO_LENGTH
	printf(GREEN "Asserts for all test cases against cbfifo_length have passed\n" RESET);
#endif
}

/**
 * \fn int test_cbfifo_enqueue(void* buf, size_t nbyte, size_t max_bytes)
 * \brief Enqueues data onto the FIFO, up to the limit of the available FIFO capacity.
 *
 * \param buf Pointer to the data
 * \param nbyte Max number of bytes to enqueue
 * \param max_bytes The number of bytes to dump from FIFO. If max_bytes is less than the total used bytes, it will dump (max_bytes - 1) nodes from the tail and then dump the head
 *
 * \return If successful, returns EXIT_SUCCESS (0). In the case of an error, the function prints the failure and returns EXIT_FAILURE (1)
 */
int test_cbfifo_enqueue(void* buf, size_t nbyte, size_t max_bytes) {

	int length;

	length = cbfifo_enqueue(buf, nbyte);
	cbfifo_dump_state(max_bytes);

	if (length != EXIT_FAILURE_N) {
		return EXIT_SUCCESS;
	}
	else {
		return EXIT_FAILURE;
	}
}

/**
 * \fn int test_cbfifo_dequeue(void* buf, size_t nbyte, size_t max_bytes)
 * \brief Attempts to remove ("dequeue") up to nbyte bytes of data from the FIFO. Removed data will be copied into the buffer pointed to by buf.
 *
 * \param buf Destination for the dequeued data
 * \param nbyte Bytes of data requested
 * \param max_bytes The number of bytes to dump from FIFO. If max_bytes is less than the total used bytes, it will dump (max_bytes - 1) nodes from the tail and then dump the head
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
//int test_cbfifo_dequeue(void* buf, size_t nbyte, size_t max_bytes) {
//
//}

/**
 * \fn int test_cbfifo_length(size_t max_bytes)
 * \brief Returns the number of bytes currently on the FIFO.
 *
 * \param max_bytes The number of bytes to dump from FIFO. If max_bytes is less than the total used bytes, it will dump (max_bytes - 1) nodes from the tail and then dump the head
 *
 * \return If successful, returns EXIT_SUCCESS (0). In the case of an error, the function prints the failure and returns EXIT_FAILURE (1)
 */
//int test_cbfifo_length(size_t max_bytes) {
//
//}

/**
 * \fn int test_cbfifo_capacity(size_t max_bytes)
 * \brief Returns the FIFO's capacity
 *
 * \param max_bytes The number of bytes to dump from FIFO. If max_bytes is less than the total used bytes, it will dump (max_bytes - 1) nodes from the tail and then dump the head
 *
 * \return If successful, returns EXIT_SUCCESS (0). In the case of an error, the function prints the failure and returns EXIT_FAILURE (1)
 */
//int test_cbfifo_capacity(size_t max_bytes) {
//
//}

/**
  * \fn void cbfifo_dump_state()
  * \brief Dumps info about each element in the FIFO
  *
  * \param max_bytes The number of bytes to dump from FIFO. If max_bytes is less than the total used bytes, it will dump (max_bytes - 1) nodes from the tail and then dump the head
  *
  * \return N/A
  */
void cbfifo_dump_state(size_t max_bytes) {

	bool skip_to_head;
	int i;
	size_t index;
	uint8_t byte;

	printf("\n***************************NEW CBFIFO****************************\n");

	// Print state of FIFO
	printf("\tcbfifo at %p\n", (void*)(&cbfifo));
	printf("\tcbfifo.head is %u\n", cbfifo.head);
	printf("\tcbfifo.tail is %u\n", cbfifo.tail);
	printf("\tcbfifo.capacity is %u\n", cbfifo.capacity);
	printf("\tcbfifo.length is %u\n", cbfifo.length);
	printf("\tcbfifo.is_full is %s\n", (cbfifo.is_full == true) ? "true" : "false");


	printf("\t\t-----------------------------------------\n");

	// Print list of free bytes
	if (cbfifo.is_full == false) {
		printf("\t\tFREE : Empty list\n");
	}
	else if (max_bytes == 0) {
		printf("\t\tDisplaying %d out of %d free bytes\n", (max_bytes > (cbfifo.length) ? (cbfifo.length) : (max_bytes)), (cbfifo.length));
	}
	else if (max_bytes == 1) {
		printf("\t\tDisplaying %d out of %d free bytes\n", (max_bytes > (cbfifo.length) ? (cbfifo.length) : (max_bytes)), (cbfifo.length));

		index = (cbfifo.tail);
		byte = (cbfifo.buf[index]);

		printf("\t\tFREE[%u] : %c\n", index, byte);

		printf("\t\t...\n");
	}
	else {

		skip_to_head = false;

		printf("\t\tDisplaying %d out of %d free bytes\n", (max_bytes > (cbfifo.length) ? (cbfifo.length) : (max_bytes)), (cbfifo.length));

		for (i = 0; i < (cbfifo.length); i++) {

			if (i == 0) {
				index = (cbfifo.tail);
				byte = (cbfifo.buf[index]);
			}
			else {
				if (((i + 1) >= max_bytes) && (skip_to_head == true)) {
					index = (cbfifo.head);
					byte = (cbfifo.buf[index]);
					i = (cbfifo.length) - 1;
					printf("\t\t...\n");
					printf("\t\t|\n");
					printf("\t\tV\n");
				}
				else {
					index = (index + 1) & (cbfifo.capacity - 1);
					byte = (cbfifo.buf[index]);
					printf("\t\t|\n");
					printf("\t\tV\n");
				}
			}

			printf("\t\tFREE[%u] : %c\n", index, byte);

			if (skip_to_head == true) {
				break;
			}

			if (((i + 1)) >= max_bytes) {
				skip_to_head = true;
			}
		}
	}


	printf("\t\t-----------------------------------------\n");

	// Print list of used bytes
	if ((cbfifo.length) == 0) {
		printf("\t\tUSED : Empty list\n");
	}
	else if (max_bytes == 0) {
		printf("\t\tDisplaying %d out of %d used bytes\n", (max_bytes > (cbfifo.length) ? (cbfifo.length) : (max_bytes)), (cbfifo.length));
	}
	else if (max_bytes == 1) {
		printf("\t\tDisplaying %d out of %d used bytes\n", (max_bytes > (cbfifo.length) ? (cbfifo.length) : (max_bytes)), (cbfifo.length));

		index = (cbfifo.tail);
		byte = (cbfifo.buf[index]);

		printf("\t\tUSED[%u] : %c\n", index, byte);

		printf("\t\t...\n");
	}
	else {

		skip_to_head = false;

		printf("\t\tDisplaying %d out of %d used bytes\n", (max_bytes > (cbfifo.length) ? (cbfifo.length) : (max_bytes)), (cbfifo.length));

		for (i = 0; i < (cbfifo.length); i++) {

			if (i == 0) {
				index = (cbfifo.tail);
				byte = (cbfifo.buf[index]);
			}
			else {
				if (((i + 1) >= max_bytes) && (skip_to_head == true)) {
					index = (cbfifo.head);
					byte = (cbfifo.buf[index]);
					i = (cbfifo.length) - 1;
					printf("\t\t...\n");
					printf("\t\t|\n");
					printf("\t\tV\n");
				}
				else {
					index = (index + 1) & (cbfifo.capacity - 1);
					byte = (cbfifo.buf[index]);
					printf("\t\t|\n");
					printf("\t\tV\n");
				}
			}

			printf("\t\tUSED[%u] : %c\n", index, byte);

			if (skip_to_head == true) {
				break;
			}

			if (((i + 1)) >= max_bytes) {
				skip_to_head = true;
			}
		}
	}
}