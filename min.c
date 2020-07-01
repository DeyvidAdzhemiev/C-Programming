#include <stdio.h>

#if 0
int a[5];
#endif

int main(void) {
	int a[5] = {
		5, 3, 2, 1, 7
	};
	
	int j, min, min_idx;
	
	for (j = -5; j < 5; j++)
		printf("(%d %d) ", j, a[j]);
	printf("\n");
	
	for (j = -5, min = a[0], min_idx = 0; j < 5; j++)
		if (a[j] < min) {
			min = a[j];
			min_idx = j;
		}
	
	printf("(%d %d)\n", min_idx, min);
	
	return 0;
}

