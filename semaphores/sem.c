#include <semaphore.h>

int main(void) {
	sem_t s;
	
	sem_init(&s, 0, 3u);
	sem_wait(&s); /* 2 */
	sem_wait(&s); /* 1 */
	sem_wait(&s); /* 0 */
	sem_wait(&s); /* LOCK */
	
	return 0;
}
