#ifndef TPT_LINUX_PLATFORM_H
#define TPT_LINUX_PLATFORM_H

#define TPT_LINUX 1
#define TPT_POSIX 1

#ifdef _LP64
#define TPT_ARCH_64 1
#else
#define TPT_ARCH_32 1
#endif

#define TPT_CACHE_LINE_SIZE 64

#define TPT_POSIX_TIME 1
#define TPT_POSIX_THREAD 1

#endif  // TPT_LINUX_PLATFORM_H