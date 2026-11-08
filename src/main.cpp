#include <Arduino.h>

#include "GamepadState.hpp"
#include "debug.hpp"
#include "bsp.hpp"
#include "DiffDrive.hpp"

InputMode input_mode = DEFAULT_INPUT_MODE;
BSPGamepad gamepad;

MotorDriver::DiffDrive motor_driver;
#if DUAL == 1
MotorDriver::DiffDrive second_driver;
#endif

void setup()
{
  Serial.begin(115200);

  DebugTools::snitchFirmware();

  BSP::setup();
  BSP::LED::set(true);
}

void loop()
{
  gamepad.update();
  if (!gamepad.isConnected())
  {
    BSP::LED::set(true);
    delay(130);
    BSP::LED::set(false);
    delay(130);

    return;
  }

  if (gamepad.getState().buttons.raw() & Button::DPAD_MASK)
  {
    if (gamepad.pressed(Button::Up))
      input_mode = InputMode::TRIGGER_STICK_RIGHT;
    else if (gamepad.pressed(Button::Down))
      input_mode = InputMode::TRIGGER_STICK_LEFT;
    else if (gamepad.pressed(Button::Right))
      input_mode = InputMode::DUAL_STICK_RIGHT;
    else if (gamepad.pressed(Button::Left))
      input_mode = InputMode::DUAL_STICK_LEFT;

    set_input_mode(motor_driver, input_mode);
#if DUAL == 1
    set_input_mode(second_driver, input_mode);
#endif

    auto current_pivot = motor_driver.getPivotMode();

    if (gamepad.held(Button::X))
    {
      if (current_pivot == MotorDriver::PivotMode::Center)
        return;

      motor_driver.setPivotMode(MotorDriver::PivotMode::Center);
#if DUAL == 1
      second_driver.setPivotMode(MotorDriver::PivotMode::Center);
#endif
    }
    else
    {
      if (current_pivot == MotorDriver::PivotMode::Wheel)
        return;

      motor_driver.setPivotMode(MotorDriver::PivotMode::Wheel);
#if DUAL == 1
      second_driver.setPivotMode(MotorDriver::PivotMode::Wheel);
#endif
    }
  }

  BSP::loop();

  motor_driver.update();
#if DUAL == 1
  second_driver.update();
#endif

  delay(10);
}