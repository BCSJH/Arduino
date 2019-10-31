#include <Firebase.h>
#include <FirebaseArduino.h>
#include <FirebaseCloudMessaging.h>
#include <FirebaseError.h>
#include <FirebaseHttpClient.h>
#include <FirebaseObject.h>

#include <ESP8266WiFi.h>

// 1. Firebase ESP8266 라이브러리 포함 (이 라이브러리) 

// 2. ESP8266WiFi.h 포함 및 FirebaseESP8266.h 다음에  포함되어야 함 

#define FIREBASE_HOST "arduinowebserver2.firebaseio.com" 
#define FIREBASE_AUTH "AIzaSyBwFV2eyPdgE4my66Mrez_zx1huksfKLA4" 
#define WIFI_SSID "KBU" 
#define WIFI_PASSWORD "1952bible!" 

// 3. 전역 범위에서 Firebase 데이터 객체를 선언합니다.



void setup() {
  Serial.begin(9600);
             
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  // put your setup code here, to run once:
  Firebase.begin (FIREBASE_HOST, FIREBASE_AUTH);

}

void loop() {
  // put your main code here, to run repeatedly:
  if (Firebase.failed()){
    Serial.println(Firebase.error());
    Serial.print("오류");
    
    delay(10000);
  }
  else{
    Serial.println(Firebase.getInt ("testBucket/AirCount" ));

  delay(10000);
  }
}
