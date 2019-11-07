  int LLED = 11; //전등
  int BLED = 12; //보일러
  int ALED = 13; //에어컨
  
  #include<Wire.h>
  #define SLAVE 4
  
  #include <SoftwareSerial.h>
  SoftwareSerial s(5,6);
  //String datad = "h";
  void setup()
  {
    pinMode(LLED, OUTPUT);   
    pinMode(BLED, OUTPUT);   
    pinMode(ALED, OUTPUT);   
    s.begin(9600);
    Wire.begin(); //Wire 라이브러리 초기화
    Serial.begin(9600); //직렬 통신 초기화
  }

  void loop()
  {
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
  
  void com()
  {
    Wire.requestFrom(SLAVE, 1); //1 바이트 크기의 데이터 요청
    
    String input = "";
    //시리얼 통신으로 문자를 입력받기 위한 준비를 합니다.
    input += (char) Wire.read();//한번에 한문자를 읽으면
   
   Serial.print("input: \n");
   Serial.print(input);
   
  input_check(input);  
}

void input_check(String input){//WIFI
  
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
  if(input == "2")
  {
     Wire.onRequest(com);
     Wire.write("2");
  } 
  }
