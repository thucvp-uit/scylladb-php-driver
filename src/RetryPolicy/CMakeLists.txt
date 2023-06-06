add_library(retry_policy STATIC)
add_library(ext_scylladb::retry_policy ALIAS retry_policy)
scylladb_php_library(retry_policy OFF ${PHP_SCYLLADB_OPTIMISE_FOR_CURRENT_MACHINE} ON)

target_sources(
        retry_policy
        PRIVATE
        DefaultPolicy.cpp
        DowngradingConsistency.cpp
        Logging.cpp
        Fallthrough.cpp
)