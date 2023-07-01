#ifndef TPT_DARWIN_PLATFORM_H
#define TPT_DARWIN_PLATFORM_H

#define TPT_DARWIN 1
#define TPT_POSIX 1

#ifdef _LP64
#define TPT_ARCH_64 1
#else
#define TPT_ARCH_32 1
#endif

#define TPT_POSIX_TIME

#endif  // TPT_ANDROID_PLATFORM_H