#include <LiquidCrystal.h>
#include <Servo.h>  //서보모터 사용
Servo servo;
  int LLED = 11; //전등
  int BLED = 12; //보일러
  int ALED = 8; //에어컨
  int a = 13;
  
  #include<Wire.h>
  #define SLAVE 4

  
  int servoPin = 3;

  
  #include <SoftwareSerial.h>
  SoftwareSerial s(5,6);
  //String datad = "h";
  String inputs ="";
  
  int count_WiFi = 0; // 현관문 1번만 실행시키기 위한 변수

  
  void setup()
  {
    pinMode(LLED, OUTPUT);   
    pinMode(BLED, OUTPUT);   
    pinMode(ALED, OUTPUT);
    servo.attach(servoPin);   
    s.begin(9600);
    Wire.begin(); //Wire 라이브러리 초기화
    Serial.begin(9600); //직렬 통신 초기화
   
    servo.write(90);
  }

  void loop()
  {
    Wire.requestFrom(SLAVE, 1); //1 바이트 크기의 데이터 요청
    if ( s.available ( ) > 0 ) 
      {
        String datad = "";
        datad += s.read();
        Serial.print("datad: ");
        Serial.println(datad);
        input_check(datad);
        
      } 
      
      com();                                                          
      delay(1000);
      
    
  }

  void com()//우노끼리 통신
  {
    
    String input = "";
    //시리얼 통신으로 문자를 입력받기 위한 준비
    input += (char) Wire.read();//한번에 한문자를 읽으면
   
    Serial.print("input: \n");
    Serial.print(input);   

    input_check(input);  
  }
  
    
  void input_check(String input){//WIFI값 받아와서 제어
    if (input == "2" & count_WiFi == 0){
          servo.write(0);
          sound_on();
          input = "";
          count_WiFi = 1;      
    }
    
    if (input == "6" & count_WiFi == 1){
        servo.write(90);
        sound_off();
        input = "";
        count_WiFi = 0;
      }
      
    if (input == "3")
    {
        digitalWrite(LLED, HIGH);
        Serial.print("전등 ON \n");

   
    }
  
    if (input == "4")
    {
        digitalWrite(BLED, HIGH);
        Serial.print("보일러 ON \n");

    }
  
  if (input == "5")
    {
        digitalWrite(ALED, HIGH);
        Serial.print("에어컨 ON \n");

    }
  
    if (input == "9")
    {
        digitalWrite(LLED, LOW);
        Serial.print("전등 OFF \n");

    }
    
  
    if (input == "0" | input == "12")
    {
        digitalWrite(BLED, LOW);
        Serial.print("보일러 OFF \n");

    }
    
    if (input == "1" | input == "15")
    {
        digitalWrite(ALED, LOW);
        Serial.print("에어컨 OFF \n");

    }
  
    //여기 수정
  
    }



  void sound_on(){//door sound on
      delay(500);
      tone(13,829.6); delay(100); noTone(13); delay(100);
      tone(13,849.6); delay(100); noTone(13); delay(100);
      tone(13,869.6); delay(100); noTone(13); delay(100);
      tone(13,909.6); delay(100); noTone(13); delay(100);
  
      servo.write(0);
    }

  
  void sound_off(){//door sound off
      servo.write(90);
        
      tone(13,909.6); delay(100); noTone(13); delay(100);
      tone(13,869.6); delay(100); noTone(13); delay(100);
      tone(13,549.6); delay(100); noTone(13); delay(100);
      tone(13,529.6); delay(100); noTone(13); delay(100);  
    }
    
