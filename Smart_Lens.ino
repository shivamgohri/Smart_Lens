#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <SoftwareSerial.h>
#include <DHT.h>

String Date,Time,Text,Phone;
#define button 8



Adafruit_SSD1306 display(128,32,&Wire);
DHT dht(9, DHT11);
SoftwareSerial bluetooth(0,1);

void setup() {

  Serial.begin(9600);
  dht.begin();
  Serial.setTimeout(5);
  bluetooth.begin(9600);

    pinMode(button,INPUT);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();

  display.setCursor(0,0);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.print("Starting...");
  display.display();
  delay(2000);

   

  display.clearDisplay();
  display.display(); 

}

void loop() {
          
  

  if(Serial.available()){                                //getting info from phone via bluetooth

    String Date = Serial.readStringUntil('-');
    String Time = Serial.readStringUntil('-');
    String Phone = Serial.readStringUntil('-');
    String Text = Serial.readStringUntil('-');
    String Lattitude = Serial.readStringUntil('-');
    String Longitude = Serial.readStringUntil('-');
    String Steps = Serial.readStringUntil('-'); 


          if(digitalRead(button)==HIGH){

            display.clearDisplay();
            display.display();          


            display.setCursor(0,0);
          display.setTextSize(1);
          display.setTextColor(SSD1306_WHITE);
          display.print("TEMPERATURE:");
          display.display();


          display.setCursor(0,16);
          display.setTextSize(1);
          display.setTextColor(SSD1306_WHITE);
          display.print("HUMIDITY:");
          display.display();

          double t = dht.readTemperature();
          double h = dht.readHumidity();  

          display.setCursor(12,8);
          display.setTextSize(1);
          display.setTextColor(SSD1306_WHITE);
          display.print(t);
          display.print(" C");
          display.display();

          display.setCursor(12,24);
          display.setTextSize(1);
          display.setTextColor(SSD1306_WHITE);
          display.print(h);
          display.print(" %");
          display.display();

          delay(3000);

          display.clearDisplay();
          display.display();

                

            
          }




       

     
          if(Phone=="phone" && Text=="text"  ){          //no call, no text , displaying steps
          
          display.setCursor(0,8);
          display.setTextSize(1);
          display.setTextColor(SSD1306_WHITE);
          display.print(Date);
          display.display();
    
          
          display.setCursor(0,16);
          display.setTextSize(1);
          display.setTextColor(SSD1306_WHITE);
          display.print(Time);
          display.display();


          display.setCursor(102,24);
          display.setTextSize(1);
          display.setTextColor(SSD1306_WHITE);
          display.print(Steps);
          display.print("-S");
          display.display();
    
          delay(1000);
    
          display.clearDisplay();
          display.display();
    
          }

          if(Phone!="phone" && Text=="text"    ){              //call incoming, no text


            display.invertDisplay(true);

            display.setCursor(30,8);
            display.setTextSize(1);
            display.setTextColor(SSD1306_WHITE);
            display.print(Phone);
            display.setCursor(30,24);
            display.setTextSize(1);
            display.setTextColor(SSD1306_WHITE);
            display.print("is calling");
            display.display();           

            delay(1000);
    
            display.clearDisplay();
            display.display();  

            display.invertDisplay(false);

            
          }

          if(Phone=="phone" && Text!="text"   ){        //no call, text received


            display.invertDisplay(true);


            display.setCursor(30,8);
            display.setTextSize(1);
            display.setTextColor(SSD1306_WHITE);
            display.print(Text);
            display.setCursor(30,24);
            display.setTextSize(1);
            display.setTextColor(SSD1306_WHITE);
            display.print("texted you");
            display.display();           

            delay(3000);
    
            display.clearDisplay();
            display.display();  


            display.invertDisplay(false);
            
          } 
            

  }

}
