/* XXX NEVER EVER!!! XXX */

#include <stdlib.h>

#include "queue_stat.h"

typedef struct queue_t {
	size_t N;
	elem_t *buf;
	size_t head, tail;
	int full, empty;
} queue_t;

queue_t *queue_constructor(size_t N) {
	queue_t *this;
	
	this = (queue_t *)malloc(sizeof (queue_t));
	if (!this) goto BAD0;
	
	this->N = N;
	this->head = this->tail = 0ul;
	this->full = 0;
	this->empty = 1;
	
	this->buf = (elem_t *)malloc(N * sizeof (elem_t));
	if (!this->buf) goto BAD1;
	
	return this;
	
BAD1:
	free(this);
	
BAD0:
	return NULL;
}

void queue_destructor(queue_t *this) {
	free(this->buf);
	free(this);
	
	return;
}

int queue_add(queue_t *this, elem_t e) {
	if (this->full) return -1;
	this->buf[this->head] = e;
	this->head = (this->head + 1ul) % this->N;
	this->empty = 0;
	if (this->head == this->tail) this->full = 1;
	
	return 0;
}

int queue_get(queue_t *this, elem_t *e) {
	if (this->empty) return -1;
	*e = this->buf[this->tail];
	this->tail = (this->tail + 1ul) % this->N;
	this->full = 0;
	if (this->tail == this->head) this->empty = 1;
	
	return 0;
}

#ifdef _DEBUG_

#include <stdio.h>

#define NELEM 16lu

int main(void) {
	queue_t *q;
	int j, res;
	
	q = queue_constructor(NELEM);
	if (!q) {
		fprintf(stderr, "cannot construct queue_t\n");
		fflush(stderr);
		goto err;
	} else {
		fprintf(stderr, "queue at %p\n", q);
		fflush(stderr);
	}
	
	for (j = 0; j < 32; j++)
		if (queue_add(q, j)) {
			fprintf(stderr, "cannot add %d\n", j);
			fflush(stderr);
		}
	
	for (res = queue_get(q, &j); !res; res = queue_get(q, &j)) {
		fprintf(stderr, "got %d\n", j);
		fflush(stderr);
	}
	
	queue_destructor(q);
		
	return 0;
	
err:
	return -1;
}

#endif
