#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "cbfifo.h"
#include "llfifo.h"
#include "test_cbfifo.h"
#include "test_llfifo.h"

#define CB_SIZE ((size_t)(128))
#define LL_SIZE ((int)(3))

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
 * \var cbfifo_t cbfifo
 * \brief A single global instance of circular buffer
 */
cbfifo_t cbfifo = { .head = 0, .tail = 0, .capacity = CB_SIZE, .length = 0, .is_full = false };

int main(void) {
	
	// It is easier to test llfifo + cbfifo separately (by having at least 1 commented out below at a time) since outputs of success
	// will be printed at the tail-end of the function. Running both llfifo + cbfifo texts 
	// might be tough to see the success/error messages for the first of llfifo or cbfifo between them
	test_llfifo();
	test_cbfifo();

	return EXIT_SUCCESS;
}