#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sysexits.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
	int fd;
	int *buf;
	pid_t pid;
	
	fd = open("/dev/zero", O_RDWR);
	if (fd < 0) {
		perror("open");
		exit(EX_OSFILE);
	}
	
	buf = (int *)mmap(NULL, 4096ul, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0l);
	if (close(fd) < 0) {
		perror("close");
		exit(EX_OSFILE);
	}
	if (!buf) {
		perror("mmap");
		exit(EX_OSERR);	
	}
	
	pid = fork();
	if (pid < 0) {
		perror("fork");
		exit(EX_OSERR);
	} else if (pid) { /* parent */
		while (1) {
			printf("%d\n", *buf);
		}
	} else { /* child */
		while (1) {
			(void)sleep(1u);
			(*buf)++;
		}
	}
	
	if (munmap(buf, 4096ul) < 0) {
		perror("munmap");
		exit(EX_OSERR);	
	}
	
	return 0;
}

