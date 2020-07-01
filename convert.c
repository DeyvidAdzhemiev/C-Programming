#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

uint32_t convert32(uint32_t);
uint64_t convert64(uint64_t);

int main(void) {
	uint64_t x;
	
	printf("%x %x\n", 0x12345678u, convert32(0x12345678u));
	x = convert64(0x0123456789abcdeflu);
	printf("%lx %lx\n", 0x0123456789abcdeflu, x);
	printf("%p %p %p %p\n", main, &main, convert32, convert64);
	return 0;
}

uint32_t convert32(uint32_t t) {
	return (t << 24) | ((t << 8) & 0x00ff0000u) | ((t >> 8) & 0x0000ff00u) | (t >> 24);
}

uint64_t convert64(uint64_t t) {
	return
			((t & 0xff00000000000000u) >> 56) |
			((t & 0x00ff000000000000u) >> 40) |
			((t & 0x0000ff0000000000u) >> 24) |
			((t & 0x000000ff00000000u) >> 8) |
			((t & 0x00000000ff000000u) << 8) |
			((t & 0x0000000000ff0000u) << 24) |
			((t & 0x000000000000ff00u) << 40) |
			((t & 0x00000000000000ffu) << 56);
}

