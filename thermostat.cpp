#include "thermostat.h"



Thermostat::Thermostat(const Thermometer& thermometer)
:m_Thermometer(thermometer)
,m_DesiredTemp(THERMOSTAT_DEFAULT_DESIRED_TEMP)
,m_Hysteresis(THERMOSTAT_DEFAULT_HYSTERESIS)
,m_HeatingRequested(true) //initially true to make sure we ask for heat even if we startup within the range of temperature hysteresis.
{
  
}
  
void Thermostat::Update()
{


  if (m_Thermometer.GetTemperature() < GetActualTriggerTemp())
  {
    m_HeatingRequested = true;
  }
  else
  {
    m_HeatingRequested = false;
  }
}

float Thermostat::GetActualTriggerTemp() const
{
    float actualTemperatureToCompare = m_DesiredTemp;
  
  //if cooling down (no heat requested), take hysteresis into account
  if (!m_HeatingRequested)
  {
    actualTemperatureToCompare = (m_DesiredTemp - m_Hysteresis);
  }

  return actualTemperatureToCompare;
}
bool Thermostat::IsHeatingRequested() const
{
  return m_HeatingRequested;
}

void Thermostat::SetDesiredTemp(float desiredTemp)
{
  m_DesiredTemp = desiredTemp;
}

float Thermostat::GetDesiredTemp() const
{
  return m_DesiredTemp;
}

void Thermostat::SetHysteresis(float hysteresis)
{
  m_Hysteresis = hysteresis;
}

float Thermostat::GetHysteresis() const
{
  return m_Hysteresis;
}

