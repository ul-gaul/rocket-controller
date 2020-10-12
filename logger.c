#include "logger.h"


void
log_data(void)
{
	static int i = 0;
	++i;
	LOG("i = %d\n", i);
}


