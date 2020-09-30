#include <stdio.h>
#include <pthread.h>


extern pthread_mutex_t antenna_tx_lock;


/*
 * Continuously transmit data to ground station
 */
void
transmit_data(void);

