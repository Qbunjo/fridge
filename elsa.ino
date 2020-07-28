#include "Arduino.h"
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>
#define ONE_WIRE_BUS 2

//initialize thermometer
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

LiquidCrystal_I2C lcd(0x27, 16, 2);

//var definitions
int hist = 2; //hysteresis
int setTemp = 10; //default set temperature after startup


//pin definitions
int coolPin = 4;
int plusButton = 9;
int minusButton = 10;



void TurnOn() {
  lcd.display();
  lcd.backlight();
}
void TurnOff() {
  lcd.noDisplay();
  lcd.noBacklight();
}

void coolMe() {
  digitalWrite(coolPin, 0);
}
void stopCooling() {
  digitalWrite(coolPin, 1);
}
int measureTemp() {
  sensors.requestTemperatures();
  float tempC = sensors.getTempCByIndex(0);
  return tempC;
}

boolean ifPressed() {
  if (digitalRead(plusButton) != 0 or digitalRead(minusButton) != 0)
    return true;
  else
    return false;
}

void hysteresisChange(){
  }


void setup()
{
  sensors.begin();
  //define in/out pins
  pinMode(coolPin, OUTPUT);
  pinMode(plusButton, INPUT);
  pinMode(minusButton, INPUT);
  lcd.init();

  // start lcd
TurnOn();

}


void loop()
{
  //measure temperature (main fridge process)
  if ((measureTemp() + hist) > setTemp) {
    coolMe();
  }
  if ((measureTemp() + hist) < setTemp) {
    stopCooling();
  }
  //display on the lcd
   lcd.setCursor(0, 1);
    lcd.print("Set Temp:");
    lcd.setCursor(9,1);
    lcd.print(setTemp);
   lcd.setCursor(0,0);
   lcd.print("Cur Temp:");
   lcd.setCursor(9,0);
   lcd.print(measureTemp());
  
}