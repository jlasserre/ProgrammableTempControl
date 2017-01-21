
#include <LiquidCrystal.h>

#include "thermostat.h"
#include "thermometer.h"
#include "temperaturelogger.h"
#include "pushbutton.h"
#include "relaycontrol.h"
#include "heatercontactsensor.h"

#define LOW_TEMP_LIMIT 11.0f
#define LOW_TEMP_HYSTERESIS 1.0f
#define DEFAULT_DESIRED_TEMP 21.0f
#define DEFAULT_HYSTERESIS 1.0f

enum HeatingState
{
  HS_Normal_Off,
  HS_Normal_On,
  HS_LowTempFailsafe_On
};

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
Thermometer thermometer(A0);
Thermostat thermostat(thermometer);
Thermostat lowTempFailsafeThermostat(thermometer);

TemperatureLogger tempLog;
PushButton relayButton(6, 2);
PushButton buttonProgram(5);
PushButton buttonUp(4);
PushButton buttonDown(3);
RelayControl relay(3, true);
HeaterContactSensor contactSensor(A1, 4);


// the setup routine runs once when you press reset:
void setup() 
{
  tempLog.Reset();
  relay.Setup();
  relayButton.Setup();
  buttonProgram.Setup();
  buttonUp.Setup();
  buttonDown.Setup();
  contactSensor.Setup();

  lowTempFailsafeThermostat.SetDesiredTemp(LOW_TEMP_LIMIT);
  lowTempFailsafeThermostat.SetHysteresis(LOW_TEMP_HYSTERESIS);

  thermostat.SetDesiredTemp(DEFAULT_DESIRED_TEMP);
  thermostat.SetHysteresis(DEFAULT_HYSTERESIS);
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Booting...");
  
  delay(800);
  lcd.clear();
  lcd.print("Reading Sensors...");
  delay(1000);
  lcd.clear();
}



// the loop routine runs over and over again forever:
void loop() 
{
  //update all the components first
  relay.Update();
  thermometer.Update();
  lowTempFailsafeThermostat.Update();
  thermostat.Update();
  relayButton.Update();
  buttonProgram.Update();
  buttonUp.Update();
  buttonDown.Update();
  contactSensor.Update();

  //execute any logic after the updates
  HeatingState heatingState = HS_Normal_Off;
  if(lowTempFailsafeThermostat.IsHeatingRequested())
  {
    heatingState = HS_LowTempFailsafe_On;
  }
  else if (thermostat.IsHeatingRequested())
  {
    heatingState = HS_Normal_On;
  }
  else
  {
    heatingState = HS_Normal_Off;
  }

  if (heatingState == HS_Normal_Off)
    relay.SetOpen(true);   
  else
    relay.SetOpen(false);
    

  float voltage = thermometer.GetVoltage();
  float temperature = thermometer.GetTemperature();

  tempLog.Update(temperature);
  
  char displayString[17];
  char temperatureString[6];
  

  dtostrf(thermostat.GetActualTriggerTemp(), 4, 1, temperatureString);

  if (heatingState == HS_LowTempFailsafe_On)
  {
    sprintf(displayString, "LOW TEMP! [ON] ");
  }
  else
  {
//    _|_|_|_|_|_|_|_|
//    OFF/Want 21.0C
//    20.5C / Closed
    sprintf(displayString, "%s/ Want %sC", thermostat.IsHeatingRequested()?"ON ":"OFF", temperatureString);
  }
  
  lcd.setCursor(0,0);
  lcd.print(displayString);
  
  dtostrf(temperature, 4, 1, temperatureString);
  
  sprintf(displayString, "%sC / %s", temperatureString, contactSensor.IsHeatingRequested()?"  Heat ":"No Heat");
  
  lcd.setCursor(0,1);
  lcd.print(displayString);
  
  if (tempLog.GetNumRecords() > 5)
  {
    tempLog.ToSerial();
    tempLog.Reset();
    lcd.clear();
  }
}

