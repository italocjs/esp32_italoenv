
#include "test_temperature_sensor.h"

TEST(TemperatureSensorTest, MockSensorReturnsExpectedValue) {
    // Ensure that USE_REAL_SENSOR is not defined
    #ifdef USE_REAL_SENSOR
    #undef USE_REAL_SENSOR
    #endif

    // Get the temperature service instance
    TemperatureService& temperatureService = TemperatureManager::getService();

    // Read the temperature from the mock sensor
    float temperature = temperatureService.readTemperature();

    // Assert that the temperature matches the expected mock value
    ASSERT_FLOAT_EQ(temperature, 59.0);
}