#ifndef TPTLOG_OUTPUT_H
#define TPTLOG_OUTPUT_H

#include <cstddef>
#include <fstream>
#include <string>

#include "tpt/ring_buffer.h"

namespace tptlog {

using std::fstream;
using std::string;
using tpt::RingBuffer;

// Output Interface
class Output {
 public:
  virtual ~Output() {}
  virtual void Serialize(const string& content) = 0;
  virtual void Flush() = 0;
};  // class Output

class FileOutput : public Output {
 public:
  FileOutput(const string& filename, size_t initial_buffer_size)
      : filename_(filename), fstream_(nullptr), buffer_(initial_buffer_size) {}
  virtual ~FileOutput() {
    if (fstream_) {
      delete fstream_;
    }
  }

  virtual void Serialize(const string& content) override;
  virtual void Flush() override;

 private:
  string filename_;
  fstream* fstream_;
  RingBuffer buffer_;
};  // class FileOutput

}  // namespace tptlog

#endif  // TPTLOG_OUTPUT_H