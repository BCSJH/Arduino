

#include <SoftwareSerial.h>//와이파이 통신

#include "FirebaseESP8266.h" //파이어베이스 사용
#include <ESP8266WiFi.h> //와이파이 사용

#include <string.h>

//와이파이와 파이어베이스 연동
#define FIREBASE_HOST "arduinowebserver2.firebaseio.com" 
#define FIREBASE_AUTH "cg" 
#define WIFI_SSID "KBU" 
#define WIFI_PASSWORD ""

int count_check = 0;//파이어베이스에 비교하기위한 기존 할일 값을 한번만 저장
  
//Define FirebaseESP8266 data object
FirebaseData firebaseData;
FirebaseJson json;

SoftwareSerial s(D6,D5); // (Rx, Tx) //와이파이 통신


void printResult(FirebaseData &data);

void setup()
{

  Serial.begin(9600);
  s.begin(9600); 
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

  //와이파이와 아두이노 연결 : https://www.youtube.com/watch?v=SiU-QZwik8w
  /*
  This option allows get and delete functions (PUT and DELETE HTTP requests) works for device connected behind the
  Firewall that allows only GET and POST requests.
  
  Firebase.enableClassicRequest(firebaseData, true);
  */

  String path = "/testBucket/WIFIControl"; //Firebase WIFI 제어 경로
  String path2 = "/testBucket/WIFIDoIt"; //Firebase WIFI 할일 경로

  Serial.println("------------------------------------");
  Serial.println("Get double test...");
  
  
    //Also can use Firebase.get instead of Firebase.setInt
    if (Firebase.getString(firebaseData, path))
    {
      Serial.print("WIFIControl VALUE: ");
      printResult(firebaseData);
      Serial.println("------------------------------------");
      Serial.println();
      
    }
    if (Firebase.getString(firebaseData, path2))
    {
      Serial.print("WIFIControl VALUE: ");
      printResult2(firebaseData);
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
String data_checks = ""; //와이파이 값 저장
void printResult2(FirebaseData &data)
{
    if (data.dataType() == "int")
        Serial.println(data.intData());

    else if (data.dataType() == "string")
    {       
            String aa = data.stringData();
            aa.remove(0,2);// "/제거
            aa.remove(aa.length()-2, aa.length()-1);// "/제거
            aa += ","; // 값을 한번만 전달하기 위한 제어 문자

            if(count_check == 0)
            {
              data_checks += aa;
              count_check = 1;
              
              char a[50];        
              aa.toCharArray(a,50);
              Serial.print("할일 : ");
              Serial.println(a);
              s.write(a);
              
            }
            else{
              if(data_checks == aa){ // 값을 한번만 전달하기 위함
                  Serial.println("특수문자");
                }
                else{
                  Serial.println("초기화");
                  count_check = 0;
                  data_checks = "";
                  }
            }
            //Serial.print("값 뭐로 저장? : "); // 값 확인
            //Serial.println(data_checks);
    delay(1000);
    }
    
}
void printResult(FirebaseData &data)
{

    if (data.dataType() == "int")
        Serial.println(data.intData());

    else if (data.dataType() == "string")
    {        
            int a;
            a = data.stringData().toInt();
            s.write(a);//a.toInt()
            //Serial.print("제어 : "); //값 확인
            //Serial.println(a);

    }
    
}

void loop()
{ 
  String path = "/testBucket/WIFIControl";//경로
  String path2 = "/testBucket/WIFIDoIt";
  delay(5000);
  if (Firebase.getString(firebaseData, path))
    {
      Serial.print("WIFIControl VALUE: ");
      printResult(firebaseData);
      Serial.println("------------------------------------");
      Serial.println();   
    }
  if (Firebase.getString(firebaseData, path2))
    {
      Serial.print("WIFIControl VALUE: ");
      printResult2(firebaseData);
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
