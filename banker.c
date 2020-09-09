#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

typedef struct banker_t {
	unsigned int sec;
	int die, empty;
	int N;
	pthread_mutex_t mtx;
	sem_t *s;
} banker_t;

typedef struct dispatcher_t {
	pthread_mutex_t mtx;
	sem_t s;
	banker_t *banker;
} dispatcher_t;

#define NUM_BANKERS 4u

void *bank_crap(void *_ctx) {
	banker_t *ctx = (banker_t *)_ctx;
	
	while (1) {
		(void)pthread_mutex_lock(&ctx->mtx);
		if (ctx->die) {
			if (ctx->empty) {
				printf("banker %d terminating\n", ctx->N);
				break;
			} else {
				printf("banker %d final task %u\n", ctx->N, ctx->sec);
				(void)pthread_mutex_unlock(&ctx->mtx);
			}
		}
		
		printf("banker %d task %u\n", ctx->N, ctx->sec);
		(void)sleep(ctx->sec);
		printf("banker %d task %u done\n", ctx->N, ctx->sec);
		
		ctx->empty = 1;
		
		(void)sem_post(ctx->s);
	}
	
	return NULL;
}

void *dispatch_officer(void *_ctx) {
	dispatcher_t *ctx = (dispatcher_t *)_ctx;
	unsigned int sec;
	int j, task_id = 0;
	
	(void)pthread_mutex_lock(&ctx->mtx);
	
	while (1) {
		(void)scanf("%u", &sec);
		if (!sec) {
			for (j = 0; j < NUM_BANKERS; j++) {
				ctx->banker[j].die = 1;
				(void)pthread_mutex_unlock(&ctx->banker[j].mtx);
			}
			break;
		}
		
		if (sem_trywait(&ctx->s) < 0) {
			printf("cannot handle %d - %u\n", task_id, sec);
			fflush(stdout);
			(void)sem_wait(&ctx->s);
		}
		
		for (j = 0; j < NUM_BANKERS; j++)
			if (ctx->banker[j].empty) {
				printf("task %d %u to bank-crap %d\n", task_id, sec, j);
				ctx->banker[j].sec = sec;
				ctx->banker[j].empty = 0;
				(void)pthread_mutex_unlock(&ctx->banker[j].mtx);
				break;
			}
		
		task_id++;
	}
	
	return NULL;
}

int main(void) {
	pthread_t bankers[NUM_BANKERS];
	banker_t banker_context[NUM_BANKERS];
	pthread_t dispatcher_thread;
	dispatcher_t dispatcher;
	int j;
	
	(void)sem_init(&dispatcher.s, 0, NUM_BANKERS);
	
	dispatcher.banker = banker_context;
	(void)pthread_mutex_init(&dispatcher.mtx, NULL);
	(void)pthread_mutex_lock(&dispatcher.mtx);
	
	for (j = 0; j < NUM_BANKERS; j++) {
		banker_context[j].sec = 0u;
		banker_context[j].die = 0;
		banker_context[j].empty = 1;
		banker_context[j].N = j;
		banker_context[j].s = &dispatcher.s;
		(void)pthread_mutex_init(&banker_context[j].mtx, NULL);
		(void)pthread_mutex_lock(&banker_context[j].mtx);
	}
	
	for (j = 0; j < NUM_BANKERS; j++)
		(void)pthread_create(&bankers[j], NULL, bank_crap, &banker_context[j]);
	(void)pthread_create(&dispatcher_thread, NULL, dispatch_officer, &dispatcher);
	
	(void)pthread_mutex_unlock(&dispatcher.mtx);
	
	(void)pthread_join(dispatcher_thread, NULL);
	for (j = 0; j < NUM_BANKERS; j++)
		(void)pthread_join(bankers[j], NULL);
	
	return 0;
}

