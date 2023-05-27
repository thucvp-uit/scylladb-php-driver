#pragma once

#include <api.h>
#include <cassandra.h>
#include <php.h>

#include <ZendCPP/ZendCPP.hpp>

BEGIN_EXTERN_C()
typedef struct {
  cass_uint32_t date;
  zend_object zval;
} php_scylladb_date;

typedef struct {
  cass_int64_t time;
  zend_object zval;
} php_scylladb_time;

typedef struct {
  cass_int64_t timestamp;
  zend_object zval;
} php_scylladb_timestamp;

extern PHP_SCYLLADB_API zend_class_entry *php_scylladb_date_ce;
extern PHP_SCYLLADB_API zend_class_entry *php_driver_time_ce;

PHP_SCYLLADB_API php_scylladb_date *php_scylladb_date_instantiate(zval *object);
PHP_SCYLLADB_API zend_result php_scylladb_date_initialize(php_scylladb_date *object,
                                                          zend_string *secondsStr = nullptr,
                                                          zend_long seconds = -1);

PHP_SCYLLADB_API php_scylladb_time *php_scylladb_time_instantiate(zval *object);
PHP_SCYLLADB_API zend_result php_scylladb_time_initialize(php_scylladb_time *object,
                                                          zend_string *nanosecondsStr = nullptr,
                                                          zend_long nanoseconds = -1);

PHP_SCYLLADB_API php_scylladb_timestamp *php_scylladb_timestamp_instantiate(zval *object);
PHP_SCYLLADB_API zend_result php_scylladb_timestamp_initialize(php_scylladb_timestamp *object,
                                                               cass_int64_t seconds,
                                                               cass_int64_t microseconds);

zend_always_inline php_scylladb_date *php_scylladb_date_from_obj(zend_object *obj) {
  return ZendCPP::ObjectFetch<php_scylladb_date>(obj);
}

zend_always_inline php_scylladb_time *php_scylladb_time_from_obj(zend_object *obj) {
  return ZendCPP::ObjectFetch<php_scylladb_time>(obj);
}

zend_always_inline php_scylladb_timestamp *php_scylladb_timestamp_from_obj(zend_object *obj) {
  return ZendCPP::ObjectFetch<php_scylladb_timestamp>(obj);
}

#define Z_SCYLLADB_DATE_P(zv) php_scylladb_date_from_obj(Z_OBJ_P((zv)))
#define Z_SCYLLADB_DATE(zv) php_scylladb_date_from_obj(Z_OBJ((zv)))

#define Z_SCYLLADB_TIME_P(zv) php_scylladb_time_from_obj(Z_OBJ_P((zv)))
#define Z_SCYLLADB_TIME(zv) php_scylladb_time_from_obj(Z_OBJ((zv)))

#define Z_SCYLLADB_TIMESTAMP_P(zv) php_scylladb_timestamp_from_obj(Z_OBJ_P((zv)))
#define Z_SCYLLADB_TIMESTAMP(zv) php_scylladb_timestamp_from_obj(Z_OBJ((zv)))

END_EXTERN_C()