#ifndef TPT_TIME_H
#define TPT_TIME_H

#include <cstdint>

#include "tpt/platform.h"

namespace tpt {

typedef struct tpt_time {
  int64_t tv_sec;  // time_t
  int32_t tv_nsec;
} tpt_time;

/**
 * @brief get current time
 *
 * @return tpt_time
 */
TPTAPI tpt_time tpt_now();

}  // namespace tpt

#endif  // TPT_TIME_H