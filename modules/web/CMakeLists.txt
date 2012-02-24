
set(CLEVER_MODULES)

if (MOD_WEB_REQUEST)
	list(APPEND CLEVER_MODULES request)
endif (MOD_WEB_REQUEST)

if (MOD_WEB_SESSION)
	list(APPEND CLEVER_MODULES session)
endif (MOD_WEB_SESSION)


foreach (module ${CLEVER_MODULES})
	add_subdirectory(${module})
endforeach (module)

add_library(modules_web STATIC
	web_pkg.cc
)

foreach (module ${CLEVER_MODULES})
	add_dependencies(modules_web "modules_web_${module}")
	target_link_libraries(modules_web "modules_web_${module}")
endforeach (module)


