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

#include "command_executor.h"

#include <UFLogger.h>

#ifdef ESP32
#include <HTTPClient.h>
#else
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#endif

#include <WiFiClientSecure.h>
#include <WiFiManager.h>

#include "commands.h"

static UCommand commands[] = {
  { COMMAND_REBOOT, commands_setReboot },
  { COMMAND_HARDRESET, commands_setHardReset },
  { COMMAND_RELAY_ON, commands_setRelayOn },
  { COMMAND_RELAY_OFF, commands_setRelayOff },
};

unsigned long lastPoll = 0;

unsigned long pollInterval = DEFAULT_POLL_INTERVAL;

static CommandResultCallback globalOnResult = nullptr;

static void handleCommandResult(const char* cmd, const char* param, const char* status);

static UCommandExecutor commandExecutor(commands, sizeof(commands) / sizeof(commands[0]));

void command_executor_handleCommandRequest(const HttpHeader* headers, size_t headersCount, CommandResultCallback onResultFunc) {
  char cmd[32] = { 0 };
  char param[64] = { 0 };

  for (size_t i = 0; i < headersCount; i++) {
    const char* name = headers[i].name;

    if (strcmp(name, X_CMD) == 0) {  // if name == X_CMD
      const char* value = headers[i].value;
      strlcpy(cmd, value, sizeof(cmd));
    } else if (strcmp(name, X_CMD_PARAM) == 0) {  // if name == X_CMD_PARAM
      strlcpy(param, headers[i].value, sizeof(param));
    } else if (strcmp(name, X_POLL_INTERVAL) == 0) {  // if name == X_POLL_INTERVAL
      pollInterval = atoi(headers[i].value);
      if (pollInterval <= 1000) pollInterval = DEFAULT_POLL_INTERVAL;
    }
  }

  log_i("command: %s; Param: %s", cmd, param);
  log_i("pollInterval: %lu", pollInterval);

  globalOnResult = onResultFunc;

  commandExecutor.execute(cmd, param, handleCommandResult);
}

static void handleCommandResult(const char* cmd, const char* param, const char* status) {
  if (strcmp(cmd, COMMAND_HARDRESET) == 0) {
    log_i("Smart device: RESET!");
    Serial.flush();
  } else {
    log_i("command: %s; Param: %s; Status: %s\n", cmd, param, status);
  }

  delay(50);

  if (globalOnResult)
    globalOnResult(cmd, param, status);  // sendResult(cmd, param, status);
}
