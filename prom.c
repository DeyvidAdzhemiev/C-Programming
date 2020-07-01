#include <stdio.h>

int main(void) {
	int a;
	long b;
	
	a = 0xffffffff; /* -1 32bit int */
	printf("%d %x\n", a, a);
	b = a; /* automatic type promotion / automatic cast */
	printf("%ld %lx\n", b, b);
	
	a = 0x7fffffff;
	printf("%d %x\n", a, a);
	b = (long)a; /* 0x000000007fffffff 64bit long */ /* manual cast */
	printf("%ld %lx\n", b, b);
	
	b = 0x1l - 02 + 0x3 - 4;
	printf("%ld %lx\n", b, b);
	b = ~b + 1l;
	printf("%ld %lx\n", b, b);
	b = (b ^ -1l) + 1l;
	printf("%ld %lx\n", b, b);
	b = ~b + 1l;
	printf("%ld %lx\n", b, b);
	b = -b;
	printf("%ld %lx\n", b, b);
	
	return 0;
}

