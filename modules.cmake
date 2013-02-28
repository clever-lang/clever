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
clever_add_module(std_events     ON "enable the event module"      "")

clever_add_module(web_request    OFF "enable the request module"    "")
clever_add_module(web_session    OFF "enable the session module"    "")

clever_add_module(db_mysql       ON  "enable the mysql module"      "")
clever_add_module(db_sqlite3     ON  "enable the sqlite3 module"    "")

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
	if (PTHREAD_FOUND)
		add_definitions(-DHAVE_MOD_STD_CONCURRENT)
		clever_use_lib(PTHREAD)
	else (PTHREAD_FOUND)
		clever_module_msg(std_concurrent "Posix Threads are not present on this system")
		set(MOD_STD_CONCURRENT OFF)
	endif (PTHREAD_FOUND)
endif (MOD_STD_CONCURRENT)

clever_module_msg(std_concurrent "${MOD_STD_CONCURRENT}")

# std.events
if (MOD_STD_EVENTS)
	if (CONCURRENCY_FOUND)
		add_definitions(-DHAVE_MOD_STD_EVENTS)
	else (CONCURRENCY_FOUND)
		clever_module_msg(std_events "Posix Threads are not present on this system")
		set(MOD_STD_EVENTS OFF)
	endif (CONCURRENCY_FOUND)
endif (MOD_STD_EVENTS)

clever_module_msg(std_events "${MOD_STD_EVENTS}")

# std.regex
if (MOD_STD_REGEX)
	if (PCRECPP_FOUND)
		add_definitions(-DHAVE_MOD_STD_REGEX)
		clever_use_lib(PCRECPP)
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
		clever_use_lib(ICU)
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
		clever_use_lib(FCGI)
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
		clever_use_lib(FFI)
		list(APPEND CLEVER_LIBRARIES dl)

	else (FFI_FOUND)
		clever_module_msg(std_ffi "libffi not found. disabling.")
		set(MOD_STD_FFI OFF)
	endif (FFI_FOUND)
endif (MOD_STD_FFI)

clever_module_msg(std_ffi ${MOD_STD_FFI})

# std.rpc
if (MOD_STD_RPC)
	if (PTHREAD_FOUND AND FFI_FOUND)
		add_definitions(-DHAVE_LIBPTHREAD)
		add_definitions(-pthread -DHAVE_FFI)
		add_definitions(-DHAVE_MOD_STD_RPC)
		clever_use_lib(FFI)
		clever_use_lib(LIBPTHREAD)
		list(APPEND CLEVER_LIBRARIES dl)
	else (PTHREAD_FOUND AND FFI_FOUND)
		clever_module_msg(std_rpc "libpthread or libffi not found. disabling.")
		set(MOD_STD_RPC OFF)
	endif (PTHREAD_FOUND AND FFI_FOUND)
endif (MOD_STD_RPC)

clever_module_msg(std_rpc ${MOD_STD_RPC})


# web.request
if (MOD_WEB_REQUEST)
	if (CGICC_FOUND)
		add_definitions(-DHAVE_MOD_WEB_REQUEST)
		clever_use_lib(CGICC)
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
		clever_use_lib(CGICC)
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
		clever_use_lib(MYSQLC)
	else (MYSQLC_FOUND)
		clever_module_msg(db_mysql "libmysqlclient not found. disabling.")
		set(MOD_DB_MYSQL OFF)
	endif (MYSQLC_FOUND)
endif (MOD_DB_MYSQL)

clever_module_msg(db_mysql ${MOD_DB_MYSQL})

# db.sqlite3
if (MOD_DB_SQLITE3)
	if (SQLITE3_FOUND)
		add_definitions(-DHAVE_MOD_DB_SQLITE3)
		clever_use_lib(SQLITE3)
	else (SQLITE3_FOUND)
		clever_module_msg(db_sqlite3 "libsqlite3 not found. disabling.")
		set(MOD_DB_SQLITE3 OFF)
	endif (SQLITE3_FOUND)
endif (MOD_DB_SQLITE3)

clever_module_msg(db_sqlite3 ${MOD_DB_SQLITE3})

