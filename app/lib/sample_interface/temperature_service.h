#include "i_temperature_sensor.h"

class TemperatureService {
public:
    TemperatureService(ITemperatureSensor& sensor) : sensor(sensor) {}

    float readTemperature() {
        return sensor.readTemperature();
    }

private:
    ITemperatureSensor& sensor;
};