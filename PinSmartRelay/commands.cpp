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

#include "commands.h"
#include "config.h"

#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>

#include <PinRelayController.h>

#define COMMAND_RESULT_SIZE 128

PinRelayController relay(relayPins, RELAY_CHANNELS_COUNT);

void commands_setup() {
  relay.begin();
}

// =======================
// Private Commands
// =======================

static void cmdReboot(char* result, size_t resultSize, const char* param, CommandResultCallback callback) {
  if (callback) {
    callback(COMMAND_REBOOT, param, "Successful");
  }

  delay(300);

  ESP.restart();
}

static void cmdHardReset(char* result, size_t resultSize, const char* param, CommandResultCallback callback) {
  if (callback) {
    callback(COMMAND_HARDRESET, param, "Successful");
  }

  yield();
  delay(500);

  WiFi.disconnect(true);
  delay(200);
  ESP.eraseConfig();
  delay(300);

  ESP.restart();
}

// =======================
// Public Commands
// =======================
void commands_setReboot(const char* param, CommandResultCallback callback) {
  char result[COMMAND_RESULT_SIZE] = { 0 };
  cmdReboot(result, COMMAND_RESULT_SIZE, param, callback);
}

void commands_setHardReset(const char* param, CommandResultCallback callback) {
  char result[COMMAND_RESULT_SIZE] = { 0 };
  cmdHardReset(result, COMMAND_RESULT_SIZE, param, callback);
}

void commands_setRelayOn(const char* param, CommandResultCallback callback) {
  int channel = (param != NULL) ? atoi(param) : 0;

  if (channel == 0) {
    uint8_t count = relay.getChannelsCount();
    for (uint8_t i = 0; i < count; i++) {
      relay.setOn(i);
    }
  } else {
    relay.setOn(channel);
  }

  if (callback) {
    callback(COMMAND_RELAY_ON, param, "Successful");
  }
}

void commands_setRelayOff(const char* param, CommandResultCallback callback) {
  uint8_t channel = (param != NULL) ? atoi(param) : 0;

  if (channel == 0) {
    int count = relay.getChannelsCount();
    for (uint8_t i = 0; i < count; i++) {
      relay.setOff(i);
    }
  } else {
    relay.setOff(channel);
  }

  if (callback) {
    callback(COMMAND_RELAY_OFF, param, "Successful");
  }
}

void commands_setRelayOn(int channel) {
  relay.setOn(channel);
}

void commands_setRelayOff(int channel) {
  relay.setOff(channel);
}
