#pragma once

#include <Arduino.h>



class PushButton
{
  public:
    PushButton(byte readPin, byte ledPin = -1);

    void Setup();
    void Update();
    bool WasPushed() const;
    bool IsPushed() const;
    
  protected:
    bool m_IsPushed;
    byte m_ReadPin;
    byte m_LedPin;
    unsigned long m_LastPushMillis;
    unsigned long m_CurrentMillis;  //only get the current millis value once per update and always compare to that cached value to avoid inconsistencies during one update.
};
