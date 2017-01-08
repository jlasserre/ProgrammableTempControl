#include "temperaturelogger.h"

TemperatureLogger::TemperatureLogger()
:m_StartTimeMillis(0),
m_CurrentRecordIndex(0)
{
  Reset();
}

void TemperatureLogger::Reset()
{
  memset(m_RecordedTemperatures, 0, ms_MaxNumRecords);
  m_CurrentRecordIndex = 0;
  m_StartTimeMillis = 0;
  m_LogIntervalMillis = (numHoursToLog * 60UL * 60UL * 1000UL) / ms_MaxNumRecords;
}

void TemperatureLogger::Update(float measuredTemperature)
{
  unsigned long currentTime = millis();
  
  if(m_StartTimeMillis == 0)
  {
    m_StartTimeMillis = currentTime;
  }
  
  if ((currentTime - m_StartTimeMillis) >= m_CurrentRecordIndex * m_LogIntervalMillis)
  {
    AddRecord(measuredTemperature);
  }
}

unsigned int TemperatureLogger::GetNumRecords()
{
  return m_CurrentRecordIndex;
}

float TemperatureLogger::GetRecord(unsigned int index)
{
  if (index > m_CurrentRecordIndex-1)
    return 0.0f;
  
  return 0.1f * m_RecordedTemperatures[index];
}

void TemperatureLogger::ToSerial()
{
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  Serial.println("---- Recorded Data ----");
  Serial.print("Start Time (millis): ");
  Serial.println(m_StartTimeMillis);
  Serial.print("Num Records:");
  Serial.println(m_CurrentRecordIndex+1);
  Serial.println("Values:");
  
  for (unsigned int i=0; i<m_CurrentRecordIndex; ++i)
  {       
    if (i > 0 && i % 10 == 0)
      Serial.println("");
    Serial.print(m_RecordedTemperatures[i]);
    Serial.print(", ");   
  }
  Serial.println("");
  Serial.println("End of recorded data");
  Serial.println("-----------------------");
  Serial.end();
}

byte TemperatureLogger::TemperatureToByte(float temperature)
{
  byte temp = 0;
  if (temperature > 25.5f)
  {
    temp = 255;
  }
  else if (temperature < 0.0f)
  {
    temp = 0;
  }
  else
  {
    temp = (byte) (temperature * 10);
  }
  return temp;      
}

void TemperatureLogger::AddRecord(float temperature)
{
  if(m_CurrentRecordIndex < ms_MaxNumRecords)
  {
    m_RecordedTemperatures[m_CurrentRecordIndex] = TemperatureToByte(temperature);
    m_CurrentRecordIndex++;
  }
}