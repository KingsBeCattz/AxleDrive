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
    delay(65);
    BSP::LED::set(false);
    delay(65);
    BSP::LED::set(true);
    delay(130);
    BSP::LED::set(false);
    delay(130);

    return;
  }

  handleInputModeSwitch(gamepad);

  handlePivotInput(gamepad);

  BSP::loop();

  motor_driver.update();
#if DUAL == 1
  second_driver.update();
#endif

  delay(10);
}