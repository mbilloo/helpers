#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "logger.h"

const char* log_path = "/run/test.log";

static void usage(void)
{
	logger_log(LOG_LEVEL_ERROR, "./app <arg 1>");
}

int main(int argc, char *argv[])
{
	if (logger_init(LOG_LEVEL_INFORMATIVE, log_path) < 0) {
		fprintf(stderr, "Failed to configure logger\n");
		return -1;
	}

	if (argc < 2) {
		usage();
		return -2;
	}

	logger_log(LOG_LEVEL_INFORMATIVE, "time test 1");
	sleep(1);
	logger_log(LOG_LEVEL_INFORMATIVE, "time test 2");

	return 0;
}
