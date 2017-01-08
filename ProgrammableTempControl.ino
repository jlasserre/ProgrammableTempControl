
#include <LiquidCrystal.h>

#include "thermostat.h"
#include "thermometer.h"
#include "temperaturelogger.h"
#include "pushbutton.h"

int relayControlPin = 3;  //out pin to control relay
bool relayOpen = false;


// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
Thermometer thermometer(A0);
Thermostat thermostat(thermometer);

TemperatureLogger tempLog;
PushButton relayButton(6, 2);
PushButton buttonProgram(5);
PushButton buttonUp(4);
PushButton buttonDown(3);


// the setup routine runs once when you press reset:
void setup() 
{
  relayOpen = false;
  relayButton.Setup();
  tempLog.Reset();
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Booting...");
  
  delay(800);
  lcd.clear();
  lcd.print("Reading Sensors...");
  delay(1000);
  pinMode(relayControlPin, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() 
{
  thermometer.Update();
  relayButton.Update();

  if (relayButton.WasPushed() == true)
  {
    relayOpen = !relayOpen;
    digitalWrite(relayControlPin, relayOpen);
  }

  float voltage = thermometer.GetVoltage();
  float temperature = thermometer.GetTemperature();

  tempLog.Update(temperature);
  
  char displayString[17];
  char temperatureString[6];
  char voltageString[6];
  
  dtostrf(temperature, 5, 1, temperatureString);
  dtostrf(voltage, 4, 2, voltageString);
  sprintf(displayString, "%s C (%s V)", temperatureString, voltageString);//fits EXACTLY in 16chars
  
  lcd.setCursor(0,0);
  lcd.print(displayString);

  lcd.setCursor(0,1);
  lcd.print(tempLog.GetNumRecords());

  lcd.setCursor(6,1);
  lcd.print(tempLog.GetRecord(tempLog.GetNumRecords()-1));
  
  if (tempLog.GetNumRecords() > 60)
  {
    tempLog.ToSerial();
    tempLog.Reset();
    lcd.clear();
  }
}

