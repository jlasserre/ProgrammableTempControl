#include <Arduino.h>

#define numHoursToLog 1UL

class TemperatureLogger
{
  public:
    TemperatureLogger();

    void Reset();

    void Update(float measuredTemperature);

    unsigned int GetNumRecords();
    float GetRecord(unsigned int index);
    void ToSerial();

  protected:
    static const unsigned int ms_MaxNumRecords = 120;

    byte TemperatureToByte(float temperature);
    void AddRecord(float temperature);


    unsigned long m_StartTimeMillis;
    unsigned long m_LogIntervalMillis;
    
    unsigned int  m_CurrentRecordIndex;

    byte m_RecordedTemperatures[ms_MaxNumRecords];
};
