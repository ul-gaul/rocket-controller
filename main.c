/*
 * Rocket controller
 */


#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#include "data-transmission/data_transmission.h"
#include "data-transmission/crc.h"
#include "motor/motor_acquisition.h"
#include "motor/motor_control.h"
#include "rocket-packet/rocket_packet.h"
#include "rocket-packet/mcu_command.h"
#include "logger.h"


#define DATATX_PERIOD  500000
#define DATALOG_PERIOD 100000


/* thread handles */
pthread_t logger_h;
pthread_t data_sender_h;


/* antenna transmission channel lock */
pthread_mutex_t antenna_tx_lock;


/*
 * Thread target function to log data and events continuously
 */
void *
log_cont(void* args)
{
	/* allow thread to be cancelled from main asynchronously */
	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);

	while (1) {
		log_data();
		usleep(100000);
	}

	return NULL;
}



/*
 * Thread target function to transmit data to ground station continuously
 */
void *
transmit_cont(void* args)
{
	/* allow thread to be cancelled from main asynchronously */
	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);

	while (1) {
		transmit_data();
		usleep(DATATX_PERIOD);
	}
	return NULL;
}


int
main(int argc, char** argv)
{
	pthread_mutex_init(&antenna_tx_lock, NULL);

	/* start all threads */
	printf("starting threads\n");

	if (pthread_create(&logger_h, NULL, log_cont, NULL)) {
		printf("error creating logger thread\n");
		return -1;
	}

	if (pthread_create(&data_sender_h, NULL, transmit_cont, NULL)) {
		printf("error creating data sender thread\n");
		return -1;
	}

	/* join threads */
	if (pthread_join(logger_h, NULL)) {
		printf("error joining logger thread\n");
		return -2;
	}

	if (pthread_join(data_sender_h, NULL)) {
		printf("error joining data sender thread\n");
		return -2;
	}

	printf("all threads joined\n");

	pthread_mutex_destroy(&antenna_tx_lock);

	/* TODO: remove this */
	/* call functions to test that make will link them */
	crc_t my_crc;
	my_crc = crc_init();

	read_motor_data();

	int test;
	test = actuators_init();

	test = mc_valid_function(1);

	return 0;
}

