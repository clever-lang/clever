#
# Clever programming language
# Copyright (c) 2011-2012 Clever Team
#
# modules.cmake - Module options and other stuff
#

# Modules
# ---------------------------------------------------------------------------
clever_add_module(std_regex      ON  "enable the regex module"      "")
clever_add_module(std_ffi        ON  "enable the ffi module"        "")
clever_add_module(std_rpc        ON  "enable the rpc module"        "")
clever_add_module(std_net        ON  "enable the net module"        "")
clever_add_module(web_request       ON "enable the request module"        "")
clever_add_module(web_session       ON "enable the session module"        "")

# Simple modules
clever_add_simple_module(std_file       ON  "enable the file module"       "")
clever_add_simple_module(std_io         ON  "enable the io module"         "")
clever_add_simple_module(std_unicode    ON  "enable the unicode module"    "")
clever_add_simple_module(std_math       ON  "enable the math module"       "")
clever_add_simple_module(std_reflection ON  "enable the reflection module" "")
clever_add_simple_module(std_sys        ON  "enable the sys module"        "")

# std.regex
if (MOD_STD_REGEX)
	if (PCRECPP_FOUND)
		add_definitions(-DHAVE_MOD_STD_REGEX)
		list(APPEND CLEVER_INCLUDE_DIRS ${PCRECPP_INCLUDE_DIRS})
		list(APPEND CLEVER_LIBRARIES ${PCRECPP_LIBRARIES})
	else (PCRECPP_FOUND)
		clever_module_msg(std_regex "libpcrecpp not found. disabling.")
		set(MOD_STD_REGEX OFF)
	endif (PCRECPP_FOUND)
endif (MOD_STD_REGEX)

clever_module_msg(std_regex ${MOD_STD_REGEX})

# std.ffi
if (MOD_STD_FFI)
	if (FFI_FOUND)
		add_definitions(-DHAVE_FFI)
		add_definitions(-DHAVE_MOD_STD_FFI)
		list(APPEND CLEVER_INCLUDE_DIRS ${FFI_INCLUDE_DIRS})
		list(APPEND CLEVER_LIBRARIES ${FFI_LIBRARIES} dl)
	else (FFI_FOUND)
		clever_module_msg(std_ffi "libffi not found. disabling.")
		set(MOD_STD_FFI OFF)
	endif (FFI_FOUND)
endif (MOD_STD_FFI)

clever_module_msg(std_ffi ${MOD_STD_FFI})

# std.rpc
if (MOD_STD_RPC)
	if (LIBPTHREAD_FOUND AND FFI_FOUND)
		add_definitions(-DHAVE_LIBPTHREAD)
		add_definitions(-pthread -DHAVE_FFI)
		add_definitions(-DHAVE_MOD_STD_RPC)
		list(APPEND CLEVER_INCLUDE_DIRS ${LIBPTHREAD_INCLUDE_DIRS} ${FFI_INCLUDE_DIRS})
		list(APPEND CLEVER_LIBRARIES ${LIBPTHREAD_LIBRARIES} ${FFI_LIBRARIES} dl)
	else (LIBPTHREAD_FOUND AND FFI_FOUND)
		clever_module_msg(std_rpc "libpthread or libffi not found. disabling.")
		set(MOD_STD_RPC OFF)
	endif (LIBPTHREAD_FOUND AND FFI_FOUND)
endif (MOD_STD_RPC)

clever_module_msg(std_rpc ${MOD_STD_RPC})


# web.request
if (MOD_WEB_REQUEST)
	if (CGICC_FOUND)
		add_definitions(-DHAVE_MOD_WEB_REQUEST)
		list(APPEND CLEVER_INCLUDE_DIRS ${CGICC_INCLUDE_DIRS})
		list(APPEND CLEVER_LIBRARIES ${CGICC_LIBRARIES})
	else (CGICC_FOUND)
		clever_module_msg(web_request "libcgicc not found. disabling.")
		set(MOD_WEB_REQUEST OFF)
	endif (CGICC_FOUND)
endif (MOD_WEB_REQUEST)

clever_module_msg(web_request ${MOD_WEB_REQUEST})

# web.session
if (MOD_WEB_SESSION)
	if (CGICC_FOUND)
		add_definitions(-DHAVE_MOD_WEB_SESSION)
		list(APPEND CLEVER_INCLUDE_DIRS ${CGICC_INCLUDE_DIRS})
		list(APPEND CLEVER_LIBRARIES ${CGICC_LIBRARIES})
	else (CGICC_FOUND)
		clever_module_msg(web_session "libcgicc not found. disabling.")
		set(MOD_WEB_SESSION OFF)
	endif (CGICC_FOUND)
endif (MOD_WEB_SESSION)

clever_module_msg(web_session ${MOD_WEB_SESSION})

# std.net
if (MOD_STD_NET)
	if (MSVC)
		list(APPEND CLEVER_LIBRARIES ws2_32)
	endif (MSVC)

	add_definitions(-DHAVE_MOD_STD_NET)
endif (MOD_STD_NET)

clever_module_msg(std_net ${MOD_STD_NET})

