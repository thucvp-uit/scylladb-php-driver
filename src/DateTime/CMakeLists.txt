add_library(datetime STATIC)
add_library(ext_scylladb::datetime ALIAS datetime)
scylladb_php_library(datetime OFF ${PHP_SCYLLADB_OPTIMISE_FOR_CURRENT_MACHINE} ON)

target_sources(
        datetime
        PRIVATE
        Date.cpp
        Time.cpp
        Timestamp.cpp
        Timeuuid.cpp
)

