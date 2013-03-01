
set(CLEVER_MODULES)

#if (STD_RPC)
#	list(APPEND CLEVER_MODULES rpc)
#endif (STD_RPC)

if (STD_FFI)
	list(APPEND CLEVER_MODULES ffi)
endif (STD_FFI)

if (STD_REGEX)
	list(APPEND CLEVER_MODULES regex)
endif (STD_REGEX)

if (STD_CLEVER)
	list(APPEND CLEVER_MODULES clever)
endif (STD_CLEVER)

if (STD_CONCURRENT)
	list(APPEND CLEVER_MODULES concurrent)
endif (STD_CONCURRENT)

if (STD_EVENTS)
	list(APPEND CLEVER_MODULES events)
endif (STD_EVENTS)

if (STD_DATE)
	list(APPEND CLEVER_MODULES date)
endif (STD_DATE)

if (STD_FILE)
	list(APPEND CLEVER_MODULES file)
endif (STD_FILE)

if (STD_IO)
	list(APPEND CLEVER_MODULES io)
endif (STD_IO)

if (STD_UNICODE)
	list(APPEND CLEVER_MODULES unicode)
endif (STD_UNICODE)

if (STD_FCGI)
	list(APPEND CLEVER_MODULES fcgi)
endif (STD_FCGI)

if (STD_MATH)
	list(APPEND CLEVER_MODULES math)
endif (STD_MATH)

if (STD_NET)
	list(APPEND CLEVER_MODULES net)
endif (STD_NET)

if (STD_SYS)
	list(APPEND CLEVER_MODULES sys)
endif (STD_SYS)

if (STD_REFLECTION)
	list(APPEND CLEVER_MODULES reflection)
endif (STD_REFLECTION)

if (STD_CRYPTO)
	list(APPEND CLEVER_MODULES crypto)
endif (STD_CRYPTO)

if (STD_JSON)
	list(APPEND CLEVER_MODULES json)
endif (STD_JSON)

foreach (module ${CLEVER_MODULES})
	add_subdirectory(${module})
endforeach (module)

add_library(modules_std STATIC
	std_pkg.cc
)

foreach (module ${CLEVER_MODULES})
	add_dependencies(modules_std "modules_std_${module}")
	target_link_libraries(modules_std "modules_std_${module}")
endforeach (module)


