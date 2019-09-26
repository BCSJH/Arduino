#include "DHT.h"
#include <DHT_U.h>

#include <LiquidCrystal.h>
DHT dht(8, DHT11);
LiquidCrystal lcd(12,11,5,4,3,2);


void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(2000);
  int h = dht.readHumidity();
  int t = dht.readTemperature();
  lcd.setCursor(0,0); lcd.print("Humi:"); lcd.print(h); lcd.print(" %");
  lcd.setCursor(0,1); lcd.print("Temp:"); lcd.print(t); lcd.print(" C");
}
