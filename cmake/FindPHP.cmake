function(scylladb_php_find_php php_config)
    if (${php_config} STREQUAL "")
        message(FATAL_ERROR "php-config is required")
    endif ()

    find_package(PkgConfig)
    if (PKG_CONFIG_FOUND)
        pkg_search_module(PHP php)
    endif ()

    execute_process(COMMAND ${php_config} --prefix OUTPUT_VARIABLE PHP_LIB_PREFIX OUTPUT_STRIP_TRAILING_WHITESPACE)
    execute_process(COMMAND ${php_config} --includes OUTPUT_VARIABLE PHP_INCLUDES OUTPUT_STRIP_TRAILING_WHITESPACE)
    execute_process(COMMAND ${php_config} --libs OUTPUT_VARIABLE PHP_LIBS OUTPUT_STRIP_TRAILING_WHITESPACE)
    execute_process(COMMAND ${php_config} --version OUTPUT_VARIABLE PHP_VERSION OUTPUT_STRIP_TRAILING_WHITESPACE)
    execute_process(COMMAND ${php_config} --vernum OUTPUT_VARIABLE ZEND_API OUTPUT_STRIP_TRAILING_WHITESPACE)

    find_library(PHP_LIB NAMES php libphp HINTS ${PHP_LIB_PREFIX} ${PHP_LIB_PREFIX}/lib ${PHP_LIB_PREFIX}/lib64)
    if (PHP_LIB)
        get_filename_component(PHP_LIB_DIR ${PHP_LIB} DIRECTORY)
        string(REGEX REPLACE "-I" "" PHP_INCLUDES "${PHP_INCLUDES}")
        string(REGEX REPLACE " " ";" PHP_INCLUDES "${PHP_INCLUDES}")
        set(PHP_LDFLAGS "-L${PHP_LIB_DIR} ${PHP_LIBS}")
        set(PHP_FOUND ON)
    endif ()

    if (NOT PHP_FOUND)
        message(
                FATAL_ERROR "Could not find libphp. "
                "Ensure PHP >=8.1.0 development libraries are installed and compiled with `--enable-embed=static`. "
                "Ensure `php-config` is in `PATH`. "
        )
    else ()
        message(STATUS "PHP Version ${PHP_VERSION}")
        set(PHP_INCLUDES ${PHP_INCLUDES} PARENT_SCOPE)
        set(PHP_LDFLAGS ${PHP_LDFLAGS} PARENT_SCOPE)
        set(PHP_LIB ${PHP_LIB} PARENT_SCOPE)
        set(PHP_VERSION ${PHP_VERSION} PARENT_SCOPE)
        set(ZEND_API ${ZEND_API} PARENT_SCOPE)
    endif ()
endfunction()
