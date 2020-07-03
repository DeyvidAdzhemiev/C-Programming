#include <stdio.h>
#include <stdlib.h>

int test0(int a) {
	return a + 1;
}

int test1(int a) {
	return a + 2;
}

typedef int (*function_p)(int); /* int (*)(int) */

#define NUM_F 2

int main(void) {
	int (*fp0[])(int) = { test0, test1, NULL };
	function_p fp1[] = { test0, test1, NULL };
	function_p fp2[] = { test0, test1 };
	int (*fp3[])(int) = { test0, test1 };
	function_p *fp4;
	int j;
	size_t k, len;
	
	for (j = 0; fp0[j]; j++)
		printf("fp0 %d %d\n", j, (fp0[j])(j));
	
	for (j = 0; fp1[j]; j++)
		printf("fp1 %d %d\n", j, (fp1[j])(j));
	
	len = sizeof (fp2) / sizeof (fp2[0]);
	for (k = 0lu; k < len; k++)
		printf("fp2 %lu %d\n", k, (fp2[k])((int)k));
	
	len = sizeof (fp3) / sizeof (fp3[0]);
	for (k = 0lu; k < len; k++)
		printf("fp3 %lu %d\n", k, (fp3[k])((int)k));
	
	fp4 = (function_p *)malloc(NUM_F * sizeof (function_p));
	if (!fp4) {
		printf("out of memory\n");
		goto err;
	}
	
	fp4[0] = test0;
	fp4[1] = test1;
	
	for (j = 0; j < NUM_F; j++)
		printf("fp4 %d %d\n", j, (fp4[j])(j));
	
	free(fp4);
	
	return 0;
	
err:
	return 1;
}

