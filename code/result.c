#include "result.h"
#include "errno.h"

struct result create_result_error(int errno_val)
{
	struct result result;

	result.success = false;
	strncpy(result.msg, strerror(errno), sizeof(result.msg));

	return result;
}

struct result create_result_success()
{
	struct result result = {true, ""};
	return result;
}