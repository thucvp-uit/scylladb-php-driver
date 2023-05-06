add_library(zend STATIC Zend.cpp)
enable_language(CXX)
set_target_properties(zend PROPERTIES POSITION_INDEPENDENT_CODE ON)

find_package(PHP REQUIRED)
find_package(Sanitizers REQUIRED)

target_include_directories(zend PUBLIC ${PHP_INCLUDES})

add_subdirectory(String)
target_link_libraries(zend Zend::String)


if (PHP_SCYLLADB_ENABLE_SANITIZERS)
    add_sanitize_undefined(zend)
    add_sanitize_address(zend)
endif ()