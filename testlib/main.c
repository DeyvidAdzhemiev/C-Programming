#include <stdio.h>

int main(void) {
/*
	int main = 5;
	
	printf("%d\n", main);
*/
	int (*t)(void);
	
	t = main;
	printf("%p\n", main);
	printf("%p\n", t);
	
	return 0;
}

