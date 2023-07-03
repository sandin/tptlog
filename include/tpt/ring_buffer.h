#ifndef TPT_RING_BUFFER_H
#define TPT_RING_BUFFER_H

#include <atomic>
#include <cstddef>  // size_t;
#include <cstdint>
#include <vector>

#include "tpt/sync.h"

namespace tpt {

template <class T>
class RingBuffer {
 public:
  explicit RingBuffer(size_t capacity) : start_pos_(0), end_pos_(0) {
    buffer_.reserve(capacity);
  }
  ~RingBuffer() {}

  T* Data() const { return buffer_.data(); }
  size_t Capacity() const { return buffer_.capacity(); }

  size_t Size() const {
    const size_t start_pos = start_pos_.load(std::memory_order_acquire);
    return end_pos_.load(std::memory_order_acquire) - start_pos;
  }

  void Write(T* data, size_t size) {
    if (!data || size <= 0) {
      return;
    }

    MutexLock lock(&pos_mutex_);
    const size_t local_end_pos = end_pos_.load(std::memory_order_relaxed);
    const size_t local_start_pos = start_pos_.load(std::memory_order_relaxed);
    const size_t buffer_free_size =
        local_start_pos <= local_end_pos
            ? (buffer_.size() - local_end_pos + local_start_pos)
            : (local_start_pos - local_end_pos);
    if (buffer_free_size <= size) {
      // TODO:
    }
  }

 private:
  std::atomic<size_t> start_pos_;
  std::atomic<size_t> end_pos_;
  tpt::Mutex pos_mutex_;
  std::vector<T> buffer_;

};  // class RingBuffer

}  // namespace tpt

#endif  // TPT_RING_BUFFER_H