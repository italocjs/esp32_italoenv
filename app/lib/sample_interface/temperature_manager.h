#include "temperature_service.h"
#include "real_temperature_sensor.cpp"
#include "mock_temperature_sensor.cpp"

class TemperatureManager
{
public:
    static TemperatureService &getService()
    {
        static TemperatureService instance(createInstance());
        return instance;
    }

private:
    TemperatureManager() {} // Private constructor to prevent instantiation

    static TemperatureService createInstance()
    {
#ifdef USE_REAL_SENSOR
        static RealTemperatureSensor sensor;
#else
        static TemperatureSensorMock sensor;
#endif
        static TemperatureService instance(sensor);
        return instance;
    }
};

// This provides a global access point to the temperature service, since its a singleton the instance is created only once
static TemperatureService &port_temperature = TemperatureManager::getService(); 
