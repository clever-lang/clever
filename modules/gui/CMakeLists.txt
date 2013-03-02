
set(CLEVER_MODULES)

if (GUI_NCURSES)
	list(APPEND CLEVER_MODULES ncurses)
endif (GUI_NCURSES)



foreach (module ${CLEVER_MODULES})
	add_subdirectory(${module})
endforeach (module)

add_library(modules_gui STATIC
	gui_pkg.cc
)

foreach (module ${CLEVER_MODULES})
	add_dependencies(modules_gui "modules_gui_${module}")
	target_link_libraries(modules_gui "modules_gui_${module}")
endforeach (module)


