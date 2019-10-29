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
void setup() 
{ 
  Serial.begin(9600);
  servo.attach(servoPin);
  pinMode(5,OUTPUT);//부저
  servo.write(90);//초기 서보모터 각도
} 

void loop() 
{ 
  keypad_sound();
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
  delay(500);
  tone(13,529.6); delay(100); noTone(13); delay(100);
  tone(13,549.6); delay(100); noTone(13); delay(100);
  tone(13,569.6); delay(100); noTone(13); delay(100);
  tone(13,589.6); delay(100); noTone(13); delay(100);
          /*
          tone(13,329.6); delay(200); noTone(13); delay(200);
          tone(13,261.6); delay(200); noTone(13); delay(200);
          tone(13,371.6); delay(200); noTone(13); delay(200);
          */        
  servo.write(0); 
  delay(3000); 
  servo.write(90);
    
  tone(13,589.6); delay(100); noTone(13); delay(100);
  tone(13,569.6); delay(100); noTone(13); delay(100);
  tone(13,549.6); delay(100); noTone(13); delay(100);
  tone(13,529.6); delay(100); noTone(13); delay(100);
  
  count = 0;
  trues = 0; 
  }
