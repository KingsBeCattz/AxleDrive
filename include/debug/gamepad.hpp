#pragma once

#include <Arduino.h>

#include "MotorDriver.hpp"
#include "GamepadState.hpp"

namespace DebugTools
{
  namespace Gamepad
  {
    inline void snitchGamepadState(const GamepadState &state)
    {
      Serial.println("Gamepad State:");
      Serial.print("Connected: ");
      Serial.println(state.connected ? "Yes" : "No");
      Serial.print("Buttons: ");
      Serial.println(state.buttons.raw(), BIN);
      Serial.print("Left Stick: (");
      Serial.print(state.leftStick.raw.x, 2);
      Serial.print(", ");
      Serial.print(state.leftStick.raw.y, 2);
      Serial.println(")");
      Serial.print("Right Stick: (");
      Serial.print(state.rightStick.raw.x, 2);
      Serial.print(", ");
      Serial.print(state.rightStick.raw.y, 2);
      Serial.println(")");
      Serial.print("Left Trigger: ");
      Serial.println(state.leftTrigger);
      Serial.print("Right Trigger: ");
      Serial.println(state.rightTrigger);
    }
  }
}