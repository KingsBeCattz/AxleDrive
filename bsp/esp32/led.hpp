#pragma once

#include <Arduino.h>

namespace BSP {
  namespace LED {
    inline void setup() {
      // Initialize LED pin as output
      pinMode(LED_BUILTIN, OUTPUT);
    }
    inline void set(bool state) {
      digitalWrite(LED_BUILTIN, state);
    }
  }
}