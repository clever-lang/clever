
set(CLEVER_MODULES)

if (MOD_WEB_CGI)
	list(APPEND CLEVER_MODULES cgi)
endif (MOD_WEB_CGI)

if (MOD_WEB_HTTP)
	list(APPEND CLEVER_MODULES http)
endif (MOD_WEB_HTTP)


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


