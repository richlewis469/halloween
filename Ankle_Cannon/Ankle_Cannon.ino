int Relay1 = 2;
int Relay2 = 3;

int relayDelay = 1000;

void setup() 
{ 
  pinMode(Relay1, OUTPUT); //Set Pin2 as output 
  pinMode(Relay2, OUTPUT); //Set Pin3 as output 
  digitalWrite(Relay1, HIGH); //Turn off relay 
  digitalWrite(Relay2, HIGH); //Turn off relay
  // Intialize the IR Sensor
}

void loop() 
{ 
  // Check sensor
  // If someone trips sensor
  // then - Fire cannon, wait 5 seconds
  // else - Loop
  
  digitalWrite(Relay1, HIGH); //Turn off relay 
  delay(relayDelay);
  digitalWrite(Relay2, HIGH); //Turn off relay 
  delay(relayDelay); 
  digitalWrite(Relay1, LOW); //Turn on relay
  delay(relayDelay);
  digitalWrite(Relay2, LOW); 
  delay(relayDelay); 
} 
