/*
 *    Copyright 2026 UDFOwner
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

#define USER_DEBUG_LEVEL 0  // DEBUG LEVEL: None

#include <UFLogger.h>

#include "config.h"

#include "network_utils.h"

#include "commands.h"
#include "command_executor.h"

void setup() {

  network_utils_SetupNetwork();
  yield();

  commands_setup();
  yield();

  commands_setRelayOn(1); // We send a relay start for one second - status: connected to the access point!

  delay(1000);
  yield();

  commands_setRelayOff(1);
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - lastPoll >= pollInterval) {
    lastPoll = currentMillis;
    pollServer();
  }
}

void pollServer() {
  if (WiFi.status() != WL_CONNECTED) {
    log_i("Reconnecting WiFi...");

    WiFi.reconnect();
    return;
  }

  const char* collectHeaders[] = {
    X_CMD,
    X_CMD_PARAM,
    X_POLL_INTERVAL
  };

  processHttpRequest(GET_COMMAND_URL, "GET", nullptr, nullptr, 0, collectHeaders, 3, 15000, [](int code, const HttpHeader* headers, size_t count) {
    log_i("HTTPS Response code: %u", code);

    switch (code) {
      case HTTP_CODE_NO_CONTENT:
        command_executor_handleCommandRequest(headers, count, network_utils_SendCommandResult);
        break;
      case HTTP_CODE_NOT_FOUND:
        log_i("No command");
        break;
      case HTTP_CODE_FORBIDDEN:
        log_e("Access Forbidden! DEVICE_ID not found or API_KEY not valid");

        commands_setRelayOn("1", nullptr);
        delay(3000);
        yield();

        commands_setRelayOff("1", nullptr);

        break;
      default:
        log_e("Unexpected code: %d", code);
    }
  });
}
