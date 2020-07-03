#include <stdio.h>

int local_static(void) {
	static int test = 0;
	return test++;
}

int main(void) {
	int j, k;
	int test;
	
	for (j = 0; j < 4; j++) {
		test = local_static();
		for (k = 0; k < 4; k++) {
			int test = k;
			printf("\t%d\n", test);
		}
		printf("%d\n", test);
	}
	
	return 0;
}

