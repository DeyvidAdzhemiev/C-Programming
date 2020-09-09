#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>

int main(void) {
	int fd[2];
	pid_t pid;
	ssize_t n;
	char a;
	
	if (pipe(fd) < 0) {
		perror("pipe");
		exit(EX_OSERR);
	}
	
	pid = fork();
	if (pid < 0) {
		perror("fork");
		close(fd[0]);
		close(fd[1]);
		exit(EX_OSERR);
	} else if (pid) { /* parent */
		close(fd[1]);
		while (1) {
			n = read(fd[0], &a, sizeof (a));
			if (n < 0) break;
			else if (n) (void)write(1, &a, n);
			else perror("read");
		}
	} else { /* child */
		close(fd[0]);
		a = 'A';
		while (1) {
			if (write(fd[1], &a, sizeof (a)) < 0) break;
			else sleep(1u);
		}
	}
	
	return 0;
}

