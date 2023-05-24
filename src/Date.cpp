/**
 * Copyright 2015-2017 DataStax, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <ctime>

#include "php_driver.h"
#include "php_driver_types.h"
#include "util/hash.h"
#include "util/types.h"
BEGIN_EXTERN_C()

#include <ext/date/php_date.h>

zend_class_entry *php_driver_date_ce = nullptr;

void php_driver_date_init(INTERNAL_FUNCTION_PARAMETERS) {
  zend_long seconds = 0;
  bool isNull = false;
  php_driver_date *self;

  ZEND_PARSE_PARAMETERS_START(0, 1)
  Z_PARAM_OPTIONAL
  Z_PARAM_LONG_OR_NULL(seconds, isNull)
  ZEND_PARSE_PARAMETERS_END();

  if (zend_parse_parameters(ZEND_NUM_ARGS(), "|z", &seconds) == FAILURE) {
    return;
  }

  if (getThis() &&
      instanceof_function(Z_OBJCE_P(getThis()), php_driver_date_ce)) {
    self = PHP_DRIVER_GET_DATE(getThis());
  } else {
    object_init_ex(return_value, php_driver_date_ce);
    self = PHP_DRIVER_GET_DATE(return_value);
  }

  if (isNull) {
    self->date = cass_date_from_epoch(time(nullptr));
  } else {
    self->date = cass_date_from_epoch(seconds);
  }
}

/* {{{ Date::__construct(string) */
PHP_METHOD(Date, __construct) {
  php_driver_date_init(INTERNAL_FUNCTION_PARAM_PASSTHRU);
}
/* }}} */

/* {{{ Date::type() */
PHP_METHOD(Date, type) {
  php5to7_zval type = php_driver_type_scalar(CASS_VALUE_TYPE_DATE);
  RETURN_ZVAL(PHP5TO7_ZVAL_MAYBE_P(type), 1, 1);
}
/* }}} */

/* {{{ Date::seconds() */
PHP_METHOD(Date, seconds) {
  php_driver_date *self = PHP_DRIVER_GET_DATE(getThis());

  RETURN_LONG(cass_date_time_to_epoch(self->date, 0));
}
/* }}} */

/* {{{ Date::toDateTime() */
PHP_METHOD(Date, toDateTime) {
  php_driver_date *self;
  zval *ztime = nullptr;
  zval datetime;
  char *str;
  int str_len;

  ZEND_PARSE_PARAMETERS_START(0, 1)
  Z_PARAM_OPTIONAL
  Z_PARAM_ZVAL(ztime)
  ZEND_PARSE_PARAMETERS_END();

  php_driver_time *time_obj = nullptr;

  if (ztime != nullptr) {
    time_obj = PHP_DRIVER_GET_TIME(ztime);
  }

  self = PHP_DRIVER_GET_DATE(getThis());
  php_date_instantiate(php_date_get_date_ce(), &datetime);

  php_date_obj *datetime_obj = php_date_obj_from_obj(Z_OBJ(datetime));

  auto cassEpoch = cass_date_time_to_epoch(
      self->date, time_obj != nullptr ? time_obj->time : 0);

  str_len = spprintf(&str, 0, "%ld", cassEpoch);
  php_date_initialize(datetime_obj, str, str_len, "U", nullptr, 0);
  efree(str);
  RETVAL_ZVAL(&datetime, 0, 1);
}
/* }}} */

/* {{{ Date::fromDateTime() */
PHP_METHOD(Date, fromDateTime) {
  php_driver_date *self;
  zval *datetime;

  ZEND_PARSE_PARAMETERS_START(1, 1)
  Z_PARAM_OBJECT_OF_CLASS(datetime, php_date_get_date_ce())
  ZEND_PARSE_PARAMETERS_END();

  zval getTimeStampResult;
  zend_call_method_with_0_params(Z_OBJ_P(datetime), php_date_get_date_ce(),
                                 nullptr, "gettimestamp", &getTimeStampResult);

  if (!Z_ISUNDEF(getTimeStampResult) &&
      Z_TYPE_P(&getTimeStampResult) == IS_LONG) {
    object_init_ex(return_value, php_driver_date_ce);
    self = PHP_DRIVER_GET_DATE(return_value);
    self->date = cass_date_from_epoch(Z_LVAL(getTimeStampResult));
    zval_ptr_dtor(&getTimeStampResult);
  }
}
/* }}} */

/* {{{ Date::__toString() */
PHP_METHOD(Date, __toString) {
  ZEND_PARSE_PARAMETERS_NONE();

  php_driver_date *self = PHP_DRIVER_GET_DATE(getThis());

  char *ret = nullptr;
  spprintf(&ret, 0, PHP_DRIVER_NAMESPACE "\\Date(seconds=%lld)",
           cass_date_time_to_epoch(self->date, 0));
  RETVAL_STRING(ret);
  efree(ret);
}
/* }}} */

ZEND_BEGIN_ARG_INFO_EX(arginfo__construct, 0, ZEND_RETURN_VALUE, 0)
ZEND_ARG_INFO(0, seconds)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_time, 0, ZEND_RETURN_VALUE, 0)
PHP_DRIVER_NAMESPACE_ZEND_ARG_OBJ_INFO(0, time, Time, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_datetime, 0, ZEND_RETURN_VALUE, 1)
ZEND_ARG_OBJ_INFO(0, datetime, DateTime, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_none, 0, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 80200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tostring, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()
#else
#define arginfo_tostring arginfo_none
#endif

static zend_function_entry php_driver_date_methods[] = {
    PHP_ME(Date, __construct, arginfo__construct,
           ZEND_ACC_CTOR | ZEND_ACC_PUBLIC)
        PHP_ME(Date, type, arginfo_none, ZEND_ACC_PUBLIC)
            PHP_ME(Date, seconds, arginfo_none, ZEND_ACC_PUBLIC)
                PHP_ME(Date, toDateTime, arginfo_time, ZEND_ACC_PUBLIC) PHP_ME(
                    Date, fromDateTime, arginfo_datetime,
                    ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
                    PHP_ME(Date, __toString, arginfo_tostring, ZEND_ACC_PUBLIC)
                        PHP_FE_END};

static php_driver_value_handlers php_driver_date_handlers;

static HashTable *php_driver_date_gc(zend_object *object, php5to7_zval_gc table,
                                     int *n) {
  *table = nullptr;
  *n = 0;
  return zend_std_get_properties(object);
}

static HashTable *php_driver_date_properties(zend_object *object) {
  php5to7_zval type;
  php5to7_zval seconds;

  php_driver_date *self = PHP5TO7_ZEND_OBJECT_GET(date, object);
  HashTable *props = zend_std_get_properties(object);

  type = php_driver_type_scalar(CASS_VALUE_TYPE_DATE);
  PHP5TO7_ZEND_HASH_UPDATE(props, "type", sizeof("type"), &type, sizeof(zval));

  ZVAL_LONG(&seconds, cass_date_time_to_epoch(self->date, 0));
  PHP5TO7_ZEND_HASH_UPDATE(props, "seconds", sizeof("seconds"), &seconds,
                           sizeof(zval));

  return props;
}

static int php_driver_date_compare(zval *obj1, zval *obj2) {
  ZEND_COMPARE_OBJECTS_FALLBACK(obj1, obj2);

  if (Z_OBJCE_P(obj1) != Z_OBJCE_P(obj2)) return 1; /* different classes */

  php_driver_date *date1 = PHP_DRIVER_GET_DATE(obj1);
  php_driver_date *date2 = PHP_DRIVER_GET_DATE(obj2);

  return PHP_DRIVER_COMPARE(date1->date, date2->date);
}

static unsigned php_driver_date_hash_value(zval *obj) {
  php_driver_date *self = PHP_DRIVER_GET_DATE(obj);
  return 31 * 17 + self->date;
}

static void php_driver_date_free(php5to7_zend_object_free *object) {
  php_driver_date *self = PHP5TO7_ZEND_OBJECT_GET(date, object);
  zend_object_std_dtor(&self->zval);
}

static php5to7_zend_object php_driver_date_new(zend_class_entry *ce) {
  auto *self = PHP5TO7_ZEND_OBJECT_ECALLOC(date, ce);

  self->date = 0;

  PHP5TO7_ZEND_OBJECT_INIT(date, self, ce);
}

void php_driver_define_Date() {
  zend_class_entry ce;

  INIT_CLASS_ENTRY(ce, PHP_DRIVER_NAMESPACE "\\Date", php_driver_date_methods);
  php_driver_date_ce = zend_register_internal_class(&ce);
  zend_class_implements(php_driver_date_ce, 1, php_driver_value_ce);
  memcpy(&php_driver_date_handlers, zend_get_std_object_handlers(),
         sizeof(zend_object_handlers));
  php_driver_date_handlers.std.get_properties = php_driver_date_properties;
  php_driver_date_handlers.std.get_gc = php_driver_date_gc;
  php_driver_date_handlers.std.compare = php_driver_date_compare;
  php_driver_date_handlers.hash_value = php_driver_date_hash_value;

  php_driver_date_ce->ce_flags |= PHP5TO7_ZEND_ACC_FINAL;
  php_driver_date_ce->create_object = php_driver_date_new;
}

END_EXTERN_C()
