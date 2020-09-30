/*
 * Rocket controller
 */


#include <stdio.h>
#include <pthread.h>


pthread_t logger_thread;


void *
logger(void * args)
{
	for (int i = 0; i < 10; ++i) {
		printf("i = %d\n", i);
	}

	return NULL;
}


int
main(int argc, char** argv)
{
	/* start all threads */
	printf("starting threads\n");

	if (pthread_create(&logger_thread, NULL, logger, NULL)) {
		printf("error creating thread\n");
		return -1;
	}

	/* joining threads */
	if (pthread_join(logger_thread, NULL)) {
		printf("error joining thread\n");
		return -2;
	}

	printf("all threads joined\n");


	return 0;
}

