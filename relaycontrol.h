#pragma once

#include <Arduino.h>

class RelayControl
{
  public:
    RelayControl(byte writePin, bool initiallyOpen);
    void Setup();
    void Update();

    void SetOpen(bool open);
    bool IsOpen() const;
    
  protected:
    byte m_WritePin;
    byte m_IsOpen;
};
