/*
 * Ring buffer implementation to manage an array of unknown structs.
 */

#ifndef __RING_BUFFER__H_
#define __RING_BUFFER__H_


#include <stddef.h>
#include <string.h>


#define RBMAXSIZE 128

#define ERBEMPTY -1
#define ERBFULL  -2
#define EBADSIZE -3
#define EBADPTR  -4


struct RingBuffer {
	unsigned int head;
	unsigned int tail;
	size_t item_size;
	size_t size;
	char* buf;
};


/*
 * Init a ring buffer struct with the pre-allocated buffer.
 *
 * Args:
 *     rb: address of the ring buffer to initialise
 *     item_size: size in bytes of the elements of the buffer
 *     size: size of the buffer to be managed
 *     buf: address of the buffer to be managed
 *
 * Returns the appropriate code on error.
 */
int rb_init(struct RingBuffer* rb, size_t item_size, size_t size, void* buf);


/*
 * Put an item in the ring buffer.
 *
 * Returns the appropriate code on error.
 */
int rb_put(struct RingBuffer* rb, void* item);


/*
 * Get an item from the ring buffer.
 *
 * Returns the appropriate code on error.
 */
int rb_get(struct RingBuffer* rb, void* item);


#endif /* __RING_BUFFER__H_ */
