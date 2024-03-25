include(CheckIPOSupported)
include(CheckCXXCompilerFlag)
include(CheckCCompilerFlag)

function(scylladb_php_target_debug_symbols target)
    target_compile_options(${target} PRIVATE -g -ggdb -g3 -gdwarf-4 -Wpedantic)
endfunction()

function(scylladb_php_target_optimization_flags target native_arch lto)
    check_ipo_supported(RESULT LTO_SUPPORTED)
    if (LTO_SUPPORTED AND lto)
        message(STATUS "LTO is supported and enabled")
        set_property(TARGET ${target} PROPERTY INTERPROCEDURAL_OPTIMIZATION ON)
    endif ()

    # target_compile_options(${target} PRIVATE -msse2 -msse3 -msse4.1 -msse4.2)

    if (native_arch)
        message(WARNING "Be careful when using `-march=native`, it may cause problems when running on different CPUs")
        check_cxx_compiler_flag(-march=native SUPPORT_MARCH_NATIVE)
        if (SUPPORT_MARCH_NATIVE)
            target_compile_options(${target} PRIVATE -march=native)
        else ()
            message(WARNING "Compiler does not support `-march=native`")
        endif ()
    endif ()
endfunction()

function(scylladb_php_target_optimize target native_arch lto)
    if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
        target_compile_options(${target} PRIVATE -O0)
        scylladb_php_target_debug_symbols(${target})
    endif ()

    if (${CMAKE_BUILD_TYPE} MATCHES "RelWithInfo")
        target_compile_options(${target} PRIVATE -O2)
        scylladb_php_target_debug_symbols(${target})
        scylladb_php_target_optimization_flags(${target} ${native_arch} ${lto})
    endif ()

    if (${CMAKE_BUILD_TYPE} MATCHES "Release")
        target_compile_options(${target} PRIVATE -O3)
        scylladb_php_target_optimization_flags(${target} ${native_arch} ${lto})
    endif ()
endfunction()
