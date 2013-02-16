
add_library(modules_std_fcgi STATIC
	fcgi.cc
	server.cc
)

list(APPEND CLEVER_INCLUDES ${FCGI_INCLUDE_DIRS})
list(APPEND CLEVER_LIBS ${FCGI_LIBRARIES})
