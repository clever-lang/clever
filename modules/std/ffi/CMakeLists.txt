
add_library(modules_std_ffi STATIC
	ffi.cc
)

set_target_properties(modules_std_ffi
	PROPERTIES
	COMPILE_FLAGS "${FFI_CFLAGS}"
	#STATIC_LIBRARY_FLAGS "${FFI_LDFLAGS}"
)

