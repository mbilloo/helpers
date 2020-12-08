#pragma once

#include <stdarg.h>

typedef enum
{
	LOG_LEVEL_DEBUG,
	LOG_LEVEL_INFORMATIVE,
	LOG_LEVEL_WARNING,
	LOG_LEVEL_ERROR
} LogLevel_t;

int logger_init(LogLevel_t log_level_base, const char *log_path);
int logger_log(LogLevel_t log_level_msg, const char *format, ...);
int log_complete(void);
