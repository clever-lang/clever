
add_library(modules_web_cgi STATIC
	cgi.cc
	cgiclass.cc
)

set_target_properties(modules_web_cgi
	PROPERTIES
	COMPILE_FLAGS "${CGI_CFLAGS}"
	#STATIC_LIBRARY_FLAGS "${FFI_LDFLAGS}"
)

