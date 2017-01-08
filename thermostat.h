#pragma once
#include <Arduino.h>
#include "thermometer.h"

class Thermostat
{
public:
	Thermostat(const Thermometer& thermometer);
protected:

  const Thermometer m_Thermometer;
};
