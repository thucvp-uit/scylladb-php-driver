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

extern PHP_SCYLLADB_API zend_class_entry *php_scylladb_date_ce;

PHP_SCYLLADB_API php_scylladb_date *php_scylladb_date_instantiate(zval *object);
PHP_SCYLLADB_API zend_result php_scylladb_date_initialize(php_scylladb_date *object,
                                                          zend_string *secondsStr = nullptr,
                                                          zend_long seconds = -1);

zend_always_inline php_scylladb_date *php_scylladb_date_from_obj(zend_object *obj) {
  return ZendCPP::ObjectFetch<php_scylladb_date>(obj);
}

#define Z_SCYLLADB_DATE_P(zv) php_scylladb_date_from_obj(Z_OBJ_P((zv)))
#define Z_SCYLLADB_DATE(zv) php_scylladb_date_from_obj(Z_OBJ((zv)))

END_EXTERN_C()