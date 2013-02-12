# clever_module_msg(<name> <msg>)
macro(clever_module_msg Name Msg)
	message(STATUS "MOD ${Name} -- ${Msg}")
endmacro(clever_module_msg)

# clever_add_module(<name> <enabled>
#                   [[<docstring>]
#                    [<mod1>;<mod2>;...]
#                    [<lib1>;<lib2>;...])
# Defines MOD_<Uppercased Name>
#         MOD_<Uppercased Name>_MOD_DEPENDS
#         MOD_<Uppercased Name>_LIB_DEPENDS
macro(clever_add_module Name Enabled)
	if(${ARGC} LESS 2)
		message(SEND_ERROR "clever_add_module needs at least 2 args")
	endif(${ARGC} LESS 2)

	string(TOUPPER "MOD_${Name}" _mod_var)
	set(_mod_doc "")

	set(${_mod_var}_MOD_DEPENDS OFF)
	set(${_mod_var}_LIB_DEPENDS OFF)

	if (${ARGC} GREATER 2)
		set(_mod_doc ${ARGV2})
	endif (${ARGC} GREATER 2)

	if (${ARGC} GREATER 3)
		set(${_mod_var}_MOD_DEPENDS "${ARGV3}")
	endif (${ARGC} GREATER 3)

	
	option(${_mod_var} "${_mod_doc}" ${Enabled})
endmacro(clever_add_module)

macro(clever_add_simple_module Name Enabled)
	if(${ARGC} LESS 2)
		message(SEND_ERROR "clever_add_simple_module needs at least 2 args")
	endif(${ARGC} LESS 2)

	clever_add_module("${Name}" ${Enabled} "${ARGV2}" "${ARGV3}")
	clever_check_mod_env("${Name}")

endmacro(clever_add_simple_module)

# clever_check_mod_depends(<name>)
#
macro(clever_check_mod_depends Name)
	string(TOUPPER "MOD_${Name}" _mod_var)
	set(_mod_deps "${${_mod_var}_MOD_DEPENDS}")
	set(_disable OFF)

	#message(STATUS "'${_mod_deps}'")
	if (NOT ${_mod_deps} STREQUAL "")
		clever_module_msg("${Name}" "checking module dependencies...")

		foreach(dep ${_mod_deps})
			string(TOUPPER "MOD_${dep}" udep)
			if(NOT ${udep})
				clever_module_msg("${Name}" "module not found (${dep}).")
				set(_disable ON)
				break()
			endif(NOT ${udep})
		endforeach(dep)

		if (_disable)
			set(${_mod_var} OFF)
		endif (_disable)
	endif (NOT ${_mod_deps} STREQUAL "")

endmacro(clever_check_mod_depends)

# clever_check_mod_env(<name>)
# 
macro(clever_check_mod_env Name)
	string(TOUPPER "MOD_${Name}" _mod_var)

	if (${_mod_var})
		clever_check_mod_depends("${Name}")
	endif (${_mod_var})

	if (${_mod_var})
		add_definitions(-DHAVE_${_mod_var})
		clever_module_msg("${Name}" ON)
	else (${_mod_var})
		clever_module_msg("${Name}" OFF)
	endif (${_mod_var})
	
endmacro(clever_check_mod_env)

