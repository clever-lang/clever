
add_library(modules_web_session STATIC
	session.cc
)

set_target_properties(modules_web_session
	PROPERTIES
	COMPILE_FLAGS "${CGI_CFLAGS}"
	#STATIC_LIBRARY_FLAGS "${FFI_LDFLAGS}"
)

list(APPEND CLEVER_INCLUDES ${CGICC_INCLUDE_DIRS})
list(APPEND CLEVER_LIBS ${CGICC_LIBRARIES})
