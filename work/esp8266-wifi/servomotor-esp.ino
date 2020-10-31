#include <SoftwareSerial.h>       //Including the software serial library

#include <Servo.h>                //including the servo library

SoftwareSerial esp(2,3);         //set ESP8266 Receiver pin = 2, and  transmitter pin = 3

#define DEBUG true                //This will display the ESP8266 messages on Serial Monitor

#define servopin 8          //connect servo on pin 8


Servo servo1;                        //variable for servo

 

int current_position = 170;     

int v = 10;                

int minposition = 20;

int maxposition = 160;

 

void setup()

{
  pinMode(led_pin, OUTPUT);
  
  digitalWrite(led_pin, LOW);

  servo1.attach(servopin);

  servo1.write(maxposition);

  servo1.detach();

  Serial.begin(115200);

  esp.begin(115200);

 

  sendData("AT+RST\r\n", 2000, DEBUG);                     

  sendData("AT+CWMODE=1\r\n", 1000, DEBUG);                  

  sendData("AT+CWJAP=\"WiFiName\",\"WiFi Password\"\r\n", 2000, DEBUG);   //Enter WiFi name and password

  while(!esp.find("OK")) {                                  //this will check for connection

  }

  sendData("AT+CIFSR\r\n", 1000, DEBUG);          //This will print IP address on the serial monitor

  sendData("AT+CIPMUX=1\r\n", 1000, DEBUG);      

  sendData("AT+CIPSERVER=1,80\r\n", 1000, DEBUG);   //This will start the web server on port 80

}

 

void loop()

{

  if (esp.available())     // This will check if input is available on ESP8266

  {

    if (esp.find("+IPD,"))     {

      String msg;

      esp.find("?");                           //run cursor until command is found

      msg = esp.readStringUntil(' ');         

      String command = msg.substring(0, 3);   

      String valueStr = msg.substring(4);     

      int value = valueStr.toInt();            //It will convert Value to integer

      if (DEBUG) {

        Serial.println(command);

        Serial.println(value);

      }

      delay(100);

    

      if(command == "sr1") {

        

         if (value >= maxposition) {

           value = maxposition;

         }

         if (value <= minposition) {

           value = minposition;

         }

         servo1.attach(servopin);

         while(current_position != value) {

           if (current_position > value) {

             current_position -= 1;

             servo1.write(current_position);

             delay(100/v);

           }

           if (current_position < value) {

             current_position += 1;

             servo1.write(current_position);

             delay(100/v);

           }

         }

         servo1.detach();

      }

      }


  }

  }

  }

String sendData(String command, const int timeout, boolean debug)

{

  String response = "";

  esp.print(command);

  long int time = millis();

  while ( (time + timeout) > millis())

  {

    while (esp.available())

    {

      char c = esp.read();

      response += c;

    }

  }

  if (debug)

  {

    Serial.print(response);

  }

  return response;

}
