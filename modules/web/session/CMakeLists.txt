
add_library(modules_web_session STATIC
	session.cc
)

set_target_properties(modules_web_session
	PROPERTIES
	COMPILE_FLAGS "${CGI_CFLAGS}"
	#STATIC_LIBRARY_FLAGS "${FFI_LDFLAGS}"
)

