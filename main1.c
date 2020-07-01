#include <stdio.h>

int main(int argc, char *argv[], char **envp) {
/*
	t ->
	envp ->
		[pointer in memory, pointing to]	->	"string"
		[pointer in memory, pointing to]	->	"string"
		[pointer in memory, pointing to]	->	"string"
		...
		[pointer in memory, pointing to]	->	"string"
		[pointer in memory, pointing to]	->	NULL
*/
	int j;
	char **t;
	
	for (j = 0; j < argc; j++)
		printf("%d %s\n", j, argv[j]);
	
	printf("--- ENV 0 ---\n");
	for (t = envp; *t; t++)
		printf("%s\n", *t);
	printf("--- ENV 0 ---\n");
	
	printf("--- ENV 1 ---\n");
	for (j = 0; envp[j]; j++)
		printf("%s\n", envp[j]);
	printf("--- ENV 1 ---\n");
	
	return 0;
}

