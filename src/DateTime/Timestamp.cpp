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

#include "php_driver.h"
#include "php_driver_types.h"

BEGIN_EXTERN_C()
#include <ext/date/php_date.h>

zend_class_entry *php_driver_timestamp_ce = nullptr;

void php_driver_timestamp_init(INTERNAL_FUNCTION_PARAMETERS) {
  cass_int64_t seconds = 0;
  cass_int64_t microseconds = 0;
  php_driver_timestamp *self;
  cass_int64_t value = 0;

  if (zend_parse_parameters(ZEND_NUM_ARGS(), "|ll", &seconds, &microseconds) == FAILURE) {
    return;
  }

  if (ZEND_NUM_ARGS() == 0) {
    struct timeval time {};
    gettimeofday(&time, nullptr);
    seconds = time.tv_sec;
    microseconds = (time.tv_usec / 1000) * 1000;
  }

  value += microseconds / 1000;
  value += (seconds * 1000);

  if (getThis() && instanceof_function(Z_OBJCE_P(getThis()), php_driver_timestamp_ce)) {
    self = PHP_DRIVER_GET_TIMESTAMP(getThis());
  } else {
    object_init_ex(return_value, php_driver_timestamp_ce);
    self = PHP_DRIVER_GET_TIMESTAMP(return_value);
  }

  self->timestamp = value;
}


PHP_METHOD(Timestamp, type) {
  php5to7_zval type = php_driver_type_scalar(CASS_VALUE_TYPE_TIMESTAMP);
  RETURN_ZVAL(&type, 1, 1);
}

PHP_METHOD(Timestamp, time) {
  php_driver_timestamp *self = PHP_DRIVER_GET_TIMESTAMP(getThis());

  RETURN_LONG(self->timestamp / 1000);
}

PHP_METHOD(Timestamp, microtime) {
  zend_bool get_as_float = false;
  php_driver_timestamp *self;
  char *ret = nullptr;
  long sec = -1;
  double usec = 0.0f;

  // clang-format off
  ZEND_PARSE_PARAMETERS_START(0, 1)
    Z_PARAM_OPTIONAL
    Z_PARAM_BOOL(get_as_float)
  ZEND_PARSE_PARAMETERS_END();
  // clang-format on

  self = PHP_DRIVER_GET_TIMESTAMP(getThis());

  if (get_as_float) {
    RETURN_DOUBLE((double)self->timestamp / 1000.00);
  }

  sec = (long)(self->timestamp / 1000);
  usec = (double)((self->timestamp - (sec * 1000)) / 1000.00);

  spprintf(&ret, 0, "%.8F %ld", usec, sec);

  PHP5TO7_RETVAL_STRING(ret);
  efree(ret);
}
PHP_METHOD(Timestamp, toDateTime) {
  php_driver_timestamp *self;
  zval datetime_object;
  zval *datetime = &datetime_object;
  php_date_obj *datetime_obj;
  char *str;
  int str_len;

  if (zend_parse_parameters_none() == FAILURE) {
    return;
  }

  self = PHP_DRIVER_GET_TIMESTAMP(getThis());

  PHP5TO7_ZVAL_MAYBE_MAKE(datetime);
  php_date_instantiate(php_date_get_date_ce(), datetime);

  datetime_obj = php_date_obj_from_obj(Z_OBJ_P(datetime));
  str_len = spprintf(&str, 0, "@%ld", (long)(self->timestamp / 1000));
  php_date_initialize(datetime_obj, str, str_len, nullptr, nullptr, 0);
  efree(str);

  RETVAL_ZVAL(datetime, 0, 1);
}
/* }}} */

/* {{{ Timestamp::__toString() */
PHP_METHOD(Timestamp, __toString) {
  char *ret = nullptr;

  ZEND_PARSE_PARAMETERS_NONE();

  php_driver_timestamp *self = PHP_DRIVER_GET_TIMESTAMP(getThis());

  spprintf(&ret, 0, "%lld", (long long int)self->timestamp);
  PHP5TO7_RETVAL_STRING(ret);
  efree(ret);
}
/* }}} */

ZEND_BEGIN_ARG_INFO_EX(arginfo__construct, 0, ZEND_RETURN_VALUE, 0)
ZEND_ARG_INFO(0, seconds)
ZEND_ARG_INFO(0, microseconds)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_microtime, 0, ZEND_RETURN_VALUE, 0)
ZEND_ARG_INFO(0, get_as_float)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_none, 0, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 80200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tostring, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()
#else
#define arginfo_tostring arginfo_none
#endif

static zend_function_entry php_driver_timestamp_methods[] = {
    PHP_ME(Timestamp, __construct, arginfo__construct, ZEND_ACC_CTOR | ZEND_ACC_PUBLIC)
        PHP_ME(Timestamp, type, arginfo_none, ZEND_ACC_PUBLIC)
            PHP_ME(Timestamp, time, arginfo_none, ZEND_ACC_PUBLIC)
                PHP_ME(Timestamp, microtime, arginfo_microtime, ZEND_ACC_PUBLIC)
                    PHP_ME(Timestamp, toDateTime, arginfo_none, ZEND_ACC_PUBLIC) PHP_ME(
                        Timestamp, __toString, arginfo_tostring, ZEND_ACC_PUBLIC) PHP_FE_END};

static php_driver_value_handlers php_driver_timestamp_handlers;

static HashTable *php_driver_timestamp_gc(zend_object *object, zval **table, int *n) {
  *table = nullptr;
  *n = 0;
  return zend_std_get_properties(object);
}
static HashTable *php_driver_timestamp_properties(zend_object *object) {
  php5to7_zval type;
  php5to7_zval seconds;
  php5to7_zval microseconds;

  php_driver_timestamp *self = PHP5TO7_ZEND_OBJECT_GET(timestamp, object);
  HashTable *props = zend_std_get_properties(object);

  long sec = (long)(self->timestamp / 1000);
  long usec = (long)((self->timestamp - (sec * 1000)) * 1000);

  type = php_driver_type_scalar(CASS_VALUE_TYPE_TIMESTAMP);
  PHP5TO7_ZEND_HASH_UPDATE(props, "type", sizeof("type"), &type, sizeof(zval));

  ZVAL_LONG(&seconds, sec);
  PHP5TO7_ZEND_HASH_UPDATE(props, "seconds", sizeof("seconds"), &seconds, sizeof(zval));

  ZVAL_LONG(&microseconds, usec);
  PHP5TO7_ZEND_HASH_UPDATE(props, "microseconds", sizeof("microseconds"), &microseconds,
                           sizeof(zval));

  return props;
}

static int php_driver_timestamp_compare(zval *obj1, zval *obj2) {
  ZEND_COMPARE_OBJECTS_FALLBACK(obj1, obj2);

  php_driver_timestamp *timestamp1 = nullptr;
  php_driver_timestamp *timestamp2 = nullptr;
  if (Z_OBJCE_P(obj1) != Z_OBJCE_P(obj2)) return 1; /* different classes */

  timestamp1 = PHP_DRIVER_GET_TIMESTAMP(obj1);
  timestamp2 = PHP_DRIVER_GET_TIMESTAMP(obj2);

  return PHP_DRIVER_COMPARE(timestamp1->timestamp, timestamp2->timestamp);
}

static unsigned php_driver_timestamp_hash_value(zval *obj) {
  php_driver_timestamp *self = PHP_DRIVER_GET_TIMESTAMP(obj);
  return php_driver_bigint_hash(self->timestamp);
}

static void php_driver_timestamp_free(php5to7_zend_object_free *object) {
  php_driver_timestamp *self = PHP5TO7_ZEND_OBJECT_GET(timestamp, object);
  zend_object_std_dtor(&self->zval);
}

static php5to7_zend_object php_driver_timestamp_new(zend_class_entry *ce) {
  auto *self = PHP5TO7_ZEND_OBJECT_ECALLOC(timestamp, ce);

  PHP5TO7_ZEND_OBJECT_INIT(timestamp, self, ce);
}

void php_driver_define_Timestamp() {
  zend_class_entry ce;

  INIT_CLASS_ENTRY(ce, PHP_DRIVER_NAMESPACE "\\Timestamp", php_driver_timestamp_methods)

  php_driver_timestamp_ce = zend_register_internal_class(&ce);
  zend_class_implements(php_driver_timestamp_ce, 1, php_driver_value_ce);
  memcpy(&php_driver_timestamp_handlers, zend_get_std_object_handlers(),
         sizeof(zend_object_handlers));
  php_driver_timestamp_handlers.std.get_properties = php_driver_timestamp_properties;
  php_driver_timestamp_handlers.std.get_gc = php_driver_timestamp_gc;
  php_driver_timestamp_handlers.std.compare = php_driver_timestamp_compare;
  php_driver_timestamp_ce->ce_flags |= PHP5TO7_ZEND_ACC_FINAL;
  php_driver_timestamp_ce->create_object = php_driver_timestamp_new;

  php_driver_timestamp_handlers.hash_value = php_driver_timestamp_hash_value;
  php_driver_timestamp_handlers.std.clone_obj = nullptr;
}
END_EXTERN_C()