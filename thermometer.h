#pragma once
#include <Arduino.h>

class Thermometer
{
   
  public:
    Thermometer(int analogPin);

    void Update();
    
    float GetTemperature() const;
    float GetVoltage() const;
    
  protected:
    int m_AnalogPin;
    float m_Voltage;

    static const float m_LowVoltageValue;
    static const float m_LowVoltageTemperature;
    
    static const float m_HighVoltageValue;
    static const float m_HighVoltageTemperature;

    static const float m_FullVoltageRange;
    static const float m_FullTemperatureRange;
};
