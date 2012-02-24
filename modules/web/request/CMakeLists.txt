
add_library(modules_web_request STATIC
	request.cc
)

set_target_properties(modules_web_request
	PROPERTIES
	COMPILE_FLAGS "${CGI_CFLAGS}"
	#STATIC_LIBRARY_FLAGS "${FFI_LDFLAGS}"
)

