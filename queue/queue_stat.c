#include <stdlib.h>

#include "queue_stat.h"

typedef struct queue_t {
	size_t N;
	queue_elem_t *buf;
	size_t head, tail;
	int full, empty;
} queue_t;

queue_t *queue_constructor(size_t N) {
	queue_t *q;
	
	q = (queue_t *)malloc(sizeof (queue_t));
	if (!q) goto BAD0;
	
	q->N = N;
	q->head = q->tail = 0ul;
	q->full = 0;
	q->empty = 1;
	
	q->buf = (queue_elem_t *)malloc(N * sizeof (queue_elem_t));
	if (!q->buf) goto BAD1;
	
	return q;
	
BAD1:
	free(q);
	
BAD0:
	return NULL;
}

void queue_destructor(queue_t *q) {
	free(q->buf);
	free(q);
	
	return;
}

int queue_add(queue_t *q, queue_elem_t e) {
	if (q->full) return -1;
	q->buf[q->head] = e;
	q->head = (q->head + 1ul) % q->N;
	q->empty = 0;
	if (q->head == q->tail) q->full = 1;
	
	return 0;
}

int queue_get(queue_t *q, queue_elem_t *e) {
	if (q->empty) return -1;
	*e = q->buf[q->tail];
	q->tail = (q->tail + 1ul) % q->N;
	q->full = 0;
	if (q->tail == q->head) q->empty = 1;
	
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
