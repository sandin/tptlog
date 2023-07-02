#ifndef TPT_TIME_H
#define TPT_TIME_H

#include <cstdint>

#include "tpt/platform.h"

namespace tpt {

class Time {
 public:
  struct TimeSpec {
    int64_t tv_sec;  // time_t
    int32_t tv_nsec;
  };

  /**
   * @brief get current time
   *
   * @return TimeSpec
   */
  static TimeSpec Now();

};  // class Time

}  // namespace tpt

#endif  // TPT_TIME_H