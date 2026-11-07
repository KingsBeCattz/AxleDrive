#pragma once
#include "shared.hpp"

namespace BSP
{
    namespace Pinout
    {
#if HBRIDGE == HBRIDGE_L298N
        constexpr HBridgeConfig Base = {
            .name = "L298N",
            .directions_mode = MotorDriver::PinMode::PWM,
            .enables_mode = MotorDriver::PinMode::PWM,
            .left_enable = MotorDriver::PIN_UNUSED,
            .left_forward = 14,
            .left_backward = 27,
            .right_enable = MotorDriver::PIN_UNUSED,
            .right_forward = 26,
            .right_backward = 25,
            .standby = MotorDriver::PIN_UNUSED,
        };
#if DUAL == 1
        constexpr HBridgeConfig Double = {
            .name = Pinout::Base.name,
            .directions_mode = Pinout::Base.directions_mode,
            .enables_mode = Pinout::Base.enables_mode,
            .left_enable = MotorDriver::PIN_UNUSED,
            .left_forward = 4,
            .left_backward = 16,
            .right_enable = MotorDriver::PIN_UNUSED,
            .right_forward = 17,
            .right_backward = 5,
            .standby = MotorDriver::PIN_UNUSED,
        };
#endif
#elif HBRIDGE == HBRIDGE_TB6612
        constexpr HBridgeConfig Base = {
            .name = "TB6612",
            .directions_mode = MotorDriver::PinMode::Digital,
            .enables_mode = MotorDriver::PinMode::PWM,
            .left_enable = 4,
            .left_forward = 17,
            .left_backward = 16,
            .right_enable = 21,
            .right_forward = 18,
            .right_backward = 19,
            .standby = 5,
        };
#if DUAL == 1
        constexpr HBridgeConfig Double = {
            .name = Pinout::Base.name,
            .directions_mode = Pinout::Base.directions_mode,
            .enables_mode = Pinout::Base.enables_mode,
            .left_enable = 32,
            .left_forward = 25,
            .left_backward = 33,
            .right_enable = 12,
            .right_forward = 27,
            .right_backward = 14,
            .standby = 26,
        };
#endif
#elif HBRIDGE == HBRIDGE_BTS7960
        constexpr HBridgeConfig Base = {
            .name = "BTS7960",
            .directions_mode = MotorDriver::PinMode::PWM,
            .enables_mode = MotorDriver::PinMode::Digital,
            .left_enable = 26,
            .left_forward = 14,
            .left_backward = 27,
            .right_enable = 16,
            .right_forward = 5,
            .right_backward = 17,
            .standby = MotorDriver::PIN_UNUSED,
        };
#if DUAL == 1
        constexpr HBridgeConfig Double = {
            .name = Pinout::Base.name,
            .directions_mode = Pinout::Base.directions_mode,
            .enables_mode = Pinout::Base.enables_mode,
            .left_enable = 32,
            .left_forward = 25,
            .left_backward = 33,
            .right_enable = 21,
            .right_forward = 18,
            .right_backward = 19,
            .standby = MotorDriver::PIN_UNUSED,
        };
#endif
#endif
    }
}