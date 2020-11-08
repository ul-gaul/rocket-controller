#include "ring_buffer.h"


inline static void
inc_head(struct RingBuffer* rb)
{
	++rb->head;
}


static int
check_full(struct RingBuffer* rb)
{
	return ((rb->head - rb->tail) == rb->size) ? ERBFULL : 0;
}


inline static void
inc_tail(struct RingBuffer* rb)
{
	++rb->tail;
}


static int
check_empty(struct RingBuffer* rb)
{
	return ((rb->head - rb->tail) == 0) ? ERBEMPTY : 0;
}


int
rb_init(struct RingBuffer* rb, size_t item_size, size_t size, void* buf)
{
	/* check that size is a power of two (otherwise indexing won't work) */
	if (((size & (size - 1)) != 0) || (size == 0)) {
		return EBADSIZE;
	}

	if ((rb == NULL) || (buf == NULL)) {
		return EBADPTR;
	}

	if (item_size <= 0) {
		return EBADSIZE;
	}

	rb->head = 0;
	rb->tail = 0;
	rb->item_size = item_size;
	rb->size = size;
	rb->buf = buf;

	return 0;
}


int
rb_put(struct RingBuffer* rb, void* item)
{
	int err;
	unsigned int offset;

	err = check_full(rb);
	if (err) return err;

	offset = (rb->head & (rb->size - 1)) * rb->item_size;
	memcpy(&rb->buf[offset], item, rb->item_size);

	inc_head(rb);

	return 0;
}


int
rb_get(struct RingBuffer* rb, void* item)
{
	int err;
	unsigned int offset;

	err = check_empty(rb);
	if (err) return err;

	offset = (rb->tail & (rb->size - 1)) * rb->item_size;
	memcpy(item, rb->buf[offset], rb->item_size);

	inc_tail(rb);

	return 0;
}

