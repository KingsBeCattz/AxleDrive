#pragma once

#include <MotorDriver.hpp>
#include "debug.hpp"
#include "input.hpp"

constexpr MotorDriver::UnsignedPWM DEFAULT_DEADZONE = 25;

struct HBridgeConfig
{
  const char *name;
  MotorDriver::PinMode directions_mode;
  MotorDriver::PinMode enables_mode;
  MotorDriver::Pin left_enable;
  MotorDriver::Pin left_forward;
  MotorDriver::Pin left_backward;
  MotorDriver::Pin right_enable;
  MotorDriver::Pin right_forward;
  MotorDriver::Pin right_backward;
  MotorDriver::Pin standby;
};

inline void configureMotorDriver(const char *name, MotorDriver::DiffDrive &motor_driver, const HBridgeConfig &config, MotorDriver::UnsignedPWM deadzone, InputMode input_mode)
{

  auto &leftMotor = motor_driver.getLeftMotor();
  auto &rightMotor = motor_driver.getRightMotor();

  leftMotor.attachInput(config.left_forward, config.left_backward, config.directions_mode);
  rightMotor.attachInput(config.right_forward, config.right_backward, config.directions_mode);

  if (config.left_enable != MotorDriver::PIN_UNUSED)
  {
    leftMotor.attachEnable(config.left_enable, config.enables_mode);
  }

  if (config.right_enable != MotorDriver::PIN_UNUSED)
  {
    rightMotor.attachEnable(config.right_enable, config.enables_mode);
  }

  if (config.standby != MotorDriver::PIN_UNUSED)
  {
    motor_driver.attachEnablePin(config.standby);
  }

  set_input_mode(motor_driver, input_mode);
  leftMotor.setDeadzoneThreshold(deadzone);
  rightMotor.setDeadzoneThreshold(deadzone);

  motor_driver.begin();

  DebugTools::snitchDiffDrive(motor_driver, name);
}