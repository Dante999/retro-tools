#ifndef LOGGER_H
#define LOGGER_H

// clang-format off

#define LOG_LEVEL_TRACE   1
#define LOG_LEVEL_DEBUG   2
#define LOG_LEVEL_INFO    3
#define LOG_LEVEL_WARNING 4
#define LOG_LEVEL_ERROR   5
#define LOG_LEVEL_NONE    6

#define LOG_LEVEL_TRACE_TXT   "Trace  "
#define LOG_LEVEL_DEBUG_TXT   "Debug  "
#define LOG_LEVEL_INFO_TXT    "Info   "
#define LOG_LEVEL_WARNING_TXT "Warning"
#define LOG_LEVEL_ERROR_TXT   "Error  "

#ifndef LOG_LEVEL
  #define LOG_LEVEL LOG_LEVEL_TRACE
#endif

#ifndef ENABLE_LOG_COLORS
  #define ENABLE_LOG_COLORS 1
#endif

#define MAX_LOG_MSG_LENGTH 255

// ---------------------------------------------------------------------------------------------------------------------

#include <stdarg.h>
#include <stddef.h>
#include <string.h>


#if LOG_LEVEL == LOG_LEVEL_NONE
  #define simple_logger( ... )
#else
  void simple_logger( const char* level, const char* location, int line, const char* fmt, ... );
#endif

/*
 * not very secure solution, but __FUNCTION__ is no ISO-C Precompiler definition and therefore not compilable with
 * -Wpedantic flag. __FILE__ itself contains the whole filepath, which could be pretty long, so this macro just returns
 * the filename and nothing else.
 */
#define LOG_LOCATION ( strrchr( __FILE__, '/' ) + 1 )

#if LOG_LEVEL > LOG_LEVEL_TRACE
  #define log_trace( ... )
#else
  #define log_trace( fmt, ... ) simple_logger( LOG_LEVEL_TRACE_TXT, LOG_LOCATION, __LINE__, fmt, ##__VA_ARGS__ )
#endif

#if LOG_LEVEL > LOG_LEVEL_DEBUG
  #define log_debug( ... )
#else
  #define log_debug( fmt, ... ) simple_logger( LOG_LEVEL_DEBUG_TXT, LOG_LOCATION, __LINE__, fmt, ##__VA_ARGS__ )
#endif

#if LOG_LEVEL > LOG_LEVEL_INFO
  #define log_info( ... )
#else
  #define log_info( fmt, ... ) simple_logger( LOG_LEVEL_INFO_TXT, LOG_LOCATION, __LINE__, fmt, ##__VA_ARGS__ )
#endif

#if LOG_LEVEL > LOG_LEVEL_WARNING
  #define log_warning( ... )
#else
  #define log_warning( fmt, ... ) simple_logger( LOG_LEVEL_WARNING_TXT, LOG_LOCATION, __LINE__, fmt, ##__VA_ARGS__ )
#endif

#if LOG_LEVEL > LOG_LEVEL_ERROR
  #define log_error( ... )
#else
  #define log_error( fmt, ... ) simple_logger( LOG_LEVEL_ERROR_TXT, LOG_LOCATION, __LINE__, fmt, ##__VA_ARGS__ )
#endif

// clang-format on

#endif
