#include "tptlog/log.h"

#include <string>

#include "absl/strings/str_format.h"
#include "absl/time/clock.h"
#include "absl/time/time.h"
#include "tpt/thread.h"
#include "tptlog/output.h"

using tptlog::FileOutput;

static FileOutput* g_Output = nullptr;

void tptlog_init(tptlog_Config config) {
  g_Output = new FileOutput(config.filename, config.initial_buffer_size);
}

void tptlog_print(int priority, const char* msg) {
  // log format: <time> <tid> <msg>
  std::string formated = absl::StrFormat(
      "%s %d %s",
      absl::FormatTime("%Y-%m-%d %H:%M:%S", absl::Now(), absl::UTCTimeZone())
          .c_str(),
      tpt::Thread::GetCurrentThreadId(), msg);
  // assert(g_Output)
  g_Output->Serialize(formated);
}