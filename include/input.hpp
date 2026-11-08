#pragma once

#include <MotorDriver.hpp>
#include <gamepad.hpp>

extern BSPGamepad gamepad;
extern MotorDriver::DiffDrive motor_driver;
#if DUAL == 1
extern MotorDriver::DiffDrive second_driver;
#endif

enum class InputMode : uint8_t
{
  TRIGGER_STICK_RIGHT = 0, // D-Up
  TRIGGER_STICK_LEFT = 1,  // D-Down
  DUAL_STICK_RIGHT = 2,    // D-Right
  DUAL_STICK_LEFT = 3,     // D-Left
};

#ifdef ESP32
constexpr InputMode DEFAULT_INPUT_MODE = InputMode::TRIGGER_STICK_RIGHT;
#else
constexpr InputMode DEFAULT_INPUT_MODE = InputMode::DUAL_STICK_RIGHT;
#endif

inline MotorDriver::SignedPWM trigger_power_right()
{
  return (gamepad.held(Button::RB) ? 255 : gamepad.rightTrigger()) - (gamepad.held(Button::LB) ? 255 : gamepad.leftTrigger());
}

inline MotorDriver::SignedPWM trigger_power_left()
{
  return -trigger_power_right();
}

inline MotorDriver::SignedPWM left_stick_y()
{
  // Use the left stick's Y axis for steering control.
  return (MotorDriver::SignedPWM)(gamepad.leftStick().filtered.y * 255.0f);
}

inline MotorDriver::SignedPWM right_stick_y()
{
  // Use the right stick's Y axis for steering control.
  return (MotorDriver::SignedPWM)(gamepad.rightStick().filtered.y * 255.0f);
}

inline float left_stick_x()
{
  // Use the left stick's X axis for steering control.
  return gamepad.leftStick().filtered.x;
}

inline float right_stick_x()
{
  // Use the right stick's X axis for steering control.
  return gamepad.rightStick().filtered.x;
}

extern MotorDriver::SteerFn current_steering_function;

inline float steer_wrapper()
{
  if (current_steering_function)
  {
    float steer_value = current_steering_function();
    if (abs(steer_value) < 0.10f) // Deadzone threshold
      return 0.0f;
    return steer_value;
  }
  return 0.0f;
}

inline void set_input_mode(MotorDriver::DiffDrive &driver, InputMode mode)
{
  switch (mode)
  {
  case InputMode::TRIGGER_STICK_RIGHT:
    driver.attachPowerFunction(trigger_power_right);
    current_steering_function = left_stick_x;
    break;
  case InputMode::TRIGGER_STICK_LEFT:
    driver.attachPowerFunction(trigger_power_left);
    current_steering_function = right_stick_x;
    break;
  case InputMode::DUAL_STICK_RIGHT:
    driver.attachPowerFunction(left_stick_y);
    current_steering_function = right_stick_x;
    break;
  case InputMode::DUAL_STICK_LEFT:
    driver.attachPowerFunction(right_stick_y);
    current_steering_function = left_stick_x;
    break;
  }
}

inline void change_input_mode(MotorDriver::DiffDrive &driver, InputMode &current_mode)
{
  auto previous_mode = current_mode;

  if (gamepad.pressed(Button::Up))
    current_mode = InputMode::TRIGGER_STICK_RIGHT;
  else if (gamepad.pressed(Button::Down))
    current_mode = InputMode::TRIGGER_STICK_LEFT;
  else if (gamepad.pressed(Button::Right))
    current_mode = InputMode::DUAL_STICK_RIGHT;
  else if (gamepad.pressed(Button::Left))
    current_mode = InputMode::DUAL_STICK_LEFT;

  if (current_mode != previous_mode)
    set_input_mode(driver, current_mode);
}