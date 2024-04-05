#pragma once

class ITemperatureSensor {
public:
    virtual ~ITemperatureSensor() {}
    virtual float readTemperature() = 0;
};