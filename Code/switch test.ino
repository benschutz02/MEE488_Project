
void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN,OUTPUT);
  pinMode(9,OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  bool val = digitalRead(9);


  while(val == LOW){
    digitalWrite(LED_BUILTIN,HIGH);
    val = digitalRead(9);
  }

  digitalWrite(LED_BUILTIN,LOW);

}
