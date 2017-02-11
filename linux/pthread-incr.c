/* gcc pthread-incr.c -pthread -o pthread-incr
 * ref: http://man7.org/tlpi/code/online/dist/threads/thread_incr.c.html */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include <assert.h>

static int glob = 0;

/* Loop 'arg' times incrementing 'glob' */
static void *threadFunc(void *arg)
{
	int loops = *((int *) arg);
	int loc, j;
	for (j = 0; j < loops; j++) {
		loc = glob;
		loc++;
		glob = loc;
	}
	return NULL;
}

int main(int argc, char *argv[])
{
	pthread_t t1, t2;
	int loops, s;

	loops = (argc > 1) ? atoi(argv[1]) : 10000000;

	s = pthread_create(&t1, NULL, threadFunc, &loops);
	assert(s == 0);

	s = pthread_create(&t2, NULL, threadFunc, &loops);
	assert(s == 0);

	s = pthread_join(t1, NULL);
	assert(s == 0);

	s = pthread_join(t2, NULL);
	assert(s == 0);

	printf("glob = %d\n", glob);
}
