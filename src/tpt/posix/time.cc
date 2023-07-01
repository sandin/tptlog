#include "tpt/time.h"

#include "tpt/platform.h"

#ifdef TPT_POSIX_TIME

#include <time.h>

namespace tpt {

tpt_time tpt_now() {
  struct timespec now;
  clock_gettime(CLOCK_REALTIME, &now);

  tpt_time time;
  time.tv_sec = now.tv_sec;
  time.tv_nsec = now.tv_nsec;
  return time;
}

}  // namespace tpt

#endif  // TPT_POSIX_TIME