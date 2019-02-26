#include <SimpleTimer.h>
#include <NewPing.h>

// -------------------- Stuff --------------------
SimpleTimer timer;
//boolean defaulting = true;

// Start Button
const int startButton = 7;

// Motor Pins
const int leftMotorDir = 9;
const int rightMotorDir = 8;
const int pwmLeft = 12;
const int pwmRight = 11;

//Motor settings
int maxSpeed = 255; // PWM Maximal analog value

// Infrared Sensors
const int iRLeft = 49;
const int iRSCenter = 47;
const int iRSRight = 45;
const int iRInterruptPin = 0;

const int echoPin = 2;
const int sonarNum = 5;
const int maxDistance = 125; // Max Distance in cm
const int pingInterval = 33;
unsigned long pingTimer[sonarNum];
uint8_t currentSensor = 0;

NewPing sonar[sonarNum] = {
  NewPing(30, echoPin, maxDistance), //Left
  NewPing(27, echoPin, maxDistance), // Right
  NewPing(28, echoPin, maxDistance), //Font Left
  NewPing(29, echoPin, maxDistance), //Front Right
  NewPing(26, echoPin, maxDistance), //Front Center
};

// Line Sensors
const int lineSFrontRight = 53;
const int lineSFrontLeft = 51;
const int lineSBackRight = 50;
const int lineSBackLeft = 52;

const int lineSInterruptPin = 3;

// Code Switch
const int codeSwitch[] = {32, 34, 36, 38, 40, 42};

void setup() {
  Serial.begin(9600);

  // -------------------- Pins --------------------
  // For testing
  pinMode(13, OUTPUT);

  // Motors
  pinMode(leftMotorDir, OUTPUT);
  pinMode(rightMotorDir, OUTPUT);

  // StartButton
  pinMode(startButton, INPUT);

  //Line Sensors
  pinMode(lineSFrontRight, INPUT);
  pinMode(lineSFrontLeft, INPUT);
  pinMode(lineSBackRight, INPUT);
  pinMode(lineSBackLeft, INPUT);

  // Infrared Sensors
  pinMode(iRLeft, INPUT); //IR Left
  pinMode(iRSCenter, INPUT); //IR Center
  pinMode(iRSRight, INPUT); //IR Right

  // CodeSwitch
  for (int i = 0; i < 6; i++) pinMode(codeSwitch[i], INPUT);

  // Interrupt Pins
  pinMode(echoPin, INPUT);
  pinMode(lineSInterruptPin, INPUT);
  pinMode(iRInterruptPin, INPUT);

  // -------------------- Interrupts --------------------
  //attachInterrupt(digitalPinToInterrupt(lineSInterruptPin), activateDontFall, FALLING);
  //attachInterrupt(digitalPinToInterrupt(iRInterruptPin), interruptSeekAndDestroyIR, FALLING); // Attach IR sensor Interrupt pin!
  // -------------------- Wait --------------------
  //Serial.println("ON!");
  while (digitalRead(startButton) == HIGH); //Wait for button
  delay(10000); //Wait 10 seconds before stating // TEST

  // -------------------- Set Up Timer! --------------------
  timer.setInterval(10, incrementMoveTimer);

  // -------------------- Set up US Sensors --------------------
  resetUS(); // Ultrasonic Sensors // TEST

  // -------------------- Set Up StartMove! --------------------
  startMove();
}

// -------------------- Main Stuff --------------------
void loop() {

  //ultrasonicSensors(); // deactivated :(
  situations();
  decisionQueue(); // Tells the motors what and how long to do something, depending on the selected move
  timer.run();

}
