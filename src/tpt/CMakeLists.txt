set(TPT_SOURCES
	posix/time.cc
	windows/time.cc
	posix/thread.cc
	windows/thread.cc
)

add_library(tpt STATIC ${TPT_SOURCES})

if(UNIX)
	find_package(Threads)
	target_link_libraries(tpt m Threads::Threads)

	if(TPT_PLATFORM_LINUX OR TPT_PLATFORM_POSIX)
		target_link_libraries(tpt rt)
	endif()
endif()

if(TPT_PLATFORM_ANDROID)
	find_library(log-log log)
	target_link_libraries(tpt ${log-lib})
endif()

target_include_directories(tpt PUBLIC ${PROJECT_SOURCE_DIR}/include/)
