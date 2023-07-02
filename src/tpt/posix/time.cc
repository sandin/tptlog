#include "tpt/time.h"

#include "tpt/platform.h"

#ifdef TPT_POSIX_TIME

#include <time.h>

namespace tpt {

// static
Time::TimeSpec Time::Now() {
  struct timespec now;
  clock_gettime(CLOCK_REALTIME, &now);
  return TimeSpec{.tv_sec = now.tv_sec,
                  .tv_nsec = static_cast<int32_t>(now.tv_nsec)};
}

}  // namespace tpt

#endif  // TPT_POSIX_TIME