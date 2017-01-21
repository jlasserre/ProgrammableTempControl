#include "heatercontactsensor.h"

static const unsigned long RESET_DELAY = 1000UL;


HeaterContactSensor::HeaterContactSensor(byte readPin, byte ledPin)
:m_ReadPin(readPin),
 m_LedPin(ledPin),
 m_MovingAverageBufferIndex(0)
{
  memset(m_DeltaTimeMovingAverage, 0, ms_MovingAverageNumSamples * sizeof(int));
}

void HeaterContactSensor::Setup()
{
  pinMode(m_LedPin, OUTPUT);     
  pinMode(m_ReadPin, INPUT);

}

void HeaterContactSensor::Update()
{
  //when the pin is HIGH, there is 24V in the furnace cable and this powers the opto-isolator's diode
  m_DeltaTimeMovingAverage[m_MovingAverageBufferIndex] = analogRead(m_ReadPin);
  
  m_MovingAverageBufferIndex = (m_MovingAverageBufferIndex + 1) % ms_MovingAverageNumSamples;
}

float HeaterContactSensor::GetAverage()
{
  int i = (m_MovingAverageBufferIndex+1) % ms_MovingAverageNumSamples;
  float avg = 0.0f;
  
  while (i != m_MovingAverageBufferIndex)
  {
    avg += m_DeltaTimeMovingAverage[i];
    i = (i+1) % ms_MovingAverageNumSamples;  
  }

  avg = avg / ms_MovingAverageNumSamples;

  return avg;
}

bool HeaterContactSensor::IsHeatingRequested()
{
  if (GetAverage() < 500)
  {
    return true;
  }
  else
  {
    return false;
  }
}

