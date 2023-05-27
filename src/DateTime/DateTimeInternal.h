#pragma once

#include <php.h>

BEGIN_EXTERN_C()
void php_driver_define_Time();
void php_driver_define_Date();
void php_driver_define_Timestamp();
void php_driver_define_Timeuuid();

#include <ext/date/php_date.h>

END_EXTERN_C()

#include <ZendCPP/ZendCPP.hpp>
#include <functional>

inline zend_result php_scylladb_to_datetime_internal(
    zval* dst, const std::function<int64_t()>& get_timestamp) {
  zval datetime;

  if (php_date_instantiate(php_date_get_date_ce(), &datetime) == nullptr) {
    return FAILURE;
  }

  auto datetime_obj = Z_PHPDATE_P(&datetime);

  char str[32];
  memset(str, 0, sizeof(str));
  int str_len = snprintf(str, str_len - 1, "%" PRId64, get_timestamp());

  if (str_len == -1) {
    return FAILURE;
  }

  if (!php_date_initialize(datetime_obj, str, str_len, "U", nullptr, 0)) {
    return FAILURE;
  }

  ZVAL_ZVAL(dst, &datetime, 1, 1);

  return SUCCESS;
}