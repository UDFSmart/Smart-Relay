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

#pragma once

#include <time.h>
#include <UCommandExecutor.h>

// COMMAND LIST
#define COMMAND_HARDRESET "HARDRESET"
#define COMMAND_REBOOT "REBOOT"

#define COMMAND_RELAY_ON "RELAY_ON"
#define COMMAND_RELAY_OFF "RELAY_OFF"
// End COMMAND LIST

void commands_setup();

// ======================== PUBLIC COMMANDS ======================== \\

void commands_setReboot(const char* param, CommandResultCallback callback);

void commands_setHardReset(const char* param, CommandResultCallback callback);

void commands_setRelayOn(const char* param, CommandResultCallback callback);

void commands_setRelayOff(const char* param, CommandResultCallback callback);

void commands_setRelayOn(int channel);

void commands_setRelayOff(int channel);