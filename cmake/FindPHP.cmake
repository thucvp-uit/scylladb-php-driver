if (NOT PHP_CONFIG_FOUND)
    message(FATAL_ERROR "php-config is required")
endif ()

execute_process(COMMAND ${PHP_CONFIG_EXECUTABLE} --prefix OUTPUT_VARIABLE PHP_LIB_PREFIX OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND ${PHP_CONFIG_EXECUTABLE} --includes OUTPUT_VARIABLE PHP_INCLUDES OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND ${PHP_CONFIG_EXECUTABLE} --libs OUTPUT_VARIABLE PHP_LIBS OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND ${PHP_CONFIG_EXECUTABLE} --version OUTPUT_VARIABLE PHP_VERSION OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND ${PHP_CONFIG_EXECUTABLE} --vernum OUTPUT_VARIABLE ZEND_API OUTPUT_STRIP_TRAILING_WHITESPACE)
#execute_process(COMMAND ${PHP_CONFIG_EXECUTABLE} --extension-dir OUTPUT_VARIABLE PHP_EXTENSION_DIR OUTPUT_STRIP_TRAILING_WHITESPACE)


find_library(PHP_LIB NAMES php libphp HINTS ${PHP_LIB_PREFIX} ${PHP_LIB_PREFIX}/lib ${PHP_LIB_PREFIX}/lib64)
if (PHP_LIB)
    get_filename_component(PHP_LIB_DIR ${PHP_LIB} DIRECTORY)
    string(REGEX REPLACE "-I" "" PHP_INCLUDES "${PHP_INCLUDES} ")
    string(REGEX REPLACE " " ";" PHP_INCLUDES " ${PHP_INCLUDES} ")
    set(PHP_LDFLAGS " -L${PHP_LIB_DIR} ${PHP_LIBS} ")
    set(PHP_FOUND ON)
endif ()

if (NOT PHP_FOUND)
    message(
            FATAL_ERROR " Could not find libphp. "
            " Ensure PHP >=8.1.0 development libraries are installed and compiled with `--enable-embed=static`. "
            " Ensure `php-config` is in `PATH`. "
    )
else ()
    message(STATUS " PHP Version ${PHP_VERSION} ")
    set(PHP_INCLUDES ${PHP_INCLUDES})
    set(PHP_LDFLAGS ${PHP_LDFLAGS})
    set(PHP_LIB ${PHP_LIB})
    set(PHP_VERSION ${PHP_VERSION})
    set(ZEND_API ${ZEND_API})
    set(PHP_EXTENSION_DIR ${PHP_EXTENSION_DIR})
endif ()
