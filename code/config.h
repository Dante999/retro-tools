#ifndef CONFIG_H
#define CONFIG_H

#include <stdint.h>

struct config {
	uint8_t terminal_print_delay_msec;
};



void config_init();
const struct config *config_get();


#endif /* CONFIG_H */
