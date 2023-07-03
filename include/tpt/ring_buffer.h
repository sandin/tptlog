#ifndef TPT_RING_BUFFER_H
#define TPT_RING_BUFFER_H

#include <cstddef>

namespace tpt {

class RingBuffer {
 public:
  explicit RingBuffer(size_t initial_buffer_size)
      : initial_buffer_size_(initial_buffer_size) {}
  ~RingBuffer() {}

 private:
  size_t initial_buffer_size_;

};  // class RingBuffer

}  // namespace tpt

#endif  // TPT_RING_BUFFER_H