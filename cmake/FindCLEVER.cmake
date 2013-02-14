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
	set(multiValue PKGS LIBS INCS)
	cmake_parse_arguments(args "${options}" "" "${multiValue}" ${ARGN})

	set(_dir ${VarName}_DIR)
	set(_found ${VarName}_FOUND)

	set(msg_level WARNING)

	if (args_REQUIRED)
		set(msg_level FATAL_ERROR)
	endif (args_REQUIRED)

	# automated checking with pkg-config
	if (NOT ${_dir})
		if (PKG_CONFIG_FOUND AND args_PKGS)
			pkg_check_modules(${VarName} ${args_PKGS})
		endif (PKG_CONFIG_FOUND AND args_PKGS)
	endif (NOT ${_dir})
	
	# fallback to manual checking
	if (NOT ${_found})
		set(_found_incs 1)
		set(_found_libs 1)

		# check includes
		if (args_INCS)
			foreach (_name ${args_INCS})
				set(_opts NAMES "${_name}")
				set(_path)

				if (${_dir})
					find_path(_path_a ${_opts} PATHS "${${_dir}}/include" NO_DEFAULT_PATH)
					set(_path ${_path_a})
				else (${_dir})
					find_path(_path_b ${_opts})
					set(_path ${_path_b})
				endif (${_dir})

				if (_path)
					list(APPEND ${VarName}_INCLUDE_DIRS ${_path})
				else (_path)
					message(${msg_level} "Failed to find include file(s) `${_name}`.")
					set(_found_incs 0)
				endif (_path)
			endforeach (_name ${args_LIBS})
		endif (args_INCS)

		# check libraries
		if (args_LIBS)
			foreach (_name ${args_LIBS})
				set(_opts NAMES "${_name}")
				set(_lib)

				if (${_dir})
					find_library(_lib_a ${_opts} PATHS "${${_dir}}/lib" NO_DEFAULT_PATH)
					set(_lib ${_lib_a})
				else (${_dir})
					find_library(_lib_b ${_opts})
					set(_lib ${_lib_b})
				endif (${_dir})
				
				if (_lib)
					#list(APPEND ${VarName}_LIBRARIES ${_lib})
					list(APPEND ${VarName}_LIBRARIES "${_name}")
					get_filename_component(_path ${_lib} PATH)
					list(APPEND ${VarName}_LINK_DIRECTORIES "${_path}")
				else (_lib)
					message(${msg_level} "Failed to find required library `${_name}`.")
					set(_found_libs 0)
				endif (_lib)
			endforeach (_name ${args_LIBS})
		endif (args_LIBS)

		if (_found_incs AND _found_libs)
			set(${_found} 1)
		endif (_found_incs AND _found_libs)
	endif (NOT ${_found})
	
	if (${_found})
		if (${VarName}_INCLUDE_DIR AND NOT ${VarName}_INCLUDE_DIRS)
			set(${VarName}_INCLUDE_DIRS ${${VarName}_INCLUDE_DIR})
		endif (${VarName}_INCLUDE_DIR AND NOT ${VarName}_INCLUDE_DIRS)

		if (NOT ${VarName}_INCLUDE_DIRS)
			set(${VarName}_INCLUDE_DIRS)
		endif (NOT ${VarName}_INCLUDE_DIRS)
		
		if (NOT ${VarName}_LINK_DIRECTORIES)
			set(${VarName}_LINK_DIRECTORIES)
		else (NOT ${VarName}_LINK_DIRECTORIES)
		endif (NOT ${VarName}_LINK_DIRECTORIES)

	endif (${_found})

	unset(args_INCS)
	unset(args_LIBS)
	unset(args_PKGS)
	unset(args_DIRS)
	unset(_lib)
	unset(_lib_a)
	unset(_lib_b)
	unset(_name)
	unset(_path_a)
	unset(_path_b)
	unset(_opts)
	unset(_path)

endmacro(clever_add_lib)

