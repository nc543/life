/* gcc pthread-incr-mutex.c -pthread -o pthread-incr-mutex
 * ref: http://man7.org/tlpi/code/online/dist/threads/thread_incr_mutex.c.html */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include <assert.h>

static int glob = 0;
static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

/* Loop 'arg' times incrementing 'glob' */
static void *threadFunc(void *arg)
{
	int loops = *((int *) arg);
	int loc, j;
	for (j = 0; j < loops; j++) {
		int s;

		s = pthread_mutex_lock(&mtx);
		assert(s == 0);

		loc = glob;
		loc++;
		glob = loc;

		s = pthread_mutex_unlock(&mtx);
		assert(s == 0);
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
