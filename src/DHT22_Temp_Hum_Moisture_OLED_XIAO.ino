#include "DHT.h"
#include <Wire.h>
#include <Arduino.h>
#include <U8g2lib.h>

#define DHTPIN 2     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

DHT dht(DHTPIN, DHTTYPE);

const int dry = 1023; // value for dry sensor
const int wet = 239; // value for wet sensor

//U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE);
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

void setup() {
  Wire.begin();
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));

  dht.begin();

  u8g2.begin();
  //u8x8.begin();//u8x8 begins
  //u8x8.setPowerSave(0);
  //u8x8.setFlipMode(1);
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();

  int sensorVal = analogRead(A0);
  int percentageMoisture = map(sensorVal, wet, dry, 100, 0);

  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("% "));
  Serial.print(F("Moisture: "));
  Serial.print(percentageMoisture);
  Serial.println(F("%"));

  u8g2.clearBuffer();          // clear the internal memory
  u8g2.setFont(u8g2_font_t0_22_tf);  // choose a suitable font
  u8g2.drawStr(0, 15, "Temp:");  // write something to the internal memory
  u8g2.setCursor(60, 15);
  u8g2.print(t,1);
  u8g2.drawStr(115, 15,"C");
  
  u8g2.drawStr(0, 35, "Hum:");
  u8g2.setCursor(60, 35);
  u8g2.print(h,0);
  u8g2.drawStr(115, 35,"%");
  
  u8g2.drawStr(0, 60, "Mois:");
  u8g2.setCursor(60, 60);
  u8g2.print(percentageMoisture);
  u8g2.drawStr(115, 60,"%");
  u8g2.sendBuffer();          // transfer internal memory to the display
  delay(1000);

delay(200);

}
