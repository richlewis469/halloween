// The Relay Assemble as 2 Relays
int Relay1 = 2;
int Relay2 = 3;

// PIR Sensor will be on Pin 4
int pirPin = 4;    //the digital pin connected to the PIR sensor's output

// Status LED
int ledPin = 13;

int pirPinVal = LOW;
int calibrationTime = 15;    // PIR Calibration    

int loopCount = 5; // Set to Max to fire off the first time.
int loopCountMax = 5;

int relayDelay = 1000; // measure in Seconds
boolean readyToFire = true;

void setup() 
{ 
  Serial.begin(9600);
  // Initialize the Relay
  Serial.println("Initialize the relay ");
  pinMode(Relay1, OUTPUT); //Set Pin2 as output 
  pinMode(Relay2, OUTPUT); //Set Pin3 as output 
  digitalWrite(Relay1, HIGH); //Turn off relay 
  digitalWrite(Relay2, HIGH); //Turn off relay
  // Intialize the IR Sensor
  Serial.println("Initialize the sensor ");
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(pirPin, LOW);

  // Calibrate the PIRsensor
  Serial.print("Calibrating sensor ");
  for(int i = 0; i < calibrationTime; i++){
    // Give the sensor some time to calibrate
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
  pirPinVal = digitalRead(pirPin);
  
  if(pirPinVal == HIGH){
    digitalWrite(ledPin, HIGH);   //the led visualizes the sensors output pin state
    // Serial.print("Motion detected at ");
    // Serial.print(millis()/1000);
    // Serial.println(" sec"); 
    if (readyToFire == true) {
      // Serial.print("Ready to Fire Relay at ");
      // Serial.print(millis()/1000);
      // Serial.println(" sec"); 
      digitalWrite(Relay1, LOW); //Turn on relay
      Serial.println("  relay on");
      delay(relayDelay/4);
      digitalWrite(Relay1, HIGH); //Turn off relay
      Serial.println("    relay off");
      delay(50);
      readyToFire = false;
    }
    loopCount = 0;
  } else {
    loopCount++;
    digitalWrite(ledPin, LOW);   //the led visualizes the sensors output pin state
    if (loopCount > loopCountMax) {
      readyToFire = true;
      loopCount = 0;
    } 
  }
} 
