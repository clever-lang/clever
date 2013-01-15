
set(CLEVER_MODULES)

#if (MOD_STD_RPC)
#	list(APPEND CLEVER_MODULES rpc)
#endif (MOD_STD_RPC)

#if (MOD_STD_FFI)
#	list(APPEND CLEVER_MODULES ffi)
#endif (MOD_STD_FFI)

#if (MOD_STD_REGEX)
#	list(APPEND CLEVER_MODULES regex)
#endif (MOD_STD_REGEX)

if (MOD_STD_CONCURRENT)
	list(APPEND CLEVER_MODULES concurrent)
endif (MOD_STD_CONCURRENT)

if (MOD_STD_FILE)
	list(APPEND CLEVER_MODULES file)
endif (MOD_STD_FILE)

if (MOD_STD_IO)
	list(APPEND CLEVER_MODULES io)
endif (MOD_STD_IO)

if (MOD_STD_UNICODE)
	list(APPEND CLEVER_MODULES unicode)
endif (MOD_STD_UNICODE)

if (MOD_STD_FCGI)
	list(APPEND CLEVER_MODULES fcgi)
endif (MOD_STD_FCGI)

if (MOD_STD_MATH)
	list(APPEND CLEVER_MODULES math)
endif (MOD_STD_MATH)

if (MOD_STD_NET)
	list(APPEND CLEVER_MODULES net)
endif (MOD_STD_NET)

if (MOD_STD_SYS)
	list(APPEND CLEVER_MODULES sys)
endif (MOD_STD_SYS)

if (MOD_STD_REFLECTION)
	list(APPEND CLEVER_MODULES reflection)
endif (MOD_STD_REFLECTION)

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


