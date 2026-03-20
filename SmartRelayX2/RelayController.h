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
 
#pragma once
#include <Arduino.h>
#include <SoftwareSerial.h>

class RelayController {
public:
    RelayController(uint8_t rxPin, uint8_t txPin);
    void begin();
    void relayOn(uint8_t channel);
    void relayOff(uint8_t channel);

private:
    SoftwareSerial _serial;
    bool isSerialReady;
    void send(uint8_t relay, bool state);
};
