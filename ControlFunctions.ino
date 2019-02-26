bool busy = false;

// Counter, timer and lists
const int maxMoves = 10;
unsigned int moveTimer = 0;

int moveCounter = 0;
int moveAmount = 0; // Amount of moves on the queue
char currentMove[maxMoves]; // TEST
int moveTime[maxMoves]; // TEST
int leftMotorSpeed[maxMoves];
int rightMotorSpeed[maxMoves];

//Motors
int leftMotorCurrentSpeed = 0;
int rightMotorCurrentSpeed = 0;
int leftMotorCurrentDir = 0;
int rightMotorCurrentDir = 0;

const int accelerationTime = 150; //(ms)
const int accelerationCalls = 50;
const int accConst = 50;

bool changeSpeedR = true;
bool changeSpeedL = true;

// Ultrasonic Sensors
bool usActive = true;
bool usReset = false;

// -------------------- Move Selection Functions --------------------

void incrementMoveTimer() {

  moveTimer++;
  //Serial.print("currentMove: ");
  //Serial.print(currentMove[moveCounter]);
  //Serial.print(". moveTimer: ");
  //Serial.println(moveTimer);

  //showMotorStatus();
  
 //showUSStatus();

}

void decisionQueue() {
  if (moveCounter < moveAmount) {
    changeSpeeds();
    //Next Move:
    if (moveTimer >= moveTime[moveCounter]) {
      moveCounter++;
      moveTimer = 0;
      changeSpeedR = true;
      changeSpeedL = true;
    }
  } else {
    //Move queue Finished.
    busy = false;
    doNow(); //  Sets all values to zero.
    asUsual(); // Do defaultMove
  }
}

void doNow() {
  changeSpeedR = true;
  changeSpeedL = true;
  moveTimer = 0;
  moveAmount = 0;
  moveCounter = 0;
}

void prioritizeMove() {
  busy = true;
}

// -------------------- Sensors --------------------

void uSSensors() {
  if (getIRLeft() || getIRCenter() || getIRRight()) {
    usActive = false;  // Deactivate US Sensors
    usReset = true;
  }
  else {
    if (usReset) {
      resetUS();
      usReset = false;
    }
    ultrasonicSensors(); // Polling US Sensors
  }
}

// -------------------- Main Movements (Queue) --------------------

// Forwards and Backwards Movement
void doStraight(int s, int t) {
  //currentMove[moveAmount] = 's'; // TEST

  s = s * maxSpeed / 100;
  leftMotorSpeed[moveAmount] = s;
  rightMotorSpeed[moveAmount] = s;
  moveTime[moveAmount] = t;
  moveAmount++;
}

void doStop(int t) {
  doStraight(0, t);
}

void doRotateL(int s, int t) {

  //currentMove[moveAmount] = 'R'; // TEST

  s = s * maxSpeed / 100;
  leftMotorSpeed[moveAmount] = -s;
  rightMotorSpeed[moveAmount] = s;

  moveTime[moveAmount] = t;
  moveAmount++;
}

// Rotate Motion
void doRotateR(int s, int t) {

  //currentMove[moveAmount] = 'R'; // TEST

  s = s * maxSpeed / 100;
  leftMotorSpeed[moveAmount] = s;
  rightMotorSpeed[moveAmount] = -s;
  moveTime[moveAmount] = t;
  moveAmount++;
}

// Moving Turn
void doTurn(int turnSpeedLeft, int turnSpeedRight, int t) {

  //currentMove[moveAmount] = 't'; // TEST

  turnSpeedLeft = turnSpeedLeft * maxSpeed / 100;
  turnSpeedRight = turnSpeedRight * maxSpeed / 100;
  leftMotorSpeed[moveAmount] = turnSpeedLeft;
  rightMotorSpeed[moveAmount] = turnSpeedRight;
  moveTime[moveAmount] = t;
  moveAmount++;
}

// -------------------- Motors --------------------

void changeSpeeds() {
  if (changeSpeedL) {
    if (leftMotorSpeed[moveCounter] == 0) changeSpeedStop();
    else {

      // Set left motor direction
      if (leftMotorCurrentSpeed > 0 ) setLeftMotorDirF();
      else setLeftMotorDirB();

      // Set left motor speed
      if (leftMotorCurrentSpeed < leftMotorSpeed[moveCounter]) {
        leftMotorCurrentSpeed += accConst;
        setLeftMotorSpeed(leftMotorCurrentSpeed);
      } else {
        leftMotorCurrentSpeed -= accConst;
        setLeftMotorSpeed(leftMotorCurrentSpeed);
      }
      if (abs(leftMotorCurrentSpeed) > abs(leftMotorSpeed[moveCounter]))changeSpeedL = false;
    }
  }

  if (changeSpeedR) {
    if (rightMotorSpeed[moveCounter] == 0) changeSpeedStop();
    else {
      // Set right motor direction
      if (rightMotorCurrentSpeed > 0 ) setRightMotorDirF();
      else setRightMotorDirB();

      // Set right motor speed
      if (rightMotorCurrentSpeed < rightMotorSpeed[moveCounter]) {
        rightMotorCurrentSpeed += accConst;
        setRightMotorSpeed(rightMotorCurrentSpeed);
      } else {
        rightMotorCurrentSpeed -= accConst;
        setRightMotorSpeed(rightMotorCurrentSpeed);
      }
      if (abs(rightMotorCurrentSpeed) > abs(rightMotorSpeed[moveCounter]))changeSpeedR = false;
    }
  }
}

void changeSpeedStop() {
  if (leftMotorCurrentSpeed != 0) {
    // Set left motor direction
    if (leftMotorCurrentSpeed > 0 ) setLeftMotorDirF();
    else setLeftMotorDirB();

    // Set left motor speed
    if (leftMotorCurrentSpeed < 0) {
      leftMotorCurrentSpeed += accConst;
      setLeftMotorSpeed(leftMotorCurrentSpeed);
    } else {
      leftMotorCurrentSpeed -= accConst;
      setLeftMotorSpeed(leftMotorCurrentSpeed);
    }
  }

  if (rightMotorCurrentSpeed != 0) {
    // Set right motor direction
    if (rightMotorCurrentSpeed > 0 ) setRightMotorDirF();
    else setRightMotorDirB();

    // Set right motor speed
    if (rightMotorCurrentSpeed < 0) {
      rightMotorCurrentSpeed += accConst;
      setRightMotorSpeed(rightMotorCurrentSpeed);
    } else {
      rightMotorCurrentSpeed -= accConst;
      setRightMotorSpeed(rightMotorCurrentSpeed);
    }
  }
}
