#include "ring_buffer.h"


inline static void
inc_head(struct RingBuffer* rb)
{
	++rb->head;
}


static int
check_full(struct RingBuffer* rb)
{
	if (rb->head >= rb->tail) {
		rb->head = rb->tail;
		return ERBFULL;
	} else {
		return 0;
	}
}


inline static void
inc_tail(struct RingBuffer* rb)
{
	++rb->tail;
}


static int
check_empty(struct RingBuffer* rb)
{
	if (rb->tail >= rb->head) {
		rb->tail = rb->head;
		return ERBEMPTY;
	} else {
		return 0;
	}
}

int
rb_init(struct RingBuffer* rb, size_t item_size, size_t size, void** buf)
{
	/* check that size is a power of two */
	if ((size & (size - 1)) != 0) {
		return EBADSIZE;
	}

	return 0;
}

int
rb_put(struct RingBuffer* rb, void* item)
{
	int err;

	err = check_full(rb);
	if (err) return err;

	memcpy(rb->buf[rb->head], item, rb->item_size);

	inc_head(rb);

	return 0;
}


int
rb_get(struct RingBuffer* rb, void* item)
{
	int err;

	err = check_empty(rb);
	if (err) return err;

	memcpy(item, rb->buf[rb->tail], rb->item_size);

	inc_tail(rb);

	return 0;
}
