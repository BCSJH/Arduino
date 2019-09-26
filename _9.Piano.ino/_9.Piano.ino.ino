void setup() {
  // put your setup code here, to run once:
  pinMode(5,OUTPUT);
  pinMode(6,INPUT);
  pinMode(7,INPUT);
  pinMode(8,INPUT);
  pinMode(9,INPUT);
  pinMode(10,INPUT);
  pinMode(11,INPUT);
  pinMode(12,INPUT);
  pinMode(13,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(13) == HIGH){
    tone(5, 130.8);
  }
  else if(digitalRead(12) == HIGH){
    tone(5, 155.6);
  }
  else if(digitalRead(11) == HIGH){
    tone(5, 164.8);
  }
  else if(digitalRead(10) == HIGH){
    tone(5, 174.6);
  }
  else if(digitalRead(9) == HIGH){
    tone(5, 196.0);
  }
  else if(digitalRead(8) == HIGH){
    tone(5, 220.0);
  }
  else if(digitalRead(7) == HIGH){
    tone(5, 246.9);
  }
  else if(digitalRead(6) == HIGH){
    tone(5, 261.6);
  }
  else{
    noTone(5);
  }
}
