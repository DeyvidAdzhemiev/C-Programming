#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "sm.h"

typedef enum states_t {
	SSTART = 1,
	SFINAL = 2,
	SDIGIT = 3
} states_t;

typedef enum events_t {
	EDIGIT = 1,
	ENONDIGIT = 2,
	EEOF = 3
} events_t;

typedef struct context_t {
	int accumulator;
	int acc_valid;
	int c;
} context_t;

static void init_ctx(context_t *ctx) {
	ctx->accumulator = 0;
	ctx->acc_valid = 0;
	
	return;
}

static int init_acc(void *_ctx, delta_t *delta) {
	context_t *ctx = (context_t *)_ctx;
	char digit[2] = { '\0', '\0' };
	
	digit[0] = (char)ctx->c;
	ctx->acc_valid = 1;
	ctx->accumulator = atoi(digit);
	
	return 1;
}

static int accumulate(void *_ctx, delta_t *delta) {
	context_t *ctx = (context_t *)_ctx;
	char digit[2] = { '\0', '\0' };
		
	digit[0] = (char)ctx->c;
	ctx->accumulator = ctx->accumulator * 10 + atoi(digit);
	
	return 1;
}

static int print_acc(void *_ctx, delta_t *delta) {
	context_t *ctx = (context_t *)_ctx;
	
	if (ctx->acc_valid) printf("%d\n", ctx->accumulator);
	ctx->acc_valid = 0;
	
	return 1;
}

static delta_t deltas[] = {
	{ SSTART, EEOF, SFINAL, NULL, print_acc },
	{ SSTART, EDIGIT, SDIGIT, NULL, init_acc },
	{ SSTART, ENONDIGIT, SSTART, NULL, NULL },
	{ SDIGIT, EDIGIT, SDIGIT, NULL, accumulate },
	{ SDIGIT, ENONDIGIT, SSTART, NULL, print_acc },
	{ SDIGIT, EEOF, SFINAL, NULL, print_acc },
	{ UNDEF, UNDEF, UNDEF, NULL, NULL }
};

int main(void) {
	context_t ctx;
	state_t sm;
	events_t event;
	char *test = "sdkjfsdkh123kfh546kdsgjn675,dfjn324";
	char *t;
	
	init_ctx(&ctx);
	state_constructor(&sm, SSTART, SFINAL, UNDEF, deltas, &ctx);
	
	for (t = test; ; t++) {
		ctx.c = ((int)*t) & 0xff;
		if (!ctx.c) event = EEOF;
		else if (isdigit(ctx.c)) event = EDIGIT;
		else event = ENONDIGIT;
		if (state_exec(&sm, event) <= 0) break;
	}
	
	return 0;
}

