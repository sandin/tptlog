/**
 * NOTE: there two rules to import this file:
 * 1. IT IS OK to import this file in any "*.cpp" files.
 * 2. TRY NOT TO import this file in any "*.h/hpp" header files. If you have to
 * do it,  please import the "macro_undef.h" file at the end of the header file
 * to avoid bringing these macro definitions to other files.
 */
// clang-format off
#ifndef TPT_MACRO_DEF_H
#define TPT_MACRO_DEF_H

// DEBUG 
#ifdef NDEBUG
#define TPT_DEBUG 0
#else
#define TPT_DEBUG 1
#endif

// LOG 
#define TPT_LOG_LEVEL 2
#if TPT_LOG_LEVEL >= 0
#define TPT_LOG_E(fmt, ...) \
  fprintf(stderr, "[ERROR] %s:%d:%s(): " fmt, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)
#else
#define TPT_LOG_E(fmt, ...)
#endif
#if TPT_LOG_LEVEL >= 1
#define TPT_LOG_I(fmt, ...) \
  printf("[INFO] %s:%d:%s(): " fmt, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)
#else
#define TPT_LOG_I(fmt, ...)
#endif
#if TPT_LOG_LEVEL >= 2
#define TPT_LOG_D(fmt, ...) \
  printf("[DEBUG] %s:%d:%s(): " fmt, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)
#else
#define TPT_LOG_D(fmt, ...)
#endif
#if TPT_LOG_LEVEL >= 3
#define TPT_LOG_V(fmt, ...) \
  printf("[VERBOSE] %s:%d:%s(): " fmt, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)
#else
#define TPT_LOG_V(fmt, ...)
#endif

// MEMORY
#define TPT_MEM_ALIGN(v, a) (((v) + (a)-1) & ~((a)-1))

// ASSERT
#define TPT_ASSERT(exp, fmt, ...) if (!(exp)) { TPT_LOG_E(fmt, ##__VA_ARGS__); } assert(exp)

// CTOR
#define TPT_DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&) = delete;          \
  void operator=(const TypeName&) = delete

#endif // TPT_MACRO_DEF_H
// clang-format on