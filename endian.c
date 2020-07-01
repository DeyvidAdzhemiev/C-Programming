#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <sys/types.h>

int main(void) {
	uint64_t a = (int64_t)((int32_t)0x82345678);
	unsigned char *p = (unsigned char *)&a;
	size_t j;
	
	printf("%lld\n", a);
	printf("%llu\n", a);
	printf("%llx\n", a);
	
	for (j = 0u; j < sizeof (a); j++)
		printf("%p %x %x %x\n", p + j, (unsigned)(*(p + j)), (unsigned)p[j], (unsigned)j[p]);
	
	return 0;
}

