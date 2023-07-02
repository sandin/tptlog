#ifdef TPT_MACRO_DEF_H  // make sure the "macro_def.h" file has been imported,
#undef TPT_MACRO_DEF_H  // and undo everything that was done in the "macro_def.h" file

// DEBUG
#undef TPT_DEBUG

// LOG
#undef TPT_LOG_LEVEL
#undef TPT_LOG_E
#undef TPT_LOG_I
#undef TPT_LOG_D
#undef TPT_LOG_V

// MEMORY
#undef TPT_MEM_ALIGN

// ASSERT
#undef TPT_ASSERT

// CTOR
#undef TPT_DISALLOW_COPY_AND_ASSIGN

#endif  // TPT_MACRO_DEF_H