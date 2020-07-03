#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "our_lib.h"

int strsep_test(void) {
	char *t_str = "ab#cd,e,,f|g,,h"; /* delimiter == ',' || '#' || '|' */
	char *delim = ",#|";
	char *t_copy, *p, *t;
	
	t_copy = our_strdup(t_str);
	if (!t_copy)
		goto error;
	
	t = t_copy;
	for (p = strsep(&t, delim); p; p = strsep(&t, delim))
		printf("strsep %s\n", p);
	
	(void)our_strcpy(t_copy, t_str);
	
	t = t_copy;
	for (p = our_strsep(&t, delim); p; p = our_strsep(&t, delim))
		printf("our_strsep %s\n", p);
	
	free(t_copy);
	return 0;
error:
	return 1;
}

int main(void) {
	char *s = "1234asdfg";
	size_t len;
	int j;
	
	len = strspn(s, "0123456789abcdef");
	printf("len %lu\n", len);
	for (j = 0; j < len; j++)
		printf("%c\n", *(s + j));
	
	len = our_strspn_bad(s, "0123456789abcdef");
	printf("len %lu\n", len);
	for (j = 0; j < len; j++)
		printf("%c\n", *(s + j));
	
	len = our_strspn(s, "0123456789abcdef");
	printf("len %lu\n", len);
	for (j = 0; j < len; j++)
		printf("%c\n", *(s + j));

	len = strcspn(s, "abcdefgh");
	printf("len %lu\n", len);
	for (j = 0; j < len; j++)
		printf("%c\n", *(s + j));

	len = our_strcspn(s, "abcdefgh");
	printf("len %lu\n", len);
	for (j = 0; j < len; j++)
		printf("%c\n", *(s + j));
	
	(void)strsep_test();
	
	return 0;
}

