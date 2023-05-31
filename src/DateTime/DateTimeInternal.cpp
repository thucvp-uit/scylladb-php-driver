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

  if (!php_date_initialize(datetime_obj, timestamp.c_str(), timestamp.size(), format, nullptr, 0))
      [[unlikely]] {
    return FAILURE;
  }

  ZVAL_ZVAL(dst, &datetime, 1, 1);

  return SUCCESS;
}
