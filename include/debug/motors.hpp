#pragma once

#include <Arduino.h>

#include "MotorDriver.hpp"
#include "constants.hpp"

namespace DebugTools
{
  inline void snitchMotorPinout(const MotorDriver::Motor &motor, const char *name)
  {
    auto inputPins = motor.getInputPins();
    auto inputMode = motor.getInputMode() == MotorDriver::PinMode::Digital ? "-" : "~";

    Serial.print("Motor ");
    Serial.print(name);
    Serial.println(":");

    for (int i = 0; i < 2; ++i)
    {
      Serial.print(" - ");
      Serial.print(Constants::output_names[i]);
      Serial.print(": ");
      Serial.print(inputMode);
      if (i == 0)
      {
        Serial.print(inputPins.in1);
      }
      else
      {
        Serial.print(inputPins.in2);
      }
    }

    auto enablePin = motor.getEnablePin();

    if (enablePin != MotorDriver::PIN_UNUSED)
    {
      auto enableMode = motor.getEnableMode() == MotorDriver::PinMode::Digital ? "-" : "~";

      Serial.print(" - Enable: ");
      Serial.print(enableMode);
      Serial.print(enablePin);
    }
    Serial.println();
  }

  inline void snitchDiffDrive(const MotorDriver::DiffDrive &driver, const char *name, const char *model)
  {
    Serial.print("DiffDrive ");
    Serial.print(name);
    Serial.print(" (");
    Serial.print(model);
    Serial.println("):");

    auto stbyPin = driver.getEnablePin();
    if (stbyPin != MotorDriver::PIN_UNUSED)
    {
      Serial.print("Standby: -");
      Serial.println(stbyPin);
    }

    snitchMotorPinout(driver.getLeftMotor(), "Left");
    snitchMotorPinout(driver.getRightMotor(), "Right");
  }
}