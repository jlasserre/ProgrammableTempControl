#pragma once
#include <Arduino.h>
#include "thermometer.h"

#define THERMOSTAT_DEFAULT_DESIRED_TEMP 15.0f
#define THERMOSTAT_DEFAULT_HYSTERESIS    1.0f

class Thermostat
{
public:
  Thermostat(const Thermometer& thermometer);

  void Update();

  //NOTE: THIS IS CURRENTLY ONLY FOR HEATING. IF APPLICATION
  //      MUST SUPPORT COOLING AS WELL, WE MUST PROVIDE A WAY
  //      TO SPECIFY IF THIS THERMOSTAT IS USED FOR COOLING OR
  //      HEATING.
  float GetDesiredTemp() const;
  void SetDesiredTemp(float desiredTemp);
  
  float GetHysteresis() const;
  void SetHysteresis(float acceptableDeltaTemp);

  bool IsHeatingRequested() const;
  float GetActualTriggerTemp() const;
  
protected:
  const Thermometer& m_Thermometer;
  float m_DesiredTemp;
  float m_Hysteresis;
  bool m_HeatingRequested;
};
