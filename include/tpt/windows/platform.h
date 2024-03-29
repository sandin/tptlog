#ifndef TPT_WINDOWS_PLATFORM_H
#define TPT_WINDOWS_PLATFORM_H

#define TPT_WINDOWS 1

#include <windows.h>

#if defined(_WIN64) || defined(WIN64)
#define TPT_ARCH_64 1
#else
#define TPT_ARCH_32 1
#endif

#define TPT_CACHE_LINE_SIZE 64

#define TPT_WINDOWS_TIME 1
#define TPT_WINDOWS_THREAD 1

#endif  // TPT_WINDOWS_PLATFORM_H