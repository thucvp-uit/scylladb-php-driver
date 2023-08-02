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

#include <php_driver.h>
#include <php_driver_types.h>

#include <ZendCPP/ZendCPP.hpp>

BEGIN_EXTERN_C()

#include "DowngradingConsistency_arginfo.h"

zend_class_entry *php_driver_retry_policy_downgrading_consistency_ce = nullptr;

static zend_object_handlers php_driver_retry_policy_downgrading_consistency_handlers;

static void php_driver_retry_policy_downgrading_consistency_free(zend_object *object)
{
  auto *self = ZendCPP::ObjectFetch<php_driver_retry_policy>(object);
  cass_retry_policy_free(self->policy);
}

static zend_object* php_driver_retry_policy_downgrading_consistency_new(zend_class_entry *ce) {
  auto *self = ZendCPP::Allocate<php_driver_retry_policy>(ce, &php_driver_retry_policy_downgrading_consistency_handlers);
  self->policy = cass_retry_policy_downgrading_consistency_new();

  zend_object_std_init(&self->zendObject, ce);
  return &self->zendObject;
}

void php_driver_define_RetryPolicyDowngradingConsistency(zend_class_entry* retry_policy_interface) {
  php_driver_retry_policy_downgrading_consistency_ce = register_class_Cassandra_RetryPolicy_DowngradingConsistency(retry_policy_interface);
  php_driver_retry_policy_downgrading_consistency_ce->create_object = php_driver_retry_policy_downgrading_consistency_new;

  ZendCPP::InitHandlers<php_driver_retry_policy>(&php_driver_retry_policy_downgrading_consistency_handlers);
  php_driver_retry_policy_downgrading_consistency_handlers.free_obj = php_driver_retry_policy_downgrading_consistency_free;
}
END_EXTERN_C()
