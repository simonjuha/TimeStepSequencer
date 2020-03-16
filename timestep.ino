// Pins
int timePots[8] = {20, 19, 18, 17, 21, 16, 15, 14}; // 8 pots for time (read)
int cvPots[8] = {10, 9, 8, 7, 6, 5, 4, 3}; // 8 pots for CV (write)
int pulsePin = 12; // clock/pulse/trigger pin (output)
int mult4Pin = 2; // switch
int mult2Pin = 1; // switch
int randPin = 0; // switch
int dirPin = 11; // switch
int runPin = 13; // switch

// Settings
bool x2 = false;
bool x4 = false;
bool randomize = false;
bool forward = false;
bool runSeq = true;

// Time
int curTimeStep = 0;
int timeStep = 0;

// Setup
void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(22)); // use pin 22 for random seed
  //set cv pots to output
  for (int i = 1; i == 8; i++) {
    pinMode(i, OUTPUT);
  }
  pinMode(pulsePin, OUTPUT);
  // switches detect connection to ground
  pinMode(mult4Pin, INPUT_PULLUP);
  pinMode(mult2Pin, INPUT_PULLUP);
  pinMode(randPin, INPUT_PULLUP);
  pinMode(dirPin, INPUT_PULLUP);
  pinMode(runPin, INPUT_PULLUP);

}

void loop() {
  // setting readings
  runSeq = digitalRead(runPin);
  x2 = digitalRead(mult2Pin);
  x4 = digitalRead(mult4Pin);
  forward = digitalRead(dirPin);
  randomize = digitalRead(randPin);
  runSeq = digitalRead(runPin);
  
if(runSeq == false){ // is run switch on?
  if (randomize) { // is random switch on?
    if (forward == false) { // is forward switch back or forth?
      if (curTimeStep > 7) { // is the current step larger than 8?
        curTimeStep = 0; // new sycle / reset
      }
      else {
        curTimeStep++; // next step
      }
    } else if (forward == true) { // go backwards
      if (curTimeStep < 1) {
        curTimeStep = 7;
      }
      else {
        curTimeStep--; // step back
      }
    }
  } else {
    curTimeStep = random(0, 7); // set random step
  }

timeStep = analogRead(timePots[curTimeStep]); // read current timestep pot
  Serial.println(timeStep);
  if (x2) { 
    timeStep = timeStep * 2; // double time
  }
  if (x4) {
    timeStep = timeStep * 4; // quadrupel time
  }
  digitalWrite(cvPots[curTimeStep], HIGH); // active CV pot

if (timeStep > 10) { // min time
  digitalWrite(pulsePin, HIGH); // PULSE the pin
  Serial.println("PULSE!");
  delay(1); // 1ms length of pulse
  digitalWrite(pulsePin, LOW); // turn off pin
 }
  
  delay(timeStep);
  digitalWrite(cvPots[curTimeStep], LOW); // set pot to LOW
  
}
}
