#include "logger.h"

/*
 * only implement logging functions and file content if logging is enabled,
 * otherwise let this file be empty
 */
#if LOG_LEVEL != LOG_LEVEL_NONE


#include <stdarg.h>
#include <string.h>
#include <stdio.h>

#define LOG_COLOR_ERROR   "\x1b[31m"
#define LOG_COLOR_WARNING "\x1b[33m"

#define LOG_COLOR_END "\x1b[0m"

void simple_logger( const char* level, const char* location, int line, const char* fmt, ... )
{
#if ENABLE_LOG_COLORS
	if ( strncmp( level, LOG_LEVEL_WARNING_TXT, strlen( LOG_LEVEL_WARNING_TXT ) ) == 0 )
	{
		printf( LOG_COLOR_WARNING );
	}
	else if ( strncmp( level, LOG_LEVEL_ERROR_TXT, strlen( LOG_LEVEL_ERROR_TXT ) ) == 0 )
	{
		printf( LOG_COLOR_ERROR );
	}
#endif

	printf("[%s] %s:%d  ", level, location, line);

	va_list arg_list;
	va_start( arg_list, fmt );
	vprintf(fmt, arg_list);

#if ENABLE_LOG_COLORS
	printf( LOG_COLOR_END );
#endif

	va_end(arg_list);
}

#endif // #if LOG_LEVEL != LOG_LEVEL_NONE%
