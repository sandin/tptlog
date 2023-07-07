#include "tptlog/output.h"

namespace tptlog {

using std::fstream;
using std::string;
using tpt::RingBuffer;
using tpt::Thread;

// [write thread]
bool FileOutput::Serialize(const string& content) {
  if (!thread_) {
    fstream_ = new std::fstream(filename_.c_str(), std::fstream::binary | std::fstream::out);
    thread_ = new Thread("tptlog_worker", std::bind(&FileOutput::Run, this, std::placeholders::_1), fstream_);
    thread_running_ = true;
    if (!thread_->Start()) {
      // TODO: log error: can not start the worker thread for tptlog
      thread_running_ = false;
      return false;
    }
  }

  uint8_t* d = reinterpret_cast<uint8_t*>(const_cast<char*>(content.data()));
  return buffer_.Write(d, content.size());
}

// [read thread]
void* FileOutput::Run(Thread::Arg arg) {
  std::fstream* f = reinterpret_cast<std::fstream*>(arg);

  while (thread_running_.load(std::memory_order_acquire)) {
    buffer_.Read([&](uint8_t* buf, size_t size) {
      f->write(reinterpret_cast<char*>(buf), size);
    });
    Thread::Sleep(200);
  }

  return nullptr;
}

void FileOutput::Flush() {
  if (fstream_) {
    fstream_->flush();
  }
}

}  // namespace tptlog