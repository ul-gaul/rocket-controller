#ifndef __DATA_TRANSMISSION__H_
#define __DATA_TRANSMISSION__H_


#include <stdio.h>
#include <pthread.h>

#include "utils.h"


extern pthread_mutex_t antenna_tx_lock;


/*
 * Continuously transmit data to ground station
 */
void transmit_data(void);

#endif /* __DATA_TRANSMISSION__H_ */
