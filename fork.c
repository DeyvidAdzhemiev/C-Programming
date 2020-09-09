#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(void) {
	pid_t t;
	int j;
	
	printf("pid = %d\n", (int)getpid());
	
	t = fork();
	
	if (t < 0) perror("fork");
	else if (t) { /* parent */
		printf("child pid = %d\n", (int)t);
		for (j = 0; j < 102400; j++)
			printf("P");
	} else { /* child */
		printf("parent pid = %d\n", (int)getppid());
		for (j = 0; j < 102400; j++)
			printf("C");
	}
	
	return 0;
}

