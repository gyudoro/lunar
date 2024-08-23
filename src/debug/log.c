#include "debug/log.h"

#include <errno.h>
#include <time.h>
#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common/bool.h"

static void signalHandle(int type)
{
	switch (type) {
		case SIGABRT:
			logMessage(LOG_FATAL, "Encountered SIGABRT");
			break;

		case SIGFPE:
			logMessage(LOG_FATAL, "Encountered SIGFPE");
			break;

		case SIGILL:
			logMessage(LOG_FATAL, "Encountered SIGILL");
			break;

		case SIGINT:
			logMessage(LOG_FATAL, "Encountered SIGINT");
			break;

		case SIGSEGV:
			logMessage(LOG_FATAL, "Encountered SIGSEGV");
			break;

		case SIGTERM:
			logMessage(LOG_FATAL, "Encountered SIGTERM");
			break;

		default:
			logMessage(LOG_FATAL, "Encountered signal %d",
			           type);
	}
}


void logMessage(LogLevel level, const char *fmt, ...)
{
	va_list va;

	time_t timer;
	struct tm *info;
	char buf[29];

	int code;
	
	va_start(va, fmt);

	/* we save this in case any library function we call in this
	   routine fails, even if there is no actual OS error to begin
	   with */
	code = errno;

	timer = time(NULL);
	info = localtime(&timer);

	strftime(buf, 29, "[%Y-%m-%d %H:%M:%S] ", info);
	fputs(buf, stderr);
	
	switch (level) {
		case LOG_TRACE:
			fputs("TRACE: ", stderr);
			break;

		case LOG_DEBUG:
			fputs("DEBUG: ", stderr);
			break;

		case LOG_WARN:
			fputs("WARN: ", stderr);
			break;

		case LOG_ERROR:
			fputs("ERROR: ", stderr);
			break;

		default:
			fputs("FATAL ERROR: ", stderr);
			break;
	}

	vfprintf(stderr, fmt, va);
	va_end(va);

	if (level == LOG_OS) {
		/* because we already printed the message, we can reuse
		   fmt! */

		fmt = strerror(code);

		if (fmt != NULL)
			fprintf(stderr, ": %s (code %d)",
			        strerror(code), code);
	}

	fputc('\n', stderr);
	
	if (level >= LOG_FATAL)
		exit(1);
}

void logAssertRaw(LogLevel level, bool condition, const char *msg)
{
	if (!condition)
		logMessage(level, "Assertion failed: %s", msg);
}

void logSignals(void)
{
	signal(SIGABRT, signalHandle);
	signal(SIGFPE, signalHandle);
	signal(SIGILL, signalHandle);
	signal(SIGINT, signalHandle);
	signal(SIGSEGV, signalHandle);
	signal(SIGTERM, signalHandle);
}
