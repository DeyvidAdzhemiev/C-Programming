#include <stdio.h>
#include <stdlib.h>

int main(void) {
	FILE *stream;
	int c;

	stream = fopen("file", "r+");
	if (!stream) {
		perror("fopen");
		goto err;
	}

	(void)fseek(stream, 0l, SEEK_END);

	printf("ftell-2 %ld\n", ftell(stream));

	fprintf(stream, "%s", "My name is Deyvid\n");

	printf("ftell-1 %ld\n", ftell(stream));

	(void)fseek(stream, 0l, SEEK_SET); /* rewind(stream); */

	printf("ftell0 %ld\n", ftell(stream));

	while ((c = fgetc(stream)) != EOF)
		(void)fputc(c, stdout);

	printf("ftell1 %ld\n", ftell(stream));

	(void)fseek(stream, 0l, SEEK_SET);

	printf("ftell2 %ld\n", ftell(stream));

	while ((c = fgetc(stream)) != EOF)
		(void)fputc(c, stdout);

	printf("ftell3 %ld\n", ftell(stream));

	(void)fseek(stream, -5l, SEEK_CUR);

	printf("ftell4 %ld\n", ftell(stream));

	while ((c = fgetc(stream)) != EOF)
		(void)fputc(c, stdout);

	printf("ftell5 %ld\n", ftell(stream));

	rewind(stream); /* (void)fseek(stream, 0l, SEEK_SET); */

	printf("ftell6 %ld\n", ftell(stream));

	while ((c = fgetc(stream)) != EOF)
		(void)fputc(c, stdout);

	printf("ftell7 %ld\n", ftell(stream));

	fprintf(stream, "%s", "My name is Deyvid\n");

	printf("ftell8 %ld\n", ftell(stream));

	fclose(stream);

	return 0;

err:
	return 1;
}
