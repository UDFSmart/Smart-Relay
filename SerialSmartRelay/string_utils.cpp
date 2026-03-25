/*
 *    Copyright 2025 UDFOwner
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 *
 *    More details: https://udfsoft.com/
 */

#include "string_utils.h"

#include <stdlib.h>

void sanitizePath(char* s) {
  for (; *s; s++) {
    if (*s == ' ') *s = '_';
  }
}

bool parseMessageСommandParam(const char* param, char* message, size_t messageSize, uint32_t* durationMs) {
  const char* sep = strchr(param, '|');
  if (!sep) return false;

  size_t len = sep - param;
  if (len >= messageSize) len = messageSize - 1;

  memcpy(message, param, len);
  message[len] = '\0';

  *durationMs = strtoul(sep + 1, nullptr, 10);

  return true;
}

void cleanNonAsciiSpaces(char* str) {
    for (size_t i = 0; str[i]; i++) {
        if ((unsigned char)str[i] == 0xA0) {
            str[i] = ' ';
        }
    }
}

bool tryParseInt(const char* str, int& result) {
    if (str == nullptr || *str == '\0') return false;

    char* endPtr;
    long val = strtol(str, &endPtr, 10);

    if (str == endPtr) {
        return false;
    }

    result = (int)val;
    return true;
}
