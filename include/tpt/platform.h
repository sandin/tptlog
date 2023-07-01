#ifndef TPT_PLATFORM_H
#define TPT_PLATFORM_H

#if defined(_WIN64) || defined(WIN64) || defined(_WIN32) || defined(WIN32)
#include "tpt/windows/platform.h"
#elif defined(ANDROID) || defined(__ANDROID__)
#include "tpt/android/platform.h"
#elif defined(__linux__)
#include "tpt/linux/platform.h"
#elif defined(__APPLE__)
#include <Availability.h>
#include <TargetConditionals.h>
#if TARGET_OS_IPHONE
#include "tpt/ios/platform.h"
#else
#include "tpt/darwin/platform.h"
#endif
#endif

#ifndef TPTAPI
#define TPTAPI
#endif

#endif  // TPT_PLATFORM_H