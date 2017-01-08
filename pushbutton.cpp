#include "pushbutton.h"


PushButton::PushButton(byte readPin, byte ledPin)
:m_ReadPin(readPin),
 m_LedPin(ledPin),
 m_LastPushMillis(0),
 m_CurrentMillis(0)
{
  
}

void PushButton::Setup()
{
  pinMode(m_LedPin, OUTPUT);     
  pinMode(m_ReadPin, INPUT);

}

void PushButton::Update()
{
  m_CurrentMillis = millis();

  bool previousPushValue = m_IsPushed;
  
  if (m_CurrentMillis - m_LastPushMillis > RESET_DELAY)
  {
    //only update when delay is passed. (Avoid glitches caused by imperfect electrical contacts)
    m_IsPushed = digitalRead(m_ReadPin);   // read the input pin
  }

  if (m_LedPin >= 0)
  {
    digitalWrite(m_LedPin, m_IsPushed);    // sets the LED to the button's value
  }

  if (!previousPushValue && m_IsPushed)
  {
    m_LastPushMillis = m_CurrentMillis;
  }
  
  
}

bool PushButton::WasPushed() const
{
  if (m_IsPushed && m_CurrentMillis == m_LastPushMillis )
  {
    return true;
  }
  else
    return false;
}

bool PushButton::IsPushed() const
{
  return m_IsPushed;
}
