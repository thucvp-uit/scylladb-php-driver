include(CheckIPOSupported)
include(CheckCXXCompilerFlag)
include(CheckCCompilerFlag)

find_package(PHPConfig REQUIRED)
find_package(PHP REQUIRED)
find_package(Sanitizers REQUIRED)

function(cxxphp_lib target enable_sanitizers native_arch)
    add_library(${target} STATIC)
    add_library(ext_scylladb::${target} ALIAS ${target})

    target_include_directories(
            ${target}
            PUBLIC
            ${PHP_INCLUDES}
            ${PROJECT_SOURCE_DIR}/include
            ${PROJECT_BINARY_DIR}
            ${libscylladb_SOURCE_DIR}/include
            ${PROJECT_SOURCE_DIR}
    )

    target_compile_features(
            ${target}
            PUBLIC
            cxx_std_20
            c_std_17
    )
    target_compile_options(
            ${target} PRIVATE
            -Wall -Wextra -Wno-long-long -Wno-deprecated-declarations -Wno-unused-parameter -Wno-unused-result -Wno-variadic-macros -Wno-extra-semi -pthread -Wimplicit-function-declaration
    )

    if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
        target_compile_definitions(${target} PRIVATE -DDEBUG)
        target_compile_options(${target} PRIVATE -g3 -gdwarf-4)
    elseif (${CMAKE_BUILD_TYPE} STREQUAL "RelWithDebInfo" OR ${CMAKE_BUILD_TYPE} STREQUAL "Release")
        target_compile_definitions(${target} PRIVATE -DRELEASE)
    endif ()

    if (enable_sanitizers)
        target_compile_options(${target} PRIVATE -fno-inline -fno-omit-frame-pointer)
        add_sanitizers(${target})
    endif ()

    scylladb_php_target_optimize(${target} ${native_arch})
endfunction()