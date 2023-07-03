set(TPTLOG_SOURCES
	log.cc
	output.cc
)

add_library(tptlog STATIC ${TPTLOG_SOURCES})
target_link_libraries(tptlog tpt absl::strings absl::str_format absl::time)
target_include_directories(tptlog PUBLIC ${PROJECT_SOURCE_DIR}/include/)
