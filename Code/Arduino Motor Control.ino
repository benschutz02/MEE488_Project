// C++ code
//


int t = 500; // time (microseconds)
bool actuator = LOW;
  
void setup()
{
  // stepper motor pins
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  
  // linear actuator pin
  pinMode(3,OUTPUT);
  
  // begin serial output
  Serial.begin(9600);
}

void loop()
{
  
  // check if someone is writing
  while (Serial.available() == 0) {
  }
  
  // read serial monitor
  int val = Serial.parseInt();// what button is pressed
  
  // decide if carriage goes up, down, or gets released
  // Up = 1, Down = 2, Release/Extend = 3

  // carry out functions
  switch (val){
  	case 1:
    	Serial.println("Carriage up!");
	
    
    	// 'up' direction
    	digitalWrite(6,HIGH);
        
    	for (int i = 0;i<200;i++){
    		digitalWrite(7,HIGH);
    		delayMicroseconds(t);
    		digitalWrite(7,LOW);
    		delayMicroseconds(t);
        }
    	
    	break;
    
    
    case 2:
        Serial.println("Carriage down!");

    
    	// 'down' direction
    	digitalWrite(6,LOW);
        
    	for (int i = 0;i<200;i++){
    		digitalWrite(7,HIGH);
    		delayMicroseconds(t);
    		digitalWrite(7,LOW);
    		delayMicroseconds(t);
        }
    	
    	break;
    
    case 3:
        Serial.println("Carriage release!");
    
    	// retract/extend linear actuator
    	actuator = !actuator;
    	digitalWrite(3,actuator);
    
    
    
    
    
    
    
    
  }
  
  
}