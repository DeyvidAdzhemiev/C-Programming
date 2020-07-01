#include <stdio.h>

#define MAX 10

int main(void) {
	int j;
#ifdef ODD
	int odd_sum = 0;
#define SUM odd_sum
#elif defined(EVEN)
	int even_sum = 0;
#define SUM even_sum
#else
#error neither EVEN nor ODD
#endif	
	
	for (
			j = 0;
			j < MAX;
			j++
	)
#if defined(ODD)
		if (j & 1) odd_sum += j;
#elif defined(EVEN)
		if (!(j & 1)) even_sum += j;
#endif
	
	printf("%d\n", SUM);
	
	return 0;
}

