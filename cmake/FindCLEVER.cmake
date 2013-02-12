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

# clever_add_lib(<var_name>
#       [PKGS pkg1 [pkg2 ...]]
#       [LIBS lib1 [lib2 ...]]
#       [INCS header1 [header2 ...]]
#       [REQUIRED]
# 	)
#
# PKGS is a list of pkg-config modules.
#
# LIBS is a list of libraries (without the `lib` prefix or the `.ext` suffix)
#
# INCS is a list of files to look for in include directories.
#
# YOU MUST SPECIFY AT LEAST ONE OF THE ABOVE OPTIONS.
#
# When REQUIRED is set, the macro will exit with an error.
#
macro(clever_add_lib VarName)
	set(options REQUIRED)
	set(multiValueArgs PKGS LIBS INCS)

	cmake_parse_arguments(_add_lib "${options}" "" "${multiValueArgs}" ${ARGN})

	set(_add_lib_found FALSE)

	# automated checking with pkg-config
	if (NOT ${VarName}_DIR)
		if (PKG_CONFIG_FOUND AND _add_lib_PKGS)
			pkg_check_modules(${VarName} ${_add_lib_PKGS})
		endif (PKG_CONFIG_FOUND AND _add_lib_PKGS)
	endif (NOT ${VarName}_DIR)

	# fallback to manual checking
	if (NOT ${VarName}_FOUND)
		set(_inc_path "")
		set(_lib_path "")

		if (${VarName}_DIR)
			set(_inc_path "${VarName}/include")
			set(_lib_path "${VarName}/lib")
		endif (${VarName}_DIR)

		if (_add_lib_INCS)
			find_path(_path NAMES ${_add_lib_INCS} PATHS "${_inc_path}")
			if (_path)
				set(${VarName}_INCLUDE_DIRS ${_path})
			else (_path)
				message(WARNING "Failed to find include directories for `${_add_lib_INCS}`.")
			endif (_path)
		endif (_add_lib_INCS)
		if (_add_lib_LIBS)
			foreach (_name ${_add_lib_LIBS})
				find_library(_lib${_name} NAMES "${_name}" PATHS "${_lib_path}")

				if (_lib${_name})
					list(APPEND ${VarName}_LIBRARIES ${_lib${_name}})
				else (_lib${_name})
					if (_add_lib_REQUIRED)
						message(SEND_ERROR "Failed to find required library `${_name}`.")
					endif (_add_lib_REQUIRED)
					break()
				endif (_lib${_name})

				unset(_lib${_name})
			endforeach (_name)
			unset(_name)
		endif (_add_lib_LIBS)

		if (${VarName}_LIBRARIES)
			set(${VarName}_FOUND TRUE)
		endif (${VarName}_LIBRARIES)
	endif (NOT ${VarName}_FOUND)

endmacro(clever_add_lib)

