# clever_module_msg(<name> <msg>)
macro(clever_module_msg Name Msg)
	message(STATUS "Module ${Name}: ${Msg}")
endmacro(clever_module_msg)

# clever_module_var(<name> <output var>)
#
# Sets the output variable to the variable that represents
# the module named by the first argument.
#
macro(clever_module_var Name Var)
	string(REPLACE "." "_" _sanitized "${Name}")
	string(TOUPPER "${_sanitized}" ${Var})
endmacro(clever_module_var)

macro(clever_module_set_prop Name Property Value)
	clever_module_var(${Name} _mod_var)
	set(${_mod_var}_${Property} ${Value})
endmacro(clever_module_set_prop)

# clever_module_path(<name> <output var>
# 		[PATH <path>])
#
# Sets the output variable to the path of the given module.
#
# The PATH argument can be used to change the module's path.
#
macro(clever_module_path Name Var)
	set(singleValue PATH)
	cmake_parse_arguments(args "" "${singleValue}" "" ${ARGN})

	clever_module_var(${Name} _mod_var)

	set(_mod_path "${_mod_var}_PATH")

	if (args_PATH)
		clever_module_set_prop(${Name} PATH "${args_PATH}")
	else (args_PATH)
		string(REPLACE "." "/" ${_mod_path} "${Name}")
		clever_module_set_prop(${Name}
			PATH "${CMAKE_CURRENT_SOURCE_DIR}/module/${${_mod_path}}")
	endif (args_PATH)

	set(${Var} "${_mod_var}_PATH")

endmacro(clever_module_path)

# clever_new_module(<name> <enabled>
# 		[[DOC <doc string>]
# 		 [LIBS <library variable names>]
# 		 [MODS <module names>]]
#
# Declares a new clever module.
#
# Example:
# 	clever_new_module(std.regex ON
# 		DOC "perl-compatible regex module"
# 		LIBS PCRECPP)
#
# 	clever_new_module(std.regex_extra ON
# 		DOC "extra regex stuff"
# 		MODS std.regex)
#
# Defines <Uppercased Name>
#         <Uppercased Name>_NAME
#         <Uppercased Name>_PATH
#         <Uppercased Name>_CHECKED (OFF by default)
#         <Uppercased Name>_MOD_DEPENDS
#         <Uppercased Name>_LIB_DEPENDS
#
macro(clever_new_module Name Enabled)
	set(singleValue DOC PATH)
	set(multiValue LIBS MODS)
	cmake_parse_arguments(args "" "${singleValue}" "${multiValue}" ${ARGN})

	clever_module_var(${Name} _mod_var)
	clever_module_path(${Name} _mod_path PATH "${args_PATH}")

	option(${_mod_var} "${args_DOC}" ${Enabled})

	clever_module_set_prop(${Name} NAME ${Name})
	clever_module_set_prop(${Name} CHECKED OFF)
	clever_module_set_prop(${Name} MOD_DEPENDS "${args_MODS}")
	clever_module_set_prop(${Name} LIB_DEPENDS "${args_LIBS}")


	list(APPEND CLEVER_AVAILABLE_MODULES ${Name})

endmacro(clever_new_module)

macro(clever_enable_module Name)
	clever_module_var(${Name} _mod_var)
	set(${_mod_var} ON)
	clever_module_msg(${Name} "enabled")
endmacro(clever_enable_module)

macro(clever_disable_module Name)
	clever_module_var(${Name} _mod_var)
	set(${_mod_var} OFF)
	if (ARG2)
		clever_module_msg(${Name} "disabled (${ARG2})")
	else (ARG2)
		clever_module_msg(${Name} "disabled")
	endif (ARG2)
endmacro(clever_disable_module)

# clever_module_check(<name>)
#
# Checks the dependencies of a module and automatically
# adds the required definitions
#
macro(clever_module_check Name)
	clever_module_var(${Name} _mod_var)
	set(_mod_checked "${_mod_var}_CHECKED")

	# check only once
	if (NOT ${_mod_checked})

		if (NOT ${_mod_var})
			clever_disable_module(${Name})
		endif (NOT ${_mod_var})

		# check libs
		set(_mod_libs "${_mod_var}_LIB_DEPENDS")
		if (${_mod_var} AND ${_mod_libs})
			foreach (_name ${${_mod_libs}})
				if (NOT ${_name}_FOUND)
					clever_disable_module(${Name} "${_name} not found")
					break()
				endif (NOT ${_name}_FOUND)
			endforeach (_name ${${_mod_libs}})
		endif (${_mod_var} AND ${_mod_libs})

		# check modules
		set(_mod_mods "${_mod_var}_MOD_DEPENDS")
		if (${_mod_var} AND ${_mod_mods})
			foreach (_name ${${_mod_mods}})
				clever_module_var(${_name} _depname)

				if (NOT ${_depname}_CHECKED)
					clever_module_check(${${_depname}_NAME})
				endif (NOT ${_depname}_CHECKED)

				if (NOT ${_depname})
					clever_disable_module(${Name} "${${_depname}_NAME} not found")
					break()
				endif (NOT ${_depname})
			endforeach (_name ${${_mod_mods}})
		endif (${_mod_var} AND ${_mod_mods})

		if (${_mod_var})
			# use the libs
			foreach (_name ${${_mod_libs}})
				clever_use_lib(${_name})
			endforeach (_name ${${_mod_libs}})

			add_definitions(-DHAVE_MOD_${_mod_var})

			clever_enable_module(${Name})
		endif (${_mod_var})

		set(${_mod_checked} ON)
	endif (NOT ${_mod_checked})
endmacro(clever_module_check)

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

	set(msg_level STATUS)

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
				set(_ipath${VarName})

				if (${_dir})
					set(_opts ${_opts} PATHS "${${_dir}}/include" NO_DEFAULT_PATH)
				endif (${_dir})

				find_path(_ipath${VarName} ${_opts})

				if (_ipath${VarName})
					list(APPEND ${VarName}_INCLUDE_DIRS "${_ipath${VarName}}")
				else (_ipath${VarName})
					message(${msg_level} "Failed to find include file(s) `${_name}`.")
					set(_found_incs 0)
				endif (_ipath${VarName})
			endforeach (_name ${args_LIBS})
		endif (args_INCS)

		# check libraries
		if (_found_incs AND args_LIBS)
			foreach (_name ${args_LIBS})
				set(_opts NAMES "${_name}")
				set(_lib${VarName})

				if (${_dir})
					set(_opts ${_opts} PATHS "${${_dir}}/lib" NO_DEFAULT_PATH)
				endif (${_dir})

				find_library(_lib${VarName} ${_opts})

				if (_lib${VarName})
					#list(APPEND ${VarName}_LIBRARIES ${_lib})
					list(APPEND ${VarName}_LIBRARIES "${_name}")
					get_filename_component(_path "${_lib${VarName}}" PATH)
					list(APPEND ${VarName}_LINK_DIRECTORIES "${_path}")
				else (_lib${VarName})
					message(${msg_level} "Failed to find required library `${_name}`.")
					set(_found_libs 0)
				endif (_lib${VarName})
			endforeach (_name ${args_LIBS})
		endif (_found_incs AND args_LIBS)

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

# clever_use_lib(Prefix)
#
# Prefix is the prefix of the variables that holds information about a library.
macro(clever_use_lib Prefix)
	list(APPEND CLEVER_INCLUDE_DIRS ${${Prefix}_INCLUDE_DIRS})
	list(APPEND CLEVER_LIBRARIES ${${Prefix}_LIBRARIES})
	list(APPEND CLEVER_LINK_DIRECTORIES ${${Prefix}_LINK_DIRECTORIES})
endmacro(clever_use_lib)

