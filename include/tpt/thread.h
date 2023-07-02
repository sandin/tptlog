#ifndef TPT_THREAD_H
#define TPT_THREAD_H

#include <functional>
#include <string>

#include "tpt/macro_def.h"
#include "tpt/platform.h"

namespace tpt {

namespace internal {

class ThreadInternalsInterface {
 public:
  virtual ~ThreadInternalsInterface() {}
  virtual bool Start() = 0;
  virtual bool Join() = 0;
};

}  // namespace internal

class Thread {
 public:
  using Arg = void*;
  using Func = std::function<void*(Arg)>;

  enum class State { kNew = 0, kStarted, kDone, kMoved };

  Thread(const char* name, Func func, Arg arg);
  ~Thread();

  // move constructor & assignment operator
  Thread(Thread& other) noexcept : state_(other.state_), impl_(other.impl_) {
    other.state_ = State::kMoved;
    other.impl_ = nullptr;
  }
  Thread& operator=(Thread& other) noexcept {
    if (this != &other) {
      state_ = other.state_;
      impl_ = other.impl_;
      other.state_ = State::kMoved;
      other.impl_ = nullptr;
    }
    return *this;
  }

  TPT_DISALLOW_COPY_AND_ASSIGN(Thread);

  static uintptr_t GetCurrentThreadId();

  State GetState() const { return state_; }

  void Start() {
    if (impl_ != nullptr && state_ == State::kNew) {
      if (impl_->Start()) {
        state_ = State::kStarted;
      }
    }
  }

  void Join() {
    if (impl_ != nullptr && state_ == State::kStarted) {
      if (impl_->Join()) {
        state_ = State::kDone;
      }
    }
  }

 private:
  State state_;
  internal::ThreadInternalsInterface* impl_;

};  // class Thread

}  // namespace tpt

#include "tpt/macro_undef.h"

#endif  // TPT_THREAD_H