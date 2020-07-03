#include <stdio.h>
#include <stdlib.h>

#include "queue_stat.h"

#define NELEM 16lu

int main(void) {
	queue_t *q;
	int j, res;
	
	q = queue_constructor(NELEM);
	if (!q) {
		fprintf(stderr, "cannot construct queue_t\n");
		fflush(stderr);
		goto err;
	} else {
		fprintf(stderr, "queue at %p\n", q);
		fflush(stderr);
	}
	
	for (j = 0; j < 32; j++)
		if (queue_add(q, j)) {
			fprintf(stderr, "cannot add %d\n", j);
			fflush(stderr);
		}
	
	for (res = queue_get(q, &j); !res; res = queue_get(q, &j)) {
		fprintf(stderr, "got %d\n", j);
		fflush(stderr);
	}
	
	queue_destructor(q);
		
	return 0;
	
err:
	return -1;
}

