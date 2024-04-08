#include "Arduino.h"
#include <gtest/gtest.h>
#define USE_REAL_SENSOR
#include "test_temperature_sensor.h"

// extern "C" {
// void app_main();
// }

// void app_main() {
//     // Initialization code here (ESP-IDF, Arduino, etc.)

//     // Initialize GoogleTest and run all tests
//     ::testing::InitGoogleTest();
//     int retVal = RUN_ALL_TESTS();
//     if (retVal != 0) {
//         // Handle test failures as needed
//     }

//     // Additional code if needed (e.g., enter a loop in an Arduino project)
// }

void setup() {
    Serial.begin(115200);
    ::testing::InitGoogleTest();
    int retVal = RUN_ALL_TESTS();
    if (retVal != 0) {
        // Handle test failures as needed
    }
}

void loop() {
    Serial.println("Hello, world!");
    delay(1000);
}