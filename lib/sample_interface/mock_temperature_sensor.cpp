#include "i_temperature_sensor.h"

class TemperatureSensorMock : public ITemperatureSensor {
public:
    float readTemperature() override {
        return 20.0; // Mock temperature value for testing
    }
};