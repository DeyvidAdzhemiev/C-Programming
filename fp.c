#include <stdio.h>
#include <stdlib.h>

int blah(int);
int gruh(int);

int main(void) {
	int (*t)(int);
	int (*tt[])(int) = { blah, gruh, NULL };
	int j;
	
	printf("%p\n", main);
	printf("%p %d\n", blah, blah(2));
	printf("%p %d\n", gruh, gruh(2));
	
	t = blah;
	printf("%p %d\n", t, t(2));
	
	t = gruh;
	printf("%p %d\n", t, t(2));
	
	for (j = 0; tt[j]; j++)
		printf("array of f' pointers %d %p %d\n", j, tt[j], (tt[j])(j));
	
	return 0;
}

int blah(int a) {
	printf("blah %d\n", a);
	
	return a + 1;
}

int gruh(int a) {
	printf("gruh %d\n", a);
	
	return a + 2;
}

