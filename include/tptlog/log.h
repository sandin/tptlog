#ifndef TPTLOG_LOG_H
#define TPTLOG_LOG_H

#include <cstddef>

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
} tptlog_LogPriority;

typedef struct tptlog_Config {
  const char* filename;
  size_t initial_buffer_size;
} tptlog_Config;

/**
 * @brief initiate log module
 *
 * @param config
 */
void tptlog_init(tptlog_Config config);

/**
 * @brief print a log
 *
 * @param priority priority
 * @param msg log
 */
void tptlog_print(int priority, const char* msg);

#ifdef __cplusplus
}
#endif

#endif  // TPTLOG_LOG_H