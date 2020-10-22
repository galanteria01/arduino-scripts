#include<LiquidCrystal.h>

LiquidCrystal lcd(12,11,10,9,8,7);

const int kPinTemp = A0;
 
 void loop()
 {
 float reading = analogRead(kPinTemp);     //Analog pin reading output voltage by Lm35
 float temperatureC=kPinTemp/2.048;        //Finding the true centigrade/Celsius temperature
 lcd.setCursor(0,0);                       //Place lcd cursor at coulomb-1 row-1

 lcd.print("CENTI TEMP= ");
 lcd.print(temperatureC);                  //Print centigrade temperature on lcd
 float temperatureF= ((temperatureC ) * 9.0 / 5.0) + 32.0; 

 lcd.setCursor(0,1);                      //Place lcd cursor at coulomb-2 row-2
 lcd.print("FARE TEMP= ");
 lcd.print(temperatureF);                 //Print Fahrenheit temperature on lcd

 delay(800);                              //Delay to remain data appear on lcd.
 lcd.clear();                             //Clear lcd screen
 }
