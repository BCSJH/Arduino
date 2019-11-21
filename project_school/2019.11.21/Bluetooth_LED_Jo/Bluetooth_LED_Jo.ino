#include <LiquidCrystal.h>
#include <Servo.h>  //서보모터 사용

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Servo servo;

  int LLED = 10; //전등
  int BLED = 12; //보일러
  int ALED = 8; //에어컨
  int a = 13;
  
  unsigned long pre_time = 0;
  unsigned long cur_time = 0;
  //출처: https://geronimob.tistory.com/20 [Geronimo]

  
  #include<Wire.h>
  #define SLAVE 4

  
  int servoPin = 11;

  
  #include <SoftwareSerial.h>
  SoftwareSerial s(5,6);
  //String datad = "h";
  String inputs ="";
  
  int count_WiFi = 0;
  int WIFI_set = 0;

  // 소프트웨어 4 SPI 사용
  #define OLED_MOSI  2    // D1
  #define OLED_CLK   3   // D0
  #define OLED_DC    4
  #define OLED_CS    7
  #define OLED_RESET 9

  // OLED 디스플레이 선언
  Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

  void setup()
  {
    pre_time = millis();
    
    pinMode(LLED, OUTPUT);   
    pinMode(BLED, OUTPUT);   
    pinMode(ALED, OUTPUT);   
    s.begin(9600);

    servo.attach(servoPin);
    servo.write(90);//초기 서보모터 각도
    servo.detach();
    
    Wire.begin(); //Wire 라이브러리 초기화
    Serial.begin(9600); //직렬 통신 초기화

    // OLED 초기화                
    display.begin(SSD1306_SWITCHCAPVCC);
    display.setTextColor(WHITE);
    display.setTextSize(1);
    
    // 저전력을 위해 OLED 밝기 조정
    display.ssd1306_command(SSD1306_SETCONTRAST);
    display.ssd1306_command(0);
  
  }
  
  String doit = "";
  int doit_count = 1;
  //String doitCheck = "";
  
  void loop()
  {
      WIFI_data();//와이파이 데이터 출력
      com(); //우노끼리 통신하여 값 보내기                                                          
      delay(1000);

  }


  void com()//우노끼리 통신
  {
    
    String input = "";
    //시리얼 통신으로 문자를 입력받기 위한 준비
    input += (char) Wire.read();//한번에 한문자를 읽으면
   
    Serial.print("input: \n");
    Serial.print(input);   

    if (input == "2"){
      Serial.print("여기 도착했지?????");
      sound_on();
      input = "";    
    }
    else if (input == "6"){
      Serial.print("여기 도착했지?????");
      sound_off();
      input = "";    
    }     
    else{
      input_check(input);
    }
  }

  
  void WIFI_data(){//와이파이 값 가져와서 제어
    Wire.requestFrom(SLAVE, 1); //1 바이트 크기의 데이터 요청
    if ( s.available ( ) > 0 ) 
      {
        char a;
        String datad = "";
        String datads = "";
        String news = ""; 
        //datad += s.read();
        
        cur_time = millis();//loop문
              a += s.read();
              datad += a;//할일
              
              Serial.print("a : ");
              Serial.println(a);
              Serial.print("제어 : ");
              //datad += (int)t;
              int ints = (int)a;
              news += (int)a;//제어
              
              Serial.print("datad : ");
              Serial.println(datad);        
   
          if ((ints != 0 & ints != 1 & ints != 2 & ints != 3 & ints != 4 & ints != 5 & ints != 9 & ints != 12 & ints != 15) & doit_count == 1)
          {
            if (datad.equals(","))// doit 넣기
            {
              Serial.print(",찍혔어"); 
              doit_count = 0;
              pre_time = cur_time; // 일정 시간마다 반복
            }
            if(doit_count == 1)
            {
              doit += a;
              Serial.print("doit: ");
              Serial.println(doit);
              Serial.print("count : ");
              Serial.println(doit_count);
            }
        }
        
        if (news == "0" | news == "1" | news == "2" | news == "3" | news == "4" | news == "5" | news == "9" | news == "12" | news == "15")
        {
          WIFI_set += 1;
          Serial.print("WIFI");
          Serial.println(WIFI_set);
          input_check(news);
          WIFI_set = 0;
          doit_count == 1;
          }      
      } 
    }  
    
    void input_check(String input){//WIFI값 받아와서 제어
      Serial.println(WIFI_set);
      Serial.println(input);
      Serial.println(count_WiFi);
      if (WIFI_set == 1 & input == "2" & count_WiFi == 0){
            Serial.print("여기 도착했어?");
            sound_on();
            input = "";
            count_WiFi++;      
      }
      else if (WIFI_set == 1 & input == "6" & count_WiFi == 1){
          sound_off();
          input = "";
          count_WiFi = 0;
        }
        
      else if (input == "3")
      {
          digitalWrite(LLED, HIGH);
          Serial.print("전등 ON \n");

          oled();
          display.setCursor(37,0);             // Start at top-left corner
          display.print(F("LIGHT"));
          display.setCursor(55,17); 
          display.print(F("ON"));
          display.display();
          delay(4000);
  
          oled();
          display.setCursor(5,0);             // Start at top-left corner
          display.print("SMART HOME    IOT");
          display.display();

  
      }
    
      else if (input == "4")
      {
          digitalWrite(BLED, HIGH);
          Serial.print("보일러 ON \n");

          oled();
          display.setCursor(32,0);             // Start at top-left corner
          display.print(F("BOILER"));
          display.setCursor(55,17); 
          display.print(F("ON"));
          display.display();
          delay(4000);
  
          oled();
          display.setCursor(5,0);             // Start at top-left corner
          display.print("SMART HOME    IOT");
          display.display();

      }
    
    else if (input == "5")
      {
          digitalWrite(ALED, HIGH);
          Serial.print("에어컨 ON \n");
  
          oled();
          display.setCursor(10,0);             // Start at top-left corner
          display.print(F("AIR"));
  
          display.setTextSize(1);
          display.setCursor(60,0);  
          display.print(F("conditioner"));
  
          display.setTextSize(2);
          display.setCursor(55,17); 
          display.print(F("ON"));
          display.display();
          delay(4000);
  
          oled();
          display.setCursor(5,0);             // Start at top-left corner
          display.print("SMART HOME    IOT");
          display.display();
  
      }
    
      else if (input == "9")
      {
          digitalWrite(LLED, LOW);
          Serial.print("전등 OFF \n");
  
          oled();
          display.setCursor(38,0);             // Start at top-left corner
          display.print(F("LIGHT"));
          display.setCursor(50,17); 
          display.print(F("OFF"));
          display.display();
          delay(4000);
  
          oled();
          display.setCursor(5,0);             // Start at top-left corner
          display.print("SMART HOME    IOT");
          display.display();
      }
      
    
      else if (input == "0" | input == "12")
      {
          digitalWrite(BLED, LOW);
          Serial.print("보일러 OFF \n");
  
          oled();
          display.setCursor(32,0);             // Start at top-left corner
          display.print(F("BOILER"));
          display.setCursor(50,17); 
          display.print(F("OFF"));
          display.display();
          delay(4000);
  
          oled();
          display.setCursor(5,0);             // Start at top-left corner
          display.print("SMART HOME    IOT");
          display.display();
  
      }
      
      else if (input == "1" | input == "15")
      {
          digitalWrite(ALED, LOW);
          Serial.print("에어컨 OFF \n");
  
          oled();
          display.setCursor(10,0);             // Start at top-left corner
          display.print(F("AIR"));
  
          display.setTextSize(1);
          display.setCursor(60,0);  
          display.print(F("conditioner"));
  
          display.setTextSize(2);
          display.setCursor(50,17); 
          display.print(F("OFF"));
          display.display();
          delay(4000);
  
          oled();
          display.setCursor(5,0);             // Start at top-left corner
          display.print("SMART HOME    IOT");
          display.display();
      }
    
        //마스터 우노
      else // node mcu에서 가져온 값
      {
          Serial.print("node mcu가 보낸값 :"); //
          Serial.println(input); //node mcu에서 전송한 할일 텍스트 출력
       }
   
     }



  void sound_on(){//door sound on
      servo.attach(servoPin);
      servo.write(0);
      tone(13,829.6); delay(100); noTone(13); delay(100);
      tone(13,849.6); delay(100); noTone(13); delay(100);
      tone(13,869.6); delay(100); noTone(13); delay(100);
      tone(13,909.6); delay(100); noTone(13); delay(100);
      servo.detach();
    }

  
  void sound_off(){//door sound off
      servo.attach(servoPin);
      servo.write(90);
      tone(13,909.6); delay(100); noTone(13); delay(100);
      tone(13,869.6); delay(100); noTone(13); delay(100);
      tone(13,549.6); delay(100); noTone(13); delay(100);
      tone(13,529.6); delay(100); noTone(13); delay(100); 
      servo.detach(); 
    }

 void oled(){// oled 반복
        display.clearDisplay();
        display.setTextSize(2);             // Normal 1:1 pixel scale
       // display.setTextColor(SSD1306_WHITE);        // Draw white text
  }
