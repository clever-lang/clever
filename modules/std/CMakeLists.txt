
set(CLEVER_MODULES 
	file
	io
	math
	net
	os
	reflection
)

if (MODFFI)
	if (FFI_FOUND)
		list(APPEND CLEVER_MODULES ffi)
	else (FFI_FOUND)
		message(WARNING "ffi module will not be compiled. reason: libffi missing")
	endif (FFI_FOUND)
endif (MODFFI)

if (MODREGEX)
	if (PCRECPP_FOUND)
		list(APPEND CLEVER_MODULES regex)
	else (PCRECPP_FOUND)
		message(WARNING "regex module will not be compiled. reason: libpcrecpp missing")
	endif (PCRECPP_FOUND)
endif (MODREGEX)

foreach (module ${CLEVER_MODULES})
	add_subdirectory(${module})
endforeach (module)

add_library(modules.std STATIC
	std_pkg.cc
)

foreach (module ${CLEVER_MODULES})
	add_dependencies(modules.std "modules.std.${module}")
	target_link_libraries(modules.std "modules.std.${module}")
endforeach (module)


