#include <stdio.h>

int main(void) {
	int j;
	
	for (j = 0; j < 15; j++) {
		printf("%d\n", j);
		switch (j) {
		case 0:
			printf("\tgot 0\n");
			break;
		case 1:
			printf("\tgot 1\n");
		case 2:
		case 3:
			printf("\tor 2 or 3\n");
			break;
		case 4:
		case 5:
		case 6:
			printf("\tgot 4, 5 or 6\n");
			break;
		case 7:
			printf("\tgot 7\n");
		default:
			printf("\tdefault - got %d\n", j);
		}
	}
	
	return 0;
}

