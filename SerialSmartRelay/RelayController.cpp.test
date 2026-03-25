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

#include "RelayController.h"

RelayController::RelayController(uint8_t rxPin, uint8_t txPin)
  : _serial(rxPin, txPin), isSerialReady(false) {}

void RelayController::begin() {
  _serial.begin(115200);
  delay(200);
}

void RelayController::relayOn(uint8_t channel) {
  send(channel, true);
  delay(350);
}

void RelayController::relayOff(uint8_t channel) {
  send(channel, false);
  delay(350);
}

void RelayController::send(uint8_t relay, bool state) {
  byte cmd[4];

  cmd[0] = 0xA0;
  cmd[1] = relay;
  cmd[2] = state ? 0x01 : 0x00;
  cmd[3] = cmd[0] + cmd[1] + cmd[2];

  _serial.write(cmd, 4);
}
