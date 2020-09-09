#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sysexits.h>
#include <fcntl.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct context_t {
	int N;
	sem_t producer, consumer;
} context_t;

void init_context(context_t *ctx) {
	ctx->N = 0;
	(void)sem_init(&(ctx->producer), 1, 1u);
	(void)sem_init(&(ctx->consumer), 1, 1u);
	(void)sem_wait(&(ctx->consumer));
	
	return;
}

void producer(context_t *ctx) {
	while (1) {
		(void)sem_wait(&(ctx->producer));
		(ctx->N)++;
		(void)sleep(1u);
		(void)sem_post(&(ctx->consumer));
	}
	
	return;
}

void consumer(context_t *ctx) {
	while (1) {
		(void)sem_wait(&(ctx->consumer));
		printf("cons %d\n", ctx->N);
		(void)sem_post(&(ctx->producer));
	}
	
	return;
}

int main(void) {
	int fd;
	context_t *ctx;
	pid_t pid;
	
	fd = open("/dev/zero", O_RDWR);
	if (fd < 0) {
		perror("open");
		exit(EX_OSFILE);
	}
	
	ctx = (context_t *)mmap(NULL, sizeof (context_t), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0l);
	if (close(fd) < 0) {
		perror("close");
		exit(EX_OSFILE);
	}
	if (!ctx) {
		perror("mmap");
		exit(EX_OSERR);	
	}
	
	init_context(ctx);
	
	pid = fork();
	if (pid < 0) {
		perror("fork");
		exit(EX_OSERR);
	} else if (pid) { /* parent */
		consumer(ctx);
	} else { /* child */
		producer(ctx);
	}
	
	if (munmap(ctx, sizeof (context_t)) < 0) {
		perror("munmap");
		exit(EX_OSERR);	
	}
	
	return 0;
}

