
add_library(modules_std_unicode STATIC
	unicode.cc
	string.cc
)

list(APPEND CLEVER_INCLUDES ${ICU_INCLUDE_DIRS})
list(APPEND CLEVER_LIBS ${ICU_LIBS})
