#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

#include "our_lib.h"

void *our_memset(void *s, int c, size_t n) {
/*
	size_t j;
	
	for (j = 0u; j < n; j++)
		((unsigned char *)s)[j] = (unsigned char)c;
*/
	uint32_t *t_s32 = (uint32_t *)s;
	uint8_t *t_s8;
	uint8_t c8 = (uint8_t)c; /* cccccccc */
	uint32_t c32 = c8; /* 000000000000000000000000cccccccc */
	size_t j, rem;
	
	c32 = (c32 << 24) | (c32 << 16) | (c32 << 8) | c32;
/*
	cccccccc000000000000000000000000 (c32 << 24) | 
	00000000cccccccc0000000000000000 (c32 << 16) |
	0000000000000000cccccccc00000000 (c32 << 8) |
	000000000000000000000000cccccccc c32
	cccccccccccccccccccccccccccccccc
*/
	rem = n & 3lu; /* 3lu == 000...011 binary; rem == 000...000 / 000...001 / 000...010 / 000...011 */
	n >>= 2; /* 00xxx...x binary (last 2 bits removed) */
	
	for (j = 0lu; j < n; j++)
		t_s32[j] = c32;
	
	if (rem) {
		t_s8 = (uint8_t *)(t_s32 + n); /* (uint8_t *)t_dst32 + n * sizeof (uint32_t) */
		for (j = 0lu; j < rem; j++)
			t_s8[j] = c8;
	}
	
	return s;
}

void *our_memcpy(void *dst, void *src, size_t n) {
/*
	unsigned char *t_dst = (unsigned char *)dst;
	unsigned char *t_src = (unsigned char *)src;
	size_t j;
	
	for (j = 0u; j < n; j++)
		t_dst[j] = t_src[j];
*/
	uint32_t *t_dst32 = (uint32_t *)dst;
	uint32_t *t_src32 = (uint32_t *)src;
	uint8_t *t_dst8;
	uint8_t *t_src8;
	size_t j, rem;
	
	rem = n & 3lu; /* 3lu == 000...011 binary; rem == 000...000 / 000...001 / 000...010 / 000...011 */
	n >>= 2; /* 00xxx...x binary (last 2 bits removed) */
	
	for (j = 0lu; j < n; j++)
		t_dst32[j] = t_src32[j];
	
	if (rem) {
		t_dst8 = (uint8_t *)(t_dst32 + n); /* (uint8_t *)t_dst32 + n * sizeof (uint32_t) */
		t_src8 = (uint8_t *)(t_src32 + n);
		for (j = 0lu; j < rem; j++)
			t_dst8[j] = t_src8[j];
	}
	
	return dst;
}

size_t our_strlen(char *t) {
	size_t len;
/*
	len = 0ul;
	while (*t++) len++;
*/
	for (len = 0ul; *t; t++) len++;
	
	return len;
}

char *our_strdup(char *s) {
	size_t len;
	char *t;
	
	if (!s) return NULL;
	
	len = our_strlen(s) + 1lu;
	
	t = (char *)malloc(len);
	if (!t) return NULL;
	
	return (char *)our_memcpy(t, s, len);
}

size_t our_strspn_bad(char *s, char *accept) {
	size_t len;
	char *t;
	int flag;
	
	for (len = 0u; s[len]; len++) {
		for (flag = 0, t = accept; *t; t++)
			if (s[len] == *t) {
				flag = 1;
				break;
			}
		if (!flag) break;
	}
	
	return len;
}

size_t our_strspn(char *s, char *accept) {
	char alphabet[256];
	size_t j;
	
	our_memset(alphabet, 0, sizeof (alphabet));
	for (j = 0u; accept[j]; j++)
		alphabet[/* !!! */ (unsigned)accept[j] /* !!! */] = 1; /* char is signed!!! */
	for (j = 0u; s[j]; j++)
		if (!alphabet[(unsigned)s[j]]) break;

	return j;
}

size_t our_strcspn(char *s, char *reject) {
	char alphabet[256];
	size_t j;
	
	our_memset(alphabet, 0, sizeof (alphabet));
	for (j = 0u; reject[j]; j++)
		alphabet[/* !!! */ (unsigned)reject[j] /* !!! */] = 1; /* char is signed!!! */
	for (j = 0u; s[j]; j++)
		if (alphabet[(unsigned)s[j]]) break;

	return j;
}

char *our_strsep(char **str, char *delim) {
	size_t span;
	char *t;
	
	if (!*str) return NULL;
	
	t = *str;
	if (!*t) {
		*str = NULL;
		return t;
	}
	
	span = our_strcspn(*str, delim);
	(*str) += span;
	
	if (!**str) *str = NULL;
	else {
		**str = '\0';
		(*str)++;
	}
	
	return t;
}

char *our_strcpy(char *dest, char *src) {
/*
	size_t j;
	
	for (j = 0u; ; j++)
		if (!(dest[j] = src[j])) break;
	
	return dest;
*/
/*
	char *t = dest;
	
	while ((*t++ = *src++));
	
	return dest;
*/
/*
	char *t = dest, c;
	
	do {
		c = (*t = *src);
		t++;
		src++;
	} while (c);
			
	return dest;
*/
	return (char *)our_memcpy(dest, src, our_strlen(src) + 1lu);
}

char *our_strchr(char *s, int c) {
/*
	for ( ; *s; s++)
		if (*s == c)
			return s;
	
	return NULL;
*/
label0:
	if (!(*s)) goto out;
	if (*s == c) return s;
	else {
		s++;
		goto label0;
	}
out:
	return NULL;
}

char *our_strchr_while0(char *s, int c) {
/*
	while (*s) {
		if (*s == c)
			return s;
		s++;
	}
	
	return NULL;
*/
label0:
	if (*s) {
		if (*s == c) return s;
		s++;
		goto label0;
	}
	return NULL;
}

char *our_strchr_while1(char *s, int c) {
/*
	while (*s && (*s != c)) s++;
	return *s ? s : NULL;
*/
label0:
	if (*s && (*s != c)) {
		s++;
		goto label0;
	}
	if (*s) return s;
	else return NULL;
}

