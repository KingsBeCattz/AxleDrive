#pragma once

#ifndef ESP32
#error "This bsp is for ESP32 only."
#endif

#include <Bluepad32.h>

#include "gamepad.hpp"
#include "led.hpp"
#include "pinout.hpp"

extern BSPGamepad gamepad;
extern InputMode input_mode;

extern MotorDriver::DiffDrive motor_driver;
#if DUAL == 1
extern MotorDriver::DiffDrive second_driver;
#endif

namespace BSP
{
  inline void setup()
  {
    LED::setup();
    gamepad.begin();

    configureMotorDriver("Main", motor_driver, Pinout::Base, DEFAULT_DEADZONE, input_mode);
#if DUAL == 1
    configureMotorDriver("Secondary", second_driver, Pinout::Double, DEFAULT_DEADZONE, input_mode);
#endif
  }

  inline void loop()
  {
    // This must be used to extra functions with gamepad buttons, like weapons
  }
}