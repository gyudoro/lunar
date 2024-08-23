#ifndef CORE_LOG_H
#define CORE_LOG_H

#include "common/bool.h"

typedef enum LogLevel {
    /* log levels */
    LOG_TRACE,
    LOG_DEBUG,
    LOG_WARN,
    LOG_ERROR,
    LOG_FATAL,

    /* external error sources */
    LOG_OS,
} LogLevel;

/* outputs to stderr -- use freopen(..., stderr) to redirect this
   output */

void logMessage(LogLevel level, const char *fmt, ...);
void logAssertRaw(LogLevel level, bool condition, const char *msg);
void logSignals(void);

#define logAssert(LEVEL, COND) logAssertRaw(LEVEL, COND, #COND)

#endif /* CORE_LOG_H */

