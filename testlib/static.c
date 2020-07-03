#include <stdio.h>

/*
static int sum1 = 0;
*/

int sum(int N) {
	int sum, j;
	
	for (sum = 0, j = 0; j < N; j++) {
		static int sum1 = 0xdeadbeef;
		printf("\tsum11 %d\n", sum1);
		sum1 += j;
		printf("\tsum12 %d\n", sum1);
		sum += j;
	}
	
/*
	printf("\tsum13 %d\n", sum1); <- ERROR
*/
/*
	printf("\tsum13 %d\n", sum1); <- ERROR
*/
	
	return sum;
}

int main(void) {
	printf("%d\n", sum(10));
	printf("%d\n", sum(10));
	printf("%d\n", sum(10));
	printf("%d\n", sum(10));
/*
	printf("\tsum14 %d\n", sum1); <- ERROR
*/
	
	return 0;
}

