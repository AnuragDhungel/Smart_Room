//codes are also imported from groove beginner kit.
//Temperature and Humidity Sensor
#include "DHT.h"
#include <Arduino.h>
#include <U8x8lib.h>

#define DHTPIN 3 // what pin we're connected to
#define DHTTYPE DHT11 // DHT 11
DHT dht(DHTPIN, DHTTYPE);
U8X8_SSD1306_128X64_ALT0_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE);

//output (relay)
const int humid=4;//humidifier
const int light=5;//light source

//input (sensors)
const int lightSensor=A6;
const int PirSensor  =7;

//internal variables
int temperature,humidity;
int motion,lightvalue;

void setup() {
  pinMode(humid,OUTPUT);//initialize relay for humidifier
 pinMode(light,OUTPUT);//initialize relay for light source
 pinMode(lightSensor,INPUT);//initialize light sensor
 pinMode(PirSensor,INPUT);//initialize pir sensor
  Serial.begin(9600);
 dht.begin();
 u8x8.begin();
 u8x8.setPowerSave(0);
 u8x8.setFlipMode(1); 
 }

void loop() {
 temperature = dht.readTemperature();
 humidity = dht.readHumidity(); 
 motion=digitalRead(PirSensor);
 lightvalue= map(analogRead(lightSensor), 0, 1023, 0, 255);
 printTemp();
 printHumidity();
 printLightandmotion();
 lightlogic();
 humidifierlogic();

}
void lightlogic(){
  if ((lightvalue<=80)&&(motion=HIGH)) {         
    digitalWrite(light, HIGH);   // turn RElay ON
    delay(150);            
    }else {
      digitalWrite(light, LOW); // turn LED OFF      
  }
}
void humidifierlogic(){
  if (humidity<=60) {         
    digitalWrite(humid, HIGH);   // turn RElay ON
    delay(150);            
    }else {
      digitalWrite(humid, LOW); // turn LED OFF      
  }
}

void printTemp(){
 u8x8.setFont(u8x8_font_chroma48medium8_r);
 u8x8.setCursor(0, 0);
 u8x8.print("Temp:");
 u8x8.print(temperature);
 u8x8.print("C");
 u8x8.refreshDisplay(); 
}
void printHumidity(){
 u8x8.setFont(u8x8_font_chroma48medium8_r);
 u8x8.setCursor(0,33);
 u8x8.print("Humidity:");
 u8x8.print(humidity);
 u8x8.print("%");
 u8x8.refreshDisplay();
} 
void printLightandmotion(){
 u8x8.setFont(u8x8_font_chroma48medium8_r);
 u8x8.setCursor(0, 50);
 u8x8.print("Light:");
 u8x8.print(lightvalue);
 u8x8.print("  ");
  u8x8.print(motion);
 
 u8x8.refreshDisplay(); 
}