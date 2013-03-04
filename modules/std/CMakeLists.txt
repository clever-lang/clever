
set(CLEVER_MODULES)

if(STD_FFI)
	list(APPEND CLEVER_MODULES ffi)
endif()

if(STD_REGEX)
	list(APPEND CLEVER_MODULES regex)
endif()

if(STD_CLEVER)
	list(APPEND CLEVER_MODULES clever)
endif()

if(STD_CONCURRENT)
	list(APPEND CLEVER_MODULES concurrent)
endif()

if(STD_EVENTS)
	list(APPEND CLEVER_MODULES events)
endif()

if(STD_DATE)
	list(APPEND CLEVER_MODULES date)
endif()

if(STD_FILE)
	list(APPEND CLEVER_MODULES file)
endif()

if(STD_IO)
	list(APPEND CLEVER_MODULES io)
endif()

if(STD_UNICODE)
	list(APPEND CLEVER_MODULES unicode)
endif()

if(STD_FCGI)
	list(APPEND CLEVER_MODULES fcgi)
endif()

if(STD_MATH)
	list(APPEND CLEVER_MODULES math)
endif()

if(STD_NET)
	list(APPEND CLEVER_MODULES net)
endif()

if(STD_SYS)
	list(APPEND CLEVER_MODULES sys)
endif()

if(STD_REFLECTION)
	list(APPEND CLEVER_MODULES reflection)
endif()

if(STD_CRYPTO)
	list(APPEND CLEVER_MODULES crypto)
endif()

if(STD_JSON)
	list(APPEND CLEVER_MODULES json)
endif()

if(STD_COLLECTION)
	list(APPEND CLEVER_MODULES collection)
endif()

foreach(module ${CLEVER_MODULES})
	add_subdirectory(${module})
endforeach()

add_library(modules_std STATIC
	std_pkg.cc
)

foreach(module ${CLEVER_MODULES})
	add_dependencies(modules_std "modules_std_${module}")
	target_link_libraries(modules_std "modules_std_${module}")
endforeach()


