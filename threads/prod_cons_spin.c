#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct context_t {
	int N;
	pthread_spinlock_t producer, consumer;
} context_t;

void *producer(void *_ctx) {
	context_t *ctx = (context_t *)_ctx;
	
	while (1) {
		(void)pthread_spin_lock(&(ctx->producer));
		(ctx->N)++;
		(void)sleep(1u);
		if (ctx->N > 63) ctx->N = -1;
		printf("prod %d\n", ctx->N);
		(void)pthread_spin_unlock(&(ctx->consumer));
		if (ctx->N < 0) break;
	}
	
	return (void *)0xdeadbeefl;
}

void *consumer(void *_ctx) {
	context_t *ctx = (context_t *)_ctx;
	
	while (1) {
		(void)pthread_spin_lock(&(ctx->consumer));
		printf("cons %d\n", ctx->N);
		if (ctx->N < 0) break;
		(void)pthread_spin_unlock(&(ctx->producer));
	}
	
	return (void *)0xcafebabel;
}

int main(void) {
/* C89 */
	context_t ctx;
/* C99 */
/*
	context_t ctx = {
		.N = 0;
	};
*/
	pthread_t prod, cons;
	void *result;
	
	ctx.N = 0;
	(void)pthread_spin_init(&ctx.producer, 0);
	(void)pthread_spin_init(&ctx.consumer, 0);
	
	(void)pthread_spin_lock(&ctx.consumer);
	
	(void)pthread_create(&prod, NULL, producer, &ctx);
	(void)pthread_create(&cons, NULL, consumer, &ctx);
	(void)pthread_join(prod, &result);
	printf("producer terminated with %ld\n", (long)result);
	(void)pthread_join(cons, &result);
	printf("consumer terminated with %ld\n", (long)result);
	
	return 0;
}

