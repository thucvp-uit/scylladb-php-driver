function(scylladb_php_find_php_config custom_path php_version php_debug php_thread_safe)
    if (NOT ${custom_path} STREQUAL "")
        if (EXISTS ${custom_path})
            message(STATUS "Found php-config: ${PHP_CONFIG_EXECUTABLE}")
            set(PHP_CONFIG_EXECUTABLE ${custom_path} PARENT_SCOPE)
            set(PHP_CONFIG_FOUND ON PARENT_SCOPE)
        else ()
            message(FATAL_ERROR "php-config not found")
            set(PHP_CONFIG_FOUND OFF PARENT_SCOPE)
        endif ()
    else ()
        if (${php_version} STREQUAL "")
            message(FATAL_ERROR "PHP version not defined: ${php_version}")
        endif ()

        set(hint "${PROJECT_SOURCE_DIR}/php/${php_version}")

        if (${php_debug})
            set(hint "${hint}-debug")
        else ()
            set(hint "${hint}-release")
        endif ()

        if (${php_thread_safe})
            set(hint "${hint}-zts")
        else ()
            set(hint "${hint}-nts")
        endif ()

        find_program(
                PHP_CONFIG_EXECUTABLE php-config
                HINTS ${hint}
                PATH_SUFFIXES bin
                NO_DEFAULT_PATH
                REQUIRED
        )
        message(STATUS "Found php-config: ${PHP_CONFIG_EXECUTABLE}")
        set(PHP_CONFIG_EXECUTABLE ${PHP_CONFIG_EXECUTABLE} PARENT_SCOPE)
        set(PHP_CONFIG_FOUND ON PARENT_SCOPE)
    endif ()
endfunction()
