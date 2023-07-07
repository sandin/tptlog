#ifndef TPTLOG_OUTPUT_H
#define TPTLOG_OUTPUT_H

#include <cstddef>
#include <fstream>
#include <string>
#include <atomic>

#include "tpt/thread.h"
#include "tpt/ring_buffer.h"

namespace tptlog {

// Output Interface
class Output {
 public:
  virtual ~Output() {}
  virtual bool Serialize(const std::string& content) = 0;
  virtual void Flush() = 0;
};  // class Output

class FileOutput : public Output {
 public:
  FileOutput(const std::string& filename, size_t initial_buffer_size)
      : filename_(filename), fstream_(nullptr), buffer_(initial_buffer_size), thread_(nullptr), thread_running_(false) {}
  virtual ~FileOutput() {
    if (fstream_) {
      delete fstream_;
    }
    if (thread_) {
      delete thread_;
    }
  }

  virtual bool Serialize(const std::string& content) override;
  virtual void Flush() override;

 private:
  void* Run(tpt::Thread::Arg arg); 

  std::string filename_;
  std::fstream* fstream_;
  tpt::RingBuffer<uint8_t> buffer_;
  tpt::Thread* thread_;
  std::atomic_bool thread_running_;
};  // class FileOutput

}  // namespace tptlog

#endif  // TPTLOG_OUTPUT_H