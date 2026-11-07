#pragma once

#include <Arduino.h>
#include "debug/motors.hpp"

namespace DebugTools
{
  inline void advice()
  {
    Serial.println("-> Debug mode active: Verbose gamepad/motor/sources state will be printed every loop.");
    Serial.println("-> To disable debug mode, comment out the #define DEBUG line in src/main.cpp and re-upload the firmware.");
  }

  inline void snitchFirmware()
  {
    Serial.println("===============================");
    Serial.print("| ");
    Serial.print(FIRMWARE_NAME);
    Serial.print(" (C) 2026 ");
    Serial.print(FIRMWARE_AUTHOR);
    Serial.println(" |");
    Serial.print("| Firmware version: v");
    Serial.print(FIRMWARE_VERSION);
    Serial.println("    |");
    Serial.println("===============================");
  }
}