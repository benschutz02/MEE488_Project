 
#include <AccelStepper.h>
 
AccelStepper stepper; // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5
 
void setup()
{  
   stepper.setMaxSpeed(4000);
   stepper.setSpeed(0);
   pinMode(13, INPUT_PULLUP); // Input for Button 1
   pinMode(12, INPUT_PULLUP); // Input for Button 2        
}
 
void loop()
{  
  if(digitalRead(13) == LOW){
   stepper.setSpeed(500);
   stepper.runSpeed();
  }
  else if(digitalRead(12) == LOW){
   stepper.setSpeed(-500);
   stepper.runSpeed();
  }
}
