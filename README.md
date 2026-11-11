# AxleDrive

**Modular robot-control firmware for ESP32-based differential-drive platforms.**

AxleDrive is a C++ firmware project designed to provide a configurable control layer for robotic platforms. It combines gamepad input handling, differential-drive control, and hardware-specific board support into a modular architecture.

The project supports multiple H-bridge drivers and input configurations through PlatformIO build environments.

## Features

- **Modular hardware support:** Separate board configurations through Board Support Packages (BSP).
- **Multiple motor drivers:** Configurations for L298N, TB6612FNG, BTS7960, and SS6625E-based hardware.
- **Differential drive:** Motor control through the MotorDriver library.
- **Gamepad abstraction:** Controller input handled through an `IGamepad` implementation using Bluepad32.
- **Flexible input modes:** Different combinations of analog sticks and triggers for steering and throttle.
- **Dual-drive configuration:** Support for two differential-drive motor configurations.
- **Compile-time configuration:** Hardware selection and build variants managed through PlatformIO.
- **Debug utilities:** Firmware, motor, and gamepad diagnostics.

## Architecture

AxleDrive separates application logic, input processing, and hardware-specific implementation.

```text
AxleDrive
├── src/
│   └── main.cpp
│
├── include/
│   ├── input.hpp
│   ├── debug.hpp
│   └── ...
│
└── bsp/
    ├── esp32/
    ├── esp32-shared/
    ├── maker-esp32-pro/
    └── avr/
```

### Main components

| Component | Responsibility |
|---|---|
| `src/` | Main firmware execution flow |
| `include/` | Input handling, control logic, and utilities |
| `bsp/` | Board-specific hardware implementation |
| `esp32-shared/` | Shared ESP32 functionality |
| `platformio.ini` | Build environments and source configuration |
| `config.ini` | Build-time configuration |
| `bases.ini` | Shared PlatformIO environment definitions |

## Hardware support

The repository currently defines the following hardware configurations:

| Driver / Platform | Configuration |
|---|---|
| L298N | Single and dual |
| TB6612FNG | Single and dual |
| BTS7960 | Single and dual |
| Maker ESP32 Pro | SS6625E-based dual configuration |

Hardware pin assignments are defined in the corresponding BSP rather than in the application logic.

## Input modes

AxleDrive provides configurable control mappings:

- `TRIGGER_STICK_RIGHT`
- `TRIGGER_STICK_LEFT`
- `DUAL_STICK_RIGHT`
- `DUAL_STICK_LEFT`

These modes determine how controller triggers and analog sticks are mapped to throttle and steering.

The default input mode is selected at compile time.

## Requirements

- Supported development board
- Compatible motor driver and DC motors
- Supported gamepad
- [PlatformIO](https://platformio.org/)
- [Bluepad32](https://github.com/ricardoquesada/bluepad32)
- [MotorDriver](https://github.com/KingsBeCattz/MotorDriver)

## Building

Clone the repository:

```bash
git clone https://github.com/KingsBeCattz/AxleDrive.git
cd AxleDrive
```

Build a specific PlatformIO environment:

```bash
pio run -e esp32_l298n
```

Other available environments:

```text
esp32_l298n
esp32_l298n-dual
esp32_tb6612
esp32_tb6612-dual
esp32_bts7960
esp32_bts7960-dual
maker-esp32-pro
```

Upload firmware using:

```bash
pio run -e esp32_l298n -t upload
```

Replace the environment name with the target configuration.

## Configuration

Build configurations are managed through `platformio.ini`, `bases.ini`, and `config.ini`.

The selected environment determines the hardware configuration and compilation flags.

To add support for another board or motor driver, implement the corresponding BSP configuration and integrate it into the PlatformIO build setup.

## Safety

This firmware controls physical motors. Verify motor wiring, power limits, driver compatibility, and emergency-stop behavior before operating a robot.

Test new configurations with the wheels lifted off the ground whenever possible.

## License

This project is licensed under the MIT License. See [LICENSE](LICENSE) for details.

## Author

**Johan E.**

GitHub: [@KingsBeCattz](https://github.com/KingsBeCattz)