#include <stdbool.h>
#include <string.h>

struct result {
	bool success;
	char msg[255];
};

struct result create_result_error(int errno_val);
struct result create_result_success();
