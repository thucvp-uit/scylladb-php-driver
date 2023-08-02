add_library(timestamp_generator STATIC)
add_library(ext_scylladb::timestamp_generator ALIAS timestamp_generator)
scylladb_php_library(timestamp_generator OFF ${PHP_SCYLLADB_OPTIMISE_FOR_CURRENT_MACHINE} ON)

target_sources(
        timestamp_generator
        PRIVATE
        Monotonic.cpp
        ServerSide.cpp
        TimestampGenerator.cpp
)