#include <stdio.h>
#include <stdlib.h>

int **alloc_array(int rows, int cols) {
	int **rp = NULL;
	int j, k;
	
	rp = (int **)malloc(rows * sizeof (int *));
	if (!rp) goto bad0;
	
	for (j = 0; j < rows; j++) {
		rp[j] = (int *)malloc(cols * sizeof (int));
		if (!rp[j]) goto bad1;
	}
	
	return rp;
	
bad1:
	for (k = 0; k < j; k++)
		free(rp[k]);
	free(rp);
bad0:
	return NULL;
}

void dealloc_array(int **rp, int rows) {
	int j;
	
	for (j = 0; j < rows; j++)
		free(rp[j]);
	
	free(rp);
	
	return;
}

int main(void) {
	int a[3][3] = {
		{ 0, 1, 2 },
		{ 3, 4, 5 },
		{ 6, 7, 8 }
	};
	int i, j;
	int **dynarr;
	int ***t = &dynarr;
	
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++)
			printf("%d ", a[i][j]);
		printf("\n");
	}
	
	dynarr = alloc_array(3, 3);
	if (!dynarr) goto error;
	
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++) {
			dynarr[i][j] = a[i][j];
/*
			*(*(dynarr + i) + j) = a[i][j];
*/
		}
	
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++)
			printf("%d ", dynarr[i][j]);
		printf("\n");
	}
	
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++)
			printf("%d ", *(*((*t) + i) + j));
		printf("\n");
	}
		
	dealloc_array(dynarr, 3);
	
	return 0;
	
error:
	return -1;
}

