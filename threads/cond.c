#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

typedef struct context_t {
	int suspend;
	pthread_mutex_t mtx;
	pthread_cond_t cond;
} context_t;

void suspend_thread(context_t *ctx) {
	(void)pthread_mutex_lock(&ctx->mtx);
	ctx->suspend = 1;
	(void)pthread_mutex_unlock(&ctx->mtx);
	
	return;
}

void check_suspend(context_t *ctx) {
	(void)pthread_mutex_lock(&ctx->mtx);
	while (ctx->suspend)
		(void)pthread_cond_wait(&ctx->cond, &ctx->mtx);
	(void)pthread_mutex_unlock(&ctx->mtx);
	
	return;
}

void resume_thread(context_t *ctx) {
	(void)pthread_mutex_lock(&ctx->mtx);
	ctx->suspend = 0;
	(void)pthread_cond_broadcast(&ctx->cond);
	(void)pthread_mutex_unlock(&ctx->mtx);
	
	return;
}

void *running_thread(void *_ctx) {
	context_t *ctx = (context_t *)_ctx;
	int j;
	
	for (j = 0; 1; j++) {
		printf("%d\n", j);
		check_suspend(ctx);
	}
	
	return NULL;
}

void *suspending_thread(void *_ctx) {
	context_t *ctx = (context_t *)_ctx;
	int flag;
	
	for (flag = 0; 1; flag = !flag) {
		if (flag) suspend_thread(ctx);
		else resume_thread(ctx);
		sleep(5u);
	}
	
	return NULL;
}

int main(void) {
	pthread_t running, suspending;
	context_t ctx = {
		.suspend = 0,
		.mtx = PTHREAD_MUTEX_INITIALIZER,
		.cond = PTHREAD_COND_INITIALIZER
	};
	
	(void)pthread_create(&running, NULL, running_thread, &ctx);
	(void)pthread_create(&suspending, NULL, suspending_thread, &ctx);
	
	(void)pthread_join(running, NULL);
	(void)pthread_join(suspending, NULL);
	
	return 0;
}

