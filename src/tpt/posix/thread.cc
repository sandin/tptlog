#include "tpt/thread.h"

#include "tpt/macro_def.h"
#include "tpt/platform.h"

#ifdef TPT_POSIX_THREAD

#include <pthread.h>
#include <unistd.h>  // gettid

namespace tpt {

namespace {
class PosixThread;  // forward declaration

struct PosixThreadArg {
  PosixThread* posix_thread;
  const char* name;
  Thread::Func func;
  Thread::Arg arg;
};

class PosixThread : public internal::ThreadInternalsInterface {
 public:
  PosixThread(const char* name, Thread::Func func, Thread::Arg arg)
      : name_(name), func_(func), arg_(arg) {}

  bool Start() override {
    int ret;
    pthread_attr_t attr;
    ret = pthread_attr_init(&attr);
    if (ret != 0) {
      TPT_LOG_E("Can not init pthread attr.\n");
      return false;
    }

    PosixThreadArg* pthread_arg =
        static_cast<PosixThreadArg*>(malloc(sizeof(PosixThreadArg)));
    if (pthread_arg == nullptr) {
      TPT_LOG_E("Out of memory\n");
      return false;
    }
    pthread_arg->posix_thread = this;
    pthread_arg->name = !name_.empty() ? name_.c_str() : nullptr;
    pthread_arg->func = func_;
    pthread_arg->arg = arg_;

    ret = pthread_create(
        &pthread_id_, &attr,
        [](void* v) -> void* {
          PosixThreadArg arg = *static_cast<PosixThreadArg*>(v);  // copy
          free(v);
          if (arg.name != nullptr) {
#if TPT_APPLE
            // https://opensource.apple.com/source/libpthread/libpthread-301.30.1/pthread/pthread.h.auto.html
            pthread_setname_np(arg.name);
#else
            // https://man7.org/linux/man-pages/man3/pthread_setname_np.3.html
            char buf[16];
            strncpy(buf, arg.name, 16 - 1);
            buf[16 - 1] = '\0';
            pthread_setname_np(pthread_self(), buf);
#endif
          }

          arg.func(arg.arg);
          return nullptr;
        },
        pthread_arg);
    if (ret != 0) {  // pthread_create failed
      free(pthread_arg);
      return false;
    }
    return true;
  }

  bool Join() override {
    int ret = pthread_join(pthread_id_, nullptr);
    return ret == 0;
  }

 private:
  std::string name_;
  Thread::Func func_;
  Thread::Arg arg_;
  pthread_t pthread_id_;
};  // class PosixThread

} // anonymous namespace

Thread::Thread(const char* name, Thread::Func func, Thread::Arg arg) {
  impl_ = new PosixThread(name, func, arg);
  state_ = State::kNew;
}

// static
uintptr_t Thread::GetCurrentThreadId() {
#if TPT_APPLE
  uint64_t tid;
  pthread_threadid_np(nullptr, &tid);
  return static_cast<uintptr_t>(tid);
#else
  // https://man7.org/linux/man-pages/man2/gettid.2.html
  return static_cast<uintptr_t>(gettid());
#endif
  // or get pthread id: return (uintptr_t)pthread_self();
}

Thread::~Thread() {
  if (impl_) {
    delete impl_;
  }
}

}  // namespace tpt

#endif  // TPT_POSIX_THREAD