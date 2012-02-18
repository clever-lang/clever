
add_library(modules.std.regex STATIC
	regex.cc
	pcre.cc
)

list(APPEND CLEVER_INCLUDES ${PCRECPP_INCLUDE_DIRS})
list(APPEND CLEVER_LIBS ${PCRECPP_LIBRARIES})

