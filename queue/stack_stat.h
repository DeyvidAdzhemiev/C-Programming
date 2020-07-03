#ifndef _QUEUE_STAT_H_
#define _QUEUE_STAT_H_

#include <stdlib.h>

typedef int stack_elem_t;

typedef struct stack_t stack_t;

stack_t *stack_constructor(size_t);
void stack_destructor(stack_t *);
int stack_push(stack_t *, stack_elem_t);
int stack_pop(stack_t *, stack_elem_t *);

#endif
