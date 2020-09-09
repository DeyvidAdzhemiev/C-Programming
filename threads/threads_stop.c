#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct context_t {
	int N;
	sem_t producer, consumer;
} context_t;

void init_context(context_t *ctx) {
	ctx->N = 0;
	(void)sem_init(&(ctx->producer), 0, 1u);
	(void)sem_init(&(ctx->consumer), 0, 1u);
	(void)sem_wait(&(ctx->consumer));
	
	return;
}

void *producer(void *_ctx) {
	context_t *ctx = (context_t *)_ctx;
	
	while (1) {
		(void)sem_wait(&(ctx->producer));
		(ctx->N)++;
		(void)sleep(1u);
		if (ctx->N > 16) ctx->N = -1;
		printf("prod %d\n", ctx->N);
		(void)sem_post(&(ctx->consumer));
		if (ctx->N < 0) break;
	}
	
	return (void *)0xdeadbeefl;
}

void *consumer(void *_ctx) {
	context_t *ctx = (context_t *)_ctx;
	
	while (1) {
		(void)sem_wait(&(ctx->consumer));
		printf("cons %d\n", ctx->N);
		if (ctx->N < 0) break;
		(void)sem_post(&(ctx->producer));
	}
	
	return (void *)0xcafebabel;
}

int main(void) {
	context_t ctx;
	pthread_t prod, cons;
	void *result;
	
	init_context(&ctx);
	
	(void)pthread_create(&prod, NULL, producer, &ctx);
	(void)pthread_create(&cons, NULL, consumer, &ctx);
	(void)pthread_join(prod, &result);
	printf("producer terminated with %ld\n", (long)result);
	(void)pthread_join(cons, &result);
	printf("consumer terminated with %ld\n", (long)result);
	
	return 0;
}

