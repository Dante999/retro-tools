#include "config.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "util_strings.h"

#define MAX_CONFIG_ENTRIES 100
#define MAX_KEY_LEN        255
#define MAX_VALUE_LEN      255

struct keyvalue_map {
	size_t count;
	char   keys[MAX_CONFIG_ENTRIES][MAX_KEY_LEN];
	char   values[MAX_CONFIG_ENTRIES][MAX_VALUE_LEN];
};

static struct keyvalue_map g_config;

static void parse_line(char *line)
{
	char key[255];
	char value[255];

	char *delimiter = strchr(line, '=');

	if (delimiter == NULL) {
		return;
	}

	*delimiter = '\0';
	strncpy(key, line, sizeof(key));
	strncpy(value, delimiter + 1, sizeof(value));

	utils_strtrim(key);
	utils_strtrim(value);

	if (g_config.count < MAX_CONFIG_ENTRIES) {
		strncpy(g_config.keys[g_config.count], key, MAX_KEY_LEN);
		strncpy(g_config.values[g_config.count], value, MAX_VALUE_LEN);
		++g_config.count;
	}
}

struct result config_init(const char *filepath)
{
	FILE *cfg_file = fopen(filepath, "r");

	if (cfg_file == NULL) {
		return create_result_error(errno);
	}

	char buffer[255];

	while (fgets(buffer, sizeof(buffer), cfg_file)) {

		utils_strtrim(buffer);

		if (strlen(buffer) == 0) {
			continue;
		}

		if (buffer[0] == '#') {
			continue;
		}

		parse_line(buffer);
	}

	return create_result_success();
}

void config_print()
{
	printf("--- CONFIG ---\n");

	for (size_t i = 0; i < g_config.count; i++) {
		printf("'%s' = '%s'\n", g_config.keys[i], g_config.values[i]);
	}

	printf("--------------\n");
}

const char *config_gets(const char *key)
{
	for (size_t i = 0; i < g_config.count; ++i) {

		if (strncmp(g_config.keys[i], key, MAX_KEY_LEN) == 0) {
			return g_config.values[i];
		}
	}

	return NULL;
}

int config_geti(const char *key)
{
	for (size_t i = 0; i < g_config.count; ++i) {

		if (strncmp(g_config.keys[i], key, MAX_KEY_LEN) == 0) {
			return atoi(g_config.values[i]);
		}
	}

	return 0;
}
