
//FirebaseESP8266.h must be included before ESP8266WiFi.h
#include "FirebaseESP8266.h" //파이어베이스 사용
#include <ESP8266WiFi.h> //와이파이 사용


//와이파이와 파이어베이스 연동
#define FIREBASE_HOST "arduinowebserver2.firebaseio.com" 
#define FIREBASE_AUTH "cg" 
#define WIFI_SSID "KBU" 
#define WIFI_PASSWORD ""

//Define FirebaseESP8266 data object
FirebaseData firebaseData;
FirebaseJson json;

void printResult(FirebaseData &data);


void setup()
{

  Serial.begin(9600);

  //와이파이 연결
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

 //파이어베이스 연결
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  
  /*
  This option allows get and delete functions (PUT and DELETE HTTP requests) works for device connected behind the
  Firewall that allows only GET and POST requests.
  
  Firebase.enableClassicRequest(firebaseData, true);
  */

  String path = "/testBucket/WIFIControl";
  
/* 
  Serial.println("------------------------------------");
  Serial.println("Set double test...");
 
  for (uint8_t i = 0; i < 10; i++)
  {
    //Also can use Firebase.set instead of Firebase.setDouble
    if (Firebase.setDouble(firebaseData, path + "/Double/Data" + (i + 1), ((i + 1) * 10) + 0.123456789))
    {
      Serial.println("PASSED");
      Serial.println("PATH: " + firebaseData.dataPath());
      Serial.println("TYPE: " + firebaseData.dataType());
      Serial.println("ETag: " + firebaseData.ETag());
      Serial.print("VALUE: ");
      printResult(firebaseData);
      Serial.println("------------------------------------");
      Serial.println();
    }
    else
    {
      Serial.println("FAILED");
      Serial.println("REASON: " + firebaseData.errorReason());
      Serial.println("------------------------------------");
      Serial.println();
    }
  }
*/

  Serial.println("------------------------------------");
  Serial.println("Get double test...");


    //Also can use Firebase.get instead of Firebase.setInt
    if (Firebase.getString(firebaseData, path))
    {
      Serial.print("AirCount VALUE: ");
      printResult(firebaseData);
      Serial.println("------------------------------------");
      Serial.println();
    }
    else
    {
      Serial.println("FAILED");
      Serial.println("REASON: " + firebaseData.errorReason());
      Serial.println("------------------------------------");
      Serial.println();
    }

}

void printResult(FirebaseData &data)
{
    if (data.dataType() == "int")
        Serial.println(data.intData());
    else if (data.dataType() == "float")
        Serial.println(data.floatData(), 5);
    else if (data.dataType() == "double")
        printf("%.9lf\n", data.doubleData());
    else if (data.dataType() == "boolean")
        Serial.println(data.boolData() == 1 ? "true" : "false");
    else if (data.dataType() == "string")
        Serial.println(data.stringData());
}

void loop()
{
}
