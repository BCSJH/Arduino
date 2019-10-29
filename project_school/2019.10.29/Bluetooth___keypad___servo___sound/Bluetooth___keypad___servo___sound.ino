#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <Servo.h> 
#include <Keypad.h>

Servo servo;

int servoPin = 11;
int angle = 0; // servo position in degrees 
int trues =0;
int count= 0;
char pw[4] = {'1','2','3','4'};

const byte ROWS = 4;
const byte COLS = 4;
byte rowpins[ROWS] = {9,8,7,6};
byte colpins[COLS] = {5,4,3,2};
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'} 
};


Keypad keypad = Keypad( makeKeymap(keys), rowpins, colpins, ROWS, COLS);

SoftwareSerial BTSerial(12, 10);   
String datas = "";

void setup() {  
  Serial.begin(9600);
  BTSerial.begin(9600);
  //pinMode(13, OUTPUT);

  Serial.begin(9600);
  servo.attach(servoPin);
  pinMode(5,OUTPUT);//부저
  servo.write(90);//초기 서보모터 각도

}
void loop() {
  keypad_sound();
  if (BTSerial.available()){
    char data = BTSerial.read();
    datas = datas + data;
    Serial.write(data);

  }
    
  if (Serial.available())
  {
    BTSerial.write(Serial.read());
  }
  control();       
}

void control(){
  if(datas == "2"){
      sound_on();
      datas = "";
    }
  if(datas == "3"){//전등 ON

     // datas = "";
    }
  if(datas == "4"){//보일러 ON

      //datas = "";
    }
  if(datas == "5"){//에어컨 ON

      //datas = "";
    }

  if(datas == "6"){//현관문 OFF
      sound_off();
      datas = "";
    }  
  if(datas == "9"){//전등 OFF
      
    }
  if(datas == "12"){//보일러 OFF
      
    }
  if(datas == "15"){//에어컨 OFF

      //datas = "";
    } 
  }

void keypad_sound(){//키패드 사운드
  char key = keypad.getKey();
  
  if (key){
    Serial.println(key);
      if(key == pw[count]){
        count++;
        trues++;
        if(count==4)
        {
          sound();
        }
        else{
          servo.write(90);
          }
      }
      else{
        count++;
        }
    if(key == '#'){
      trues = 0;
      count = 0;
      }
    if(count > 4){
      delay(500);
      for(int i =0; i<10; i++){
          tone(13,589.6); delay(50); noTone(13); delay(100);
        }
      trues = 0;
      count = 0;
      }
    }  
  }

void sound(){//사운드
    
    sound_on();
    
    delay(3000); 
    
    sound_off();
    count = 0;
    trues = 0; 
  }

  void sound_on(){
  
    delay(500);
    tone(13,829.6); delay(100); noTone(13); delay(100);
    tone(13,849.6); delay(100); noTone(13); delay(100);
    tone(13,869.6); delay(100); noTone(13); delay(100);
    tone(13,909.6); delay(100); noTone(13); delay(100);
          /*
          tone(13,329.6); delay(200); noTone(13); delay(200);
          tone(13,261.6); delay(200); noTone(13); delay(200);
          tone(13,371.6); delay(200); noTone(13); delay(200);
          */        
  
    servo.write(0); 
    }

  
  void sound_off(){
    servo.write(90);
      
    tone(13,909.6); delay(100); noTone(13); delay(100);
    tone(13,869.6); delay(100); noTone(13); delay(100);
    tone(13,549.6); delay(100); noTone(13); delay(100);
    tone(13,529.6); delay(100); noTone(13); delay(100);  
    }
