/*
// -------------------- MOTORS --------------------//
doStraight(int speed, int time); //
doRotate(int speed, int time ); //
doTurn(int leftMotor, int rightMotor, int time);
doStop(int time); // Don't move for a while

// -------------------- US --------------------//
getUSLeft()
getUSFrontLeft()
getUSFrontCenter()
getUSFrontRight()
getuSRight()

// -------------------- IR --------------------//
 getIRRight()
 getIRLeft()
 getIRCenter()

// -------------------- IR OR US --------------------//
getUSIRCenter()
getUSIRRight()
getUSIRLeft()

// -------------------- LINE SENSORS --------------------//
getLineSFrontRight()
getLineSFrontLeft()
getLineSBackRight()
getLineSBackLeft()

// -------------------- CONTROL FUNCTIONS --------------------//
doNow() // Very very important. You have to call this function at the beginning of every move that you want to be excecuted inmediately

// -------------------- Start Moves --------------------
// StartMoves don't need a doNow() at the beginning because the are excecuted right away...
*/

//✓
void frontAttack() {
  doStraight(95, 100);
}

// Side attack

void sideAttackL() {
  doRotateL(50, 25); // ~45°
  doStraight(60, 70);
  doRotateR(55, 50);
  doStraight(50, 50);
}

void sideAttackR() {
  doRotateR(50, 25); // ~45°
  doStraight(60, 70);
  doRotateL(55, 50);
  doStraight(50, 50);
}

void sideAttackAndTurnL() {
  sideAttackL();
  doTurn(25,70,150); 
}

void sideAttackAndTurnR() {
  sideAttackR();
  doTurn(70,25,150); 
}

//✓
void backAwayL() {
  doRotateR(55, 25); // ~90°
  doTurn(-40, -70, 110);
}

void backAwayR() {
  doRotateL(55, 25); // ~90°
  doTurn(-70, -40, 110);
}

//✓
void backAwayAndAttackL() {
  backAwayL();
  doRotateL(50, 40);
  doStraight(70, 50);
}

void backAwayAndAttackR() {
  backAwayR();
  doRotateR(50, 40);
  doStraight(70, 50);
}

// -------------------- Defaults --------------------
// Defaults don't need a doNow cause


void randomSearch() {
  doNow();
  doStraight(75, 30);
  if (random(1, 100) > 50) doRotateR(60, 14);
  else doRotateL(60, 14);
}


// -------------------- Situations --------------------
void dontFall() {
  // Front Right
  if (getLineSFrontRight()) {
    doNow();
    doStraight(-90, 19);
    doRotateL(75, 21);
  }
  // Front Right
  else if (getLineSFrontLeft()) {
    doNow();
    doStraight(-90, 19);
    doRotateR(75, 21);
  }
  // Back Right OR Back Left
  else if (getLineSBackRight()) {
    doNow();
    doStraight(95, 30);
  }
  else if (getLineSBackLeft()) {
    doNow();
    doStraight(95, 30);
  }
}

void seekAndDestroyIR() {
  if (getIRCenter() || (getIRCenter() && ( (getIRRight() && getIRLeft()) || getIRRight() || getIRLeft() ) ) ) {
    doNow();
    doStraight(95, 2);
  }
  // Front Right
  else if (getIRRight()) {
    doNow();
    doRotateR(65, 1);
  }
  // Front Left
  else if (getIRLeft()) {
    doNow();
    doRotateL(65, 1);
  }
}
