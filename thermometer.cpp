#include "thermometer.h"

const float Thermometer::m_LowVoltageValue = 2.21f;
const float Thermometer::m_LowVoltageTemperature = 48.3f;

const float Thermometer::m_HighVoltageValue = 4.28f;
const float Thermometer::m_HighVoltageTemperature = 4.3f;

const float Thermometer::m_FullVoltageRange = m_HighVoltageValue - m_LowVoltageValue;
const float Thermometer::m_FullTemperatureRange = m_HighVoltageTemperature - m_LowVoltageTemperature;

Thermometer::Thermometer(int analogPin)
:m_AnalogPin(analogPin),
m_Voltage(0.0f)
{
}

void Thermometer::Update()
{
  // read the input on analog pin:
  int sensorValue = analogRead(m_AnalogPin);
  
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  m_Voltage = sensorValue * (5.0 / 1023.0);
}
  
float Thermometer::GetTemperature() const
{
  float voltage = GetVoltage();
  float temperature = m_LowVoltageTemperature + (voltage-m_LowVoltageValue)/m_FullVoltageRange * m_FullTemperatureRange;
  return temperature;    
}

float Thermometer::GetVoltage() const
{
  return m_Voltage;
}
