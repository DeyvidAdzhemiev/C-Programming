#ifndef _OUR_LIB_
#define _OUR_LIB_

#include <stdlib.h>

extern void *our_memset(void *s, int c, size_t n);
extern void *our_memcpy(void *dst, void *src, size_t n);
extern size_t our_strlen(char *t);
extern char *our_strdup(char *s);
extern size_t our_strspn_bad(char *s, char *accept);
extern size_t our_strspn(char *s, char *accept);
extern size_t our_strcspn(char *s, char *reject);
extern char *our_strsep(char **str, char *delim);
extern char *our_strcpy(char *dest, char *src);
extern char *our_strchr(char *s, int c);
extern char *our_strchr_while0(char *s, int c);
extern char *our_strchr_while1(char *s, int c);

#endif

