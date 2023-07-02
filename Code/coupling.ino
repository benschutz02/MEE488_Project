void setup() {
  pinMode(50, OUTPUT);
  pinMode(51, OUTPUT); 
  pinMode(13, INPUT_PULLUP); // Input for Button 1
  pinMode(12,INPUT_PULLUP); // Input for Button 2

  digitalWrite(50, HIGH); // Initialize pin 50 as HIGH
  digitalWrite(51, HIGH); // Initialize pin 51 as HIGH
  
}

void loop() {
  if(digitalRead(13)== HIGH & digitalRead(12) == LOW){
    // Retract linear actuator 
    digitalWrite(50, HIGH);
    digitalWrite(51, LOW);
  }
  else if(digitalRead(13)== LOW & digitalRead(12) == HIGH){
    // Extend linear actuator 
    digitalWrite(50, LOW);
    digitalWrite(51, HIGH);
}
  else{
    // Stops linear actuator
    digitalWrite(50, HIGH);
    digitalWrite(51, HIGH);
  }
  }
