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

#include <util/hash.h>
#include <util/types.h>

#include <ZendCPP/ZendCPP.hpp>
#include <ctime>

#include "php_driver.h"
#include "php_driver_types.h"

BEGIN_EXTERN_C()

#include <ext/date/php_date.h>

#include "Date_arginfo.h"

zend_class_entry *php_driver_date_ce = nullptr;

zend_result php_driver_date_init(zend_long seconds, zval *returnValueOrThis) {
  if (returnValueOrThis == nullptr) {
    return FAILURE;
  }

  if (Z_TYPE_P(returnValueOrThis) == IS_UNDEF) {
    zval val;
    object_init_ex(&val, php_driver_date_ce);
    ZVAL_OBJ(returnValueOrThis, Z_OBJ(val));
  }

  auto self = ZendCPP::ObjectFetch<php_driver_date>(returnValueOrThis);
  self->date = cass_date_from_epoch(seconds == -1 ? time(nullptr) : seconds);

  return SUCCESS;
}

/* {{{ Date::__construct(string) */
ZEND_METHOD(Cassandra_Date, __construct) {
  zend_long seconds = -1;

  // clang-format off
  ZEND_PARSE_PARAMETERS_START(0, 1)
    Z_PARAM_OPTIONAL
    Z_PARAM_LONG(seconds)
  ZEND_PARSE_PARAMETERS_END();
  // clang-format on

  if (php_driver_date_init(seconds, getThis()) == FAILURE) {
    zend_throw_exception_ex(php_driver_invalid_argument_exception_ce, 0,
                            "Cannot create Cassandra\\Date from invalid value");
    return;
  }
}
/* }}} */

/* {{{ Date->type() */
ZEND_METHOD(Cassandra_Date, type) {
  zval type = php_driver_type_scalar(CASS_VALUE_TYPE_DATE);
  RETURN_ZVAL(&type, 1, 1);
}
/* }}} */

/* {{{ Date->seconds() */
ZEND_METHOD(Cassandra_Date, seconds) {
  auto *self = ZendCPP::ObjectFetch<php_driver_date>(getThis());

  RETURN_LONG(cass_date_time_to_epoch(self->date, 0));
}
/* }}} */

/* {{{ Date->toDateTime() */
ZEND_METHOD(Cassandra_Date, toDateTime) {
  zval *ztime = nullptr;

  // clang-format off
  ZEND_PARSE_PARAMETERS_START(0, 1)
    Z_PARAM_OPTIONAL
    Z_PARAM_OBJECT_OF_CLASS(ztime, php_driver_time_ce)
  ZEND_PARSE_PARAMETERS_END();
  // clang-format on

  php_driver_time *time_obj = nullptr;

  if (ztime != nullptr) {
    time_obj = ZendCPP::ObjectFetch<php_driver_time>(ztime);
  }

  auto *self = ZendCPP::ObjectFetch<php_driver_date>(getThis());

  zval datetime;
  php_date_instantiate(php_date_get_date_ce(), &datetime);
  php_date_obj *datetime_obj = php_date_obj_from_obj(Z_OBJ(datetime));

  auto cassEpoch = cass_date_time_to_epoch(self->date, time_obj != nullptr ? time_obj->time : 0);

  char str[11];
  memset(str, 0, sizeof(str));
  auto str_len = snprintf(str, sizeof(str), "%ld", cassEpoch);

  php_date_initialize(datetime_obj, str, str_len, "U", nullptr, 0);
  RETVAL_ZVAL(&datetime, 0, 1);
}
/* }}} */

/* {{{ Date::fromDateTime() */
ZEND_METHOD(Cassandra_Date, fromDateTime) {
  zval *datetime;

  // clang-format off
  ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_OBJECT_OF_CLASS(datetime, php_date_get_interface_ce())
  ZEND_PARSE_PARAMETERS_END();
  // clang-format on

  zval getTimeStampResult;
  zend_call_method_with_0_params(Z_OBJ_P(datetime), php_date_get_interface_ce(), nullptr,
                                 "getTimestamp", &getTimeStampResult);

  object_init_ex(return_value, php_driver_date_ce);
  auto *self = ZendCPP::ObjectFetch<php_driver_date>(return_value);
  self->date = cass_date_from_epoch(Z_LVAL(getTimeStampResult));
  zval_ptr_dtor(&getTimeStampResult);
}
/* }}} */

/* {{{ Date->__toString() */
ZEND_METHOD(Cassandra_Date, __toString) {
  ZEND_PARSE_PARAMETERS_NONE();

  auto *self = ZendCPP::ObjectFetch<php_driver_date>(getThis());

  char *ret = nullptr;
  spprintf(&ret, 0, PHP_DRIVER_NAMESPACE "\\Date(seconds=%ld)",
           cass_date_time_to_epoch(self->date, 0));
  RETVAL_STRING(ret);
  efree(ret);
}
/* }}} */

static php_driver_value_handlers php_driver_date_handlers;

static HashTable *php_driver_date_gc(zend_object *object, zval **table, int *n) {
  *table = nullptr;
  *n = 0;
  return zend_std_get_properties(object);
}

static HashTable *php_driver_date_properties(zend_object *object) {
  HashTable *props = zend_std_get_properties(object);

  auto type = php_driver_type_scalar(CASS_VALUE_TYPE_DATE);
  zend_hash_str_update(props, ZEND_STRL("type"), &type);

  zval seconds;
  auto self = ZendCPP::ObjectFetch<php_driver_date>(object);
  ZVAL_LONG(&seconds, cass_date_time_to_epoch(self->date, 0));
  zend_hash_str_update(props, ZEND_STRL("seconds"), &seconds);

  return props;
}

static int php_driver_date_compare(zval *obj1, zval *obj2) {
  ZEND_COMPARE_OBJECTS_FALLBACK(obj1, obj2)

  if (Z_OBJCE_P(obj1) != Z_OBJCE_P(obj2)) return 1; /* different classes */

  auto date1 = ZendCPP::ObjectFetch<php_driver_date>(obj1);
  auto date2 = ZendCPP::ObjectFetch<php_driver_date>(obj2);

  return PHP_DRIVER_COMPARE(date1->date, date2->date);
}

static unsigned php_driver_date_hash_value(zval *obj) {
  auto self = ZendCPP::ObjectFetch<php_driver_date>(obj);
  return 31 * 17 + self->date;
}

static zend_object *php_driver_date_new(zend_class_entry *ce) {
  auto *self = ZendCPP::Allocate<php_driver_date>(ce, &php_driver_date_handlers);
  self->date = 0;
  return &self->zval;
}

void php_driver_define_Date() {
  php_driver_date_ce = register_class_Cassandra_Date(php_driver_value_ce);
  php_driver_date_ce->create_object = php_driver_date_new;

  ZendCPP::InitHandlers(&php_driver_date_handlers);
  php_driver_date_handlers.std.get_properties = php_driver_date_properties;
  php_driver_date_handlers.std.get_gc = php_driver_date_gc;
  php_driver_date_handlers.std.compare = php_driver_date_compare;
  php_driver_date_handlers.hash_value = php_driver_date_hash_value;
  php_driver_date_handlers.std.offset = XtOffsetOf(php_driver_date, zval);
}

END_EXTERN_C()
