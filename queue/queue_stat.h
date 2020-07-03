#ifndef _QUEUE_STAT_H_
#define _QUEUE_STAT_H_

#include <stdlib.h>

typedef int queue_elem_t;

typedef struct queue_t queue_t;

queue_t *queue_constructor(size_t);
void queue_destructor(queue_t *);
int queue_add(queue_t *, queue_elem_t);
int queue_get(queue_t *, queue_elem_t *);

#endif
