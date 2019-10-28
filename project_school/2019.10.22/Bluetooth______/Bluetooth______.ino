#include <LiquidCrystal.h>


#include <Adafruit_GFX.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>
#include <gfxfont.h>

#include <Adafruit_SSD1306.h>
#include <splash.h>

#include <SoftwareSerial.h>

LiquidCrystal lcd(12,11,5,4,3,2);//RS,E,DB4,DB5,DB6,DB7
SoftwareSerial BTSerial(2, 3);   
char datas;
void setup() {  
  Serial.begin(9600);
  BTSerial.begin(9600);
  lcd.display();
  lcd.begin(16,2);


}
void loop() {
  if (BTSerial.available()){
    char data = BTSerial.read();
    Serial.write(data);
    datas = datas + data;
  }
    
  if (Serial.available())
    BTSerial.write(Serial.read());
      pinMode(13, OUTPUT);

  lcd.setCursor(0,0);
  lcd.display();
  lcd.print("hello"); 

}
