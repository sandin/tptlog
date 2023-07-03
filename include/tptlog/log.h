#ifndef TPTLOG_LOG_H
#define TPTLOG_LOG_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum tptlog_LogPriority {
  TPTLOG_LOG_NONE,
  TPTLOG_LOG_FATAL,
  TPTLOG_LOG_ERROR,
  TPTLOG_LOG_WARNING,
  TPTLOG_LOG_INFO,
  TPTLOG_LOG_DEBUG,
  TPTLOG_LOG_VERBOSE
} tptlog_LogPriority

void tptlog_print_utf8(int priority, const char* tag, const char* str);

#ifdef __cplusplus
}
#endif

#endif  // TPTLOG_LOG_H