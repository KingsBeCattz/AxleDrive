#pragma once
#include "shared.hpp"

namespace BSP
{
  namespace Pinout
  {
    constexpr HBridgeConfig Base = {
        .name = "SS6625E",
        .directions_mode = MotorDriver::PinMode::PWM,
        .enables_mode = MotorDriver::PinMode::PWM,
        .left_enable = MotorDriver::PIN_UNUSED,
        .left_forward = 27,
        .left_backward = 13,
        .right_enable = MotorDriver::PIN_UNUSED,
        .right_forward = 4,
        .right_backward = 2,
        .standby = MotorDriver::PIN_UNUSED,
    };
    constexpr HBridgeConfig Double = {
        .name = Pinout::Base.name,
        .directions_mode = Pinout::Base.directions_mode,
        .enables_mode = Pinout::Base.enables_mode,
        .left_enable = MotorDriver::PIN_UNUSED,
        .left_forward = 17,
        .left_backward = 12,
        .right_enable = MotorDriver::PIN_UNUSED,
        .right_forward = 14,
        .right_backward = 15,
        .standby = MotorDriver::PIN_UNUSED,
    };
  }
}