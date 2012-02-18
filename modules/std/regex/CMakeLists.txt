
add_library(modules_std_regex STATIC
	regex.cc
	pcre.cc
)

list(APPEND CLEVER_INCLUDES ${PCRECPP_INCLUDE_DIRS})
list(APPEND CLEVER_LIBS ${PCRECPP_LIBRARIES})

