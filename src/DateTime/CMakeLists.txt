add_library(datetime STATIC)
add_library(ext_scylladb::datetime ALIAS datetime)
target_sources(
        datetime
        PRIVATE
        DateTime.cpp
        Time.cpp
        Timestamp.cpp
        Timeuuid.cpp
)

find_package(PHP REQUIRED)
find_package(Sanitizers REQUIRED)

set_target_properties(datetime PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_include_directories(
        datetime
        PUBLIC
        ${PHP_INCLUDES}
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_BINARY_DIR}
        ${libscylladb_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}
)

if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    target_compile_definitions(datetime PRIVATE -DDEBUG)
elseif (${CMAKE_BUILD_TYPE} STREQUAL "RelWithDebInfo" OR ${CMAKE_BUILD_TYPE} STREQUAL "Release")
    target_compile_definitions(datetime PRIVATE -DRELEASE)
endif ()

if (PHP_SCYLLADB_ENABLE_SANITIZERS)
    add_sanitize_undefined(datetime)
    add_sanitize_address(datetime)
endif ()

