#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <dht.h>

// Temp and Humidity
#define dataPin 8
dht DHT;

// Soil moisture
const int dry = 791; // value for dry sensor
const int wet = 239; // value for wet sensor

// OLED
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET 4
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define BLUE 0x001F

void setup() 
{
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //initialize with the I2C addr 0x3C (128x64) if any error use i2c scanner
  display.clearDisplay();
}

void loop() 
{
  int readData = DHT.read22(dataPin); 
  float t = DHT.temperature;
  float h = DHT.humidity;

  int sensorVal = analogRead(A0);
  int percentagemoisture = map(sensorVal, wet, dry, 100, 0);
  
  Serial.print("Temperature = ");
  Serial.print(t);
  Serial.print("*C");
  Serial.print("Humidity = ");
  Serial.print(h);
  Serial.print(" % ");
  Serial.print("Moisture = ");
  Serial.print(sensorVal);
  Serial.println("%");

  display.setCursor(0,0);  //set cursor on OLED display
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.print("T: ");
  display.print(t,1);
  display.println(" *C");
  
  display.setCursor(0,25);  
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.print("H: ");
  display.print(h,0);
  display.println(" %");

  
  display.setCursor(0,50);  
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.print("M: ");
  if(percentagemoisture >= 100)
{
  display.print(100);
}
  else if(percentagemoisture <=0)
  {
    display.print(0);
  }
  else if(percentagemoisture >0 && percentagemoisture < 100)
{
  display.print(percentagemoisture);
}
  
  display.println(" %");

  display.display();
  delay(250);
  display.clearDisplay();
  
  delay(10000);
}
