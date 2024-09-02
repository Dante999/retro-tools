#include "config.h"


static struct config g_config;


const struct config *config_get()
{
	return &g_config;
}

void config_init()
{
	g_config.terminal_print_delay_msec = 10;
}
