#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

#include "logger.h"

static FILE *log_fp;
double start_time_msecs;

static LogLevel_t base_log_level = LOG_LEVEL_ERROR;

int logger_init(LogLevel_t log_level_base, const char *log_path)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	start_time_msecs = (tv.tv_sec*1000) + tv.tv_usec/1000;

	log_fp = fopen(log_path, "a");
	if (log_fp == NULL) {
		fprintf(stderr, "Failed to open %s for writing\n", log_path);
		return -1;
	} else {
		fprintf(stdout, "Successfully opened %s for writing\n", log_path);
	}

	base_log_level = log_level_base;
	return 0;
}

int logger_log(LogLevel_t log_level_msg, const char *format, ...)
{
	char print_buffer[1024];
	struct timeval tv;
	gettimeofday(&tv, NULL);
	double elapsed_time_msecs = (tv.tv_sec*1000) + (tv.tv_usec/1000) - start_time_msecs;

	sprintf(print_buffer, "[%.3f] ", elapsed_time_msecs);

	va_list args;
	va_start(args, format);
	vsprintf(print_buffer + strlen(print_buffer), format, args);
	va_end(args);

	if (log_level_msg >= base_log_level) {
		fprintf(log_fp, "%s\n", print_buffer);
		fflush(log_fp);
	}
	return 0;
}

int log_complete()
{
	if (log_fp == NULL) {
		return -1;
	}

	fclose(log_fp);
	return 0;
}
