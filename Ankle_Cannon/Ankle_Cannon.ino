int Relay1 = 2;
int Relay2 = 3;
int pirPin = 4;    //the digital pin connected to the PIR sensor's output
int ledPin = 13;

int calibrationTime = 30;    // PIR Calibration    
long unsigned int lowIn;         

boolean lockLow = true;
boolean takeLowTime;  

int relayDelay = 1000;

void setup() 
{ 
  Serial.begin(9600);
  // Initialize the Relay
  Serial.println("setting the relay ");
  pinMode(Relay1, OUTPUT); //Set Pin2 as output 
  pinMode(Relay2, OUTPUT); //Set Pin3 as output 
  digitalWrite(Relay1, HIGH); //Turn off relay 
  digitalWrite(Relay2, HIGH); //Turn off relay
  // Intialize the IR Sensor
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(pirPin, LOW);

  //give the sensor some time to calibrate
  Serial.print("calibrating sensor ");
  for(int i = 0; i < calibrationTime; i++){
    Serial.print(".");
    digitalWrite(ledPin, HIGH);   //the led visualizes the sensors output pin state
    delay(500);
    digitalWrite(ledPin, LOW);   //the led visualizes the sensors output pin state
    delay(500);
  }
  Serial.println(" done");
  Serial.println("SENSOR ACTIVE");
  delay(50);
}

void loop() 
{ 
  // Check sensor
  // If someone trips sensor
  // then - Fire cannon, wait 5 seconds
  // else - Loop
  if(digitalRead(pirPin) == HIGH){
    digitalWrite(ledPin, HIGH);   //the led visualizes the sensors output pin state
    Serial.print("motion detected at ");
    Serial.print(millis()/1000);
    Serial.println(" sec"); 
    digitalWrite(Relay1, LOW); //Turn on relay
    Serial.println("relay on");
    delay(relayDelay/4);
    digitalWrite(Relay1, HIGH); //Turn off relay
    Serial.println("    relay off");
    digitalWrite(ledPin, LOW);   //the led visualizes the sensors output pin state
    delay(relayDelay * 5);
  } else {
    digitalWrite(Relay1, HIGH); //Turn off relay   
  }
} 
