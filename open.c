#include <stdio.h>
#include <stdlib.h>

int main(void) {
	FILE *stream;
	
	stream = fopen("file", "w");
	if (!stream) {
		fprintf(stderr, "cannot open\n");
		fflush(stderr);
		goto err;
	}
	
	fprintf(stream, "Hello world!\n");
	
	fclose(stream);
	
	stream = fopen("file", "a");
	if (!stream) {
		fprintf(stderr, "cannot open\n");
		fflush(stderr);
		goto err;
	}
	
	fprintf(stream, "Hello world!\n");
	
	fclose(stream);
	
	return 0;

err:
	return 1;
}

