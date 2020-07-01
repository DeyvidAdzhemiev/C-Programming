#include <stdio.h>

int main(void) {
	int j = 0;
	
label:
	if (j < 10) {
		printf("%d\n", j);
		j++;
		goto label;
	}
	
/*
	j = 0;
	while (j < 10) {
		printf("%d\n", j);
		j++;
	}
*/
/*
	for (j = 0; j < 10; j++)
		printf("%d\n", j);		
*/
	
	return 0;
}

