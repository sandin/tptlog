#include "tpt/time.h"

#include "tpt/platform.h"

#ifdef TPT_WINDOWS_TIME

#include <sys/timeb.h>

namespace tpt {

// static
Time::TimeSpec Time::Now() {
  struct _timeb now;
  _ftime_s(&now);
  return TimeSpec{.tv_sec = static_cast<int64_t>(now.time),
                  .tv_nsec = now..millitm * 1000000};
}

}  // namespace tpt

#endif  // TPT_WINDOWS_TIME