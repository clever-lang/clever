
add_library(modules_web_http STATIC
	http.cc
	sessionclass.cc
)

set_target_properties(modules_web_http
	PROPERTIES
	COMPILE_FLAGS "${CGI_CFLAGS}"
	#STATIC_LIBRARY_FLAGS "${FFI_LDFLAGS}"
)

