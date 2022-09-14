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

#define ELEMENTS_PER_ROW ((int)(8))
#define EXIT_FAILURE_N ((int)(-1))

#define TEST_CBFIFO_ENQUEUE
#define TEST_CBFIFO_DEQUEUE
#define TEST_CBFIFO_CAPACITY
#define TEST_CBFIFO_LENGTH

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

	char element1_enqueue[17] = "element1_enqueue*";
	char element2_enqueue[17] = "element2_enqueue*";
	char element3_enqueue[17] = "element3_enqueue*";
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
	//		Enqueue over the available space to cbfifo capacity 128, length 128. Resulting length will be 128
	assert(test_cbfifo_enqueue((void*)element4_enqueue, (size_t)(-1), CB_SIZE) == EXIT_SUCCESS);

#endif

#ifdef TEST_CBFIFO_DEQUEUE
	// Set first parameter to the buffer to write to (from cbfifo)
	// Set second parameter to the amount of bytes to read from cbfifo and store into buffer
	// Set third parameter to how many bytes you want to dump from cbfifo + buffer

	char buf_dequeue[128] = "";
	char element1_dequeue[7] = "abcdefg";
	char element2_dequeue[9] = "hijklmnop";
	char element3_dequeue[10] = "qrstuvwxyz";
	char element4_dequeue[128] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";

	// ------------------- //
	// Happy Test Cases    //
	// ------------------- //
	//		Dequeue 128 bytes to buffer from cbfifo capacity 128, length 128. Resulting length will be 0
	assert(test_cbfifo_dequeue((void*)buf_dequeue, 128, CB_SIZE) == EXIT_SUCCESS);
	//		Enqueue 7 bytes of element1 to cbfifo capacity 128, length 0. Resulting length will be 7
	assert(test_cbfifo_enqueue((void*)element1_dequeue, 7, CB_SIZE) == EXIT_SUCCESS);
	//		Dequeue 7 bytes to buffer from cbfifo capacity 128, length 7. Resulting length will be 0
	assert(test_cbfifo_dequeue((void*)buf_dequeue, 7, CB_SIZE) == EXIT_SUCCESS);
	//		Enqueue 5 bytes of element2 to cbfifo capacity 128, length 0. Resulting length will be 5
	assert(test_cbfifo_enqueue((void*)element2_dequeue, 5, CB_SIZE) == EXIT_SUCCESS);
	//		Dequeue 2 bytes to buffer from cbfifo capacity 128, length 5. Resulting length will be 3
	assert(test_cbfifo_dequeue((void*)buf_dequeue, 2, CB_SIZE) == EXIT_SUCCESS);
	//		Dequeue over the available bytes to buffer from cbfifo capacity 128, length 3. Resulting length will be 0
	assert(test_cbfifo_dequeue((void*)buf_dequeue, 128, CB_SIZE) == EXIT_SUCCESS);
	//		Enqueue 10 bytes of element3 to cbfifo capacity 128, length 0. Resulting length will be 10
	assert(test_cbfifo_enqueue((void*)element3_dequeue, 10, CB_SIZE) == EXIT_SUCCESS);
	//		Dequeue over the available bytes to buffer from cbfifo capacity 128, length 10. Resulting length will be 0
	assert(test_cbfifo_dequeue((void*)buf_dequeue, 128, CB_SIZE) == EXIT_SUCCESS);

	// ------------------- //
	// Failure Test Cases  //
	// ------------------- //
	//		Attempt to dequeue data to NULL pointer from cbfifo
	assert(test_cbfifo_dequeue(NULL, 128, CB_SIZE) == EXIT_FAILURE);

	// ------------------- //
	// Boundary Test Cases //
	// ------------------- //
	//		Enqueue over the available space to cbfifo capacity 128, length 0. Resulting length will be 128
	assert(test_cbfifo_enqueue((void*)element4_dequeue, (size_t)(-1), 20) == EXIT_SUCCESS);
	//		Dequeue over the available bytes to buffer from cbfifo capacity 128, length 128. Resulting length will be 0
	assert(test_cbfifo_dequeue((void*)buf_dequeue, (size_t)(-1), CB_SIZE) == EXIT_SUCCESS);

#endif

#ifdef TEST_CBFIFO_CAPACITY
	// Set first parameter to how many bytes you want to dump from cbfifo

	char buf_capacity[128] = "";
	char element1_capacity[18] = "element1_capacity*";
	char element2_capacity[128] = "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";

	// ------------------- //
	// Happy Test Cases    //
	// ------------------- //
	//		Grab capacity of cbfifo capacity 128, length 0. Answer should be 128
	assert(test_cbfifo_capacity(CB_SIZE) == EXIT_SUCCESS);
	//		Enqueue 18 bytes of element1 to cbfifo capacity 128, length 18. Resulting length will be 18
	assert(test_cbfifo_enqueue((void*)element1_capacity, 18, CB_SIZE) == EXIT_SUCCESS);
	//		Grab capacity of cbfifo capacity 128, length 18. Answer should be 128
	assert(test_cbfifo_capacity(CB_SIZE) == EXIT_SUCCESS);
	//		Dequeue 7 bytes to buffer from cbfifo capacity 128, length 18. Resulting length will be 11
	assert(test_cbfifo_dequeue((void*)buf_capacity, 7, CB_SIZE) == EXIT_SUCCESS);
	//		Grab capacity of cbfifo capacity 128, length 11. Answer should be 128
	assert(test_cbfifo_capacity(CB_SIZE) == EXIT_SUCCESS);
	//		Enqueue over the available space to cbfifo capacity 128, length 11. Resulting length will be 128
	assert(test_cbfifo_enqueue((void*)element2_capacity, (size_t)(-1), CB_SIZE) == EXIT_SUCCESS);
	//		Grab capacity of cbfifo capacity 128, length 128. Answer should be 128
	assert(test_cbfifo_capacity(CB_SIZE) == EXIT_SUCCESS);
	//		Dequeue over the available bytes to buffer from cbfifo capacity 128, length 128. Resulting length will be 0
	assert(test_cbfifo_dequeue((void*)buf_capacity, (size_t)(-1), CB_SIZE) == EXIT_SUCCESS);
	//		Grab capacity of cbfifo capacity 128, length 0. Answer should be 128
	assert(test_cbfifo_capacity(CB_SIZE) == EXIT_SUCCESS);

	// ------------------- //
	// Failure Test Cases  //
	// ------------------- //

	// ------------------- //
	// Boundary Test Cases //
	// ------------------- //

#endif

#ifdef TEST_CBFIFO_LENGTH
	// Set first parameter to how many bytes you want to dump from cbfifo

	char buf_length[128] = "";
	char element1_length[18] = "element1_length*";
	char element2_length[128] = "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";

	// ------------------- //
	// Happy Test Cases    //
	// ------------------- //
	//		Grab length of cbfifo capacity 128, length 0. Answer should be 0
	assert(test_cbfifo_length(CB_SIZE) == EXIT_SUCCESS);
	//		Enqueue 18 bytes of element1 to cbfifo capacity 128, length 18. Resulting length will be 18
	assert(test_cbfifo_enqueue((void*)element1_length, 18, CB_SIZE) == EXIT_SUCCESS);
	//		Grab length of cbfifo capacity 128, length 18. Answer should be 18
	assert(test_cbfifo_length(CB_SIZE) == EXIT_SUCCESS);
	//		Dequeue 7 bytes to buffer from cbfifo capacity 128, length 18. Resulting length will be 11
	assert(test_cbfifo_dequeue((void*)buf_length, 7, CB_SIZE) == EXIT_SUCCESS);
	//		Grab length of cbfifo capacity 128, length 11. Answer should be 11
	assert(test_cbfifo_length(CB_SIZE) == EXIT_SUCCESS);
	//		Enqueue over the available space to cbfifo capacity 128, length 11. Resulting length will be 128
	assert(test_cbfifo_enqueue((void*)element2_length, (size_t)(-1), CB_SIZE) == EXIT_SUCCESS);
	//		Grab length of cbfifo capacity 128, length 128. Answer should be 128
	assert(test_cbfifo_length(CB_SIZE) == EXIT_SUCCESS);
	//		Dequeue over the available bytes to buffer from cbfifo capacity 128, length 128. Resulting length will be 0
	assert(test_cbfifo_dequeue((void*)buf_length, (size_t)(-1), CB_SIZE) == EXIT_SUCCESS);
	//		Grab length of cbfifo capacity 128, length 0. Answer should be 0
	assert(test_cbfifo_length(CB_SIZE) == EXIT_SUCCESS);

	// ------------------- //
	// Failure Test Cases  //
	// ------------------- //

	// ------------------- //
	// Boundary Test Cases //
	// ------------------- //
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

	int i;
	int length;
	int limit;

	if (nbyte == 0) {
		limit = 0;
	}
	else if (nbyte > (cbfifo.capacity - cbfifo.length)) {
		limit = cbfifo.capacity - cbfifo.length;
	}
	else {
		limit = nbyte;
	}

	length = cbfifo_enqueue(buf, nbyte);
	cbfifo_dump_state(max_bytes);

	printf("\t\t-----------------------------------------\n");

	if (limit == 0 || buf == NULL) {
		printf("\t\tENQD : Empty buffer\n");
	}
	else {
		printf("\t\tENQD : [%03u] to [%03u]\n", 0, (limit - 1));

		for (i = 0; i < limit; i++) {

			if (i == 0) {
				printf("\n\t\t   ENQD[%03d]=%c\t", i, *(((char*)(buf)) + i));
			}
			else {

				if (i % ELEMENTS_PER_ROW == 0) {
					printf("\n\t\t");
				}

				printf("-> ENQD[%03d]=%c\t", i, *(((char*)(buf)) + i));
			}
		}

		printf("\n");
	}

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
int test_cbfifo_dequeue(void* buf, size_t nbyte, size_t max_bytes) {

	int i;
	int length;
	int limit;

	if (nbyte == 0) {
		limit = 0;
	}
	else if (nbyte > cbfifo.length) {
		limit = cbfifo.length;
	}
	else {
		limit = nbyte;
	}

	length = cbfifo_dequeue(buf, nbyte);
	cbfifo_dump_state(max_bytes);

	printf("\t\t-----------------------------------------\n");
	
	if (limit == 0 || buf == NULL) {
		printf("\t\tDEQD : Empty buffer\n");
	}
	else {
		printf("\t\tDEQD : [%03u] to [%03d]\n", 0, (limit - 1));

		for (i = 0; i < limit; i++) {
			
			if (i == 0) {
				printf("\n\t\t   DEQD[%03d]=%c\t", i, *(((char*)(buf)) + i));
			}
			else {

				if (i % ELEMENTS_PER_ROW == 0) {
					printf("\n\t\t");
				}

				printf("-> DEQD[%03d]=%c\t", i, *(((char*)(buf)) + i));
			}
		}

		printf("\n");
	}

	if (length != EXIT_FAILURE_N) {
		return EXIT_SUCCESS;
	}
	else {
		return EXIT_FAILURE;
	}
}

/**
 * \fn int test_cbfifo_length(size_t max_bytes)
 * \brief Returns the number of bytes currently on the FIFO.
 *
 * \param max_bytes The number of bytes to dump from FIFO. If max_bytes is less than the total used bytes, it will dump (max_bytes - 1) nodes from the tail and then dump the head
 *
 * \return If successful, returns EXIT_SUCCESS (0). In the case of an error, the function prints the failure and returns EXIT_FAILURE (1)
 */
int test_cbfifo_length(size_t max_bytes) {

	int length;

	length = cbfifo_length();
	cbfifo_dump_state(max_bytes);

	if (length != EXIT_FAILURE_N) {
		return EXIT_SUCCESS;
	}
	else {
		return EXIT_FAILURE;
	}
}

/**
 * \fn int test_cbfifo_capacity(size_t max_bytes)
 * \brief Returns the FIFO's capacity
 *
 * \param max_bytes The number of bytes to dump from FIFO. If max_bytes is less than the total used bytes, it will dump (max_bytes - 1) nodes from the tail and then dump the head
 *
 * \return If successful, returns EXIT_SUCCESS (0). In the case of an error, the function prints the failure and returns EXIT_FAILURE (1)
 */
int test_cbfifo_capacity(size_t max_bytes) {

	int capacity;

	capacity = cbfifo_capacity();
	cbfifo_dump_state(max_bytes);

	if (capacity != EXIT_FAILURE_N) {
		return EXIT_SUCCESS;
	}
	else {
		return EXIT_FAILURE;
	}
}

/**
  * \fn void cbfifo_dump_state()
  * \brief Dumps info about each element in the FIFO
  *
  * \param max_bytes The number of bytes to dump from FIFO. If max_bytes is less than the total used bytes, it will dump (max_bytes - 1) nodes from the tail and then dump the head
  *
  * \return N/A
  */
void cbfifo_dump_state(size_t max_bytes) {

	int i;
	size_t index;

	printf("\n***************************NEW CBFIFO****************************\n");

	// Print state of FIFO
	printf("\tcbfifo at %p\n", (void*)(&cbfifo));
	printf("\tcbfifo.head is %u\n", (unsigned int)cbfifo.head);
	printf("\tcbfifo.tail is %u\n", (unsigned int)cbfifo.tail);
	printf("\tcbfifo.capacity is %u\n", (unsigned int)cbfifo.capacity);
	printf("\tcbfifo.length is %u\n", (unsigned int)cbfifo.length);
	printf("\tcbfifo.is_full is %s\n", (cbfifo.is_full == true) ? "true" : "false");


	printf("\t\t-----------------------------------------\n");

	// Print range of free bytes
	if (cbfifo.is_full == true) {
		printf("\t\tFREE : Empty list\n");
	}
	else {
		printf("\t\tFREE : [%03u] to [%03u]\n", (unsigned int)cbfifo.head, (unsigned int)((cbfifo.tail - 1) & (cbfifo.capacity - 1)));
	}

	printf("\t\t-----------------------------------------\n");

	// Print range + list of used bytes
	if ((cbfifo.length) == 0) {
		printf("\t\tUSED : Empty list\n");
	}
	else {
		printf("\t\tUSED : [%03u] to [%03u]\n", (unsigned int)cbfifo.tail, (unsigned int)((cbfifo.head - 1) & (cbfifo.capacity - 1)));

		for (i = 0; i < cbfifo.length; i++) {

			if (i == 0) {
				index = cbfifo.tail;
				printf("\n\t\t   USED[%03d]=%c\t", (unsigned int)index, cbfifo.buf[index]);
			}
			else {

				if (((i + 1) >= max_bytes) && ((i + 1) < cbfifo.length)) {
					index = cbfifo.head - 1;
					printf("\n\t\t   ...");
					printf("\n\t\t-> USED[%03d]=%c\t", (unsigned int)index, cbfifo.buf[index]);
					break;
				}
				else {

					index = (index + 1) & (cbfifo.capacity - 1);

					if (i % ELEMENTS_PER_ROW == 0) {
						printf("\n\t\t");
					}

					printf("-> USED[%03d]=%c\t", (unsigned int)index, cbfifo.buf[index]);
				}
			}
		}

		printf("\n");
	}
}