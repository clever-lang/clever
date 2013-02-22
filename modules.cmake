#
# Clever programming language
# Copyright (c) Clever Team
#
# modules.cmake - Module options and other stuff
#

# Modules
# ---------------------------------------------------------------------------
clever_add_module(std_date       ON  "enable the date module"       "")
clever_add_module(std_concurrent ON  "enable the concurrent module" "")
clever_add_module(std_regex      ON  "enable the regex module"      "")
clever_add_module(std_ffi        ON  "enable the ffi module"        "")
clever_add_module(std_rpc        OFF "enable the rpc module"        "")
clever_add_module(std_net        ON  "enable the net module"        "")
clever_add_module(std_unicode    ON  "enable the unicode module"    "")
clever_add_module(std_fcgi       OFF "enable the fcgi module"       "")
clever_add_module(web_request    OFF "enable the request module"    "")
clever_add_module(web_session    OFF "enable the session module"    "")
clever_add_module(db_mysql       ON  "enable the mysql module"      "")

# Simple modules
clever_add_simple_module(std_clever     ON  "enable the clever module"     "")
clever_add_simple_module(std_file       ON  "enable the file module"       "")
clever_add_simple_module(std_io         ON  "enable the io module"         "")
clever_add_simple_module(std_json       ON  "enable the json module"       "")
clever_add_simple_module(std_math       ON  "enable the math module"       "")
clever_add_simple_module(std_reflection ON  "enable the reflection module" "")
clever_add_simple_module(std_sys        ON  "enable the sys module"        "")
clever_add_simple_module(std_crypto     ON  "enable the crypto module"     "")

# std.date
if (MOD_STD_DATE)
	add_definitions(-DHAVE_MOD_STD_DATE)
	set(MOD_STD_DATE ON)
else (MOD_STD_DATE)
	set(MOD_STD_DATE OFF)
endif (MOD_STD_DATE)

clever_module_msg(std_date "${MOD_STD_DATE}")

# std.concurrent
if (MOD_STD_CONCURRENT)
	if (CONCURRENCY_FOUND)
		add_definitions(-DHAVE_MOD_STD_CONCURRENT)
		list(APPEND CLEVER_INCLUDE_DIRS ${CONCURRENCY_INCLUDE_DIRS})
		list(APPEND CLEVER_LIBRARIES ${CONCURRENCY_LIBRARIES})
	else (CONCURRENCY_FOUND)
		clever_module_msg(std_concurrent, "Posix Threads are not present on this system")
		set(MOD_STD_CONCURRENT OFF)
	endif (CONCURRENCY_FOUND)
endif (MOD_STD_CONCURRENT)

clever_module_msg(std_concurrent "${MOD_STD_CONCURRENT}")

# std.regex
if (MOD_STD_REGEX)
	if (PCRECPP_FOUND)
		add_definitions(-DHAVE_MOD_STD_REGEX)
		list(APPEND CLEVER_INCLUDE_DIRS ${PCRECPP_INCLUDE_DIRS})
		list(APPEND CLEVER_LIBRARIES ${PCRECPP_LIBRARIES})
		list(APPEND CLEVER_LINK_DIRECTORIES ${PCRECPP_LINK_DIRECTORIES})
	else (PCRECPP_FOUND)
		clever_module_msg(std_regex "libpcrecpp not found. disabling.")
		set(MOD_STD_REGEX OFF)
	endif (PCRECPP_FOUND)
endif (MOD_STD_REGEX)

clever_module_msg(std_regex ${MOD_STD_REGEX})

# std.unicode
if (MOD_STD_UNICODE)
	if (ICU_FOUND)
		add_definitions(-DHAVE_MOD_STD_UNICODE)
		list(APPEND CLEVER_INCLUDE_DIRS ${ICU_INCLUDE_DIRS})
		list(APPEND CLEVER_LIBRARIES ${ICU_LIBRARIES})
	else (ICU_FOUND)
		clever_module_msg(std_unicode "libicu not found. disabling.")
		set(MOD_STD_UNICODE OFF)
	endif (ICU_FOUND)
endif (MOD_STD_UNICODE)

clever_module_msg(std_unicode ${MOD_STD_UNICODE})

# std.fcgi
if (MOD_STD_FCGI)
	if (FCGI_FOUND)
		add_definitions(-DHAVE_MOD_STD_FCGI)
		list(APPEND CLEVER_INCLUDE_DIRS ${FCGI_INCLUDE_DIRS})
		list(APPEND CLEVER_LIBRARIES ${FCGI_LIBRARIES})
	else (FCGI_FOUND)
		clever_module_msg(std_fcgi "libfcgi not found. disabling.")
		set(MOD_STD_FCGI OFF)
	endif (FCGI_FOUND)
endif (MOD_STD_FCGI)

clever_module_msg(std_fcgi ${MOD_STD_FCGI})

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

# db.mysql - TODO: Check if mysql is really available in the system
if (MOD_DB_MYSQL)
	if (MYSQLC_FOUND)
		add_definitions(-DHAVE_MOD_DB_MYSQL)
		list(APPEND CLEVER_INCLUDE_DIRS ${MYSQLC_INCLUDE_DIRS})
		list(APPEND CLEVER_LIBRARIES ${MYSQLC_LIBRARIES})
	else (MYSQLC_FOUND)
		clever_module_msg(db_mysql "libmysqlclient not found. disabling.")
		set(MOD_DB_MYSQL OFF)
	endif (MYSQLC_FOUND)
endif (MOD_DB_MYSQL)

clever_module_msg(db_mysql ${MOD_DB_MYSQL})
