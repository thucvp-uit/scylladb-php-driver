option(CUSTOM_PHP_CONFIG "Use custom php-config" CACHE)

if (PHP_CONFIG_FOUND)
    set(PHP_CONFIG_FIND_QUIETLY TRUE)
endif ()

if (NOT ${CUSTOM_PHP_CONFIG} STREQUAL "")
    set(PHP_CONFIG_EXECUTABLE ${CUSTOM_PHP_CONFIG})
    set(PHP_CONFIG_FOUND TRUE)
endif ()

if (NOT ${PHP_CONFIG_FOUND})
    message(STATUS "Looking for php-config ${PROJECT_SOURCE_DIR}")
    find_program(
            PHP_CONFIG_EXECUTABLE php-config
            HINTS
            "${PROJECT_SOURCE_DIR}/php/8.2-debug-nts"
            "${PROJECT_SOURCE_DIR}/php/8.2-debug-zts"
            "${PROJECT_SOURCE_DIR}/php/8.2-release-zts"
            "${PROJECT_SOURCE_DIR}/php/8.2-release-nts"
            "${PROJECT_SOURCE_DIR}/php/8.1-debug-nts"
            "${PROJECT_SOURCE_DIR}/php/8.1-release-nts"
            "${PROJECT_SOURCE_DIR}/php/8.1-debug-zts"
            "${PROJECT_SOURCE_DIR}/php/8.1-release-zts"
            PATH_SUFFIXES bin
            NO_DEFAULT_PATH
            REQUIRED
    )
    if (${PHP_CONFIG_EXECUTABLE-NOTFOUND})
        message(FATAL_ERROR "php-config not found")
        set(PHP_CONFIG_FOUND FALSE)
    else ()
        message(STATUS "Found php-config: ${PHP_CONFIG_EXECUTABLE}")
        set(PHP_CONFIG_FOUND TRUE)
    endif ()
endif ()