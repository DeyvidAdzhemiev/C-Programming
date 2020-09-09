#ifndef _LIST_
#define _LIST_

#include <pthread.h>
#include "our_types.h"

typedef struct dlist_t {
	out_types_container_t data;
	struct dlist_t *prev, *next;
} dlist_t;

typedef struct list_t {
	pthread_mutex_t mtx;
	dlist_t *head, *tail;
} list_t;

typedef struct iter_t {
	pthread_mutex_t *mtx;
	dlist_t *iter;
} iter_t;

void list_init(list_t *);

int add_head(list_t *, out_types_container_t);
int del_head(list_t *, out_types_container_t *);

int add_tail(list_t *, out_types_container_t);
int del_tail(list_t *, out_types_container_t *);

void iter_init_head(list_t *, iter_t *);
void iter_init_tail(list_t *, iter_t *);
int iter_next(iter_t *, out_types_container_t *);
int iter_prev(iter_t *, out_types_container_t *);
int iter_peek(iter_t *, out_types_container_t *);
void iter_end(iter_t *);

#endif
