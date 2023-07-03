#ifndef TPT_SYNC_H
#define TPT_SYNC_H

#ifdef TPT_ABSEIL_SYNC
#include "absl/synchronization/mutex.h"
#endif

namespace tpt {

#ifdef TPT_ABSEIL_SYNC

using Mutex = absl::Mutex;
using MutexLock = absl::MutexLock;
using ReleasableMutexLock = absl::ReleasableMutexLock;
using CondVar = absl::CondVar;

#else

// TODO: impl sync without abseil-cpp

#endif

}  // namespace tpt

#endif  // TPT_SYNC_H