#ifndef TPT_RING_BUFFER_H
#define TPT_RING_BUFFER_H

#include <atomic>
#include <cstddef>  // size_t;
#include <cstdint>
#include <functional>
#include <vector>

#include "tpt/sync.h"

namespace tpt {

template <class T>
class RingBuffer {
 public:
  explicit RingBuffer(size_t capacity) : write_idx_(0), read_idx_(0) {
    buffer_.reserve(capacity);
  }
  ~RingBuffer() {}

  T* Data() const { return buffer_.data(); }
  size_t Capacity() const { return buffer_.capacity(); }

  size_t Size() const {
    const size_t start_pos = write_idx_.load(std::memory_order_acquire);
    return read_idx_.load(std::memory_order_acquire) - start_pos;
  }

  bool Write(T* data, size_t size) {
    if (!data || size <= 0) {
      return;
    }

    MutexLock lock(&write_mutex_);

    const size_t write_idx = write_idx_.load(std::memory_order_relaxed);
    const size_t read_idx = read_idx_.load(std::memory_order_acquire);  // -V-
    const size_t free_size = read_idx <= write_idx
                                 ? (buffer_.size() - (write_idx - read_idx))
                                 : (read_idx - write_idx);
    if (TPT_LIKELY(size <= free_size)) {
      if (write_idx + size <= buffer_.capacity()) {
        memcpy(buffer_.data() + write_idx, data, size);
      } else {
        size_t buffer_size_to_end = buffer_.capacity() - write_idx;
        memcpy(buffer_.data() + write_idx, data, buffer_size_to_end);
        memcpy(buffer_.data(), data + buffer_size_to_end,
               size - buffer_size_to_end);
      }
      write_idx_.store((write_idx + size) % buffer_.capacity(),
                       std::memory_order_release);  // -^-
      return true;
    }

    return false;  // not enough space
  }

  bool Read(std::function<void(T*, size_t)> consumer) {
    // TODO: is empty: return false
    const size_t read_idx = read_idx_.load(std::memory_order_relaxed);
    const size_t write_idx = write_idx_.load(std::memory_order_acquire);  // -V-
    if (write_idx >= read_idx) {
      consumer(buffer_.data() + read_idx, write_idx - read_idx);
    } else {
      consumer(buffer_.data() + read_idx, buffer_.capacity() - read_idx);
      consumer(buffer_.data(), write_idx);
    }
    read_idx_.store(write_idx, std::memory_order_release);  // -^-
    return true;
  }

 private:
  alignas(TPT_CACHE_LINE_SIZE) std::atomic<size_t> write_idx_;
  alignas(TPT_CACHE_LINE_SIZE) std::atomic<size_t> read_idx_;

  tpt::Mutex write_mutex_;
  std::vector<T> buffer_;

};  // class RingBuffer

}  // namespace tpt

#endif  // TPT_RING_BUFFER_H