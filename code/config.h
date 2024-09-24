#ifndef CONFIG_H
#define CONFIG_H

#include <stdint.h>

#include "result.h"

struct result config_init(const char *filepath);
void          config_print();

const char *config_gets(const char *key);
int         config_geti(const char *key);

#endif /* CONFIG_H */
