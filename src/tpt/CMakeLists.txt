set(TPT_SOURCES
	posix/time.cc
	windows/time.cc
)

add_library(tpt STATIC ${TPT_SOURCES})
target_include_directories(tpt PUBLIC ${PROJECT_SOURCE_DIR}/include/)
