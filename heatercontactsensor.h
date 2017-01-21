#pragma once

#include <Arduino.h>



class HeaterContactSensor
{
  public:
    HeaterContactSensor(byte readPin, byte ledPin = -1);

    void Setup();
    void Update();
    
    float GetAverage();
    bool IsHeatingRequested();
    
  protected:
    byte m_ReadPin;
    byte m_LedPin;

    static const int ms_MovingAverageNumSamples = 100;
    int  m_DeltaTimeMovingAverage[ms_MovingAverageNumSamples];
    int  m_MovingAverageBufferIndex;
};
