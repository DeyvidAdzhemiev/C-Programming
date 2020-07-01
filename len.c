
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
	char *t, *tt;
	char ttt;
	
	tt = t = (char *)malloc(our_strlen(s) + 1ul);
	if (!t) return t;
	
/*
	for (; *s; s++) {
		*t = *s;
		t++;
	}
	*t = '\000';
*/
	
/*	
	while ((*t++ = *s++));
*/

/*
	while (1)
		if (!(*t++ = *s++)) break;
*/
	
	while (1) {
		ttt = *t = *s;
		t++;
		s++;
		if (!ttt) break;
	}
		
	return tt;
}

int main(void) {
	char *t = "blah", *s;
	char *blah;
	
	s = strdup(t);
	*s = 'Z';
	printf("%lu %lu\n", strlen(s), our_strlen(s));
	printf("%s\n", s);
	
	blah = our_strdup(s);
	printf("%lu %lu\n", strlen(blah), our_strlen(blah));
	printf("%s\n", blah);
	
	free(blah);
	free(s);
	
	return 0;
}

