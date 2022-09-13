#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "cbfifo.h"
#include "llfifo.h"
#include "test_cbfifo.h"
#include "test_llfifo.h"

#define BUF_SIZE ((size_t)(8))

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
 * \var cbfifo_t cbfifo
 * \brief A single global instance of circular buffer
 */
cbfifo_t cbfifo = { .head = 0, .tail = 0, .capacity = BUF_SIZE, .length = 0, .is_full = false };

int main(void) {
	printf("Hello world!\n");

	return EXIT_SUCCESS;
}