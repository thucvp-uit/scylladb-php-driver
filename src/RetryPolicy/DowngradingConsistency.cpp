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

#include "php_driver.h"
#include "php_driver_types.h"

BEGIN_EXTERN_C()

#include "DowngradingConsistency_arginfo.h"

zend_class_entry *php_driver_retry_policy_downgrading_consistency_ce = nullptr;

static zend_function_entry php_driver_retry_policy_downgrading_consistency_methods[] = {PHP_FE_END};

static zend_object_handlers php_driver_retry_policy_downgrading_consistency_handlers;

static void php_driver_retry_policy_downgrading_consistency_free(php5to7_zend_object_free *object) {
  php_driver_retry_policy *self = PHP5TO7_ZEND_OBJECT_GET(retry_policy, object);

  cass_retry_policy_free(self->policy);

  zend_object_std_dtor(&self->zval);
  PHP5TO7_MAYBE_EFREE(self);
}

static php5to7_zend_object php_driver_retry_policy_downgrading_consistency_new(
    zend_class_entry *ce) {
  php_driver_retry_policy *self = PHP5TO7_ZEND_OBJECT_ECALLOC(retry_policy, ce);

  self->policy = cass_retry_policy_downgrading_consistency_new();

  PHP5TO7_ZEND_OBJECT_INIT_EX(retry_policy, retry_policy_downgrading_consistency, self, ce);
}

void php_driver_define_RetryPolicyDowngradingConsistency() {
  php_driver_retry_policy_downgrading_consistency_ce = register_class_Cassandra_RetryPolicy_DowngradingConsistency(php_driver_retry_policy_downgrading_consistency_ce);
  php_driver_retry_policy_downgrading_consistency_ce->create_object = php_driver_retry_policy_downgrading_consistency_new;

  ZendCPP::InitHandlers(&php_driver_retry_policy_downgrading_consistency_handlers);
}
END_EXTERN_C()