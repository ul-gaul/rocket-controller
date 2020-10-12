#include "data_transmission.h"


void
transmit_data(void)
{
	pthread_mutex_lock(&antenna_tx_lock);
	LOG("sending packet\n");
	pthread_mutex_unlock(&antenna_tx_lock);
}


