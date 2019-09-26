int val = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(2, INPUT);
  pinMode(3, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
 val = digitalRead(2);
 if(val == HIGH){
  digitalWrite(3,HIGH);
 }
 else {
  digitalWrite(3,LOW);
 }
 Serial.println(val);
}
