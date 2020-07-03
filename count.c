#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t count(char *str, char *word) {
	size_t number, len;
	char *t, *f;
#if 0
	for (
			len = strlen(word), t = str, number = 0lu; /* init */
			(f = strstr(t, word)); /* predicate */
			t = f + len, number++ /* update */
	);
#endif
	len = strlen(word);
	number = 0lu;
	t = str;
	while ((f = strstr(t, word))) {
		t = f + len;
		number++;
	}

	return number;
}

int main(void) {
	char *str = "blah blah blah blah";
	char *word = "blah";

	printf("%lu\n", count(str, word));

	return 0;
}
