#include <stdio.h>
#include <stdlib.h>

int main(void) {
	char *line = NULL;
	size_t len = 0u;
	ssize_t read;
	
/*	
	while ((read = getline(&line, &len, stdin)) >= 0) {
		printf("got line \"%s\"\n", line);
	}
*/
	
	for (
			read = getline(&line, &len, stdin);
			read >= 0;
			read = getline(&line, &len, stdin)
	) {
		printf("got line \"%s\"\n", line);
	}
	
	free(line);
	
	return 0;
}

