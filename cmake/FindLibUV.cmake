if (PHP_SCYLLADB_LIBUV_FROM_SRC)

    if (PHP_SCYLLADB_LIBUV_STATIC)
        set(LIBUV_BUILD_SHARED OFF)
    else ()
        set(LIBUV_BUILD_SHARED ON)
    endif ()

    CPMAddPackage(
            NAME libuv
            VERSION 1.44.2
            URL https://github.com/libuv/libuv/tarball/v1.44.2
            URL_HASH MD5=3e22e24d53aab67252907dfa004a6b53
            OPTIONS
            "BUILD_TESTING OFF"
            "BUILD_BENCHMARKS OFF"
            "LIBUV_BUILD_SHARED ${LIBUV_BUILD_SHARED}"
            "CMAKE_C_FLAGS ${CMAKE_C_FLAGS} -fPIC"
            "CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -fPIC"
    )

    set(LIBUV_ROOT_DIR ${libuv_BINARY_DIR})

    if (PHP_SCYLLADB_LIBUV_STATIC)
        set(LIBUV_LIBRARY "${libuv_BINARY_DIR}/libuv_a.a")
    else ()
        set(LIBUV_LIBRARY "${libuv_BINARY_DIR}/libuv.so")
    endif ()
else ()

endif ()