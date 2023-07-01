// C++ code
//
# include <AccelStepper.h>

int t = 500; // time (microseconds)
bool actuator = LOW;
String x;



void setup()
{
  //Built in LED
  pinMode(LED_BUILTIN,OUTPUT);

  // stepper motor pins
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  
  // linear actuator pins
  pinMode(3,OUTPUT); // carriage arms
  pinMode(4,OUTPUT); // stepper motor
  
  // begin serial output
  Serial.begin(9600);
}

void loop()
{
  val = 0;

  // check if something is writing, give visual confirmation if read
  while (!Serial.available() > 0);
  char val = Serial.read();

  digitalWrite(LED_BUILTIN,HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN,LOW);
  
  // decide if carriage goes up, down, or gets released
  // Raise = 1, Release Actuators = 2, Release Carriage = 3, Item Hold Actuators = 4
  // Reset System = 5

  // carry out functions
  if(val == '1'){
    x = "Raise";
    
    // raise until you hit the switch
    digitalWrite(6,HIGH);
    while (i < 1000; i++){ // change the 'while' to whatever the switch pin is
    	digitalWrite(7,HIGH);
    	delayMicroseconds(t);
  		digitalWrite(7,LOW);
  		delayMicroseconds(t);
    }


    // drop a lil bit, then raise again slowly
    digitalWrite(6,LOW);
    for (int i = 0;i<200;i++){
    	digitalWrite(7,HIGH);
    	delayMicroseconds(t);
  		digitalWrite(7,LOW);
  		delayMicroseconds(t);
    }

    digitalWrite(6,HIGH);
    while (i < 1000; i++){ // change the 'while' to whatever the switch pin is
    	digitalWrite(7,HIGH);
    	delayMicroseconds(2*t);
  		digitalWrite(7,LOW);
  		delayMicroseconds(2*t);
    }    

  }else if (val == '2'){
    x = "Device Release";

    digitalWrite(3,HIGH);

  }else if (val == '3'){
    x = "Carriage Release";

    digitalWrite(4,HIGH);

  }else if (val == '4'){
    x = "Item Set";

    // send confirmation

    // check which item it is

    // move actuators to the time they need

  }else if (val == '5'){
    x = "Reset";

    // Open carriage arms
    // check if recoupled (recouple if not)
    // raise to drop height
    

  }
  
  Serial.println(x);
}
