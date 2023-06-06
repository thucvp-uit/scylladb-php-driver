add_library(zend STATIC Zend.cpp)
scylladb_php_library(zend OFF ${PHP_SCYLLADB_OPTIMISE_FOR_CURRENT_MACHINE} ON)
