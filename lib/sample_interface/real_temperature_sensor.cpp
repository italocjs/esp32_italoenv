#include "i_temperature_sensor.h"

class RealTemperatureSensor : public ITemperatureSensor {
public:
    float readTemperature() override {
        // Implementation for actual hardware
        return 59.0; // Dummy temperature value
    }
};