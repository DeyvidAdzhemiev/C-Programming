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
	char *str = "Hello world!\n", *buf;
	int fd;
	
	fd = open("abrahadabra", O_RDWR);
	if (fd < 0) {
		perror("open");
		exit(EX_OSFILE);
	}
	
	buf = (char *)mmap(NULL, 4096ul, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0l);
	if (close(fd) < 0) {
		perror("close");
		exit(EX_OSFILE);
	}
	if (!buf) {
		perror("mmap");
		exit(EX_OSERR);	
	}
	
	(void)strcpy(buf, str);
	
	if (munmap(buf, 4096ul) < 0) {
		perror("munmap");
		exit(EX_OSERR);	
	}
	
	return 0;
}

