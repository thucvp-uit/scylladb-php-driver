add_library(database STATIC)
add_library(ext_scylladb::database ALIAS database)
scylladb_php_library(database OFF ${PHP_SCYLLADB_OPTIMISE_FOR_CURRENT_MACHINE} ON)

target_sources(
        database
        PRIVATE
        Aggregate.cpp
        Column.cpp
        Function.cpp
        Index.cpp
        Keyspace.cpp
        MaterializedView.cpp
        Rows.cpp
        Schema.cpp
        Table.cpp

        DefaultAggregate.cpp
        DefaultColumn.cpp
        DefaultFunction.cpp
        DefaultIndex.cpp
        DefaultKeyspace.cpp
        DefaultMaterializedView.cpp
        DefaultSchema.cpp
        DefaultTable.cpp
)

