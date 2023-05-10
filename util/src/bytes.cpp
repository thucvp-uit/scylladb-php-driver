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

#include "bytes.h"

#include <php.h>

static const char hex_str[] = "0123456789abcdef";

void php_driver_bytes_to_hex(const char* bin, size_t len, char** out,
                             size_t* out_len) {
  const size_t size = len * 2 + 2;
  char* value = (char*)emalloc(sizeof(char) * (size + 1));

  value[0] = '0';
  value[1] = 'x';
  value[size] = '\0';

  for (size_t i = 0; i < len; i++) {
    value[i * 2 + 2] = hex_str[(bin[i] >> 4) & 0x0F];
    value[i * 2 + 3] = hex_str[(bin[i]) & 0x0F];
  }

  *out = value;
  *out_len = (int)size;
}
