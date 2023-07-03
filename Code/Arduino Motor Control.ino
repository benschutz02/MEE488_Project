// C++ code
//
# include <AccelStepper.h>

AccelStepper stepper; // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5
String x; // string to communicate w python

// timing for carriage open/close (in milliseconds)
const unsigned long phone = 1000;
const unsigned long tablet = 100;
const unsigned long laptop = 50;

// pins on arduino
int couple1 = 51;
int couple2 = 53;

int carriage1 = 41;
int carriage2 = 43;

int stop = 20;

void setup()
{
  //Built in LED
  pinMode(LED_BUILTIN,OUTPUT);
  
  // carriage actuator pins
  pinMode(carriage1, OUTPUT);
  pinMode(carriage2, OUTPUT); 
  pinMode(9, INPUT_PULLUP); // Input for extend
  pinMode(8,INPUT_PULLUP); // Input for retract

  // stop switch
  pinMode(stop,OUTPUT);

  // coupling/decoupling system
  pinMode(couple1, OUTPUT);
  pinMode(couple2, OUTPUT); 
  pinMode(11, INPUT_PULLUP); // Input for couple
  pinMode(10,INPUT_PULLUP); // Input for decouple
  digitalWrite(couple1, HIGH); // Initialize pin 50 as HIGH
  digitalWrite(couple2, HIGH); // Initialize pin 51 as HIGH

  // stepper motor
  stepper.setMaxSpeed(4000);
  stepper.setSpeed(0);
  pinMode(13, INPUT_PULLUP); // Input for Raise Button
  pinMode(12, INPUT_PULLUP); // Input for Lower Button 

  // begin serial output
  Serial.begin(9600);
}

void loop()
{
  char val = '0';
  int i = 0;

  /* MANUAL OVERRIDES */

  // stepper motor
  if(digitalRead(13) == LOW){
   stepper.setSpeed(500);
   stepper.runSpeed();
  }
  else if(digitalRead(12) == LOW){
   stepper.setSpeed(-500);
   stepper.runSpeed();
  }

  // coupling/decoupling
  if(digitalRead(11) == HIGH & digitalRead(10) == LOW){
    // Retract linear actuator 
    digitalWrite(50, HIGH);
    digitalWrite(51, LOW);
  }else if(digitalRead(10) == HIGH & digitalRead(11) == LOW){
    // Extend linear actuator 
    digitalWrite(50, LOW);
    digitalWrite(51, HIGH);
  }else{
    // Stops linear actuator
    digitalWrite(50, HIGH);
    digitalWrite(51, HIGH);
  }

  // carriage
  // coupling/decoupling
  if(digitalRead(8) == HIGH & digitalRead(9) == LOW){
    // Retract linear actuator 
    digitalWrite(50, HIGH);
    digitalWrite(51, LOW);
  }else if(digitalRead(9) == HIGH & digitalRead(8) == LOW){
    // Extend linear actuator 
    digitalWrite(50, LOW);
    digitalWrite(51, HIGH);
  }else{
    // Stops linear actuator
    digitalWrite(50, HIGH);
    digitalWrite(51, HIGH);
  }




  /* APP SENDS */
  // check if something is writing, give visual confirmation if read
  if(!Serial.available() > 0){
    char val = Serial.read();

    digitalWrite(LED_BUILTIN,HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN,LOW);
  }
  
  // decide if carriage goes up, down, or gets released
  // Raise = 1, Release Actuators = 2, Release Carriage = 3, Item Hold Actuators = 4
  // Recouple System = 5

  // carry out functions
  if(val == '1'){
    x = "Raise";
    
    // raise until you hit the switch
    stepper.setSpeed(500);
    while (digitalRead(stop) == LOW){ // change the 'while' to whatever the switch pin is
      stepper.runSpeed();
      i++;
    }

    // drop a lil bit, then raise again slowly
    stepper.setSpeed(-500); 
    for (int i = 0;i<200;i++){
      stepper.runSpeed();
      i++;      
    }

    stepper.setSpeed(250);
    while(i<200){ // change the 'while' to whatever the switch pin is
      stepper.runSpeed();   
      i++;         
    }
    stepper.setSpeed(0);
    stepper.runSpeed();

  }else if (val == '2'){
    x = "Device Release";

    // Retract linear actuators 
    digitalWrite(40, HIGH);
    digitalWrite(41, LOW);

  }else if (val == '3'){
    x = "Carriage Release";

    // Retract linear actuator 
    digitalWrite(50, HIGH);
    digitalWrite(51, LOW);

  }else if (val == '4'){
    x = "Item Set";

    unsigned long time;

    // check which item it is
    switch(Serial.parseInt()){
      case 1:
      time = phone;

      case 2:
      time = tablet;

      case 3:
      time = laptop;
    }

    // move actuators to the time they need
    unsigned long start = millis();

    // Extend linear actuators 
    digitalWrite(40, LOW);
    digitalWrite(41, HIGH);

    // Stop linear actuators when they reach specific time
    while (!start-millis() == time);
    digitalWrite(40, HIGH);
    digitalWrite(41, HIGH);

  }else if (val == '5'){
    x = "Recouple";

    // Extend linear actuator, slowly turn wheel
    unsigned long start = millis();

    digitalWrite(50, LOW);
    digitalWrite(51, HIGH); 

    stepper.setSpeed(100);
    stepper.runSpeed();    

  }
  
  Serial.println(x);
}
