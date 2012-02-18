
add_library(modules.std.ffi STATIC
	ffi.cc
)

set_target_properties(modules.std.ffi
	PROPERTIES
	COMPILE_FLAGS "${FFI_CFLAGS}"
	#STATIC_LIBRARY_FLAGS "${FFI_LDFLAGS}"
)

