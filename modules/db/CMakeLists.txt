
set(CLEVER_MODULES)

if (MOD_DB_MYSQL)
	list(APPEND CLEVER_MODULES mysql)
endif (MOD_DB_MYSQL)

foreach (module ${CLEVER_MODULES})
	add_subdirectory(${module})
endforeach (module)

add_library(modules_db STATIC
	db_pkg.cc
)

foreach (module ${CLEVER_MODULES})
	add_dependencies(modules_db "modules_db_${module}")
	target_link_libraries(modules_db "modules_db_${module}")
endforeach (module)


