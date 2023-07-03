
#include <AccelStepper.h>
 
AccelStepper stepper; // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5


void setup() {
  
// stepper
   stepper.setMaxSpeed(4000);
   stepper.setSpeed(0);
   pinMode(13, INPUT_PULLUP); // Input for raise
   pinMode(12, INPUT_PULLUP); // Input for lower 

  
// coupling
  pinMode(51, OUTPUT);
  pinMode(53, OUTPUT); 
  pinMode(11, INPUT_PULLUP); // Input for couple
  pinMode(10,INPUT_PULLUP); // Input for decouple

  digitalWrite(51, HIGH); // Initialize pin 50 as HIGH
  digitalWrite(53, HIGH); // Initialize pin 51 as HIGH

// carriage
  pinMode(41, OUTPUT);
  pinMode(43, OUTPUT); 
  pinMode(9, INPUT_PULLUP); // Input for grip
  pinMode(8,INPUT_PULLUP); // Input for release

  digitalWrite(41, HIGH); // Initialize pin 50 as HIGH
  digitalWrite(43, HIGH); // Initialize pin 51 as HIGH


  
}

void loop() {

// Start stepper
{  
  if(digitalRead(13) == LOW){
   stepper.setSpeed(500);
   stepper.runSpeed();
  }
  else if(digitalRead(12) == LOW){
   stepper.setSpeed(-500);
   stepper.runSpeed();
  }

// Start couple/decouple
    if(digitalRead(11)== HIGH & digitalRead(10) == LOW){
    // Retract linear actuator 
    digitalWrite(51, HIGH);
    digitalWrite(53, LOW);
  }
  else if(digitalRead(11)== LOW & digitalRead(10) == HIGH){
    // Extend linear actuator 
    digitalWrite(51, LOW);
    digitalWrite(53, HIGH);
}
  else{
    // Stops linear actuator
    digitalWrite(52, HIGH);
    digitalWrite(53, HIGH);
  }

// Start carriage
    if(digitalRead(8)== HIGH & digitalRead(9) == LOW){
    // Retract linear actuator 
    digitalWrite(41, HIGH);
    digitalWrite(43, LOW);
  }
  else if(digitalRead(8)== LOW & digitalRead(9) == HIGH){
    // Extend linear actuator 
    digitalWrite(41, LOW);
    digitalWrite(43, HIGH);
}
  else{
    // Stops linear actuator
    digitalWrite(41, HIGH);
    digitalWrite(43, HIGH);
  }
}

}
