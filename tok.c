#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int strchr_test(void) {
	char *s = "abcdefgh";
	
	printf("%p\n", strchr(s, 'e'));
	printf("%p\n", our_strchr(s, 'e'));
	printf("%p\n", strchr(s, 'z'));
	printf("%p\n", our_strchr(s, 'z'));
	printf("%p\n", strchr(s, 'e'));
	printf("%p\n", our_strchr_while0(s, 'e'));
	printf("%p\n", strchr(s, 'z'));
	printf("%p\n", our_strchr_while0(s, 'z'));
	printf("%p\n", strchr(s, 'e'));
	printf("%p\n", our_strchr_while1(s, 'e'));
	printf("%p\n", strchr(s, 'z'));
	printf("%p\n", our_strchr_while1(s, 'z'));

	return 0;
}

int strtok_test(void) {
	char *t = "ab#cd,e,,f|g,,h"; /* delimiter == ',' || '#' || '|' */
	char *delim = ",#|";
	char *t_copy, *p;
	
	t_copy = strdup(t);
	if (!t_copy) goto error;
	
	for (p = strtok(t_copy, delim); p; p = strtok(NULL, delim))
		printf("strtok %s\n", p);
	
	free(t_copy);
	return 0;
error:
	return 1;
}

int strsep_test(void) {
	char *t_str = "ab#cd,e,,f|g,,h"; /* delimiter == ',' || '#' || '|' */
	char *delim = ",#|";
	char *t_copy, *p, *t;
	
	t_copy = strdup(t_str);
	if (!t_copy) goto error;
	
	t = t_copy;
	for (p = strsep(&t, delim); p; p = strsep(&t, delim))
		printf("strsep %s\n", p);
	
	free(t_copy);
	return 0;
error:
	return 1;
}

int main(void) {
	(void)strchr_test();
	(void)strtok_test();
	(void)strsep_test();
	
	return 0;
}

