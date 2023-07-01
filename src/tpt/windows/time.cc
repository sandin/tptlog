#include "tpt/time.h"

#include "tpt/platform.h"

#ifdef TPT_WINDOWS_TIME

#include <sys/timeb.h>

namespace tpt {

tpt_time tpt_now() {
  struct _timeb now;
  _ftime_s(&now);

  tpt_time time;
  time.tv_sec = (int64_t)now_tb.time;
  time.tv_nsec = now_tb.millitm * 1000000;
  return time;
}

}  // namespace tpt

#endif  // TPT_WINDOWS_TIME