#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct context_t {
	int N;
	pthread_mutex_t producer, consumer;
} context_t;

void *producer(void *_ctx) {
	context_t *ctx = (context_t *)_ctx;
	
	while (1) {
		(void)pthread_mutex_lock(&(ctx->producer));
		(ctx->N)++;
		(void)sleep(1u);
		if (ctx->N > 16) ctx->N = -1;
		printf("prod %d\n", ctx->N);
		(void)pthread_mutex_unlock(&(ctx->consumer));
		if (ctx->N < 0) break;
	}
	
	return (void *)0xdeadbeefl;
}

void *consumer(void *_ctx) {
	context_t *ctx = (context_t *)_ctx;
	
	while (1) {
		(void)pthread_mutex_lock(&(ctx->consumer));
		printf("cons %d\n", ctx->N);
		if (ctx->N < 0) break;
		(void)pthread_mutex_unlock(&(ctx->producer));
	}
	
	return (void *)0xcafebabel;
}

int main(void) {
/* XXX 1989 / C89 */
/*
	context_t ctx = {
		0,
		PTHREAD_MUTEX_INITIALIZER,
		PTHREAD_MUTEX_INITIALIZER
	};
*/
/* XXX 1999 / C99 */
	context_t ctx = {
		.N = 0,
		.producer = PTHREAD_MUTEX_INITIALIZER,
		.consumer = PTHREAD_MUTEX_INITIALIZER
	};
	pthread_t prod, cons;
	void *result;
	
	(void)pthread_mutex_lock(&ctx.consumer);
	
	(void)pthread_create(&prod, NULL, producer, &ctx);
	(void)pthread_create(&cons, NULL, consumer, &ctx);
	(void)pthread_join(prod, &result);
	printf("producer terminated with %ld\n", (long)result);
	(void)pthread_join(cons, &result);
	printf("consumer terminated with %ld\n", (long)result);
	
	return 0;
}

