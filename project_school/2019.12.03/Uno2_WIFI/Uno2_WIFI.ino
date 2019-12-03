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
  SoftwareSerial s(5, 6);

  int count_WiFi = 0; //현관문 한번만 실행하기 위한 제어 변수
  int WIFI_set = 0;//WIFI 한번만 실행 하기 위한 변수

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

    //oled 초기 화면
    oled_dsc();
    oled_pv();

  }

  String doit = ""; //nodemcu에서 불러온 값을 저장할 변수
  int doit_count = 1; //nodemcu에서 불러온 값을 우노에서 1번만 실행시키기위한 카운트 변수

  void loop()
  {
    cur_time = millis();

    WIFI_data();//와이파이 데이터 출력
    com(); //우노끼리 통신하여 값 보내기                                                          
    delay(1000);

  }


  void com()//우노끼리 통신
  {

    String input = "";
    //시리얼 통신으로 문자를 입력받기 위한 준비
    input += (char)Wire.read();//한 `번에 한문자를 읽으면

    //값 전달 확인
    //Serial.print("input: \n");
    //Serial.print(input);

    if (input == "2") { // 현관문 ON
      //Serial.print("여기 도착했지?????"); //값 전달 확인
      sound_on();
      input = "";
    }
    else if (input == "6") { //현관문 OFF
      //Serial.print("여기 도착했지?????");//값 전달 확인
      sound_off();
      input = "";
    }

    else if (input == "0"){
      digitalWrite(BLED, LOW);
      Serial.print("보일러 OFF \n");

      oled_dsc(); // oled (삭제, 크기, 컬러)
      display.setCursor(32, 0);             // Start at top-left corner
      display.print(F("BOILER"));
      display.setCursor(50, 17);
      display.print(F("OFF"));
      display.display();
      delay(3000);
      oled_dsc(); // oled (삭제, 크기, 컬러)
      oled_pv; //oled (위치, 값)
    }
    else {
      input_check(input);
    }
  }


  void WIFI_data() {//와이파이 값 가져와서 제어
    Wire.requestFrom(SLAVE, 1); //1 바이트 크기의 데이터 요청
    if (s.available() > 0)
    {
      char a;
      String datad = "";
      String news = "";

      cur_time = millis();//loop문
      a += s.read(); //char형으로 nodemcu 데이터 값을 1개씩 읽음
      if((int)a==32){
        doit += " ";
        Serial.println("스페이스 등장");
      }
      datad += a;//할일 //datad에 읽은 데이터값을 저장

      Serial.print("a : ");
      Serial.println(a);
      Serial.print("제어 : ");

     
      
      int ints = (int)a; //a를 int형으로 ints에 저장
      news += (int)a;//제어 //a를 int형으로 news에 누적 저장
      
      Serial.println("news:"); //기기 제어용 변수
      Serial.println(news);
      
      Serial.print("datad : "); //할일 제어용 변수
      Serial.println(datad);

      if ((ints != 0 & ints != 1 & ints != 2 & ints != 3 & ints != 4 & ints != 5 &  ints != 6 &ints != 9 & ints != 12 &  ints != 11 & ints != 15 & ints != ' ') & doit_count == 1)
      {
        if (datad.equals(","))// ,로 원하는 데이터값만 추출되게 하는 조건문
        {
          //Serial.print(",찍혔어"); // 값 전달 확인
          doit_count = 0;

          if (cur_time - pre_time >= 5000) //5초마다 출력
          {
            
            //Serial.println("시간초 실행");
            display.clearDisplay();
            display.setTextSize(1);             // Normal 1:1 pixel scale
            display.setTextColor(SSD1306_WHITE);        // Draw white text
            display.setCursor(0, 0);             // Start at top-left corner
            display.print(doit);
            display.display();
            delay(5000);

            //oled 초기 화면
            oled_dsc();
            oled_pv();
            
            pre_time = cur_time; // 5초마다 출력
            doit_count = 1;
            doit = "";
          }
          
           // 값 확인
          //Serial.print("cur_time");
          //Serial.println(cur_time);
          //Serial.print("pre_time");
          //Serial.println(pre_time);
        }
        if (doit_count == 1) //할일 출력
        {
          doit += a;
          Serial.print("doit: ");
          Serial.println(doit);
          Serial.print("count : ");
          Serial.println(doit_count);
        }
      }

      if (news == "0" | news == "1" | news == "2" | news == "3" | news == "4" | news == "5" | news == "6" | news == "9" | news == "12" | news == "15") //제어 (할일 메모 제외) -> 현관문, 보일러, 에어컨, 전등
      {
        
        WIFI_set += 1;
        Serial.print("WIFI");
        Serial.println(WIFI_set);
        input_check(news);
        WIFI_set = 0;
        doit_count == 1; //
      }
    }
  }

  void input_check(String input) //WIFI값 받아와서 제어
  {
    //값 전달 확인
    Serial.println(WIFI_set);
    Serial.println(input);
    Serial.println(count_WiFi);
    if (WIFI_set == 1 & input == "2" & count_WiFi == 0) { //현관문 ON
      //Serial.print("여기 도착했어?"); // 값 확인
      sound_on();
      input = "";
    }
    else if (WIFI_set == 1 & input == "6" & count_WiFi == 1) { // 현관문 OFF
      sound_off();
      input = "";
    }
    
    else if (input == "3")//전등 ON
    {
      digitalWrite(LLED, HIGH);
      Serial.print("전등 ON \n");

      oled_dsc(); // oled (삭제, 크기, 컬러)
      display.setCursor(37, 0);             // Start at top-left corner
      display.print(F("LIGHT"));
      display.setCursor(55, 17);
      display.print(F("ON"));
      display.display();
      delay(3000);
      oled_dsc(); // oled (삭제, 크기, 컬러)
      oled_pv; //oled (위치, 값)
    }

    else if (input == "4") //보일러 ON
    {
      digitalWrite(BLED, HIGH);
      Serial.print("보일러 ON \n");

      oled_dsc(); // oled (삭제, 크기, 컬러)
      display.setCursor(32, 0);             // Start at top-left corner
      display.print(F("BOILER"));
      display.setCursor(55, 17);
      display.print(F("ON"));
      display.display();
      delay(3000);
      oled_dsc(); // oled (삭제, 크기, 컬러)
      oled_pv; //oled (위치, 값)

    }

    else if (input == "5") //에어컨 ON
    {
      digitalWrite(ALED, HIGH);
      Serial.print("에어컨 ON \n");

      oled_dsc(); // oled (삭제, 크기, 컬러)
      display.setCursor(10, 0);             // Start at top-left corner
      display.print(F("AIR"));
      display.setTextSize(1);
      display.setCursor(60, 0);
      display.print(F("conditioner"));
      display.setTextSize(2);
      display.setCursor(55, 17);
      display.print(F("ON"));
      display.display();
      delay(3000);
      oled_dsc(); // oled (삭제, 크기, 컬러)
      oled_pv; //oled (위치, 값)

    }

    else if (input == "9") //전등 OFF
    {
      digitalWrite(LLED, LOW);
      Serial.print("전등 OFF \n");

      oled_dsc();
      display.setCursor(38, 0);             // Start at top-left corner
      display.print(F("LIGHT"));
      display.setCursor(50, 17);
      display.print(F("OFF"));
      display.display();
      delay(3000);
      oled_dsc(); // oled (삭제, 크기, 컬러)
      oled_pv; //oled (위치, 값)
    }


    else if (input == "12") //보일러 OFF
    {
      digitalWrite(BLED, LOW);
      Serial.print("보일러 OFF \n");

      oled_dsc(); // oled (삭제, 크기, 컬러)
      display.setCursor(32, 0);             // Start at top-left corner
      display.print(F("BOILER"));
      display.setCursor(50, 17);
      display.print(F("OFF"));
      display.display();
      delay(3000);
      oled_dsc(); // oled (삭제, 크기, 컬러)
      oled_pv; //oled (위치, 값)

    }

    else if (input == "1" | input == "15") //에어컨 OFF
    {
      digitalWrite(ALED, LOW);
      Serial.print("에어컨 OFF \n");

      oled_dsc(); // oled (삭제, 크기, 컬러)
      display.setCursor(10, 0);             // Start at top-left corner
      display.print(F("AIR"));
      display.setTextSize(1);
      display.setCursor(60, 0);
      display.print(F("conditioner"));
      display.setTextSize(2);
      display.setCursor(50, 17);
      display.print(F("OFF"));
      display.display();
      delay(3000);
      oled_dsc(); // oled (삭제, 크기, 컬러)
      oled_pv; //oled (위치, 값)

    }

    //마스터 우노
    else // node mcu에서 가져온 값
    {
      //지정된 이외의 값 데이터 받아올 시 기본 화면 출력
      oled_dsc(); // oled (삭제, 크기, 컬러)
      oled_pv; //oled (위치, 값)

      //값 전달 확인
      Serial.print("node mcu가 보낸값 :"); //
      Serial.println(input); //node mcu에서 전송한 할일 텍스트 출력
    }

  }



  void sound_on() 
  {//door sound on
    count_WiFi++;
    
    servo.attach(servoPin);
    servo.write(0);
    tone(13, 829.6); delay(100); noTone(13); delay(100);
    tone(13, 849.6); delay(100); noTone(13); delay(100);
    tone(13, 869.6); delay(100); noTone(13); delay(100);
    tone(13, 909.6); delay(100); noTone(13); delay(100);
    servo.detach();

    oled_dsc(); // oled (삭제, 크기, 컬러)
    display.setCursor(0, 0);             // Start at top-left corner
    display.print(F("DOOR OPEN"));
    display.display();
    delay(3000);

    oled_dsc();
    oled_pv();
  }


  void sound_off() 
  {//door sound off
    count_WiFi = 0; /
    
    servo.attach(servoPin);
    servo.write(90);
    tone(13, 909.6); delay(100); noTone(13); delay(100);
    tone(13, 869.6); delay(100); noTone(13); delay(100);
    tone(13, 549.6); delay(100); noTone(13); delay(100);
    tone(13, 529.6); delay(100); noTone(13); delay(100);
    servo.detach();

    oled_dsc(); // oled (삭제, 크기, 컬러)
    display.setCursor(0, 0);             // Start at top-left corner
    display.print(F("DOOR CLOSE"));
    display.display();
    delay(3000);

    oled_dsc();
    oled_pv(); 
   }

  void oled_dsc() // oled (삭제, 사이즈, 컬러)
  {
    display.clearDisplay();
    display.setTextSize(2);             // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE);        // Draw white text
  }

  void oled_pv()  //oled  (위치, 값)
  {
    display.setCursor(5, 0);             // Start at top-left corner
    display.print("SMART HOME    IOT");
    display.display();

  }
