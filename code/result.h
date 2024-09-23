#ifndef RESULT_H
#define RESULT_H

#include <stdbool.h>
#include <string.h>

struct result {
	bool success;
	char msg[255];
};

struct result create_result_error(int errno_val);
struct result create_result_fmt(bool success, const char *fmt, ...);
struct result create_result_success();

#endif // RESULT_H
