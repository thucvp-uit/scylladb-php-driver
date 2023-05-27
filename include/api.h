#pragma once


#if defined(__GNUC__) && __GNUC__ >= 4
#define PHP_SCYLLADB_API __attribute__((visibility("default")))
#else
#define PHP_SCYLLADB_API
#endif