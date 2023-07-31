#include <php.h>
BEGIN_EXTERN_C()
#include <ext/date/php_date.h>
END_EXTERN_C()

#include "DateTimeInternal.h"

#undef vsnprintf

zend_result scylladb_php_to_datetime_internal(
    zval* dst, const char* format, const std::function<int64_t()>& get_timestamp) noexcept {
  zval datetime;

  if (php_date_instantiate(php_date_get_date_ce(), &datetime) == nullptr) [[unlikely]] {
    return FAILURE;
  }

  auto datetime_obj = Z_PHPDATE_P(&datetime);

  auto timestamp = std::to_string(get_timestamp());

  const char* timestampStr = timestamp.c_str();
  size_t timestampLen = timestamp.size();

  if (!php_date_initialize(datetime_obj, timestampStr, timestampLen, format, nullptr, PHP_DATE_INIT_CTOR)) [[unlikely]] {
    zend_object_std_dtor(&datetime_obj->std);
    zval_ptr_dtor(&datetime);
    return FAILURE;
  }

  ZVAL_ZVAL(dst, &datetime, 1, 1);

  return SUCCESS;
}
