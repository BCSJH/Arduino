void setup() {
  // put your setup code here, to run once:
  pinMode(3,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i = 10; i< 255; i=i+10){
    analogWrite(3,i);
    delay(100);
  }
}
