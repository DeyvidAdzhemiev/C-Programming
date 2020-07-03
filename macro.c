#include <stdio.h>

#define FUN(A, B) \
	((A) * (B) + 1)

#define PRINT(N) do { \
	int j; \
	for (j = 0; j < (N); j++) \
		printf("%d\n", j); \
} while (0)

#define PRINT_(A, B) do { \
	int j; \
	for (j = 0; j < FUN(A, B); j++) { \
		printf("%d\n", j); \
	} \
} while (0)

int fun(int a, int b) {
	return a * b + 1;
}

int main(void) {
	int a = 5, b = 6, c;
	int j = 100;
	
	c = fun(a, b);
	printf("c fun %d\n", c);
	c = FUN(a, b);
	printf("c FUN %d\n", c);
	
	PRINT(c);
	
	printf("j %d\n", j);
	
	PRINT_(a, b);
		
	return 0;
}

